#include "TextRenderComponent.h"
#include <Framework/Resource/ResourceManager.h>
#include <Framework/Actor.h>
#include <memory>

namespace neko
{
	CLASS_DEFINITION(TextRenderComponent)
		TextRenderComponent::TextRenderComponent(const TextRenderComponent& other) {
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;
		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}

	bool TextRenderComponent::initialize() {
		if (!fontName.empty()) m_text = std::make_unique<neko::Text>(GET_RESOURCE(Font, fontName, fontSize));
			return true;
	}

	void TextRenderComponent::update(float dt) {
		//
	}

	void TextRenderComponent::draw(Renderer& renderer) {
		// update the text if changed
		if (m_changed) {
			m_changed = false;
			// create text using text string and color
			m_text->create(renderer, text, color);
		}
		// draw text
		m_text->draw(renderer, m_owner->transform);
	}

	void TextRenderComponent::setText(const std::string& string) {
		// check if text has changed, if changed set new string and update
		if (string != text) {
			text = string;
			m_changed = true;
		}
	}

	void TextRenderComponent::read(const json_t& value) {
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
		READ_DATA(value, color);
	}
}
