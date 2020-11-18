#include "CollisionHandler.h"

namespace Soul
{
	CollisionHandler::CollisionHandler(Entity* entity) :
		Component(entity),
		m_Collider(nullptr)
	{

	}

	CollisionHandler::~CollisionHandler()
	{

	}

	void CollisionHandler::SetCollider(Collider* collider)
	{
		m_Collider = collider;
		m_Collider->SetHandler(this);
	}
}