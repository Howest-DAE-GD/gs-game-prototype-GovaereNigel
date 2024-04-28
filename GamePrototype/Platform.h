#pragma once
#include <vector>
class Platform
{
public:
	Platform(Point2f& pos, float width, float height);
	void Draw();
	void Update(float speedIncrease);
	Point2f GetPosition() const;
	Rectf GetBounds() const;
	float GetHeight()const;
	void GetRandomHeight(float previousPlatformHeight,float startHeight);
	void ResetPosition(Rectf platform);

private:
	Rectf m_BoundsPlatform;
	static const int m_SIZEPLATFORM{4};
	std::vector<Point2f>m_WallPlatform;


};

