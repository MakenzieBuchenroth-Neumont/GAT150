#include "TilemapComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"

namespace neko
{
    CLASS_DEFINITION(TilemapComponent)

    bool TilemapComponent::initialize()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            int index = tiles[i];
            if (index == 0) continue;

            auto actor = INSTANTIATE(Actor, tileNames[index]);
            if (actor)
            {
                int x = i % numColumns;
                int y = i / numColumns;

                actor->transform.position = m_owner->transform.position + (vec2{ x, y } * size);
                m_owner->m_scene->add(std::move(actor));
            }
        }

        return true;
    }

    void TilemapComponent::update(float dt)
    {
        //
    }
        
    void TilemapComponent::read(const json_t& value)
    {
        READ_DATA(value, numColumns);
        READ_DATA(value, numRows);
        READ_DATA(value, size);
        
        READ_DATA(value, tileNames);
        READ_DATA(value, tiles);
    }

}