#pragma once
class SpecialZomb
{
public:
	SpecialZomb(float windowWidth,float windowHeight);
	void Draw();
	void Update(float elapsedSec, Point2f& m_PosPlayer,float speed);
	void ResetPos();
	Point2f GetRandomStartPos();
	Rectf GetBounds();
	bool IsHitByAsteroid(Point2f& posAsteroid, float radius, bool stateOfAsteroid);

private:
	Point2f m_Window;
	Point2f m_PosSpecialZomb;
	Rectf m_BoundsSpecialZomb;
};

