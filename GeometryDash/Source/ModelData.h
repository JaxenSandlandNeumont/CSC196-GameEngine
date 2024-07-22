#pragma once
#include "Vector2.h"
#include <Vector>

class ModelData
{
public:
    static const std::vector<std::vector<Vector2>>& GetFriendlyModel(uint8_t modelNum)
    {
        static const std::vector<std::vector<Vector2>> emptyModel{};
        switch (modelNum)
        {
        case 0:
            return m_cube0;
        case 1:
            return m_ship1;
        case 2:
            return m_ship2;
        default:
            return emptyModel;
        }
    }
    static const std::vector<std::vector<Vector2>>& GetLevelModel(uint8_t modelNum)
    {
        static const std::vector<std::vector<Vector2>> emptyModel{};
        switch (modelNum)
        {
        case 0:
            return m_spike0;
        case 1:
            return m_spike1;
        case 2:
            return m_spike2;
        case 3:
            return m_platform3;
        default:
            return emptyModel;
        }
    }

private:
    const static std::vector<std::vector<Vector2>> m_cube0;
    const static std::vector<std::vector<Vector2>> m_ship1;
    const static std::vector<std::vector<Vector2>> m_ship2;


    const static std::vector<std::vector<Vector2>> m_spike0;
    const static std::vector<std::vector<Vector2>> m_spike1;
    const static std::vector<std::vector<Vector2>> m_spike2;
    const static std::vector<std::vector<Vector2>> m_platform3;
};