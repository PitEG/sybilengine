#pragma once

#include "sybilengine/util/vec.hpp"

#include <vector>
#include <string>

namespace sbl {
  /** 
   * @brief Container of a union that can be of int, float, or vector and a name.
   * Can be extended to house more types.
   */
  struct Property {
    /**
     * @brief Name of property.
     */
    std::string name;
    /**
     * @brief Value type.
     */
    enum Type {
      Int,
      Float,
      Vec2f
    };
    /**
     * @brief Type of Value.
     */
    Type type;

    /**
     * @brief Property can be one of a few types.
     */
    union {
      int*          pInt;
      float*        pFloat;
      sbl::Vec2f* pVec2f;
    };
  };

  /** 
   * @brief List container for properties
   */
  struct Properties {
  public:
    /**
     * @brief List of properties.
     */
    std::vector<Property> list;

    /**
     * @brief Add an Int property.
     * 
     * @param name Name of the property.
     * @param i The int pointer.
     */
    void AddInt(std::string name, int* i) {
      Property p;
      p.type = Property::Type::Int;
      p.pInt = i;
      list.push_back(p);
    }
    /**
     * @brief Add a Float property.
     * 
     * @param name Name of the property.
     * @param f The float pointer.
     */
    void AddFloat(std::string name, float* f) {
      Property p;
      p.type = Property::Type::Float;
      p.pFloat = f;
      list.push_back(p);
    }
    /**
     * @brief Add a Vec2f property.
     * 
     * @param name Name of the property.
     * @param v The Vec2f pointer.
     */
    void AddVec2f(std::string name, Vec2f* v) {
      Property p;
      p.type = Property::Type::Vec2f;
      p.pVec2f = v;
      list.push_back(p);
    }
    //add more pushes here
  };

  /**
   * @brief For the use of modifying values of components in a scene. 
   * Allows the inheriting object to expose its values.
   * CAREFUL: scenes can be copied and deleted pretty freely, so the
   * property pointers returned will likley be invalid if the scene
   * was deleted.
   */
  class Inspectable {
  public:
    /**
     * @brief Get the Properties of an object
     * 
     * @return Properties The Properties of the object.
     */
    virtual Properties GetProperties() = 0;

    /* EXAMPLE
     *
     * int hp;
     * int score;
     * float gravity;
     * float speed;
     *
     * Properties GetProperties() override {
     *   Properties p;
     *   p.AddInt("hp", &hp);
     *   p.AddInt("SCORE!", &score);
     *   p.AddFloat("gravity", &gravity);
     *   p.AddFloat("zoom value", &speed);
     *   return p;
     * }
     */
  };
}
