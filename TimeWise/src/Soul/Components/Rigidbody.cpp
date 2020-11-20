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
		// Apply gravity
		m_Collider->ApplyForce(sf::Vector2f(0.0f, m_Collider->GetMass() * dt * 0.0098f));

		// TODO: Find better method for calculating surface area perpendicular to velocity?
		// Apply drag
		sf::Vector2f vSquared(m_AffectedEntity->GetVelocity().x * m_AffectedEntity->GetVelocity().x, m_AffectedEntity->GetVelocity().y * m_AffectedEntity->GetVelocity().y);
		float cDrag = 0.5f * 0.7f * 0.001f;
		m_Collider->ApplyForce(-vSquared * cDrag * m_Collider->GetRadius() * dt);
	}

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}
}