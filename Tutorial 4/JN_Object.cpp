

#include "JN_Object.h"
#include "JN_ObjectLoader.h"

JN_Object::JN_Object(std::string file, PxTransform pose) : mesh(0)
{
	JN_ObjectLoader loader(file); 

	mesh = new TriangleMesh(loader.vertices, loader.indices, pose);
}

void JN_Object::AddToScene(JN_Scene* scene)
{
	scene->Add(mesh);
}

void JN_Object::Color(PxVec3 v, PxU32 c)
{
	mesh->Color(v, c);
}
