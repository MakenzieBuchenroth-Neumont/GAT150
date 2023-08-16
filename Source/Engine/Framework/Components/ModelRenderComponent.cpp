#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace neko {
	CLASS_DEFINITION(ModelRenderComponent)

	bool ModelRenderComponent::initialize() {
		m_model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void ModelRenderComponent::update(float dt) {

	}

	void ModelRenderComponent::draw(Renderer& renderer) {
		m_model->draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::read(const json_t& value) {
		READ_DATA(value, modelName);
	}

}