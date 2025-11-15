#include "pch.h"


namespace Utils 
{
    bool Normalize(Vect2& vector)
    {
        float magnitude = std::sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y);

		if (magnitude != 0)
		{
			vector.m_x /= magnitude;
			vector.m_y /= magnitude;
		
			return true;
		}

		return false;
    }

	float GetDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return std::sqrt(x * x + y * y);
	}
}