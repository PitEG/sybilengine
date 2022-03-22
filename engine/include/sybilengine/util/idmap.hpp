#pragma once

#include <stack>
#include <vector>

namespace sbl {
  template<typename T>
  class IdMap {
  public:
    int Add(T thing) {
      // if there are open slots, use those
      if (m_openIds.size() > 0) {
        int id = m_openIds.top();
        m_openIds.pop();
        m_entries[id] = thing;
        m_open[id] = false;
        return id;
      }

      m_entries.push_back(thing);
      m_open.push_back(false);

      return m_entries.size()-1;
    }
    bool Get(int id, T& thing) const {
      if (!Exists(id)) {
        return false;
      }
      thing = m_entries[id];

      return true;
    }
    bool Set(int id, const T& thing) {
      if (!Exists(id)) {
        return false;
      }
      m_entries[id] = thing;
      return true;
    }
    int Size() const {
      return m_entries.size();
    }
    bool Remove(int id) {
      if (!Exists(id)) {
        return false;
      }
      m_open[id] = true;
      m_openIds.push(id);
      return true;
    }
    bool Exists(int id) const {
      // if impossible id, return false
      if (id < 0 || id > m_entries.size()-1 || m_entries.size() == 0) {
        return false;
      }
      // if open, return false;
      if (m_open[id]) {
        return false;
      }
      return true;
    }

    // not index safe
    inline T& operator[](const int index) {
      return m_entries[index];
    }

    const std::vector<T> GetList() {
      return m_entries;
    }

  private:
    std::vector<T>    m_entries;
    std::vector<T>    m_returnEntries;
    std::vector<bool> m_open;
    std::stack<int>   m_openIds;
  };
}