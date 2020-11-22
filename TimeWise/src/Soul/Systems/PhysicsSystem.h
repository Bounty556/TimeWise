#pragma once

#include <utility>

#include <Components/Collider.h>
#include <Structures/ObjectPool.h>
#include <Utility/Simplex.h>

namespace Soul
{
	/*
	This system creates and manages all Collider components, including collisions between
	colliders and reporting them properly.
	*/
	class PhysicsSystem
	{
	public:
		PhysicsSystem(unsigned int capacity = 32);

		template <class... Args>
		Collider* CreateCollider(Args&&... args);

		void Update(float dt, Context& context);

	private:
		sf::Vector2f CheckColliding(const Collider& a, const Collider& b);
		sf::Vector2f Support(const Collider& a, const Collider& b, sf::Vector2f& direction);

	private:
		ObjectPool<Collider> m_Colliders;
	};

	template <class... Args>
	Collider* PhysicsSystem::CreateCollider(Args&&... args)
	{
		return m_Colliders.RequestObject(std::forward<Args>(args)...);
	}
}