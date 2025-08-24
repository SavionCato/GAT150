#pragma once
#include "RendererComponent.h"

namespace Rex {
	class SpriteRenderer : public RendererComponent {
	public:

		std::string TextureName;
	public:

		void Update(float dt) override;

		void Draw(Renderer& renderer) override;

	};
}