#include "pch.h"
#include "Screen.h"
#include "utils.h"
#include <iostream>

Screen::Screen(const Point2f& position, Point2f& window)
	:m_Window{ window }
	, m_PosScreen{ position }
	, m_PosButton{}
	, m_StateOfStartScreen{ true }
	, m_StateOfEndScreen{false}
	, m_StateOfButton{ false }
	, m_AlphaValue{ 1.f }
{

	std::string title{"60 SECONDS TO SURVIVE"};
	std::string text1{"dodge the bright green squared zombies and big red asteroids falling to the ground"};
	std::string text2{"as player you have 6 health, hit by zomb you lose 1 health, hit by asteroid you lose 2 health" };
	std::string text3{"you can gain 1 health if you pick up the red looking like heart on the playing field"};
	std::string text4{"CONTROLS: arrow up, arrow down, arrow left, arrow right"};
	std::string text5{ "PRESS SPACE IF YOU WANT TO TRY" };

	m_Text[0] = new Texture{title,"DIN-Light.otf",25,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f}};
	m_Text[1] = new Texture{ text1,"DIN-Light.otf",20,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f} };
	m_Text[2] = new Texture{ text2,"DIN-Light.otf",20,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f} };
	m_Text[3] = new Texture{ text3,"DIN-Light.otf",20,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f} };
	m_Text[4] = new Texture{ text4,"DIN-Light.otf",20,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f} };
	m_Text[5] = new Texture{ text5,"DIN-Light.otf",20,Color4f{ 0.0f, 0.5f, 0.5f, 1.0f} };

}

Screen::~Screen()
{
	for (int idx{}; idx < m_TOTALTEXT; ++idx)
	{
		delete m_Text[idx];
		m_Text[idx] = nullptr;
	}
}

void Screen::Update(float elapsedSec)
{
	const float speed{0.01f};
	if (m_StateOfButton == true)
	{
		if (m_StateOfEndScreen == false)
		{
			if (m_AlphaValue > 0) m_AlphaValue -= speed;
			else m_StateOfStartScreen = false;
		}
	}
	if (m_StateOfEndScreen == true)
	{
		if (m_AlphaValue < 1)m_AlphaValue += speed;
		else m_AlphaValue = 1;
	}
}

void Screen::Draw()
{
	if (m_StateOfStartScreen == true)
	{
		utils::SetColor(Color4f{ 0.f,0.f,0.f,m_AlphaValue });
		utils::FillRect(Rectf(0.f, 0.f, m_Window.x, m_Window.y));

		const float distanceHeightText{50.f};
		
		m_Text[0]->Draw(Point2f{m_Window.x / 2-m_Text[0]->GetWidth()/2, m_Window.y / 4 * 3 });
		m_Text[1]->Draw(Point2f{ m_Window.x / 2 - m_Text[1]->GetWidth() / 2, m_Window.y / 4 *3 -distanceHeightText });
		m_Text[2]->Draw(Point2f{ m_Window.x / 2 - m_Text[2]->GetWidth() / 2, m_Window.y / 4 * 3 - distanceHeightText*2 });
		m_Text[3]->Draw(Point2f{ m_Window.x / 2 - m_Text[3]->GetWidth() / 2, m_Window.y / 4 * 3 - distanceHeightText*3 });
		m_Text[4]->Draw(Point2f{ m_Window.x / 2 - m_Text[4]->GetWidth() / 2, m_Window.y / 4 * 3 - distanceHeightText*4 });
		m_Text[5]->Draw(Point2f{ m_Window.x / 2 - m_Text[5]->GetWidth() / 2, m_Window.y / 4 * 3 - distanceHeightText * 5 });
	}

	if (m_StateOfEndScreen == true)
	{
		utils::SetColor(Color4f{ 0.f,0.f,0.f,m_AlphaValue });
		utils::FillRect(Rectf(0.f, 0.f, m_Window.x, m_Window.y));
	}

}

void Screen::ChangeStateOfButton()
{
	m_StateOfButton = true;
}

void Screen::ChangeStateOfEndScreen(bool changeState)
{
	m_StateOfEndScreen = changeState;
}

bool Screen::GetStateOfStartScreen() const
{
	return m_StateOfStartScreen;
}

bool Screen::GetStateOfEndScreen() const
{
	return m_StateOfEndScreen;
}
