#pragma once
#include "Renderer/Texture.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace Rex {
	class Renderer {
	public:

		Renderer() = default;

		bool Initialize();
		void Shutdown();
		bool CreateWindow(const std::string& name, int width, int height);

		void Clear();
		void Present();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColor(float r, float g, float b, float a = 1.0f);

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);
		void DrawTexture(class Texture& texture, float x, float y, float angle = 0);
		void DrawTexture(class Texture& texture, float x, float y, float scale, float angle = 0);

		int GetWidth() const { return s_width; }
		int GetHeight() const { return s_height; }
	private:

		friend class Text;
		friend class Texture;

		int s_width{ 0 };
		int s_height{ 0 };

		SDL_Window* s_window = nullptr;
		SDL_Renderer* s_renderer = nullptr;
	};
}
