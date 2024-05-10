#include "pch.h"
#include "Zomb.h"
#include "utils.h"
#include <iostream>


Zomb::Zomb(Point2f& window, float width, float height)
	:m_TypeOfZomb{GetRandomType()}
	,m_Window{window.x,window.y}
	,m_Inverse{false}
	,m_Direction{false}
	,m_Width{width}
	,m_Height{height}
	,m_StateOfSpeed{false}
	,m_Pos{}
    ,m_Bounds{m_Pos.x,m_Pos.y,width,height}
	,m_Health{1}
	,m_Damage{1}
{
	ResetPos();
}

void Zomb::Draw()
{
	utils::SetColor(Color4f{ 0.f,0.8f,0.f,1.f });
	utils::FillRect(m_Bounds);
}

void Zomb::Update(float elapsedSec,float speedX,float speedY)
{
	//const float speedX{ 60.f * elapsedSec };
	//const float speedY{ 120.f * elapsedSec };
	if (m_TypeOfZomb == 0)
	{
		if (m_Inverse == true)
		{
			if (m_Direction == false)
			{
				if (m_Pos.x < m_Window.x + m_Width)
				{
					if (m_StateOfSpeed == true)
					{
						if (m_Pos.y < m_Window.y - m_Height)
						{
							m_Pos.y += speedY;
						}
						else
						{
							m_StateOfSpeed = false;
						}
					}
					if (m_StateOfSpeed == false)
					{
						if (m_Pos.y > 0.f)
						{
							m_Pos.y -= speedY;
						}
						else
						{
							m_StateOfSpeed = true;
						}
					}
				}
				else
				{
					ResetPos();
				}

				m_Pos.x += speedX;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
			}
			else
			{
				if (m_Pos.x > 0.f - m_Width)
				{
					if (m_StateOfSpeed == true)
					{
						if (m_Pos.y < m_Window.y - m_Height)
						{
							m_Pos.y += speedY;
						}
						else
						{
							m_StateOfSpeed = false;
						}
					}
					if (m_StateOfSpeed == false)
					{
						if (m_Pos.y > 0.f)
						{
							m_Pos.y -= speedY;
						}
						else
						{
							m_StateOfSpeed = true;
						}
					}
				}
				else
				{
					ResetPos();
				}

				m_Pos.x -= speedX;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
			}
		}
		else
		{
			
			if (m_Direction == false)
			{
				if (m_Pos.x < m_Window.x + m_Width)
				{
					if (m_StateOfSpeed == true)
					{
						if (m_Pos.y < m_Window.y - m_Height)
						{
							m_Pos.y += speedY;
						}
						else
						{
							m_StateOfSpeed = false;
						}
					}
					if (m_StateOfSpeed == false)
					{
						if (m_Pos.y > 0.f)
						{
							m_Pos.y -= speedY;
						}
						else
						{
							m_StateOfSpeed = true;
						}
					}
				}
				else
				{
					ResetPos();
				}

				m_Pos.x += speedX;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
			}
			else
			{
				if (m_Pos.x > 0.f - m_Width)
				{
					if (m_StateOfSpeed == true)
					{
						if (m_Pos.y < m_Window.y - m_Height)
						{
							m_Pos.y += speedY;
						}
						else
						{
							m_StateOfSpeed = false;
						}
					}
					if (m_StateOfSpeed == false)
					{
						if (m_Pos.y > 0.f)
						{
							m_Pos.y -= speedY;
						}
						else
						{
							m_StateOfSpeed = true;
						}
					}
				}
				else
				{
					ResetPos();
				}

				m_Pos.x -= speedX;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
			}
		}
		
	}
	if (m_TypeOfZomb == 1)
	{
		if (m_Direction == false)
		{
			const Point2f path1{ m_Pos.x,m_Window.y * 7 / 8 };
			const Point2f path2{ path1.x + 10.f,m_Window.y * 6 / 8 };
			const Point2f path3{ path1.x,m_Window.y * 5 / 8 };
			const Point2f path4{ path1.x,m_Window.y * 4 / 8 };
			const Point2f path5{ path1.x + 10.f,m_Window.y * 3 / 8 };
			const Point2f path6{ path1.x,m_Window.y * 2 / 8 };
			const Point2f path7{ path1.x, 0.f };


			if (m_Inverse == true)
			{

				if (m_Pos.y > path1.y)
				{
					m_Pos.y -= speedY;
				}
				else if (m_Pos.y > path2.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y > path3.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y > path4.y)
				{
					m_Pos.y -= speedY;
				}
				else if (m_Pos.y > path5.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y > path6.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y > path7.y)
				{
					m_Pos.y -= speedY;
				}
				else
				{
					ResetPos();
				}

				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;


			}
			else
			{


				if (m_Pos.y > path1.y)
				{
					m_Pos.y -= speedY;
				}
				else if (m_Pos.y > path2.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y > path3.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y > path4.y)
				{
					m_Pos.y -= speedY;
				}
				else if (m_Pos.y > path5.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y > path6.y)
				{
					m_Pos.y -= speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y > path7.y)
				{
					m_Pos.y -= speedY;
				}
				else
				{
					ResetPos();
				}

				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;


			}
		}
		else
		{
			const Point2f path1{ m_Pos.x,m_Window.y * 1 / 8 };
			const Point2f path2{ path1.x + 10.f,m_Window.y * 2 / 8 };
			const Point2f path3{ path1.x,m_Window.y * 3 / 8 };
			const Point2f path4{ path1.x,m_Window.y * 4 / 8 };
			const Point2f path5{ path1.x + 10.f,m_Window.y * 5 / 8 };
			const Point2f path6{ path1.x,m_Window.y * 6 / 8 };
			const Point2f path7{ path1.x, m_Window.y};

			if (m_Inverse == true)
			{
				if (m_Pos.y < path1.y)
				{
					m_Pos.y += speedY;
				}
				else if (m_Pos.y < path2.y)
				{
					m_Pos.y += speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y < path3.y)
				{
					m_Pos.y += speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y < path4.y)
				{
					m_Pos.y += speedY;
				}
				else if (m_Pos.y < path5.y)
				{
					m_Pos.y += speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y < path6.y)
				{
					m_Pos.y += speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y < path7.y)
				{
					m_Pos.y += speedY;
				}
				else
				{
					ResetPos();
				}

				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;


			}
			else
			{


				if (m_Pos.y < path1.y)
				{
					m_Pos.y += speedY;
				}
				else if (m_Pos.y < path2.y)
				{
					m_Pos.y += speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y < path3.y)
				{
					m_Pos.y += speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y < path4.y)
				{
					m_Pos.y += speedY;
				}
				else if (m_Pos.y < path5.y)
				{
					m_Pos.y += speedY;
					m_Pos.x -= speedY;
				}
				else if (m_Pos.y < path6.y)
				{
					m_Pos.y += speedY;
					m_Pos.x += speedY;
				}
				else if (m_Pos.y < path7.y)
				{
					m_Pos.y += speedY;
				}
				else
				{
					ResetPos();
				}

				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;


			}

		}
	}
}

