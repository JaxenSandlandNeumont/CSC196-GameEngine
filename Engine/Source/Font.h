#pragma once
#include <string>
#include <SDL_ttf.h>

class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);
	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };
};