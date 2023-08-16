#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace neko {
	class ModelRenderComponent : public RenderComponent {
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool initialize() override;
		void update(float dt) override;
		void draw(class Renderer& renderer) override;

		virtual float getRadius() override { return m_model->getRadius(); }
	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}