void Zomb::ResetPos()
{
	m_TypeOfZomb = GetRandomType();
	Point2f pos{};
	if (m_TypeOfZomb == 0)
	{
		int randomDirection{rand()%2+0};
		if (randomDirection == 0) m_Direction = false;
		else m_Direction = true;

		int random{ rand() % 2 + 0 };
		if (random == 0)
		{
			if (m_Direction == false)
			{
				m_Pos.x = 0.f;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
				m_StateOfSpeed = false;
			}
			else
			{
				m_Pos.x = m_Window.x;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
				m_StateOfSpeed = false;
			}
		}
		else
		{
			if (m_Direction == false)
			{
				m_Pos.x = 0.f;
				m_Pos.y = 0.f - m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
				m_StateOfSpeed = true;
			}
			else
			{
				m_Pos.x = m_Window.x;
				m_Pos.y = 0.f - m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
				m_StateOfSpeed = true;

			}
		}
	}
	if (m_TypeOfZomb == 1)
	{
		int randomDirection{ rand() % 2 + 0 };
		if (randomDirection == 0) m_Direction = false;
		else m_Direction = true;

		int random{rand()%8+0};
		if (random == 0)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
			else
			{
				m_Pos.x = m_Window.x / 8;
				m_Pos.y = 0.f-m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
		}
		if (random == 1)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 3 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
			else
			{
				m_Pos.x = m_Window.x * 3 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;

			}
		}
		if (random == 2)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 5 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
			else
			{
				m_Pos.x = m_Window.x * 5 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}

		}
		if (random == 3)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 7 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
			else
			{
				m_Pos.x = m_Window.x * 7 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = true;
			}
		}
		if (random == 4)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
			else
			{
				m_Pos.x = m_Window.x / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
		}
		if (random == 5)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 3 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
			else
			{
				m_Pos.x = m_Window.x * 3 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
		}
		if (random == 6)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 5 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
			else
			{
				m_Pos.x = m_Window.x * 5 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
		}
		if (random == 7)
		{
			if (m_Direction == false)
			{
				m_Pos.x = m_Window.x * 7 / 8;
				m_Pos.y = m_Window.y;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
			else
			{
				m_Pos.x = m_Window.x * 7 / 8;
				m_Pos.y = 0.f- m_Height;
				m_Bounds.left = m_Pos.x;
				m_Bounds.bottom = m_Pos.y;
				m_Inverse = false;
			}
		}

	}
}

int Zomb::GetRandomType()
{
	int random{ rand() % 2 + 0 }; 

	return random;
}

bool Zomb::IsHitByAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid)
{
	const Point2f bottomLeft{m_Bounds.left,m_Bounds.bottom};
	const Point2f bottomRight{ m_Bounds.left+m_Bounds.width,m_Bounds.bottom };
	const Point2f topLeft{ m_Bounds.left,m_Bounds.bottom+m_Bounds.height};
	const Point2f topRight{ m_Bounds.left+m_Bounds.width,m_Bounds.bottom+m_Bounds.height};

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

Rectf Zomb::GetBounds()
{
	return m_Bounds;
}

int Zomb::GetDamage()
{
	return m_Damage;
}
