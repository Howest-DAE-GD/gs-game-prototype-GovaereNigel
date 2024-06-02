#pragma once
class Player;
class Healthbar
{
public:
	Healthbar(int health, Point2f& window);
	void Draw();
	void Update(Player* player);
private:
	Point2f m_Window;
	int m_Health;
};

