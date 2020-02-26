#include "JN_Hexagon.h"

#include <vector>


JN_Hexagon::JN_Hexagon(const PxTransform& pose, PxReal height, PxReal radius) : convex(0)
{
	std::vector<PxVec3> verts;

	const int SIDES = 6;

	height /= 2;
	radius /= 2;

	// Material
	PxMaterial* hexMaterial = CreateMaterial(0.0f, 0.0f, 0.0f);

	hexMaterial->setRestitution(2.5f);

	for (int i = 0; i < SIDES; i++)
	{
		float angle = i * PxPi * 2 / SIDES;

		PxVec3 pos = PxVec3(PxCos(angle), height, PxSin(angle)) * radius;

		verts.push_back(pos);

		pos.y = -height;

		verts.push_back(pos);
	}

	for (int i = 0; i < verts.size(); ++i)
	{
		verts[i] += pose.p;
	}

	convex = new ConvexMesh(verts);

	convex->Color({ 0, 0, 0 });
	convex->Material(hexMaterial);
	convex->SetKinematic(true);
}

JN_Hexagon::~JN_Hexagon()
{

}

void JN_Hexagon::AddToScene(JN_Scene* scene)
{
	scene->Add(convex);
}
