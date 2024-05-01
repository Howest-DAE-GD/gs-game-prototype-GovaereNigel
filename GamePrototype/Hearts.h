#pragma once
class Hearts
{
public:
	Hearts(Point2f& pos);
	void Draw();
	void SetPosition(Point2f& pos);
	int GetHealth()const;
	float GetRadius();

private:
	Point2f m_PositionHeart;
	int m_Health;
	float m_Radius;
};

