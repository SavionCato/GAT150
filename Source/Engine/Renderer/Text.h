#pragma once
#include "../Math/Vector3.h"
#include <string>
#include <memory>

struct SDL_Texture;

namespace Rex {
	class Text {
	public:

		Text() = default;
		Text(std::shared_ptr<class Font> font) : s_font{ font } {}
		~Text();

		bool Create(class Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(class Renderer& renderer, float x, float y);
	private:

		std::shared_ptr<class Font> s_font{ nullptr };
		SDL_Texture* s_texture{ nullptr };
	};
}