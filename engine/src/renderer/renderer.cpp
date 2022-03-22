#include "sybilengine/renderer/renderer.hpp"
#include "sybilengine/util/math.hpp"

#include "sybilengine/renderer/opengl/vertexarray.hpp"
#include "sybilengine/renderer/opengl/vertexbuffer.hpp"
#include "sybilengine/renderer/opengl/elementbuffer.hpp"
#include "sybilengine/renderer/opengl/bufferlayout.hpp"
#include "sybilengine/renderer/opengl/shader.hpp"
#include "sybilengine/renderer/opengl/framebuffer.hpp"

#include "sybilengine/debug/logger.hpp"
#include "sybilengine/util/time.hpp"
#include <string>

namespace sbl {
  //helper functions
  void ClearDefaultTexture(Texture* texture, gl::FrameBuffer* fb, Color color) {
    fb->Bind();
    fb->BindTexture(*texture);
    fb->Clear(color.r, color.g, color.b, color.a);
  }

  struct RenderObjects {
    RenderObjects(
      gl::VertexBuffer*  vb     = nullptr,
      gl::VertexArray*   va     = nullptr,
      gl::ElementBuffer* eb     = nullptr,
      gl::Shader*        shader = nullptr
    ) 
    : vb(vb), va(va), eb(eb), shader(shader) {}

    ~RenderObjects() {
      /*
      if (vb != nullptr)      delete vb;
      if (va != nullptr)      delete va;
      if (eb != nullptr)      delete eb;
      if (shader != nullptr)  delete shader;
      */
    }
    gl::VertexBuffer*  vb     = nullptr;
    gl::VertexArray*   va     = nullptr;
    gl::ElementBuffer* eb     = nullptr;
    gl::Shader*        shader = nullptr;
  };

  RenderObjects CreateSpriteInstance() {
    //INITIALIZE OPENGL CONSTRUCTS
    const float spriteVertices[] = {
      //vertex     //texture coords
      -0.5f, -0.5f, 0, 0, //bl
      -0.5f,  0.5f, 0, 1, //tl
       0.5f, -0.5f, 1, 0, //br
       0.5f,  0.5f, 1, 1  //tr
    };
    const unsigned int quadElements[] = {
      0, 1, 3,
      0, 2, 3
    };

    //bufferlayout
    sbl::gl::BufferLayout bl;
    bl.PushFloat(2, false); //position
    bl.PushFloat(2, false); //texturecoords

    RenderObjects spriteInstance;

    //INSTANCE SPRITES
    spriteInstance.vb = new gl::VertexBuffer (&spriteVertices, sizeof(spriteVertices));
    spriteInstance.va = new gl::VertexArray;
    spriteInstance.va->AddBuffer(*spriteInstance.vb, bl);
    spriteInstance.eb = new gl::ElementBuffer(quadElements, 6);
    spriteInstance.shader = new gl::Shader(
#include "glsl/sprite_instance.vs.glsl"
        ,
#include "glsl/sprite_instance.fs.glsl"
    );

    return spriteInstance;
  }

  RenderObjects CreateLineInstance() {
    float lineVertices[4] = {
      0,0,
      1,1
    };
    //bufferlayout
    sbl::gl::BufferLayout bl;
    bl.PushFloat(2, false); //position

    RenderObjects lineInstance;

    //INSTANCE SPRITES
    lineInstance.vb = new gl::VertexBuffer(&lineVertices, sizeof(lineVertices));
    lineInstance.va = new gl::VertexArray();
    lineInstance.va->AddBuffer(*lineInstance.vb, bl);
    lineInstance.shader = new gl::Shader(
#include "glsl/line.vs.glsl"
        ,
#include "glsl/line.fs.glsl"
    );

    return lineInstance;
  }

  RenderObjects CreateSprite() {
    //INITIALIZE OPENGL CONSTRUCTS
    const float spriteVertices[] = {
      //vertex     //texture coords
      -0.5f, -0.5f, 0, 0, //bl
      -0.5f,  0.5f, 0, 1, //tl
       0.5f, -0.5f, 1, 0, //br
       0.5f,  0.5f, 1, 1  //tr
    };
    const unsigned int quadElements[] = {
      0, 1, 3,
      0, 2, 3
    };

    //bufferlayout
    sbl::gl::BufferLayout bl;
    bl.PushFloat(2, false); //position
    bl.PushFloat(2, false); //texturecoords

    RenderObjects sprite;

    // SPRITE
    sprite.vb = new gl::VertexBuffer (&spriteVertices, sizeof(spriteVertices));
    sprite.va = new gl::VertexArray;
    sprite.va->AddBuffer(*sprite.vb, bl);
    sprite.eb= new gl::ElementBuffer(quadElements, 6);
    sprite.shader = new gl::Shader(
#include "glsl/sprite.vs.glsl"
        ,
#include "glsl/sprite.fs.glsl"
    );

    return sprite;
  }

