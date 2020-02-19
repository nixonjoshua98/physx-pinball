

#include "JN_Model.h"
#include "JN_ModelLoader.h"

JN_Model::JN_Model(std::string file, PxTransform pose) : mesh(0)
{
	JN_ModelLoader loader(file);

	mesh = new TriangleMesh(loader.vertices, loader.indices, pose);
}

void JN_Model::AddToScene(JN_Scene* scene)
{
	scene->Add(mesh);
}

void JN_Model::Color(PxVec3 v, PxU32 c)
{
	mesh->Color(v, c);
}
