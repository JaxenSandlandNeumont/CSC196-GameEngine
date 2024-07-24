#pragma once
#include "Actor.h"
#include "Input.h"
#include "Model.h"

class Text;

class Button : public Actor
{
public:
	Button() = default;
	Button(const Transform& transform, Model& model, Text* text) :
		m_transform{ transform },
		m_model{ model },
		m_text{ text }
	{}
	Button(const Transform& transform, Model& model) :
		m_transform{ transform },
		m_model{ model }
	{}

	~Button() = default;

	void Update();
	void Draw(Renderer& renderer);
	bool MouseHoveringOver (Vector2 mousePosition) const;
	bool ButtonClicked(Input* input) const;
	bool ButtonHeld(Input* input) const;
	void SetText(Text* text) { m_text = text; }
	void SetClickable(bool clickable) { m_clickable = clickable; }
	Text* GetText() { return m_text; }

private:

	Model& m_model;
	Transform m_transform;

	bool m_clickable{ true };
	Text* m_text{ nullptr };
	std::string m_tag{ "button" };


};

