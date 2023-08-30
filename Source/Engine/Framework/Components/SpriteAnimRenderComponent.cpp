#include "SpriteAnimRenderComponent.h"
#include <Framework/Resource/ResourceManager.h>
#include <Framework/Actor.h>
#include "Renderer/Renderer.h"

namespace neko {
	CLASS_DEFINITION(SpriteAnimRenderComponent)

	bool SpriteAnimRenderComponent::initialize() {
		SpriteComponent::initialize();

		setSequence(defaultSequenceName, false);

		if (source.w == 0 && source.h == 0) {
			updateSource();
		}

		return true;
	}

	void SpriteAnimRenderComponent::update(float dt) {
		frameTimer -= dt;
		if (frameTimer <= 0) {
			frameTimer = 1.0f / m_sequence->fps;
			frame++;
			if (frame > m_sequence->endFrame) {
				frame = (m_sequence->loop) ? frame = m_sequence->startFrame : m_sequence->endFrame;
			}
		}

		updateSource();
	}

	void SpriteAnimRenderComponent::setSequence(const std::string& name, bool update) {
		// prevent setting sequence again
		if (m_sequence && m_sequence->name == name) return;

		if (m_sequences.find(name) != m_sequences.end()) {
			// set new sequence
			m_sequence = &m_sequences[name];
			// set texture
			if (m_sequence->texture) m_texture = m_sequence->texture;
			// reset frame info
			frame = m_sequence->startFrame;
			frameTimer = 1.0f / m_sequence->fps;

			if (update) updateSource();
		}
	}

	void SpriteAnimRenderComponent::updateSource() {
		vec2 cellSize = m_texture->getSize() / vec2{ m_sequence->numColumns, m_sequence->numRows };
		int column = (frame - 1) % m_sequence->numColumns;
		int row = (frame - 1) / m_sequence->numColumns;
		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);
	}

	void SpriteAnimRenderComponent::read(const json_t& value) {
		SpriteComponent::read(value);

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray())
		{
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray())
			{
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName))
		{
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}
}
