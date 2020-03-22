

#include "JN_Model.h"
#include "JN_ModelLoader.h"

// Taken from TriangleMesh

JN_Model::JN_Model(std::string file, PxTransform pose) : StaticActor(pose)
{
	JN_ModelLoader loader(file);

	for (auto object : loader.indicesVector)
	{
		PxTriangleMeshDesc mesh_desc;

		mesh_desc.points.count = (PxU32)loader.vertices.size();
		mesh_desc.points.stride = sizeof(PxVec3);
		mesh_desc.points.data = &loader.vertices.front();

		mesh_desc.triangles.count = (PxU32)(object.second.size() / 3);
		mesh_desc.triangles.stride = 3 * sizeof(PxU32);
		mesh_desc.triangles.data = &object.second.front();

		CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
	}
}

PxTriangleMesh* JN_Model::CookMesh(const PxTriangleMeshDesc& mesh_desc)
{
	PxDefaultMemoryOutputStream stream;

	if (!GetCooking()->cookTriangleMesh(mesh_desc, stream))
		throw new Exception("TriangleMesh::CookMesh, cooking failed.");

	PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

	return GetPhysics()->createTriangleMesh(input);
}