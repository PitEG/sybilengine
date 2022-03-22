#include "sybilengine/ecs/phys/collidergrid.hpp"

#include <cmath>
#include <algorithm>

namespace sbl {
  const int END_LIST = -1;

  ColliderGrid::ColliderGrid(const sbl::Rect bounds, const unsigned int numRows, const unsigned int numColumns) 
  : m_bounds(bounds), m_numRows(numRows), m_numColumns(numColumns) { 
    m_cellWidth = bounds.Size().x / numRows;
    m_cellHeight = bounds.Size().y / numColumns;

    m_cells = std::vector<Cell>(numRows * numColumns, Cell{END_LIST,END_LIST});
  }

  // HELPERS
  static int floor(const float f) { // does not need to work well with - values
    int i = (int)f;
    if (i < 0) { i = 0; }
    return i;
  }
  static void findCandidateCells(const ColliderGrid& grid, const Collider& collider, 
  int& leftmost, int& rightmost, int& bottommost, int& topmost) {

    const Rect& bounds = grid.Bounds();
    Vector2 bottomLeft = bounds.BL();
    float leftBorder = bottomLeft.x;
    float bottomBorder = bottomLeft.y;

    Rect cull = collider.GetCull();
    Vector2 cullBottomLeft = cull.BL();
    Vector2 cullTopRight = cull.TR();

    float width = grid.CellWidth();
    float height = grid.CellHeight();

    leftmost =    floor((cullBottomLeft.x - leftBorder) / width);
    rightmost =   floor((cullTopRight.x - leftBorder) / width);
    bottommost =  floor((cullBottomLeft.y - bottomBorder) / height);
    topmost =     floor((cullTopRight.y - bottomBorder) / height);

    // leftmost = std::min(leftmost, 0);
    leftmost = std::min(leftmost, grid.NumColumns() - 1);
    rightmost = std::min(rightmost, grid.NumColumns() - 1);
    // bottommost = std::max(bottommost, 0);
    bottommost = std::min(bottommost, grid.NumRows() - 1);
    topmost = std::min(topmost, grid.NumRows() - 1);
  }
  // END HELPERS

  void ColliderGrid::InsertEntry(const int id, const Collider& collider) {
    // find the cells that this collider would fit into
    int leftmost;
    int rightmost;
    int bottommost;
    int topmost;
    findCandidateCells(*this, collider, leftmost, rightmost, bottommost, topmost);

    // insert into rows
    int lastCellIdx = END_LIST;
    for (int i = bottommost; i <= topmost; i++) {
      // insert into cells
      int rowIndex = i * m_numRows;
      for (int j = leftmost; j <= rightmost; j++) {
        int cellIdx = rowIndex + j;

        // add to entry's EntryLocations (list of cells)
        int nodeIdx = m_occupiedCells.Add(EntryLocation{END_LIST, 0, 0});
        if (lastCellIdx == END_LIST) {
          m_entries[id].location = nodeIdx;
        } else {
          m_occupiedCells[lastCellIdx].next = nodeIdx;
        }
        lastCellIdx = nodeIdx;

        // add to cell
        Cell& cell = m_cells[cellIdx];
        int entryNode = m_entryNodes.Add(EntryNode{cell.last, END_LIST, id});
        m_occupiedCells[nodeIdx].node = entryNode;
        m_occupiedCells[nodeIdx].cell = cellIdx;
        if (cell.last != END_LIST) {
          m_entryNodes[cell.last].next = entryNode;
        }
        cell.last = entryNode;
        if (cell.first == END_LIST) {
          cell.first = entryNode;
        }
      }
    }
  }
  int ColliderGrid::Add(const Collider& collider) {
    // create entry
    Entry entry;
    entry.collider = collider;
    int id = m_entries.Add(entry);

    InsertEntry(id, collider);

    m_numEntries++;
    m_bitset.resize(m_entries.Capacity(), false);
    m_bitsetRecent.reserve(m_entries.Capacity());
    return id;
  }
  void ColliderGrid::RemoveEntryNode(const int id) {
    int locationIdx = m_entries[id].location;
    EntryLocation location; // = m_occupiedCells[locationIdx];
    while (locationIdx != END_LIST) {
      location = m_occupiedCells[locationIdx];
      int entryNode = location.node;
      EntryNode node = m_entryNodes[entryNode];
      if (node.prev == END_LIST) { m_cells[location.cell].first = node.next; }
      else { m_entryNodes[node.prev].next = node.next; }
      if (node.next == END_LIST) { m_cells[location.cell].last = node.prev; }
      else { m_entryNodes[node.next].prev = node.prev; }

      m_entryNodes.Delete(entryNode);
      m_occupiedCells.Delete(locationIdx);
      locationIdx = location.next;
    }
  }
  bool ColliderGrid::Delete(const int id) {
    if (!m_entries.Contains(id)) {
      return false;
    }

    RemoveEntryNode(id);

    // remove entry
    m_entries.Delete(id);

    m_numEntries--;
    return true;
  }
  bool ColliderGrid::Modify(const int id, const Collider& collider) {
    if (!m_entries.Contains(id)) {
      return false;
    }
    m_entries[id].collider = collider;
    RemoveEntryNode(id);
    InsertEntry(id, collider);

    return true;
  }
  bool ColliderGrid::Exists(const int id) {
    return m_entries.Contains(id);
  }
  void ColliderGrid::GetCollisions(const int id, std::vector<Collision>& collisions) {
    if (!m_entries.Contains(id)) {
      return;
    }

    // bitset
    std::vector<u_int8_t/*bool*/>& bitset = m_bitset;
    bitset[id] = true;
    m_bitsetRecent.push_back(id);
    collisions.clear();

    const Collider& collider = m_entries[id].collider;

    int location = m_entries[id].location;
    while (location != END_LIST) {
      int cellIdx = m_occupiedCells[location].cell;
      Cell& cell = m_cells[cellIdx];
      int entryNode = cell.first;
      while (entryNode != END_LIST) {
        EntryNode& node = m_entryNodes[entryNode];
        int entry = node.entry;
        if (bitset[entry]) {
          entryNode = node.next;
          continue;
        }
        bitset[entry] = true;
        m_bitsetRecent.push_back(entry);
        const Collider& otherCollider = m_entries[entry].collider;
        bool collision = Collider::CalculateCollisionAlg(collider, otherCollider);
        if (collision) {
          collisions.push_back(Collision(otherCollider));
        }
        entryNode = node.next;
      }
      location = m_occupiedCells[location].next;
    }

    // clear bitset
    for (int i = 0; i < m_bitsetRecent.size(); i++) {
      m_bitset[m_bitsetRecent[i]] = false;
    }
    m_bitsetRecent.clear();
  }

  void ColliderGrid::CacheCollisions() {
    // go through each cell
    for (int i = 0; i < m_cells.size(); i++) {
      // go through each entry in the cell
    }
  }
  void ColliderGrid::ClearCollisionsCache() {
  }
  void ColliderGrid::GetCollisionChache(const int id, std::vector<Collision>& collisions) const {
  }

  void ColliderGrid::GetCellInfo(std::vector<std::vector<int>>& cellInfo) const {
    cellInfo.clear();
    cellInfo.resize(m_cells.size());
    for (int i = 0; i < m_cells.size(); i++) {
      int entryNode = m_cells[i].first;
      while (entryNode != END_LIST) {
        cellInfo[i].push_back(m_entryNodes[entryNode].entry);
        entryNode = m_entryNodes[entryNode].next;
      }
    }
  }
}