#include "JN_Hexagon.h"
#include "JN_FilterGroup.h"

#include <vector>

using namespace Actors;


JN_Hexagon::JN_Hexagon(const PxTransform& pose, PxReal height, PxReal radius) : convex(0)
{
	std::vector<PxVec3> verts;

	const int SIDES = 6;

	height /= 2;
	radius /= 2;

	// Material
	PxMaterial* hexMaterial = CreateMaterial(0.0f, 0.0f, 1.5f);

	// Grab points around the 'circle'
	for (int i = 0; i < SIDES; i++)
	{
		float angle = i * PxPi * 2 / SIDES;

		PxVec3 pos = PxVec3(PxCos(angle), height, PxSin(angle)) * radius;

		// Top verts
		verts.push_back(pos);

		pos.y = -height;

		// Bottom verts
		verts.push_back(pos);
	}

	for (int i = 0; i < verts.size(); ++i)
	{
		verts[i] += pose.p;
	}

	convex = new JN_ConvexMesh(verts);

	convex->Color({ 0, 0, 0 });
	convex->Material(hexMaterial);
	convex->SetKinematic(true);

	convex->Name("Hexagon");

	convex->SetupFiltering(JN_FilterGroup::HEXAGONS, JN_FilterGroup::BALLS);
}

JN_Hexagon::~JN_Hexagon()
{

}

void JN_Hexagon::AddToScene(JN_Scene* scene)
{
	scene->Add(convex);
}
