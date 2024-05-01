#include "pch.h"
#include "Hearts.h"
#include "utils.h"

Hearts::Hearts(Point2f& pos)
	:m_PositionHeart{pos}
	,m_Health{1}
	,m_Radius{12.f}
{
}

void Hearts::Draw()
{
	utils::SetColor(Color4f{ 0.4, 0.0f, 0.0f, 1.0f });
	utils::FillEllipse(m_PositionHeart, m_Radius, m_Radius);
	utils::SetColor(Color4f{ 0.f, 0.0f, 0.2f, 1.0f });
	utils::DrawEllipse(m_PositionHeart, m_Radius, m_Radius,2.f);

}

void Hearts::SetPosition(Point2f& pos)
{
	m_PositionHeart.x = pos.x;
	m_PositionHeart.y = pos.y;

}

int Hearts::GetHealth() const
{
	return m_Health;
}

float Hearts::GetRadius()
{
	return m_Radius;
}
