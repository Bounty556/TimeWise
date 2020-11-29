#include "Rigidbody.h"

#include <Utility/Math.h>

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity) :
		CollisionHandler(entity, "Rigidbody"),
		m_FinalForce(0.0f, 0.0f)
	{

	}

	void Rigidbody::AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		if (collider.IsSolid())
		{
			m_AffectedEntity->move(correction);
		
			sf::Vector2f normalForce = Math::Project((m_AffectedEntity->GetVelocity() - collider.GetVelocity()) * m_Collider->GetMass(), correction);
			sf::Vector2f rejectionForce = (m_AffectedEntity->GetVelocity() - collider.GetVelocity()) * m_Collider->GetMass() - normalForce;

			sf::Vector2f finalForce(-normalForce);

			// Add bounce force
			finalForce -= normalForce * Math::Max(m_Collider->GetBounciness() + collider.GetBounciness() / 2.0f, 0.0f);

			// Add frictional force
			sf::Vector2f frictionalForce = Math::Magnitude(normalForce * (m_Collider->GetFriction() * collider.GetFriction() / 2.0f)) * Math::Normalize(rejectionForce);
			if (Math::Magnitude(frictionalForce) > Math::Magnitude(rejectionForce))
			{
				finalForce -= rejectionForce;
			}
			else
			{
				finalForce -= frictionalForce;
			}

			m_FinalForce += finalForce;
		}
	}

	void Rigidbody::ResolveCollisions()
	{
		m_Collider->ApplyForce(m_FinalForce);
		m_FinalForce = sf::Vector2f(0.0f, 0.0f);
	}

	void Rigidbody::Update(float dt)
	{
		// Apply gravity
		sf::Vector2f finalForce(0.0f, m_Collider->GetMass() * 9.8f);

		// Apply drag
		// TODO: Find better method for calculating surface area perpendicular to velocity?
		sf::Vector2f direction = Math::Normalize(m_AffectedEntity->GetVelocity());
		float vSquared = Math::Dot(m_AffectedEntity->GetVelocity(), m_AffectedEntity->GetVelocity());
		sf::Vector2f dragVector = direction * vSquared;
		float cDrag = 0.5f * 0.5f;
		finalForce += -dragVector * cDrag * m_Collider->GetRadius();

		m_Collider->ApplyForce(finalForce * dt * 0.001f);
	}
}