#pragma once
class Player
{
public:
	Player(Point2f& pos);
	void Draw();
	void Update(float elapsedSec, const Uint8* pStates);
	bool IsHitAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid);
	bool IshHitZomb(Rectf boundsZomb);
	bool IsHitHeart(Point2f pos, float radius);
	int GetHealth();
	void LoseHealth(int damage);
	void ReceiveHealth(int health);

private:
	Rectf m_BoundsPlayer;
	int m_Health;
};
