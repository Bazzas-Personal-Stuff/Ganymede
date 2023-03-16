#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"

namespace Ganymede {
    struct SpriteData {
        // Visual
        Ref<Texture2D> Texture = Texture2D::Create(glm::vec4(1.0f));
        glm::vec4 Tint = glm::vec4(1.0f);
    };

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitive Modifiers
        static void Fill(const glm::vec4& color);
        // static void Stroke(const glm::vec4& color);
        // static void StrokeWidth(float width);
        
        // Primitives
        static void Rect(const glm::vec3& position, const glm::vec2& size);
        static void Rect(const glm::vec3& position, const glm::vec2& size, float rotation);

        // Sprites
        static void Sprite(const glm::vec3& position, const glm::vec2& size, const SpriteData& spriteData);
        static void Sprite(const glm::vec3& position, const glm::vec2& size, float rotation, const SpriteData& spriteData);
    };
}
