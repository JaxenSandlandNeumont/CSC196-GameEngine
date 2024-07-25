#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Renderer.h"
#include "Transform.h"
#include <vector>

class Model
{
public:


	//Model() = default;

	Model(std::vector<Vector2>& points, Color& color) :
		m_color{ color },
		m_points{ points }
	{
		SetHitbox(points);
	};

	Model(std::vector<std::vector<Vector2>>& shapes, Color& color) :
		m_color{ color },
		m_shapes{ shapes }
	{
		SetHitbox(shapes);
	};

	void Draw(Renderer& renderer, const Vector2& position, const float angle, const float scale);
	void Draw(Renderer& renderer, Transform& transform);
	void Draw(std::vector<Vector2> points, Renderer& renderer, Transform& transform);
	void Draw(Vector2 hitbox[5], Renderer& renderer, Transform& transform);
	void DrawBox(Renderer& renderer, Transform& transform, Color color);
	void DrawShapes(Renderer& renderer, Transform& transform);

	void SetHitbox(std::vector<std::vector<Vector2>> hitbox);
	void SetHitbox(std::vector<Vector2> hitbox);
	void SetColor(Color color) { m_color = color; }
	Color GetColor() const { return m_color; }

	Vector2 m_hitboxPoints[5];
	float m_xMin{};
	float m_xMax{};
	float m_yMin{};
	float m_yMax{};

private:
	std::vector<Vector2> m_points{};
	std::vector<std::vector<Vector2>> m_shapes{ };
	Color m_color;



};