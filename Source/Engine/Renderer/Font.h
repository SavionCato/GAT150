#pragma once
#include "Resources/Resource.h"

#include <string>

struct TTF_Font;

namespace Rex {
	class Font : public Resource {
	public:

		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);
	private:
		friend class Text;

		TTF_Font* s_ttfFont{ nullptr };
	};
}