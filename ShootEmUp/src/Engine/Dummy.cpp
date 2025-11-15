#include "pch.h"
#include "Dummy.h"


void DummyEntity::OnUpdate()
{
	m_pText->SetPosition(GetPosition());
}

void DummyEntity::OnDraw(MyWindow* pWindow)
{
	pWindow->Draw(m_pText);
}

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "AAAAAAAAAAAAAAAA" << std::endl;
}