#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace Rex {
	Font::~Font() {
		if (s_ttfFont != nullptr) {
			TTF_CloseFont(s_ttfFont);
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		s_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (s_ttfFont == nullptr) {
			std::cerr << "Could not load font: " << name << std::endl;
			return false;
		}

		return true;
	}
}