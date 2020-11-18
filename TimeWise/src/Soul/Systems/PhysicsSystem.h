#pragma once

#include <utility>

#include <Components/Collider.h>
#include <Structures/ObjectPool.h>

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
		bool SATCollision(unsigned int normalCount, unsigned int vertexCountA, unsigned int vertexCountB, const UniquePointer<sf::Vector2f>& normals, const UniquePointer<sf::Vector2f>& verticesA, const UniquePointer<sf::Vector2f>& verticesB);

	private:
		ObjectPool<Collider> m_Colliders;
	};

	template <class... Args>
	Collider* PhysicsSystem::CreateCollider(Args&&... args)
	{
		return m_Colliders.RequestObject(std::forward<Args>(args)...);
	}
}