  //Constructor
  Renderer::Renderer() {
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();

    //default texture
    defaultTexture = new Texture(1,1);
    ClearDefaultTexture(defaultTexture, framebuffer, Color(1,1,1,1));
  }

  //Destructor
  Renderer::~Renderer() {
    delete defaultTexture;
  }

  void Renderer::Clear(Texture& texture, const Color color) {
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();

    framebuffer->BindTexture(texture);
    framebuffer->Clear(color.r, color.g, color.b, color.a);
  }

  //SPRITE
  void Renderer::Draw(
    std::vector<Sprite>&  sprites, 
    View&                 view, 
    Sprite&               canvas, 
    Texture*              texture, 
    const BlendMode&      blendMode) {

    static RenderObjects spriteInstance = CreateSpriteInstance();
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();

    framebuffer->Bind();
    if (canvas.GetTexture() == nullptr) { return; }
    framebuffer->BindTexture(*canvas.GetTexture());
    gl::Viewport canvasViewport(0, 0, canvas.Width(), canvas.Height());
    canvasViewport.Bind();
    // view.GetViewport().Bind();

    //before you finish this, test to see if the shader works
    int numSprites = sprites.size();
    std::vector<float> origins   (numSprites * 2);
    std::vector<float> positions (numSprites * 2);
    std::vector<float> rots      (numSprites);
    std::vector<float> scales    (numSprites * 2);
    std::vector<float> colors    (numSprites * 4);
    std::vector<float> texDisp   (numSprites * 2);
    std::vector<float> texSize   (numSprites * 2);
    //THIS FOR LOOP IS EXPENSIVE AS HELL. 25k sprites takes almost 2ms
    for (int i = 0; i < sprites.size(); i++) {
      Sprite& currSprite = sprites[i];
      origins[i * 2]     = currSprite.origin.x;
      origins[i * 2 + 1] = currSprite.origin.y;

      positions[i * 2] = currSprite.transform.position.x;
      positions[i * 2 + 1] = currSprite.transform.position.y;

      rots[i] = -currSprite.transform.rotation;

      scales[i * 2] = currSprite.Size().x;
      scales[i * 2 + 1] = currSprite.Size().y;

      colors[i * 4] = currSprite.color.r;
      colors[i * 4 + 1] = currSprite.color.g;
      colors[i * 4 + 2] = currSprite.color.b;
      colors[i * 4 + 3] = currSprite.color.a;
      
      // dont push texture info if there is no texture
      if(currSprite.GetTexture() == nullptr) continue; 
      const Texture& currTexture = *(currSprite.GetTexture());
      texDisp[i * 2]     = 
        currSprite.textureCoords.BL().x / currTexture.Width();
      texDisp[i * 2 + 1] = 
        currSprite.textureCoords.BL().y / currTexture.Height();

      texSize[i * 2]     = 
        currSprite.textureCoords.Size().x / currTexture.Width();
      texSize[i * 2 + 1] = 
        currSprite.textureCoords.Size().y / currTexture.Height();
    }

    gl::VertexBuffer originBuffer (origins.data(),    origins.size() * sizeof(float));
    gl::VertexBuffer posBuffer    (positions.data(),  positions.size() * sizeof(float));
    gl::VertexBuffer rotBuffer    (rots.data(),       rots.size() * sizeof(float));//rotation buffer
    gl::VertexBuffer scaleBuffer  (scales.data(),     scales.size() * sizeof(float));
    gl::VertexBuffer colorBuffer  (colors.data(),     colors.size() * sizeof(float));
    gl::VertexBuffer texDispBuffer(texDisp.data(),    texDisp.size() * sizeof(float));
    gl::VertexBuffer texSizeBuffer(texSize.data(),    texSize.size() * sizeof(float));
    // hardwiring enabled
    std::vector<int/*bool*/> enabled(sprites.size(), true); 
    gl::VertexBuffer enabledBuffer(enabled.data(),    enabled.size() * sizeof(int));

    gl::BufferLayout vec2BL;
    vec2BL.PushFloat(2, false);
    gl::BufferLayout vec4BL;
    vec4BL.PushFloat(4, false);
    gl::BufferLayout floatBL;
    floatBL.PushFloat(1, false);
    gl::BufferLayout intBL;
    intBL.PushUnsignedInt(1, false);

    // cast object to something usuable
    //RenderObjects& spriteInstance = *(RenderObjects*)(this->spriteInstance);

    spriteInstance.va->AddBuffer(originBuffer,  vec2BL,  2);
    spriteInstance.va->AddBuffer(posBuffer,     vec2BL,  3);
    spriteInstance.va->AddBuffer(rotBuffer,     floatBL, 4);
    spriteInstance.va->AddBuffer(scaleBuffer,   vec2BL,  5);
    spriteInstance.va->AddBuffer(colorBuffer,   vec4BL,  6);
    spriteInstance.va->AddBuffer(texDispBuffer, vec2BL,  7);
    spriteInstance.va->AddBuffer(texSizeBuffer, vec2BL,  8);
    spriteInstance.va->AddBuffer(enabledBuffer, intBL,   9);

    spriteInstance.va->SetBufferDivisor(2,1);
    spriteInstance.va->SetBufferDivisor(3,1);
    spriteInstance.va->SetBufferDivisor(4,1);
    spriteInstance.va->SetBufferDivisor(5,1);
    spriteInstance.va->SetBufferDivisor(6,1);
    spriteInstance.va->SetBufferDivisor(7,1);
    spriteInstance.va->SetBufferDivisor(8,1);
    spriteInstance.va->SetBufferDivisor(9,1);

    spriteInstance.shader->Bind();
    spriteInstance.shader->SetMat("projection", view.GetProjection());

    spriteInstance.va->Bind();
    defaultTexture->Bind();
    if (texture != nullptr) texture->Bind();
    blendMode.Bind(); // blendmode should be an argument
    glDrawElementsInstanced(
      GL_TRIANGLES, 
      spriteInstance.eb->IndexCount(), 
      GL_UNSIGNED_INT, 
      0, 
      sprites.size()
    ); 
  }

