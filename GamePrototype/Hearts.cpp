#include "pch.h"
#include "Hearts.h"
#include "utils.h"

Hearts::Hearts(Point2f& pos)
	:m_PositionHeart{pos}
	,m_Health{1}
{
}

void Hearts::Draw()
{
	utils::SetColor(Color4f{ 0.4, 0.0f, 0.0f, 1.0f });
	utils::FillEllipse(m_PositionHeart, 10.f, 10.f);
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
