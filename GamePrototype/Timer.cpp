#include "pch.h"
#include "Timer.h"
#include "Texture.h"


static const int m_TOTALSPRITES{10};
Texture* m_SpriteSheet[m_TOTALSPRITES];

Timer::Timer(const Point2f& position, Point2f& window)
	:m_Window{window}
,m_FirstPosition{position.x-10.f,position.y}
, m_SecondPosition{ position.x +10.f,position.y }
, m_FirstNumber{0}
, m_SecondNumber{0}
, m_Scale{1.f}
{
	m_SpriteSheet[0] = new Texture{"0.png"};
	m_SpriteSheet[1] = new Texture{ "1.png" };
	m_SpriteSheet[2] = new Texture{ "2.png" };
	m_SpriteSheet[3] = new Texture{ "3.png" };
	m_SpriteSheet[4] = new Texture{ "4.png" };
	m_SpriteSheet[5] = new Texture{ "5.png" };
	m_SpriteSheet[6] = new Texture{ "6.png" };
	m_SpriteSheet[7] = new Texture{ "7.png" };
	m_SpriteSheet[8] = new Texture{ "8.png" };
	m_SpriteSheet[9] = new Texture{ "9.png" };


}

Timer::~Timer()
{
	for (int idx{}; idx < m_TOTALSPRITES; ++idx)
	{
		delete m_SpriteSheet[idx];
		m_SpriteSheet[idx] = nullptr;
	}
}

void Timer::Draw(bool stateEndScreen)
{
	const float scaleChange{0.1f};
	const float totalScale{3.f};
	if (stateEndScreen == true)
	{
		if (m_Scale < totalScale)
		{
			m_Scale += scaleChange; 
		}
	}

	for (int idx{}; idx < m_TOTALSPRITES; ++idx)
	{
		if (m_FirstNumber == idx) m_SpriteSheet[idx]->Draw(Rectf{m_FirstPosition.x,m_FirstPosition.y,m_SpriteSheet[idx]->GetWidth()*m_Scale,m_SpriteSheet[idx]->GetHeight() * m_Scale });
	}
	for (int idx{}; idx < m_TOTALSPRITES; ++idx)
	{
		if (m_SecondNumber == idx) m_SpriteSheet[idx]->Draw(Rectf{ m_SecondPosition.x,m_SecondPosition.y,m_SpriteSheet[idx]->GetWidth() * m_Scale,m_SpriteSheet[idx]->GetHeight() * m_Scale });
	}
}

void Timer::Update(float elapsedSec, float timer, bool stateEndScreen)
{
	if (timer < 1)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 0;
	}
	else if (timer < 2)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 1;
	}
	else if (timer < 3)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 2;
	}
	else if (timer < 4)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 3;
	}
	else if (timer < 5)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 4;
	}
	else if (timer < 6)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 5;
	}
	else if (timer < 7)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 6;
	}
	else if (timer < 8)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 7;
	}
	else if (timer < 9)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 8;
	}
	else if (timer < 10)
	{
		m_FirstNumber = 0;
		m_SecondNumber = 9;
	}
	else if (timer < 11)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 0;
	}
	else if (timer < 12)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 1;
	}
	else if (timer < 13)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 2;
	}
	else if (timer < 14)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 3;
	}
	else if (timer < 15)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 4;
	}
	else if (timer < 16)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 5;
	}
	else if (timer < 17)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 6;
	}
	else if (timer < 18)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 7;
	}
	else if (timer < 19)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 8;
	}
	else if (timer < 20)
	{
		m_FirstNumber = 1;
		m_SecondNumber = 9;
	}
	else if (timer < 21)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 0;
	}
	else if (timer < 22)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 1;
	}
	else if (timer < 23)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 2;
	}
	else if (timer < 24)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 3;
	}
	else if (timer < 25)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 4;
	}
	else if (timer < 26)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 5;
	}
	else if (timer < 27)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 6;
	}
	else if (timer < 28)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 7;
	}
	else if (timer < 29)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 8;
	}
	else if (timer < 30)
	{
		m_FirstNumber = 2;
		m_SecondNumber = 9;
	}
	else if (timer < 31)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 0;
	}
	else if (timer < 32)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 1;
	}
	else if (timer < 33)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 2;
	}
	else if (timer < 34)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 3;
	}
	else if (timer < 35)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 4;
	}
	else if (timer < 36)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 5;
	}
	else if (timer < 37)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 6;
	}
	else if (timer < 38)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 7;
	}
	else if (timer < 39)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 8;
	}
	else if (timer < 40)
	{
		m_FirstNumber = 3;
		m_SecondNumber = 9;
	}
	else if (timer < 41)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 0;
	}
	else if (timer < 42)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 1;
	}
	else if (timer < 43)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 2;
	}
	else if (timer < 44)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 3;
	}
	else if (timer < 45)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 4;
	}
	else if (timer < 46)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 5;
	}
	else if (timer < 47)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 6;
	}
	else if (timer < 48)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 7;
	}
	else if (timer < 49)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 8;
	}
	else if (timer < 50)
	{
		m_FirstNumber = 4;
		m_SecondNumber = 9;
	}
	else if (timer < 51)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 0;
	}
	else if (timer < 52)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 1;
	}
	else if (timer < 53)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 2;
	}
	else if (timer < 54)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 3;
	}
	else if (timer < 55)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 4;
	}
	else if (timer < 56)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 5;
	}
	else if (timer < 57)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 6;
	}
	else if (timer < 58)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 7;
	}
	else if (timer < 59)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 8;
	}
	else if (timer < 60)
	{
		m_FirstNumber = 5;
		m_SecondNumber = 9;
	}
	else
	{
		m_FirstNumber = 6;
		m_SecondNumber = 0;
	}

	if (stateEndScreen == true)
	{
		float speed{elapsedSec*100.f};
		const Point2f GoToPos1{m_Window.x/2-(10.f*m_Scale),m_Window.y/2};
		const Point2f GoToPos2{ m_Window.x / 2 +(10.f * m_Scale),m_Window.y / 2 };
		if (m_FirstPosition.x > GoToPos1.x)
		{
			m_FirstPosition.x -= speed;
		}
		else m_FirstPosition.x = GoToPos1.x;
		if (m_FirstPosition.y > GoToPos1.y)
		{
			m_FirstPosition.y -= speed;
		}
		else m_FirstPosition.y = GoToPos1.y;

		if (m_SecondPosition.x > GoToPos2.x)
		{
			m_SecondPosition.x -= speed;
		}
		else m_SecondPosition.x = GoToPos2.x;
		if (m_SecondPosition.y > GoToPos2.y)
		{
			m_SecondPosition.y -= speed;
		}
		else m_SecondPosition.y = GoToPos2.y;
	}

}