  /*
  void Renderer::Draw(std::vector<RectangleShape>& rects, View& view, Sprite& canvas, const BlendMode& blendMode) {
    // convert rects to sprites without textures
    std::vector<Sprite> sprites(rects.size());
    for (int i = 0; i < rects.size(); i++ ) {
      Sprite& sprite = sprites[i];
      RectangleShape& rect = rects[i];

      sprite.color = rect.color; 
      sprite.transform = rect.GetTransform();
      sprite.origin = rect.origin;
    }

    Draw(sprites, view, canvas, defaultTexture, blendMode);
  }
  */

  //SPRITE
  void Renderer::Draw(
    std::vector<LineShape>&   lines, 
    View&                     view, 
    Sprite&                   canvas, 
    const BlendMode&          blendMode) {

    static RenderObjects lineInstance = CreateLineInstance();
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();

    framebuffer->Bind();
    if (canvas.GetTexture() == nullptr) { return; }
    framebuffer->BindTexture(*canvas.GetTexture());
    gl::Viewport canvasViewport(0, 0, canvas.Width(), canvas.Height());
    canvasViewport.Bind();
    // view.GetViewport().Bind();

    int numLines = lines.size();
    std::vector<float> positions (numLines * 4); // 2 vector2's
    std::vector<float> colors    (numLines * 4); // rgba

    for (int i = 0; i < lines.size(); i++) {
      LineShape& currLine = lines[i];
      positions[i * 4]     = currLine.line.a.x;
      positions[i * 4 + 1] = currLine.line.a.y;
      positions[i * 4 + 2] = currLine.line.b.x;
      positions[i * 4 + 3] = currLine.line.b.y;

      colors[i * 4]     = currLine.color.r;
      colors[i * 4 + 1] = currLine.color.g;
      colors[i * 4 + 2] = currLine.color.b;
      colors[i * 4 + 3] = currLine.color.a;
    }

    gl::VertexBuffer posBuffer    (positions.data(),  positions.size() * sizeof(float));
    gl::VertexBuffer colorBuffer  (colors.data(),     colors.size() * sizeof(float));

    gl::BufferLayout vec4BL;
    vec4BL.PushFloat(4, false);

    lineInstance.va->AddBuffer(posBuffer,     vec4BL,  1);
    lineInstance.va->AddBuffer(colorBuffer,   vec4BL,  2);
    lineInstance.va->SetBufferDivisor(1,1);
    lineInstance.va->SetBufferDivisor(2,1);

    lineInstance.shader->Bind();
    lineInstance.shader->SetMat("projection", view.GetProjection());

    lineInstance.va->Bind();
    blendMode.Bind(); // blendmode should be an argument
    glDrawArraysInstanced(GL_LINES, 0, 4, lines.size());
  }

  void Renderer::Draw(const Sprite& sprite, const View& view, Sprite& canvas) {
    static RenderObjects lineInstance = CreateLineInstance();
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();
  }

  RenderObjects CreateRectangleInstance() {
    const float rectVertices[] = {
      //vertex     
       0.0f,  0.0f, 
       0.0f,  1.0f, 
       1.0f,  0.0f, 
       1.0f,  1.0f 
    };
    const unsigned int quadElements[] = {
      0, 1, 3,
      0, 2, 3
    };
    //bufferlayout
    sbl::gl::BufferLayout bl;
    bl.PushFloat(2, false); //position

    RenderObjects rectInstance;

    //INSTANCE SPRITES
    rectInstance.vb = new gl::VertexBuffer (&rectVertices, sizeof(rectVertices));
    rectInstance.va = new gl::VertexArray;
    rectInstance.va->AddBuffer(*rectInstance.vb, bl);
    rectInstance.eb = new gl::ElementBuffer(quadElements, 6);
    rectInstance.shader = new gl::Shader(
#include "glsl/rectangle.vs.glsl"
        ,
#include "glsl/rectangle.fs.glsl"
    );

    return rectInstance;
  }

