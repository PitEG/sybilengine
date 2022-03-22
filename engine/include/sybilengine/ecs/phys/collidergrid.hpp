#pragma once

#include "sybilengine/util/rect.hpp"
#include "sybilengine/util/freelist.hpp"
#include "sybilengine/ecs/phys/collider.hpp"
#include "sybilengine/ecs/phys/collision.hpp"

#include <vector>
#include <set>
#include <unordered_map>

/**
 * Two big optimizations left:
 * 1. Organize entry nodes into rows, improves cache misses.
 * 2. Do all the collision checks at once, so it'd be (n^2)/2 checks, instead
 * of n^2.
 */

namespace sbl {
  class ColliderGrid{
  private:
    struct EntryLocation { // list of cells the collider is in
      int next;
      int node;
      int cell;
    };

    struct Entry { // actual collider itself
      Collider collider;
      int location;
    };

    struct EntryNode { // objects that cells hold that refer to the colliders by id
      int prev;
      int next;
      int entry;
    };

    struct Cell {
      int first;
      int last; // this is possibly redundant
    };

    /*
    struct CollisionEntry {
      int entry;
      Collision collision;
      int next;
    };
    */

    int m_numEntries = 0;

    sbl::FreeList<Entry> m_entries; // actual colliders
    sbl::FreeList<EntryLocation> m_occupiedCells; // list of cells colliders are in
    std::vector<Cell> m_cells; // the cells 
    sbl::FreeList<EntryNode> m_entryNodes; // the colliders of these cells

    // used to prevent retesting
    std::vector<u_int8_t/*bool*/> m_bitset;
    std::vector<int> m_bitsetRecent;

    sbl::Rect m_bounds;
    int m_numRows;
    int m_numColumns;

    float m_cellWidth;
    float m_cellHeight;

    void RemoveEntryNode(const int id);
    void InsertEntry(const int id, const Collider& collider);

  public:
    ColliderGrid(const sbl::Rect bounds, const unsigned int num_rows, const unsigned int num_columns);

    inline sbl::Rect Bounds() const { return m_bounds; };
    inline int NumRows() const { return m_numRows; };
    inline int NumColumns() const { return m_numColumns; };
    inline float CellWidth() const { return m_cellWidth; };
    inline float CellHeight() const { return m_cellHeight; };

    int Add(const Collider& collider);
    bool Delete(const int id);
    bool Modify(const int id, const Collider& collider);
    bool Exists(const int id);
    void GetCollisions(const int id, std::vector<Collision>& collisions);
    void GetCollisions(const Collider& collider, std::vector<Collision>& collisions);

    void CacheCollisions();
    void ClearCollisionsCache();
    void GetCollisionChache(const int id, std::vector<Collision>& collisions) const;

    void GetCellInfo(std::vector<std::vector<int>>& cellInfo) const;
  };
}
