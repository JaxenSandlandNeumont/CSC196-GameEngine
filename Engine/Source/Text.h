#pragma once
#include "Font.h"
#include "Renderer.h"
#include "Vector2.h"

struct Color;

class Text
{
public:
	Text() = default;
	Text(Vector2 position) :
		m_position{ position }
	{}
	Text(Font* font) : m_font{ font } {}
	Text(Font* font, Vector2 position) :
		m_font{ font },
		m_position{ position }
	{}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer);
	void Draw(Renderer& renderer, int x, int y);

private:
	Vector2 m_position{ 40, 40 };
	Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};