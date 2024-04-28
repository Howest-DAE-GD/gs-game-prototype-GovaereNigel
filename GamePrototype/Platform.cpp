#include "pch.h"
#include "Platform.h"
#include "utils.h"

Platform::Platform(Point2f& pos,float width, float height)
	:m_BoundsPlatform{ pos.x,pos.y,width,height}
	,m_WallPlatform{ Point2f{pos.x,pos.y},Point2f{pos.x,pos.y + height},Point2f{pos.x + width,pos.y},Point2f{pos.x+width,pos.y+height}}
{
}

void Platform::Draw()
{
	utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
	utils::DrawPolygon(m_WallPlatform);

}

void Platform::Update(float speedIncrease)
{
	m_BoundsPlatform.left -= speedIncrease;
	for (int idx{}; idx < m_SIZEPLATFORM; ++idx)
	{
		m_WallPlatform[idx].x -= speedIncrease;
	}
}

Point2f Platform::GetPosition() const
{
	return Point2f{m_BoundsPlatform.left,m_BoundsPlatform.bottom};
}

Rectf Platform::GetBounds() const
{
	return m_BoundsPlatform;
}

float Platform::GetHeight() const
{
	return m_BoundsPlatform.height;
}

void Platform::GetRandomHeight(float previousPlatformHeight, float startHeight)
{
	const float distance{100.f};
	int random{};
	
		if (previousPlatformHeight == (startHeight - distance / 2))
		{
			random = rand() % 3 + 1;
		}
		else if (previousPlatformHeight == (startHeight - distance))
		{
			random = rand() % 2 + 2;
		}
		else if (previousPlatformHeight == (startHeight + distance / 2))
		{
			random = rand() % 3 + 0;
		}
		else if (previousPlatformHeight == (startHeight + distance))
		{
			random = rand() % 2 + 0;
		}
		else
		{
			random = rand() % 4 + 0;
		}
	
		if (random == 4)
		{
			m_BoundsPlatform.height = previousPlatformHeight + distance;
			m_WallPlatform[1].y = previousPlatformHeight + distance;
			m_WallPlatform[3].y = previousPlatformHeight + distance;
		}
		else if (random == 3)
		{
			m_BoundsPlatform.height = previousPlatformHeight + distance / 2;
			m_WallPlatform[1].y = previousPlatformHeight + distance / 2;
			m_WallPlatform[3].y = previousPlatformHeight + distance / 2;

		}
		else if (random == 2)
		{
			m_BoundsPlatform.height = previousPlatformHeight;
			m_WallPlatform[1].y = previousPlatformHeight;
			m_WallPlatform[3].y = previousPlatformHeight;

		}
		else if (random == 1)
		{
			m_BoundsPlatform.height = previousPlatformHeight - distance / 2;
			m_WallPlatform[1].y = previousPlatformHeight - distance / 2;
			m_WallPlatform[3].y = previousPlatformHeight - distance / 2;

		}
		else
		{
			m_BoundsPlatform.height = previousPlatformHeight - distance;
			m_WallPlatform[1].y = previousPlatformHeight - distance;
			m_WallPlatform[3].y = previousPlatformHeight - distance;

		}
}

void Platform::ResetPosition(Rectf platform)
{
	m_BoundsPlatform.left = platform.left + platform.width;
	m_WallPlatform[0].x = platform.left + platform.width;
	m_WallPlatform[1].x = platform.left + platform.width;
	m_WallPlatform[2].x = platform.left + platform.width*2;
	m_WallPlatform[3].x = platform.left + platform.width*2;

}


