#pragma once

#include "Vector2.h"
#include "Color.h"
#include <vector>

struct ModelPreset
{
    std::vector<std::vector<Vector2>> m_model;
    Color m_color;
    std::vector<Vector2> m_hitbox;

    ModelPreset(const std::vector<std::vector<Vector2>>& modelData, const Color& color, const std::vector<Vector2>& hitbox)
        : m_model(modelData), m_color(color), m_hitbox(hitbox)
    {}

    ModelPreset()
        : m_model(), m_color(), m_hitbox()
    {}
};

class ModelData
{
private:
    static std::vector<std::vector<Vector2>> m_cube0;
    static std::vector<std::vector<Vector2>> m_ship1;
    static std::vector<std::vector<Vector2>> m_ship2;

    static const std::vector<std::vector<Vector2>> m_spike0;
    //static const std::vector<std::vector<Vector2>> m_spike1;
    //static const std::vector<std::vector<Vector2>> m_spike2;
    //static const std::vector<std::vector<Vector2>> m_platform3;

public:
    static ModelPreset GetFriendlyModel(uint8_t gamemode);
    static const std::vector<std::vector<Vector2>>& GetLevelModel(uint8_t modelNum);
};
