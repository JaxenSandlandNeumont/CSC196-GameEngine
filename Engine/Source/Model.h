#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Renderer.h"
#include "Transform.h"
#include <vector>

class Model
{
public:

	class Hitbox
	{
	public:
		Vector2 m_hitboxPoints[5];
		float m_xMin{ FLT_MAX };
		float m_xMax{ FLT_MIN };
		float m_yMin{ FLT_MAX };
		float m_yMax{ FLT_MIN };
	};


	//Model() = default;

	Model(std::vector<Vector2>& points, Color& color) :
		m_color{ color }
	{
		SetPoints(points);
	};

	Model(std::vector<std::vector<Vector2>>& shapes, Color& color) :
		m_color{ color }
	{
		SetPoints(shapes);
	};

	void Draw(Renderer& renderer, const Vector2& position, const float angle, const float scale);
	void Draw(Renderer& renderer, Transform& transform);
	void Draw(std::vector<Vector2> points, Renderer& renderer, Transform& transform);
	void Draw(Vector2 hitbox[5], Renderer& renderer, Transform& transform);
	void DrawShapes(Renderer& renderer, Transform& transform);


	void SetPoints(std::vector<std::vector<Vector2>> shapes);
	void SetPoints(std::vector<Vector2> points);

	void SetHitbox(std::vector<Vector2> hitbox);
	Hitbox* GetHitbox() { return m_hitbox; };

private:
	Hitbox* m_hitbox;
	std::vector<Vector2> m_points;
	std::vector<std::vector<Vector2>> m_shapes;
	Color m_color;
};