#include "Rigidbody.h"

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity, bool isSolid, float bounciness, float friction) :
		CollisionHandler(entity)
	{

	}

	void Rigidbody::HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		if (collider.IsSolid())
		{
			m_AffectedEntity->move(correction);
			m_AffectedEntity->SetVelocity(0.0f, 0.0f);
		}
	}

	void Rigidbody::Update(float dt)
	{
		// TODO: Calculate actual drag and gravity

		// Apply gravity
		m_AffectedEntity->Accelerate(0.0f, 0.0005f * dt);

		// Apply drag
		m_AffectedEntity->SetVelocity((1.0f - (.0005f * dt)) * m_AffectedEntity->GetVelocity());
	}

	

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}
}