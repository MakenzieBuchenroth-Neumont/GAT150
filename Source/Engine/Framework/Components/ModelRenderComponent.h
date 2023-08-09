#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace neko {
	class ModelRenderComponent : public RenderComponent {
	public:
		void update(float dt) override;
		void draw(class Renderer& renderer) override;

	public:
		res_t<Model> m_model;
	};
}