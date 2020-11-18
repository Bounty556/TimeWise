#include "Rigidbody.h"

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity, bool isSolid, float bounciness, float friction) :
		CollisionHandler(entity),
		m_IsSolid(isSolid),
		m_Bounciness(bounciness),
		m_Friction(friction)
	{

	}

	void Rigidbody::HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		m_AffectedEntity->move(correction);
		m_AffectedEntity->SetVelocity(0.0f, 0.0f);
	}

	void Rigidbody::Update(float dt)
	{
		// Apply gravity
		m_AffectedEntity->Accelerate(0.0f, 0.0005f * dt);

		// Apply drag
		m_AffectedEntity->SetVelocity((1.0f - (.0005f * dt)) * m_AffectedEntity->GetVelocity());
	}

	bool Rigidbody::IsSolid() const
	{
		return m_IsSolid;
	}

	float Rigidbody::GetBounciness() const
	{
		return m_Bounciness;
	}

	float Rigidbody::GetFriction() const
	{
		return m_Friction;
	}

	void Rigidbody::SetIsSolid(bool isSolid)
	{
		m_IsSolid = isSolid;
	}

	void Rigidbody::SetBounciness(float bounciness)
	{
		m_Bounciness = bounciness;
	}

	void Rigidbody::SetFriction(float friction)
	{
		m_Friction = friction;
	}

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}
}