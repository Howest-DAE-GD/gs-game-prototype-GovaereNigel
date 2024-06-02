#include "pch.h"
#include "Healthbar.h"
#include "Player.h"
#include "utils.h"

Healthbar::Healthbar(int health, Point2f& window)
	:m_Window{window}
	,m_Health{health}
{
}

void Healthbar::Draw()
{
	utils::SetColor(Color4f{ 1.f,0.f,0.f,0.3f });
	if (m_Health >= 8) utils::FillRect(20.f, m_Window.y - 50.f, 200.f, 20.f);
	else if (m_Health == 7) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8), 20.f);
	else if (m_Health == 6) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 2), 20.f);
	else if (m_Health == 5) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 3), 20.f);
	else if (m_Health == 4) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 4), 20.f);
	else if (m_Health == 3) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 5), 20.f);
	else if (m_Health == 2) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 6), 20.f);
	else if (m_Health == 1) utils::FillRect(20.f, m_Window.y - 50.f, 200.f - (200.f / 8 * 7), 20.f);
}

void Healthbar::Update(Player* player)
{
	m_Health = player->GetHealth();
}

