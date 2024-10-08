#pragma once
#include "Object3D.h"
#include "MeshCollider.h"

class Door : public Object3D {
public:
	Door();
	~Door();
	/// <summary>
	/// ���̂Ǝ����Ƃ̓����蔻�������
	/// �������Ă���ꍇ�A�����Ԃ������Ɨʂ�push�x�N�g���ŕԂ�
	/// </summary>
	/// <param name="sphere">���̃R���W����</param>
	/// <param name="push">�����Ԃ��x�N�g��</param>
	/// <returns>�������Ă���true</returns>
	bool CollisionSphere(SphereCollider sphere,VECTOR3* push);
private:
	MeshCollider* collider;
};