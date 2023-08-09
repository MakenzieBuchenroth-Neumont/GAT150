#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace neko {
	void ModelRenderComponent::update(float dt) {

	}

	void ModelRenderComponent::draw(Renderer& renderer) {
		m_model->draw(renderer, m_owner->m_transform);
	}

}