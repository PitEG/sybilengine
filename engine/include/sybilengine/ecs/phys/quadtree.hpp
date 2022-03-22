#pragma once 

#include "sybilengine/util/rect.hpp"

#include <vector>

namespace sbl {
  template<typename T>
  class Quadtree {
  public:
    Quadtree(const int level, const int maxLevel, const int maxObjects, const Rect bounds)
    : m_level(level), m_maxLevel(maxLevel), m_maxObjects(maxObjects), m_bounds(bounds) {
      // preallocate some space
      // m_objects = std::vector<std::pair<T,Rect>>(maxObjects * 2);
      m_objects.reserve(maxObjects * 2);
    }

    ~Quadtree() {
      Clear();
    }

    /**
     * @brief Clear the quadtree (and child quad tree)
     * 
     */
    void Clear() {
      m_objects.clear();
      for (int i = 0; i < 4; i++) {
        if (m_nodes[i] == nullptr) { continue; }
        m_nodes[i]->Clear();
        delete m_nodes[i];
        m_nodes[i] = nullptr;
      }
    }

    /**
     * @brief Insert a new Collider into the quadtree
     * 
     * @param collider The Collider to insert.
     */
    void Insert(const T object, const Rect& bounds) {
      if (m_nodes[0] != nullptr) {
        int quad = GetQuad(bounds);

        if (quad != -1) {
          m_nodes[quad]->Insert(object,bounds);
          return;
        }
      }

      m_objects.push_back(std::pair<T,Rect>(object,bounds));

      // if we reach max objects, and we haven't reach max levels, we 
      // move all the current objects into new sub quads
      if (m_objects.size() > m_maxObjects && m_level < m_maxLevel) {
        if (m_nodes[0] == nullptr) {
          Split();
        }

        int i = 0;
        while (i < m_objects.size()) {
          int quad = GetQuad(m_objects[i].second);
          // if we can fit into a sub quad, remove from this list
          if (quad != -1) {
            // we are trying to remove an element from the list.
            // since deleting an element in the middle of the vector
            // on average is a O(N/2) process we swap it for the last 
            // element, then shrink the vector by 1.
            std::pair<T,Rect> temp = m_objects[i];
            m_objects[i] = m_objects[m_objects.size() - 1];
            m_objects[m_objects.size() - 1] = temp;
            m_objects.resize(m_objects.size() - 1);

            m_nodes[quad]->Insert(temp.first, temp.second);
          }
          else {
            i++;
          }
        } 
      }

    }

    /**
     * @brief Gets the list of objects within the given rect.
     *
     * @param std::vector<T>& User should pass an empty vector for the function to 
     * populate with objects.
     * @param rect The Rect we are interested in
     * @return std::vector<T> The list of T objects that we can collide with.
     */
    std::vector<T> RetrieveObjects(std::vector<T>& collidedObjects, const Rect& rect) {
      int quad = GetQuad(rect);
      // if rect fits into a quad, take only from that quad
      if (quad != -1 && m_nodes[0] != nullptr) {
        m_nodes[quad]->RetrieveObjects(collidedObjects, rect);
      }
      // if rect doesn't fit in a quad, take from all
      else if (m_nodes[0] != nullptr){
        m_nodes[0]->RetrieveObjects(collidedObjects, rect);
        m_nodes[1]->RetrieveObjects(collidedObjects, rect);
        m_nodes[2]->RetrieveObjects(collidedObjects, rect);
        m_nodes[3]->RetrieveObjects(collidedObjects, rect);
      }
      // add stuff from the parent quad
      for (int i = 0; i < m_objects.size(); i++) {
        collidedObjects.push_back(m_objects[i].first);
      }

      return collidedObjects;
    }

  private:
    /**
     * @brief Split the quadtree into 4 different nodes. It won't
     * resplit it if has already done so.
     * 
     */
    void Split() {
      if (m_nodes[0] != nullptr) { return; }
      Vector2 subBounds = m_bounds.Size() / 2;
      Vector2 boundsCenter = m_bounds.Center();

      Rect trQuad(boundsCenter, subBounds);
      m_nodes[0] = new Quadtree(m_level+1, m_maxLevel,  m_maxObjects,trQuad);
      Rect tlQuad(boundsCenter - Vector2(subBounds.x, 0), subBounds);
      m_nodes[1] = new Quadtree(m_level+1, m_maxLevel,  m_maxObjects,tlQuad);
      Rect blQuad(boundsCenter - subBounds, subBounds);
      m_nodes[2] = new Quadtree(m_level+1, m_maxLevel,  m_maxObjects,blQuad);
      Rect brQuad(boundsCenter - Vector2(0,subBounds.y), subBounds);
      m_nodes[3] = new Quadtree(m_level+1, m_maxLevel,  m_maxObjects,brQuad);
    }

    /**
     * @brief Get the quadrant that this Rect fits into. The quadrants range 
     * from 0 to 3 and are ordered in the same way they are in a math graph. 
     * If it doesn't fit, return -1. 
     * 
     */
    int GetQuad(const Rect& rect) {
      int index = -1;
      Vector2 boundsCenter = m_bounds.Center();
      Vector2 subBounds = m_bounds.Size();

      bool topQuads = rect.BL().y > boundsCenter.y; // && rect.TR().y < boundsCenter.y + subBounds.y;
      bool bottomQuads = rect.TR().y < boundsCenter.y; // && rect.BL().y > boundsCenter.y - subBounds.y;
      bool rightQuads = rect.BL().x > boundsCenter.x; // && rect.TR().x < boundsCenter.x + subBounds.x;
      bool leftQuads = rect.TR().x < boundsCenter.x; // && rect.BL().x > boundsCenter.x - subBounds.x;

      // if the rect doesn't cleanly fit into one quad, return -1;
      if ((int)topQuads + (int)bottomQuads + (int)leftQuads + (int)rightQuads != 2) {
        return index;
      }

      if (topQuads && rightQuads) {
        index = 0;
      }
      else if (topQuads && leftQuads) {
        index = 1;
      }
      else if (bottomQuads && leftQuads) {
        index = 2;
      }
      else if (bottomQuads && rightQuads) {
        index = 3;
      }
      return index;
    }

  private:
    int m_maxLevel;
    int m_maxObjects;
    int m_level;
    Rect m_bounds;

    std::vector<std::pair<T,Rect>> m_objects;
    Quadtree* m_nodes[4] = {nullptr};
  };
}