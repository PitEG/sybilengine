#pragma once 

#include <glm/glm.hpp>

namespace sbl {
  /**
   * @brief 2D Vector class
   */
  struct Vector2 {
  public:
    float x, y;

    /**
     * @brief Construct a Vector2 object with an x and y coord
     * 
     * @param x X coord
     * @param y Y coord
     */
    Vector2(const float x, const float y);

    /**
     * @brief Construct Default Vector2 object. It will be the zero vector, (0,0).
     */
    Vector2(); 

    /**
     * @brief Construct a new Vector 2 object using radians
     * 
     * @param radians radians 
     */
    Vector2(const float radians);

    /*
     * Instance Methods
     */

    /**
     * @brief Magnitude of vector. Pythagorean theorem.
     * 
     * @return Magntitude of the Vector.
     */
    float Magnitude() const;
    //returns the normalized versoin of the vector
    /**
     * @brief Normalizes the Vector. It will be a vector that points at the same
     * direction but has the magnitude of 1.
     * 
     * @return A normalized vector.
     */
    Vector2 Normalize() const;
    /**
     * @brief The same vector but only positive values
     * 
     * @return Vector2
     */
    Vector2 Absolute() const;
    /**
     * @brief Normal of the Vector?
     * 
     * @return Vector2 
     */
    Vector2 Normal() const;

    /*
     * Static Methods 
     */

    //reflects a vector by a normal
    static Vector2 Reflect(const Vector2 vector, const Vector2 normal);
    //dot product
    static float Dot(const Vector2 a, const Vector2 b);
    //distance magnitude of two vectors
    static float Distance(const Vector2 a, const Vector2 b);
    //angle in degrees between to vectors. 
    //angle is the shortest rotation from a to b, clamped to [0, PI]
    static float AngleDegree(const Vector2 a, const Vector2 b);
    //angle in radians between to vectors, 
    //angle is the shortest rotation from a to b. clamped to [0, PI]
    static float AngleRad(const Vector2 a, const Vector2 b);

    //library of standard vectors
    static Vector2 Up();
    static Vector2 Down();
    static Vector2 Left();
    static Vector2 Right();
    static Vector2 Zero();

    /*
     * Overrided Operators
     */
    //add/subtract vectors
    Vector2 operator+(const Vector2& b) const;
    Vector2 operator-(const Vector2& b) const;
    Vector2& operator+=(const Vector2& b);
    Vector2& operator-=(const Vector2& b);
    Vector2 operator-() const;
    //multiply/divide vector by scalar
    Vector2 operator*(const float& scalar) const;
    Vector2 operator/(const float& scalar) const; //pls don't divide by 0
    Vector2& operator*=(const float& scalar);
    Vector2& operator/=(const float& scalar); //pls don't divide by 0
    //component wise vector multiplication
    Vector2 operator*(const Vector2& b) const;
    Vector2 operator/(const Vector2& b) const;
    //equal operator. Checks if both this and the other vector are the exact same
    bool operator==(const Vector2& b) const;
    bool operator!=(const Vector2& b) const;

    //convert to glm::vec2
    glm::vec2 ConvertGLM() const;

  };
}
