#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(Point2f& pos)
	:m_BoundsPlayer{pos.x,pos.y,25.f,25.f}
	, m_Health{4}
	, m_pTexture{ new Texture{"player.png"}}
	,m_FrameNr{0}
{
}

Player::~Player()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Player::Draw()
{
	const int totalSprites{14};
	if (m_FrameNr < totalSprites)
	{
		m_FrameNr++;
	}
	else
	{
		m_FrameNr = 0;
	}
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::FillRect(m_BoundsPlayer);
}

void Player::Update(float elapsedSec, const Uint8* pStates)
{
	const float speed{ elapsedSec * 150.f };


		if (pStates[SDL_SCANCODE_DOWN])
		{
			m_BoundsPlayer.bottom -= speed;
		}
		if (pStates[SDL_SCANCODE_UP])
		{
			m_BoundsPlayer.bottom += speed;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_BoundsPlayer.left -= speed;
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_BoundsPlayer.left += speed;
		}
	
}

bool Player::IsHitAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid)
{
	const Point2f bottomLeft{ m_BoundsPlayer.left,m_BoundsPlayer.bottom };
	const Point2f bottomRight{ m_BoundsPlayer.left + m_BoundsPlayer.width,m_BoundsPlayer.bottom };
	const Point2f topLeft{ m_BoundsPlayer.left,m_BoundsPlayer.bottom + m_BoundsPlayer.height };
	const Point2f topRight{ m_BoundsPlayer.left + m_BoundsPlayer.width,m_BoundsPlayer.bottom + m_BoundsPlayer.height };

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

bool Player::IshHitZomb(Rectf boundsZomb)
{
	bool value{};
	if ((boundsZomb.bottom >= m_BoundsPlayer.bottom || (boundsZomb.bottom + boundsZomb.height) >= m_BoundsPlayer.bottom) && (boundsZomb.bottom <= (m_BoundsPlayer.bottom + m_BoundsPlayer.height) || (boundsZomb.bottom + boundsZomb.height) <= (m_BoundsPlayer.bottom + m_BoundsPlayer.height))
		&& (boundsZomb.left >= m_BoundsPlayer.left || (boundsZomb.left + boundsZomb.width) >= m_BoundsPlayer.left) && (boundsZomb.left <= (m_BoundsPlayer.left + m_BoundsPlayer.width) || (boundsZomb.left + boundsZomb.width) <= (m_BoundsPlayer.left + m_BoundsPlayer.width)))
	{
		value = true;
	}
	return value;
}

bool Player::IsHitHeart(Point2f pos, float radius)
{
	const Point2f bottomLeft{ m_BoundsPlayer.left,m_BoundsPlayer.bottom };
	const Point2f bottomRight{ m_BoundsPlayer.left + m_BoundsPlayer.width,m_BoundsPlayer.bottom };
	const Point2f topLeft{ m_BoundsPlayer.left,m_BoundsPlayer.bottom + m_BoundsPlayer.height };
	const Point2f topRight{ m_BoundsPlayer.left + m_BoundsPlayer.width,m_BoundsPlayer.bottom + m_BoundsPlayer.height };

	bool isHit{};
	const float distanceBottomLeft{ utils::GetDistance(pos.x,pos.y,bottomLeft.x,bottomLeft.y) };
	const float distanceBottomRight{ utils::GetDistance(pos.x,pos.y,bottomRight.x,bottomRight.y) };
	const float distancetopLeft{ utils::GetDistance(pos.x,pos.y,topLeft.x,topLeft.y) };
	const float distancetopRight{ utils::GetDistance(pos.x,pos.y,topRight.x,topRight.y) };

	if (distanceBottomLeft <= radius)
	{
		isHit = true;
	}
	else if (distanceBottomRight <= radius)
	{
		isHit = true;
	}
	else if (distancetopLeft <= radius)
	{
		isHit = true;
		
	}
	else if (distancetopRight <= radius)
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}

	return isHit;
}

bool Player::IsHitSpecialZomb(Rectf boundsSpecialZomb)
{
	bool value{};
	if ((boundsSpecialZomb.bottom >= m_BoundsPlayer.bottom || (boundsSpecialZomb.bottom + boundsSpecialZomb.height) >= m_BoundsPlayer.bottom) && (boundsSpecialZomb.bottom <= (m_BoundsPlayer.bottom + m_BoundsPlayer.height) || (boundsSpecialZomb.bottom + boundsSpecialZomb.height) <= (m_BoundsPlayer.bottom + m_BoundsPlayer.height))
		&& (boundsSpecialZomb.left >= m_BoundsPlayer.left || (boundsSpecialZomb.left + boundsSpecialZomb.width) >= m_BoundsPlayer.left) && (boundsSpecialZomb.left <= (m_BoundsPlayer.left + m_BoundsPlayer.width) || (boundsSpecialZomb.left + boundsSpecialZomb.width) <= (m_BoundsPlayer.left + m_BoundsPlayer.width)))
	{
		value = true;
	}
	return value;
}


int Player::GetHealth()
{
	return m_Health;
}

void Player::LoseHealth(int damage)
{
	m_Health -= damage;
}

void Player::ReceiveHealth(int health)
{
	m_Health += 1;
}

Point2f Player::GetPosition()
{
	const Point2f pos{ m_BoundsPlayer.left,m_BoundsPlayer.bottom };
	return pos;
}





