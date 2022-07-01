#pragma once 

#include "sybilengine/util/vec.hpp"

namespace sbl {
  /**
   * @brief Generic Rectangle class. It is defined by it's bottom 
   * left point (as a Vec2f) and it's size (an absolute Vec2f)
   */
  struct Rect {
  public:
    /*
     * Constructor
     */

    /**
     * @brief Construct a new Rect object.
     * 
     * @param displacement The bottom left corner of the rectangle.
     * @param size The size of rectangle.
     */
    Rect(Vec2f displacement, Vec2f size)
    : m_displacement(displacement), m_size(size.Abs()) {
    }

    Rect(const Rect& other)
    : m_displacement(other.m_displacement), m_size(other.m_size) {
    }

    /**
     * @brief Construct a new Rect object using floats instead of vectors.
     * Requires the same format for the most part.
     * 
     * @param BRx BR x coordinate
     * @param BRy BL y coordinate
     * @param TRx TR x coordinate
     * @param TRy TR y coordinate
     */
    Rect(const float BRx, const float BRy, const float TRx, const float TRy) 
    : m_displacement(Vec2f(BRx, BRy)), m_size(Vec2f(TRx, TRy)) {
    }

    /**
     * @brief Construct a default Rect object. Its bottom left corner is
     * (0,0) and it's size is (0,0)
     */
    Rect() : Rect(Vec2f::Zero(), Vec2f::Zero()) {
    }

    /**
     * @brief Move the rectangle a given amount. Essentially moves all the points.
     * 
     * @param displacement Vec2f displacement.
     */
    void Move(Vec2f displacement);

    void SetPosition(const Vec2f& position);

    /* 
     * Getters
     */

    /**
     * @brief Returns the height and width of the rect.
     * 
     * @return Vec2f (x,y) where x is the width and y is the height.
     */
    Vec2f Size() const;

    /**
     * @brief Area of the rect. Width * Height.
     * 
     * @return float the area.
     */
    float Area() const;

    /**
     * @brief Height of the rect
     * 
     * @return float 
     */
    inline float Height() const { return m_size.y; }

    /**
     * @brief Width of the rect
     * 
     * @return float 
     */
    inline float Width()  const { return m_size.x; }

    //points
    /**
     * @brief Top Left Corner
     * 
     * @return Vec2f 
     */
    Vec2f TL() const;

    /**
     * @brief Top Right Corner
     * 
     * @return Vec2f 
     */
    Vec2f TR() const;

    /**
     * @brief Bottom Left Corner
     * 
     * @return Vec2f 
     */
    Vec2f BL() const;

    /**
     * @brief Bottom Right Corner
     * 
     * @return Vec2f 
     */
    Vec2f BR() const;

    /*
     * Setters
     */

    /**
     * @brief Scales the size of the rect. Keeps the proportion of the rect's
     * with and height.
     * 
     * @param factor multiplies both the width and height by this amount.
     */
    void Scale(const float factor);

    /*
     * Static Methods
     */

    /**
     * @brief Check if two rectangles overlap
     * 
     * @param a Rect a
     * @param b Rect b
     * @return true If a and b's areas overlap or touch
     * @return false If a and b's areas do not overlap or touch.
     */
    bool IsOverlapping(const Rect& a, const Rect& b) const;

    Vec2f Center() const;

  private:
    /*
     * Displacement is bottom left corner. 
     * Size + Displacmenet is top right corner
     */
    Vec2f m_displacement;
    Vec2f m_size;
  };
}
