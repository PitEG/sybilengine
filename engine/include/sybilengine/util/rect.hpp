#pragma once 

#include "sybilengine/util/vector2.hpp"

namespace sbl {
  /**
   * @brief Generic Rectangle class. It is defined by it's bottom 
   * left point (as a Vector2) and it's size (an absolute Vector2)
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
    Rect(Vector2 displacement, Vector2 size)
    : m_displacement(displacement), m_size(size.Absolute()) {
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
    : m_displacement(Vector2(BRx, BRy)), m_size(Vector2(TRx, TRy)) {
    }

    /**
     * @brief Construct a default Rect object. Its bottom left corner is
     * (0,0) and it's size is (0,0)
     */
    Rect() : Rect(Vector2::Zero(), Vector2::Zero()) {
    }

    /**
     * @brief Move the rectangle a given amount. Essentially moves all the points.
     * 
     * @param displacement Vector2 displacement.
     */
    void Move(Vector2 displacement);

    void SetPosition(const Vector2& position);

    /* 
     * Getters
     */

    /**
     * @brief Returns the height and width of the rect.
     * 
     * @return Vector2 (x,y) where x is the width and y is the height.
     */
    Vector2 Size() const;

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
     * @return Vector2 
     */
    Vector2 TL() const;

    /**
     * @brief Top Right Corner
     * 
     * @return Vector2 
     */
    Vector2 TR() const;

    /**
     * @brief Bottom Left Corner
     * 
     * @return Vector2 
     */
    Vector2 BL() const;

    /**
     * @brief Bottom Right Corner
     * 
     * @return Vector2 
     */
    Vector2 BR() const;

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

    Vector2 Center() const;

  private:
    /*
     * Displacement is bottom left corner. 
     * Size + Displacmenet is top right corner
     */
    Vector2 m_displacement;
    Vector2 m_size;
  };
}
