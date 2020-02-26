#include "JN_BaseActors.h"

#include "MyPhysicsEngine.h"

using namespace PhysicsEngine;

using namespace Actors;

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

void Actor::Material(PxMaterial * new_material, PxU32 shape_index)
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
	if (index < ((PxRigidActor*)actor)->getShapes((PxShape * *)& shapes.front(), (PxU32)shapes.size()))
		return shapes[index];
	else
		return 0;
}

std::vector<PxShape*> Actor::GetShapes(PxU32 index)
{
	std::vector<PxShape*> shapes(((PxRigidActor*)actor)->getNbShapes());
	((PxRigidActor*)actor)->getShapes((PxShape * *)& shapes.front(), (PxU32)shapes.size());
	if (index == -1)
		return shapes;
	else if (index < shapes.size())
	{
		return std::vector<PxShape*>(1, shapes[index]);
	}
	else
		return std::vector<PxShape*>();
}

void Actor::Name(const std::string & new_name)
{
	name = new_name;
	actor->setName(name.c_str());
}

std::string Actor::Name()
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

void DynamicActor::CreateShape(const PxGeometry & geometry, PxReal density)
{
	PxShape* shape = ((PxRigidDynamic*)actor)->createShape(geometry, *GetMaterial());

	PxRigidBodyExt::updateMassAndInertia(*(PxRigidDynamic*)actor, density);

	colors.push_back(default_color);

	shape->userData = new UserData();

	for (unsigned int i = 0; i < colors.size(); i++)
		((UserData*)GetShape(i)->userData)->color = &colors[i];
}

void DynamicActor::SetKinematic(bool value, PxU32 index)
{
	((PxRigidDynamic*)actor)->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
}

void DynamicActor::AddForce(PxVec3 force)
{
	Get()->is<PxRigidBody>()->addForce(force, PxForceMode::eIMPULSE);
}

PxRigidBody* Actors::DynamicActor::GetRigidBody()
{
	return static_cast<PxRigidBody*>(Get());
}

PxRigidActor* Actors::DynamicActor::GetRigidActor()
{
	return static_cast<PxRigidActor*>(Get());
}

StaticActor::StaticActor(const PxTransform & pose)
{
	actor = (PxActor*)GetPhysics()->createRigidStatic(pose);

	Name("");
}

StaticActor::~StaticActor()
{
	for (unsigned int i = 0; i < colors.size(); i++)
		delete (UserData*)GetShape(i)->userData;
}

void StaticActor::CreateShape(const PxGeometry & geometry, PxReal density)
{
	PxShape* shape = ((PxRigidStatic*)actor)->createShape(geometry, *GetMaterial());
	colors.push_back(default_color);
	//pass the color pointers to the renderer
	shape->userData = new UserData();
	for (unsigned int i = 0; i < colors.size(); i++)
		((UserData*)GetShape(i)->userData)->color = &colors[i];
}