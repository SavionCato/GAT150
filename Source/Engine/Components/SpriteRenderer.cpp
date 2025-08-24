#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace Rex {

	void SpriteRenderer::Update(float dt) {


	}

	void SpriteRenderer::Draw(Renderer& renderer) {

		auto texture = Resources().Get<Texture>(TextureName, renderer).get();

		if (texture) {

			renderer.DrawTexture(*texture, owner->transform.position.x,
				owner->transform.position.y, owner->transform.scale, owner->transform.rotation);
		}
	}
}