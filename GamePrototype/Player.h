#pragma once
class Player
{
public:
	Player(Point2f& pos);
	void Draw();
	void Update();
	bool HitPlatform();

private:
	Rectf m_BoundsPlayer;

};

