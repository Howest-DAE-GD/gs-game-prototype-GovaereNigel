#pragma once
#include <Texture.h>
class Player
{
public:
	Player(Point2f& pos, float windowWidth, float windowHeight);
	~Player();
	void Draw();
	void Update(float elapsedSec, const Uint8* pStates);
	bool IsHitAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid);
	bool IshHitZomb(Rectf boundsZomb);
	bool IsHitHeart(Point2f pos, float radius);
	bool IsHitSpecialZomb(Rectf boundsSpecialZomb);
	int GetHealth();
	void LoseHealth(int damage);
	void ReceiveHealth(int health);
	Point2f GetPosition();
private:
	Rectf m_BoundsPlayer;
	int m_Health;
	Texture* m_pTexture;
	int m_FrameNr;
	Point2f m_Range;
};
