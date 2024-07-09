#include "Model.h"

void Model::Draw(Renderer& renderer, const Vector2& position, const float angle, const float scale)
{
	for (int i = 0; i < m_points.size() - 1; i++)
	{
		if (m_points.empty()) return;

		Vector2 p1 = m_points[i].Rotate(angle) * scale + position;
		Vector2 p2 = m_points[i + 1].Rotate(angle) * scale + position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}
