#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(Point2f& pos)
	:m_BoundsPlayer{pos.x,pos.y,40.f,40.f}
{
}

void Player::Draw()
{
	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::FillRect(m_BoundsPlayer);
}

void Player::Update()
{
}

bool Player::HitPlatform()
{
	return false;
}

