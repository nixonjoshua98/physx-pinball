#pragma once

#include "PxPhysicsAPI.h"

#include <vector>
#include <string>

namespace Actors
{
	using namespace physx;

	class Actor
	{
	protected:
		PxActor* actor;
		std::vector<PxVec3> colors;
		std::string name;

	public:
		Actor() : actor(0) {}

		PxActor* Get();
		void Color(PxVec3 new_color, PxU32 shape_index = -1);
		const PxVec3* Color(PxU32 shape_indx = 0);
		void Actor::Name(const std::string& name);
		std::string Actor::Name();
		void Material(PxMaterial* new_material, PxU32 shape_index = -1);
		PxShape* GetShape(PxU32 index = 0);
		std::vector<PxShape*> Actor::GetShapes(PxU32 index = -1);
		virtual void CreateShape(const PxGeometry& geometry, PxReal density) = 0;
		void SetTrigger(bool value, PxU32 index = -1);
		void SetupFiltering(PxU32 filterGroup, PxU32 filterMask, PxU32 shape_index = -1);
	};

	class DynamicActor : public Actor
	{
	public:
		DynamicActor(const PxTransform& pose);

		~DynamicActor();

		void CreateShape(const PxGeometry& geometry, PxReal density);

		void SetKinematic(bool value, PxU32 index = -1);

		void AddForce(PxVec3 force);

		PxRigidBody* GetRigidBody();
		PxRigidActor* GetRigidActor();
	};

	class StaticActor : public Actor
	{
	public:
		StaticActor(const PxTransform& pose);

		~StaticActor();

		void CreateShape(const PxGeometry& geometry, PxReal density = 0.f);
	};
}