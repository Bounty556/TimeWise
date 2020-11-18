#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class Rigidbody : public CollisionHandler
	{
	public:
		Rigidbody(Entity* entity, bool isSolid, float bounciness, float friction);

		/*
		To be called from the entity's collider component. Sets Entity's velocity appropriately
		based on collision data.
		*/
		virtual void HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		/*
		Handles gravity, angular momentum, drag, etc.
		*/
		void Update(float dt);

		// Getters

		bool IsSolid() const;
		float GetBounciness() const;
		float GetFriction() const;

		// Setters

		void SetIsSolid(bool isSolid);
		void SetBounciness(float bounciness);
		void SetFriction(float friction);

		virtual const char* GetType() const override;

	private:
		bool m_IsSolid;
		float m_Bounciness;
		float m_Friction;
	};
}