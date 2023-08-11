#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace neko {
	class ModelRenderComponent : public RenderComponent {
	public:
		void update(float dt) override;
		void draw(class Renderer& renderer) override;

		virtual float getRadius() override { return m_model->getRadius(); }
	public:
		res_t<Model> m_model;
	};
}