  void Renderer::Draw(std::vector<RectangleShape>& rects, const View& view, Sprite& canvas, const BlendMode& bm) {
    static RenderObjects rectInstance = CreateRectangleInstance();
    static gl::FrameBuffer* framebuffer = new gl::FrameBuffer();

    framebuffer->Bind();
    if (canvas.GetTexture() == nullptr) { return; }
    framebuffer->BindTexture(*canvas.GetTexture());
    gl::Viewport canvasViewport(0, 0, canvas.Width(), canvas.Height());
    canvasViewport.Bind();

    int numRects = rects.size();
    std::vector<float> positions(numRects * 2);
    std::vector<float> sizes     (numRects * 2);
    std::vector<float> colors   (numRects * 4);
    for (int i = 0; i < numRects; i++) {
      RectangleShape& currRect = rects[i];

      const Vector2& position = currRect.GetTransform().position;
      positions[i * 2] = position.x;
      positions[i * 2 + 1] = position.y;

      const Vector2& size = currRect.size;
      sizes[i * 2] = size.x;
      sizes[i * 2 + 1] = size.y;

      const Color& color = rects[i].color;
      colors[i * 4] = color.r;
      colors[i * 4 + 1] = color.g;
      colors[i * 4 + 2] = color.b;
      colors[i * 4 + 3] = color.a;
    }

    gl::VertexBuffer positionBuffer (positions.data(),positions.size() * sizeof(float));
    gl::VertexBuffer sizeBuffer (sizes.data(),sizes.size() * sizeof(float));
    gl::VertexBuffer colorBuffer (colors.data(),colors.size() * sizeof(float));

    gl::BufferLayout vec2BL;
    vec2BL.PushFloat(2, false);
    gl::BufferLayout vec4BL;
    vec4BL.PushFloat(4, false);

    rectInstance.va->AddBuffer(positionBuffer,vec2BL,  1);
    rectInstance.va->AddBuffer(sizeBuffer,vec2BL,  2);
    rectInstance.va->AddBuffer(colorBuffer,vec4BL, 3);

    rectInstance.va->SetBufferDivisor(1,1);
    rectInstance.va->SetBufferDivisor(2,1);
    rectInstance.va->SetBufferDivisor(3,1);

    rectInstance.shader->Bind();
    rectInstance.shader->SetMat("projection", view.GetProjection());

    rectInstance.va->Bind();
    bm.Bind(); // blendmode should be an argument
    glDrawElementsInstanced(
      GL_TRIANGLES, 
      rectInstance.eb->IndexCount(), 
      GL_UNSIGNED_INT, 
      0, 
      rects.size()
    ); 
  }

  //TO SCREEN
  void Renderer::DrawToScreen(Sprite& sprite, Rect& rect) {
    if (sprite.GetTexture() == nullptr) { return; }

    gl::FrameBuffer framebuffer = gl::FrameBuffer::DefaultFrameBuffer();
    gl::Viewport vp(rect.BL().x, rect.BL().y, rect.TR().x, rect.TR().y);
    vp.Bind();

    // cast object to something usuable
    static RenderObjects spriteInstance = CreateSprite();

    framebuffer.Bind();
    spriteInstance.shader->Bind();
    sprite.GetTexture()->Bind();
    spriteInstance.va->Bind();
    sprite.blendMode.Bind();

    //uniforms
    glm::mat4 identity(1);
    spriteInstance.shader->SetMat("projection", identity);
    identity = glm::scale(identity, glm::vec3(2,2,1));
    spriteInstance.shader->SetMat("model", identity);
    Color color = sprite.color;
    spriteInstance.shader->SetVec4("color", color.r, color.g, color.b, color.a);
    //tex coord
    const Texture& texture = *sprite.GetTexture();
    Vector2 tSize = Vector2(texture.Width(), texture.Height());
    const Rect& spriteTC = sprite.textureCoords;
    spriteInstance.shader->SetVec2("tcDisplacement", (spriteTC.BL().x/tSize.x), (spriteTC.BL().y/tSize.y));
    spriteInstance.shader->SetVec2("tcSize", spriteTC.Size().x/tSize.x, spriteTC.Size().y/tSize.y);

    glDrawElements(GL_TRIANGLES, spriteInstance.eb->IndexCount(), GL_UNSIGNED_INT, 0); 
  }
}
