#include "pch.h"
#include "SpecialZomb.h"
#include <utils.h>

SpecialZomb::SpecialZomb(float windowWidth, float windowHeight)
:m_Window{windowWidth,windowHeight}
,m_PosSpecialZomb{GetRandomStartPos()}
,m_BoundsSpecialZomb{m_PosSpecialZomb.x,m_PosSpecialZomb.y,25.f,25.f}
{
}

void SpecialZomb::Draw()
{
	utils::SetColor(Color4f{ 0.f,0.8f,0.f,1.f });
	utils::FillRect(m_BoundsSpecialZomb);
}

void SpecialZomb::Update(float elapsedSec, Point2f& m_PosPlayer, float speed)
{
	//float speed{ elapsedSec * 90.f };

	if (m_PosSpecialZomb.x < m_PosPlayer.x)
	{
		m_PosSpecialZomb.x += speed;
	}
	else
	{
		m_PosSpecialZomb.x -= speed;
	}
	if (m_PosSpecialZomb.y < m_PosPlayer.y)
	{
		m_PosSpecialZomb.y += speed;
	}
	else
	{
		m_PosSpecialZomb.y -= speed;
	}

	m_BoundsSpecialZomb.left = m_PosSpecialZomb.x;
	m_BoundsSpecialZomb.bottom = m_PosSpecialZomb.y;
}

void SpecialZomb::ResetPos()
{
	m_PosSpecialZomb = GetRandomStartPos();
	m_BoundsSpecialZomb.left = m_PosSpecialZomb.x;
	m_BoundsSpecialZomb.bottom = m_PosSpecialZomb.y;

}

Point2f SpecialZomb::GetRandomStartPos()
{
	const int random{rand()%17+0};
	Point2f newPos{};

	if (random == 1)
	{
		newPos.x = m_Window.x/8;
		newPos.y = m_Window.y;
	}
	if (random == 2)
	{
		newPos.x = m_Window.x/8*3;
		newPos.y = m_Window.y;
	}
	if (random == 3)
	{
		newPos.x = m_Window.x/8*5;
		newPos.y = m_Window.y;
	}
	if (random == 4)
	{
		newPos.x = m_Window.x/8*7;
		newPos.y = m_Window.y;
	}
	if (random == 5)
	{
		newPos.x = m_Window.x;
		newPos.y = m_Window.y/8*7;
	}
	if (random == 6)
	{
		newPos.x = m_Window.x;
		newPos.y = m_Window.y/8*5;
	}
	if (random == 7)
	{
		newPos.x = m_Window.x;
		newPos.y = m_Window.y/8*3;
	}
	if (random == 8)
	{
		newPos.x = m_Window.x;
		newPos.y = m_Window.y/8;
	}
	if (random == 9)
	{
		newPos.x = m_Window.x/8*7;
		newPos.y = 0.f - m_BoundsSpecialZomb.height;
	}
	if (random == 10)
	{
		newPos.x = m_Window.x / 8 * 5;
		newPos.y = 0.f - m_BoundsSpecialZomb.height;
	}
	if (random == 11)
	{
		newPos.x = m_Window.x / 8 * 3;
		newPos.y = 0.f - m_BoundsSpecialZomb.height;
	}
	if (random == 12)
	{
		newPos.x = m_Window.x / 8 ;
		newPos.y = 0.f - m_BoundsSpecialZomb.height;
	}
	if (random == 13)
	{
		newPos.x = 0.f-m_BoundsSpecialZomb.width;
		newPos.y = m_Window.y/8;
	}
	if (random == 14)
	{
		newPos.x = 0.f - m_BoundsSpecialZomb.width;
		newPos.y = m_Window.y / 8*3;
	}
	if (random == 15)
	{
		newPos.x = 0.f - m_BoundsSpecialZomb.width;
		newPos.y = m_Window.y / 8*5;
	}
	if (random == 16)
	{
		newPos.x = 0.f - m_BoundsSpecialZomb.width;
		newPos.y = m_Window.y / 8*7;
	}



	return newPos;
}

Rectf SpecialZomb::GetBounds()
{
	return m_BoundsSpecialZomb;
}

bool SpecialZomb::IsHitByAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid)
{
	const Point2f bottomLeft{ m_BoundsSpecialZomb.left,m_BoundsSpecialZomb.bottom };
	const Point2f bottomRight{ m_BoundsSpecialZomb.left + m_BoundsSpecialZomb.width,m_BoundsSpecialZomb.bottom };
	const Point2f topLeft{ m_BoundsSpecialZomb.left,m_BoundsSpecialZomb.bottom + m_BoundsSpecialZomb.height };
	const Point2f topRight{ m_BoundsSpecialZomb.left + m_BoundsSpecialZomb.width,m_BoundsSpecialZomb.bottom + m_BoundsSpecialZomb.height };

	bool isHit{};
	const float distanceBottomLeft{ utils::GetDistance(posAsteroid.x,posAsteroid.y,bottomLeft.x,bottomLeft.y) };
	const float distanceBottomRight{ utils::GetDistance(posAsteroid.x,posAsteroid.y,bottomRight.x,bottomRight.y) };
	const float distancetopLeft{ utils::GetDistance(posAsteroid.x,posAsteroid.y,topLeft.x,topLeft.y) };
	const float distancetopRight{ utils::GetDistance(posAsteroid.x,posAsteroid.y,topRight.x,topRight.y) };

	if (distanceBottomLeft <= radius)
	{
		if (stateOfAsteroid == true)isHit = true;
		else isHit = false;
	}
	else if (distanceBottomRight <= radius)
	{
		if (stateOfAsteroid == true)isHit = true;
		else isHit = false;
	}
	else if (distancetopLeft <= radius)
	{
		if (stateOfAsteroid == true)isHit = true;
		else isHit = false;
	}
	else if (distancetopRight <= radius)
	{
		if (stateOfAsteroid == true)isHit = true;
		else isHit = false;
	}
	else
	{
		isHit = false;
	}

	return isHit;
}

