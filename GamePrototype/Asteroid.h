#pragma once
class Asteroid
{
public:
	Asteroid(float radius,Point2f& window);
	void Draw();
	void Update(float elapsedSec);
	Point2f GetRandomPosition();
	Point2f GetPosition();
	float GetRadius();
	bool GetStateOfAsteroid();
	bool HasAHeart();
	int GetDamage();
	void ResetAsteroid();


private:
	float m_Radius;
	Point2f m_Window;
	Point2f m_Position;
	int m_Damage;

	float m_FakeRadius;
	bool m_State;
	float m_Timer;

	bool m_HasHeart;
};

