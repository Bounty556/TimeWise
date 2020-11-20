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
		sf::Vector2f* MyCollision(sf::Vector2f* polygonA, unsigned int vertexCountA, const sf::Vector2f& centerA, sf::Vector2f* polygonB, unsigned int vertexCountB, const sf::Vector2f& centerB, bool& firstPolygon);

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