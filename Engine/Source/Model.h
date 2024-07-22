#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Renderer.h"
#include "Transform.h"
#include <vector>

class Model
{
public:
	Model() = default;

	Model(std::vector<Vector2>& points, Color& color) :
		m_points{ points },
		m_color{ color }
	{};

	Model(std::vector<std::vector<Vector2>>& shapes, Color& color) :
		m_shapes{ shapes },
		m_color{ color }
	{};

	void Draw(Renderer& renderer, const Vector2& position, const float angle, const float scale);
	void Draw(Renderer& renderer, Transform& transform);
	void Draw(std::vector<Vector2> points, Renderer& renderer, Transform& transform);
	void Draw(Vector2 hitbox[5], Renderer& renderer, Transform& transform);
	void DrawShapes(Renderer& renderer, Transform& transform);

private:
	std::vector<Vector2> m_points;
	std::vector<std::vector<Vector2>> m_shapes;
	Color m_color;
};