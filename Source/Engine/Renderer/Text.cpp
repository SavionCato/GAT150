#include "Text.h"
#include "Font.h"
#include "Renderer.h"
#include "../Math/Vector3.h"
#include "Core/Logger.h"

#include <SDL3/SDL.h>
#include <string>

namespace Rex {
	
	Text::~Text() {

		if (s_texture != nullptr) {

			SDL_DestroyTexture(s_texture);
		}
	}

	bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {

		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(s_font->s_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {

			Rex::Logger::Error("Could not create surface.\n");
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		s_texture = SDL_CreateTextureFromSurface(renderer.s_renderer, surface);
		if (s_texture == nullptr) {

			SDL_DestroySurface(surface);
			Rex::Logger::Error("Could not create texture " , std::string(SDL_GetError()));
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);

		return true;
	}

	void Text::Draw(Renderer& renderer, float x, float y) {

		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(s_texture, &width, &height);
		assert(success);

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.s_renderer, s_texture, NULL, &rect);
		assert(success);
	}
}
