#pragma once
#include "Actor.h"
#include "Input.h"
#include "Model.h"
#include "Text.h"

class Button : public Actor
{
public:
	Button() = default;

	Button(const Transform& transform, Model* model, Text* text, Color bgColor) :
		Actor{ transform, model },
		m_text{ text },
		m_bgColor{ bgColor }
	{}

	Button(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	//~Button() = default;

	void Update();
	void Draw(Renderer& renderer);
	bool MouseHoveringOver (Vector2 mousePosition);
	bool ButtonClicked(Input& input);
	bool ButtonHeld(Input& input);
	void SetText(Text* text) { m_text = text; }
	void SetClickable(bool clickable) { m_clickable = clickable; }
	Text* GetText() { return m_text; }

private:
	Color m_bgColor{};

	bool m_clickable{ true };
	Text* m_text{ nullptr };
	std::string m_tag{ "button" };

};

