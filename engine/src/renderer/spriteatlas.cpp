#include "sybilengine/renderer/spriteatlas.hpp"
#include "glad/glad.h"

#include <queue>

namespace sbl {
  struct SortAlgorithm {
    bool operator() (const Sprite& a, const Sprite& b) {
      //return a if tallest
      if (a.Height() > b.Height()) {
        return true;
      }
      //if equal, return biggest
      else if (a.Height() == b.Height()) {
        if (a.Height()*a.Width() >= b.Height()*b.Width()) {
          return true;
        }
        else {
          return false;
        }
      }
      // if a is shorter return b;
      else {
        return false;
      }
    }
  };

  //TODO TEST THIS
  std::vector<Texture*> SpriteAtlas::PackSprites(std::vector<Sprite>& sprites) {
    //initialize atlas
    int atlasSize = 4096;
    std::vector<Texture*> spriteAtlases;
    Texture* spriteAtlas = new Texture(atlasSize, atlasSize);
    
    //sort by height, then by area
    std::priority_queue<Sprite, std::vector<Sprite>, SortAlgorithm> 
      orderedSprites;
    for(int i = 0; i < sprites.size(); i++) {
      if (sprites[i].GetTexture() == nullptr) { continue; }
      orderedSprites.push(sprites[i]);
    }

    //packing algorithm
    Rect currRect = Rect(Vector2::Zero(), Vector2(atlasSize, atlasSize));
    for(int i = 0; i < orderedSprites.size(); i ++) {
      Sprite sprite = orderedSprites.top();
      orderedSprites.pop();
    }

    return spriteAtlases;
  }
}
