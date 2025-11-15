#include "pch.h"
#include "Caow.h"

void Caow::OnUpdate()
{
	if (GetScene()->m_getCaowed)
	{
		if (GetPosition().m_x > 1700)
			SetDirection(-1, 0, 200.f);
		else if (GetPosition().m_x <= 1700)
		{
			m_goback = true;
			GetScene()->m_getCaowed = false;
		}
	}
	else {
		if (m_goback)
			SetDirection(1, 0, 200.f);
		if (GetPosition().m_x > 2200)
		{
			SetDirection(0, 0, 0);
			m_goback = false;
		}
	}


}
