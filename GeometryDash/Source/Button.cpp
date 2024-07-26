#include "Button.h"
#include "Engine.h"
#include <iostream>


void Button::Update()
{

}

void Button::Draw(Renderer& renderer)
{
   m_model->DrawBox(renderer, m_transform, m_bgColor);
   m_text->Draw(renderer);
   Actor::Draw(renderer);
}

bool Button::MouseHoveringOver(Vector2 mousePosition)
{
    float xMax = m_model->m_xMax + m_transform.position.x;
    float xMin = m_model->m_xMin + m_transform.position.x;
    float yMax = m_model->m_yMax + m_transform.position.y;
    float yMin = m_model->m_yMin + m_transform.position.y;

    bool mouseWithinX = mousePosition.x > xMin && mousePosition.x < xMax;
    bool mouseWithinY = mousePosition.y > yMin && mousePosition.y < yMax;
    if (mouseWithinX && mouseWithinY)
    {
        return true;
    }
    return false;

}

bool Button::ButtonClicked(Input& input)
{

    bool hovering = MouseHoveringOver(input.GetMousePosition());
    bool clicked = !input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0);
    if (clicked && hovering)
    {
        g_engine.GetAudio().PlaySound("buttonPressSound.wav");
    }
    return hovering && m_clickable && clicked;
}

bool Button::ButtonHeld(Input& input)
{
    bool hovering = MouseHoveringOver(input.GetMousePosition());
    return hovering && input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0) && m_clickable;
}
