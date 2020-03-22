#include "PhysicsEngine.h"
#include <iostream>

namespace PhysicsEngine
{
	using namespace physx;
	using namespace std;

	// Default error and allocator callbacks
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocatorCallback;

	// PhysX objects
	PxPvd* pvd = 0;
	PxPhysics* physics = 0;
	PxCooking* cooking = 0;
	PxFoundation* foundation = 0;

	// PhysX functions
	void PxInit()
	{
		// Foundation
		if (!foundation)
		{
			foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
		}

		if (!foundation)
			throw new Exception("PhysicsEngine::PxInit, Could not create the PhysX SDK foundation.");

		// Visual debugger
		if (!pvd)
		{
			pvd = PxCreatePvd(*foundation);
			PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
			pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);		
		}

		// Physics
		if (!physics)
			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);

		if (!physics)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the PhysX SDK.");

		if (!cooking)
			cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));

		if (!cooking)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the cooking component.");

		// Create a deafult material
		CreateMaterial();
	}

	void PxRelease()
	{
		if (cooking)
			cooking->release();

		if (physics)
			physics->release();

		if (pvd)
			pvd->release();

		if (foundation)
			foundation->release();
	}

	PxPhysics* GetPhysics()
	{
		return physics;
	}

	PxCooking* GetCooking()
	{
		return cooking;
	}

	PxMaterial* GetMaterial(PxU32 index)
	{
		std::vector<PxMaterial*> materials(physics->getNbMaterials());

		if (index < physics->getMaterials((PxMaterial**)&materials.front(), (PxU32)materials.size()))
			return materials[index];

		else
			return 0;
	}

	PxMaterial* CreateMaterial(PxReal sf, PxReal df, PxReal cr)
	{
		return physics->createMaterial(sf, df, cr);
	}
}
