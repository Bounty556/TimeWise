#include "PhysicsSystem.h"

#include <Entities/Entity.h>

namespace Soul
{
	PhysicsSystem::PhysicsSystem(unsigned int maxColliders) :
		m_Components(maxColliders)
	{

	}

	void PhysicsSystem::Update(float dt, Context& context)
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->Update(dt, context);

			for (unsigned int j = i + 1; j < m_Components.Length(); ++j)
			{
				sf::FloatRect a = m_Components[i]->GetBounds();
				a.left += m_Components[i]->GetEntity()->getPosition().x;
				a.top += m_Components[i]->GetEntity()->getPosition().y;
				sf::FloatRect b = m_Components[j]->GetBounds();
				b.left += m_Components[j]->GetEntity()->getPosition().x;
				b.top += m_Components[j]->GetEntity()->getPosition().y;

				if (a.intersects(b))
				{
					m_Components[i]->HandleCollision(dt, context);
					m_Components[j]->HandleCollision(dt, context);
				}
			}
		}
		// TODO: Oriented AABB collision checks
	}
}