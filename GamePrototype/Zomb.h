#pragma once
class Zomb
{
public:
	Zomb(Point2f& window,float width, float height);
	void Draw();
	void Update(float elapsedSec);
	void ResetPos();
	int GetRandomType();
	bool IsHitByAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid);


private:
	int m_TypeOfZomb;
	Point2f m_Window;
	bool m_Inverse;
	bool m_Direction;
	float m_Width;
	float m_Height;
	bool m_StateOfSpeed;
	Point2f m_Pos;
	Rectf m_Bounds;
	int m_Health;
	int m_Damage;
};

