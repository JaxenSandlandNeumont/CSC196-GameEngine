#include "Model.h"

void Model::Draw(Renderer& renderer, const Vector2& position, const float angle, const float scale)
{


	if (m_points.empty()) return;
	renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

	for (int i = 0; i < m_points.size() - 1; i++)
	{

		Vector2 p1 = m_points[i].Rotate(angle) * scale + position;
		Vector2 p2 = m_points[i + 1].Rotate(angle) * scale + position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

void Model::Draw(Renderer& renderer, Transform& transform)
{
	if (m_shapes.empty() && m_points.empty()) return;
	renderer.SetColor(m_color);

	if (m_shapes.empty())
	{
		Model::Draw(m_points, renderer, transform);
	}
	else
	{
		Model::DrawShapes(renderer, transform);
	}
	
}

void Model::Draw(std::vector<Vector2> points, Renderer& renderer, Transform& transform)
{
	if (points.empty()) return;
	renderer.SetColor(m_color);

	for (int i = 0; i < points.size() - 1; i++)
	{


		Vector2 p1 = points[i].Rotate(transform.rotation) * transform.scale + transform.position;
		Vector2 p2 = points[i + 1].Rotate(transform.rotation) * transform.scale + transform.position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void Model::Draw(Vector2 hitbox[5], Renderer& renderer, Transform& transform)
{
	renderer.SetColor(m_color);

	for (int i = 0; i < 4; i++)
	{


		Vector2 p1 = hitbox[i].Rotate(transform.rotation) * transform.scale + transform.position;
		Vector2 p2 = hitbox[i + 1].Rotate(transform.rotation) * transform.scale + transform.position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}


void Model::DrawBox(Renderer& renderer, Transform& transform, Color color)
{
	renderer.SetColor(color);
	Vector2 p1{ m_xMin + ((m_xMax - m_xMin) / 2) + transform.position.x, m_yMin + ((m_yMax - m_yMin) / 2) + transform.position.y };

	renderer.DrawRect(p1.x, p1.y, m_xMax * 2, m_yMax * 2);

}

void Model::DrawShapes(Renderer& renderer, Transform& transform)
{
	for (std::vector<Vector2> shape : m_shapes)
	{
		Model::Draw(shape, renderer, transform);
	}
}



void Model::SetHitbox(std::vector<std::vector<Vector2>> hitbox)
{
	SetHitbox(hitbox[0]);
}


void Model::SetHitbox(std::vector<Vector2> hitbox)
{

	for (int i = 0; i < 5; i++)
	{
		m_hitboxPoints[i] = hitbox.at(i);

		m_xMin = ((int)hitbox.at(i).x < m_xMin) ? (int)hitbox.at(i).x : m_xMin;
		m_xMax = ((int)hitbox.at(i).x > m_xMax) ? (int)hitbox.at(i).x : m_xMax;
		m_yMin = ((int)hitbox.at(i).y < m_yMin) ? (int)hitbox.at(i).y : m_yMin;
		m_yMax = ((int)hitbox.at(i).y > m_yMax) ? (int)hitbox.at(i).y : m_yMax;
	}
}
