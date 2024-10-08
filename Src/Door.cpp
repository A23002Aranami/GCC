#include "Door.h"

Door::Door()
{
	collider = nullptr;
	//�^�O��ݒ�
	SetTag("STAGEOBJ");
	mesh = new CFbxMesh();
	mesh->Load("Data/MapItem/DOOR1.mesh");
	//collider = new MeshCollider;
	//collider->MakeFromMesh(mesh);//mesh���瓖���蔻��������

	meshCol = new MeshCollider;
	meshCol->MakeFromMesh(mesh);

}

Door::~Door()
{
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
}

bool Door::CollisionSphere(SphereCollider sphere, VECTOR3* push)
{

	//VECTOR3 pushVec = VECTOR3(0, 0, 0);//�ŏI�I�ɉ����Ԃ��x�N�g��

	//std::list < MeshCollider::CollInfo> ret =
	//	collider->CheckCollisionSphereList(matrix, sphere.center, sphere.radius);
	////�����̃|���S���ƐڐG���Ă���ꍇ�̂��߂Ɋg��for���ł������������擾���Ă���
	//if(ret.size() > 0){
	//	for(MeshCollider::CollInfo info: ret)
	//	{
	//		//Door�̃��f���Ɠ�������?info�ɏ�񂪓���
	//		float pushLen = sphere.radius - (info.hitPosition - sphere.center).Length();
	//		//�@�������ɐH�����񂾕����������߂�
	//		pushVec += info.normal * pushLen;//�����̃|���S��������͂��Ȃ̂ŁA���̕��������Z����
	//	}
	//	if (push != nullptr)
	//	{
	//		*push = pushVec;
	//	}
	//	return true;
	//}
	return false;
}
