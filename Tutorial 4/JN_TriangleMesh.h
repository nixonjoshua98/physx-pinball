

#include "JN_BaseActors.h"

#include "PhysicsEngine.h"


namespace Actors
{
	class TriangleMesh : public StaticActor
	{
	public:
		TriangleMesh(const PxTransform& pose = PxTransform(PxIdentity)) : StaticActor(pose) { }

		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, const PxTransform& pose = PxTransform(PxIdentity)) : StaticActor(pose)
		{
			PxTriangleMeshDesc mesh_desc;

			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();

			mesh_desc.triangles.count = (PxU32)(trigs.size() / 3);
			mesh_desc.triangles.stride = 3 * sizeof(PxU32);
			mesh_desc.triangles.data = &trigs.front();

			CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
		}

		PxTriangleMesh * CookMesh(const PxTriangleMeshDesc & mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if (!PhysicsEngine::GetCooking()->cookTriangleMesh(mesh_desc, stream))
				throw new Exception("TriangleMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return PhysicsEngine::GetPhysics()->createTriangleMesh(input);
		}
	};
}