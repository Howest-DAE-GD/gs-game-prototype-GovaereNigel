#include "pch.h"
#include "Asteroid.h"
#include "utils.h"
#include <iostream>

Asteroid::Asteroid(float radius, Point2f& window)
	:m_Radius{radius}
	,m_Window{window}
	,m_Position{GetRandomPosition()}
	,m_Damage{2}
	,m_FakeRadius{}
	,m_State{false}
	,m_Timer{}
	,m_HasHeart{false}
{
}

void Asteroid::Draw()
{

	utils::SetColor(Color4f{ 0.0f, 0.2f, 0.2f, 1.0f });
	utils::FillEllipse(m_Position, m_FakeRadius, m_FakeRadius);


	if (m_State == true)
	{
		utils::SetColor(Color4f{ 0.2, 0.0f, 0.0f, 1.0f });
		utils::FillEllipse(m_Position, m_FakeRadius, m_FakeRadius);
	}

}

void Asteroid::Update(float elapsedSec)
{
	const float speedAsteroid{35.f*elapsedSec};
	const float maxResetTime{0.5f};

	if (m_State == false)
	{
		if (m_FakeRadius <= m_Radius)
		{
			m_FakeRadius += speedAsteroid;
		}
		else
		{
			m_State = true;
		}
	}
	if (m_State == true)
	{
		if (m_Timer <= maxResetTime)
		{
			m_Timer += elapsedSec;
		}
		else
		{
			m_State = false;
			m_Timer = 0;
			m_FakeRadius = 0;

			m_Position = GetRandomPosition();
			const int random{rand()%2+0};
			if (random == 0) m_HasHeart = false;
			else m_HasHeart = true;

		}
	}

}

Point2f Asteroid::GetRandomPosition()
{
	Point2f pos{};

	pos.x = float(rand() % int((m_Window.x-m_Radius*2)) + m_Radius);
	pos.y = float(rand() % int((m_Window.y - m_Radius * 2)) + m_Radius);

	return pos;
}

Point2f Asteroid::GetPosition()
{
	return m_Position;
}

float Asteroid::GetRadius()
{
	return m_Radius;
}

bool Asteroid::GetStateOfAsteroid()
{
	return m_State;
}

bool Asteroid::HasAHeart()
{
	return m_HasHeart;
}
