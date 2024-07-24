#include "Button.h"


void Button::Update()
{

}

void Button::Draw(Renderer& renderer)
{

}

bool Button::MouseHoveringOver(Vector2 mousePosition) const
{
    float xMax = m_model.GetHitbox()->m_xMax;
    float xMin = m_model.GetHitbox()->m_xMin;
    float yMax = m_model.GetHitbox()->m_yMax;
    float yMin = m_model.GetHitbox()->m_yMin;

    bool mouseWithinX = mousePosition.x > xMin && mousePosition.x < xMax;
    bool mouseWithinY = mousePosition.y > yMin && mousePosition.y < yMax;

    return (mouseWithinX && mouseWithinY);
}

bool Button::ButtonClicked(Input* input) const
{
    bool hovering = MouseHoveringOver(input->GetMousePosition());

    return hovering && !input->GetMouseButtonDown(0) && input->GetPreviousMouseButtonDown(0) && m_clickable;
}

bool Button::ButtonHeld(Input* input) const
{
    bool hovering = MouseHoveringOver(input->GetMousePosition());
    
    return hovering && input->GetMouseButtonDown(0) && input->GetPreviousMouseButtonDown(0) && m_clickable;
}
