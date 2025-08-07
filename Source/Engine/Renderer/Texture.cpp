#include "Texture.h"

namespace Rex {

	Texture::~Texture() {

        if (s_texture) SDL_DestroyTexture(s_texture);
	}

	bool Texture::load(const std::string& filename, class Renderer& renderer) {

        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (surface == nullptr)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        s_texture = SDL_CreateTextureFromSurface(renderer.s_renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (s_texture == nullptr) {

            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }
        
        return true;
	}

	vec2 Texture::GetSize() {

        vec2 size;
        SDL_GetTextureSize(s_texture, &size.x, &size.y);

		return size;
	}

}
