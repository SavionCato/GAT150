#pragma once
#include "Renderer.h"
#include "Math/Vector2.h"
#include "Resources/Resource.h"

#include <iostream>

namespace Rex {
	class Texture : public Resource {
	public:

		Texture() = default;
		~Texture();

		bool load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;
	private:

		struct SDL_Texture* s_texture{ nullptr };
	};
}
