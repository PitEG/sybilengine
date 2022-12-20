#pragma once

#include <vector>

namespace sbl {

  // HEADER
  template<class T>
  class FreeList {
  private:
    std::vector<T> m_data;
    std::vector<int> m_nextFree;
    int m_freeSlot = -1;

  public:

    /**
     * @brief Construct a new FreeList object.
     * 
     */
    FreeList();

    FreeList(const unsigned int reserveSize);

    /**
     * @brief Add an element to the list.
     * 
     * @param thing The thing to add.
     * @return int The index location of the added thing.
     */
    int Add(const T& thing);

    /**
     * @brief Delete the element at a specific index.
     * 
     * @param id The index location of the element to delete.
     */
    void Delete(const int id);

    /**
     * @brief Check if an id is taken and exists
     * 
     * @param id The id to check.
     */
    bool Contains(const int id) const;

    /**
     * @brief Clears the whole list.
     */
    void Clear();

    /**
     * @brief Returns the current capacity of the list.
     * 
     * @return int The capacity of the list.
     */
    int Capacity() const;

    /**
     * @brief Returns the next available index.
     * 
     * @return int The next available index. -1, if it's full.
     */
    int NextFree() const;

    T& operator [](const int idx);
    const T& operator [](const int idx) const;

    const std::vector<T>& GetData() const;

  };

  static const int TAKEN = -2; // if taken, set to -2
  static const int END_FREE_LIST = -1; // if at the end of free list, it should point to -1

  // IMPLEMENTATION

  template<class T>
  FreeList<T>::FreeList() : m_freeSlot(-1) {}

  template<class T>
  int FreeList<T>::Add(const T& thing) {
    // there is a free slot to use
    int id;
    if (m_freeSlot != END_FREE_LIST) {
      id = m_freeSlot;
      m_freeSlot = m_nextFree[id];
      m_data[id] = thing;
      m_nextFree[id] = TAKEN;
      return id;
    }
    id = m_data.size();
    m_data.push_back(thing);
    m_nextFree.push_back(TAKEN);
    return id;
  }

  template<class T>
  void FreeList<T>::Delete(const int id) {
    if (m_nextFree[id] == TAKEN) {
      m_nextFree[id] = m_freeSlot;
      m_freeSlot = id;
    }
  }

  template<class T>
  bool FreeList<T>::Contains(const int id) const {
    // for impossible id's return false
    if (id < 0 || id >= Capacity()) {
      return false;
    }
    if (m_nextFree[id] != TAKEN) {
      return false;
    }

    return true;
  }

  template<class T>
  void FreeList<T>::Clear() {
    m_data.clear();
    m_nextFree.clear();
    m_freeSlot = -1;
  }

  template<class T>
  int FreeList<T>::NextFree() const {
    return m_freeSlot;
  }

  template<class T>
  int FreeList<T>::Capacity() const {
    return m_data.size();
  }

  template<class T>
  T& FreeList<T>::operator[](int id) {
    return m_data[id];
  }

  template<class T>
  const T& FreeList<T>::operator[](int id) const {
    return m_data[id];
  }

  template<class T>
  const std::vector<T>& FreeList<T>::GetData() const {
    return m_data;
  }
}
