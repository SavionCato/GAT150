#pragma once
#include "Framework/Component.h"

namespace Rex {
	class RendererComponent : public Component {
	public:

		virtual void Draw(class Renderer& renderer) = 0;
	private:


	};
}