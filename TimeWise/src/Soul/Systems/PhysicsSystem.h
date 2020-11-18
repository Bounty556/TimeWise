#pragma once

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
		PhysicsSystem();



	private:
		ObjectPool<Collider> m_Colliders;
	};
}