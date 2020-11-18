#pragma once

#include <Components/Component.h>
#include <Components/Collider.h>
#include <Entities/Entity.h>

namespace Soul
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody(Entity* entity, bool isSolid, float bounciness, float friction);

		/*
		To be called from the entity's collider component. Sets Entity's velocity appropriately
		based on collision data.
		*/
		void HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider);

		// Getters

		bool IsSolid() const;
		float GetBounciness() const;
		float GetFriction() const;

		// Setters

		void SetIsSolid(bool isSolid);
		void SetBounciness(float bounciness);
		void SetFriction(float friction);
		void SetCollider(Collider* collider);

		virtual const char* GetType() const override;

	private:
		bool m_IsSolid;
		float m_Bounciness;
		float m_Friction;

		Collider* m_Collider;
	};
}