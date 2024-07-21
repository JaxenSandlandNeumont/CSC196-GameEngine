#include "ModelData.h"

const std::vector<std::vector<Vector2>> ModelData::m_cube0 =
{
    {
        {-5, 5}, {5, 5}, {5, -5}, {-5, -5}, {-5, 5}
    },
    {
        {-4, 4}, {4, 4}, {4, -4}, {-4, -4}, {-4, 4}
    }
};

const std::vector<std::vector<Vector2>> ModelData::m_ship1 =
{
    {
        {5, 0}, {-5, 3}, {-3, 0}, {-5, -3}, {5, 0}
    }
};

const std::vector<std::vector<Vector2>> ModelData::m_ship2 =
{
    {
        {2.0f, 0.9f}, {-5, 3}, {-3, 0}, {-5, -3}, {2.0f, -0.9f} //Body
    },
    {
        {2.0f, 0.9f}, {4, 0}, {2.0f, -0.9f} //Head
    },
    {
        {0, 0}, {-2.0f, -0.85f}, {-0.8f, 1.1f}, {-0.8f, -1.1f}, {-2.0f, 0.85f}, {0, 0} //Star
    },
    {
        {0.5f, 1.4f}, {-2.5f, 6.0f}, {-2.5f, 2.3f} //Right wing
    },
    {
        {0.5f, -1.4f}, {-2.5f, -6.0f}, {-2.5f, -2.3f} //Left wing
    },
    {
        {2.0, 0.8f}, {2.0, -0.8f} //Cockpit
    },
    {
        {-1.7f, 5.0f}, {0.4f, 5.0f}, {0.4f, 4.0f}, {-1.1f, 4.0f} //Right gun
    },
    {
        {-1.7f, -5.0f}, {0.4f, -5.0f}, {0.4f, -4.0f}, {-1.1f, -4.0f} //Left gun
    },
    {
        {0.4f, 4.2f}, {0.6f, 4.2f}, {0.6f, 4.8f}, {0.4f, 4.8f} //Right gun middle
    },
    {
        {0.4f, -4.2f}, {0.6f, -4.2f}, {0.6f, -4.8f}, {0.4f, -4.8f} //Left gun middle
    },
    {
        {0.6f, 4.3f}, {1.2f, 4.3f}, {1.2f, 4.7f}, {0.6f, 4.7f} //Right gun tip
    },
    {
        {0.6f, -4.3f}, {1.2f, -4.3f}, {1.2f, -4.7f}, {0.6f, -4.7f} //Left gun tip
    }
};