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
	if (!m_points.empty())
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
	//renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

	for (int i = 0; i < points.size() - 1; i++)
	{


		Vector2 p1 = points[i].Rotate(transform.rotation) * transform.scale + transform.position;
		Vector2 p2 = points[i + 1].Rotate(transform.rotation) * transform.scale + transform.position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void Model::Draw(Vector2 hitbox[5], Renderer& renderer, Transform& transform)
{
	//renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

	for (int i = 0; i < 4; i++)
	{


		Vector2 p1 = hitbox[i].Rotate(transform.rotation) * transform.scale + transform.position;
		Vector2 p2 = hitbox[i + 1].Rotate(transform.rotation) * transform.scale + transform.position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void Model::DrawShapes(Renderer& renderer, Transform& transform)
{
	for (std::vector<Vector2> shape : m_shapes)
	{
		Model::Draw(shape, renderer, transform);
	}
}
