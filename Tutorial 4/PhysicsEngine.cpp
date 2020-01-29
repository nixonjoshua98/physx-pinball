#include "PhysicsEngine.h"
#include <iostream>

namespace PhysicsEngine
{
	using namespace physx;
	using namespace std;

	//default error and allocator callbacks
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocatorCallback;

	//PhysX objects
	PxFoundation* foundation = 0;
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
	debugger::comm::PvdConnection* pvd = 0;
#else
	PxPvd*  pvd = 0;
#endif
	PxPhysics* physics = 0;
	PxCooking* cooking = 0;

	///PhysX functions
	void PxInit()
	{
		//foundation
		if (!foundation) {
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
			foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
#else
			foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
#endif
		}

		if (!foundation)
			throw new Exception("PhysicsEngine::PxInit, Could not create the PhysX SDK foundation.");

		//visual debugger
		if (!pvd) {
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
			pvd = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), "localhost", 5425, 100,
				PxVisualDebuggerExt::getAllConnectionFlags());
#else
			pvd = PxCreatePvd(*foundation);
			PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
			pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
#endif
		}

		//physics
		if (!physics)
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale());
#else
			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);
#endif

		if (!physics)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the PhysX SDK.");

		if (!cooking)
			cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));

		if (!cooking)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the cooking component.");

		//create a deafult material
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

	///Actor methods

	PxActor* Actor::Get()
	{
		return actor;
	}

	void Actor::Color(PxVec3 new_color, PxU32 shape_index)
	{
		//change color of all shapes
		if (shape_index == -1)
		{
			for (unsigned int i = 0; i < colors.size(); i++)
				colors[i] = new_color;
		}
		//or only the selected one
		else if (shape_index < colors.size())
		{
			colors[shape_index] = new_color;
		}
	}

	const PxVec3* Actor::Color(PxU32 shape_indx)
	{
		if (shape_indx < colors.size())
			return &colors[shape_indx];
		else
			return 0;
	}

	void Actor::Material(PxMaterial* new_material, PxU32 shape_index)
	{
		std::vector<PxShape*> shape_list = GetShapes(shape_index);
		for (PxU32 i = 0; i < shape_list.size(); i++)
		{
			std::vector<PxMaterial*> materials(shape_list[i]->getNbMaterials());
			for (unsigned int j = 0; j < materials.size(); j++)
				materials[j] = new_material;
			shape_list[i]->setMaterials(materials.data(), (PxU16)materials.size());
		}
	}

	PxShape* Actor::GetShape(PxU32 index)
	{
		std::vector<PxShape*> shapes(((PxRigidActor*)actor)->getNbShapes());
		if (index < ((PxRigidActor*)actor)->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size()))
			return shapes[index];
		else
			return 0;
	}

	std::vector<PxShape*> Actor::GetShapes(PxU32 index)
	{
		std::vector<PxShape*> shapes(((PxRigidActor*)actor)->getNbShapes());
		((PxRigidActor*)actor)->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size());
		if (index == -1)
			return shapes;
		else if (index < shapes.size())
		{
			return std::vector<PxShape*>(1, shapes[index]);
		}
		else
			return std::vector<PxShape*>();
	}

	void Actor::Name(const string& new_name)
	{
		name = new_name;
		actor->setName(name.c_str());
	}

	string Actor::Name()
	{
		return name;
	}

	DynamicActor::DynamicActor(const PxTransform& pose) : Actor()
	{
		actor = (PxActor*)GetPhysics()->createRigidDynamic(pose);
		Name("");
	}

	DynamicActor::~DynamicActor()
	{
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;
	}

	void DynamicActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = ((PxRigidDynamic*)actor)->createShape(geometry, *GetMaterial());
		PxRigidBodyExt::updateMassAndInertia(*(PxRigidDynamic*)actor, density);
		colors.push_back(default_color);
		//pass the color pointers to the renderer
		shape->userData = new UserData();
		for (unsigned int i = 0; i < colors.size(); i++)
			((UserData*)GetShape(i)->userData)->color = &colors[i];
	}

	void DynamicActor::SetKinematic(bool value, PxU32 index)
	{
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
		((PxRigidDynamic*)actor)->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, value);
#else
		((PxRigidDynamic*)actor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
#endif
	}

	StaticActor::StaticActor(const PxTransform& pose)
	{
		actor = (PxActor*)GetPhysics()->createRigidStatic(pose);
		Name("");
	}

	StaticActor::~StaticActor()
	{
		for (unsigned int i = 0; i < colors.size(); i++)
			delete (UserData*)GetShape(i)->userData;
	}

	void StaticActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = ((PxRigidStatic*)actor)->createShape(geometry, *GetMaterial());
		colors.push_back(default_color);
		//pass the color pointers to the renderer
		shape->userData = new UserData();
		for (unsigned int i = 0; i < colors.size(); i++)
			((UserData*)GetShape(i)->userData)->color = &colors[i];
	}
}
