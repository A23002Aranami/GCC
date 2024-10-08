#pragma once
#include "Object3D.h"
#include "Animator.h"
#include "Score.h"

class Dancer : public Object3D {
public:
	Dancer();
	~Dancer();
	void Start() override;//�ŏ��̃A�b�v�f�[�g�̑O�ɌĂ΂��֐�
	void Update() override;
	SphereCollider Collider() override;
	void AddDamage(float damage, VECTOR3 pos);
private:
	Animator* animator;
	Score* sc;
	float hitPoint;

	enum State {
		sNormal = 0, //�ʏ���(����)
		sReach,//�ǂ�������
		sBack,//�A��
		sDead,//���S

	};
	State state;
	void updateNormal();
	void updateReach();
	void updateBack();
	void updateDead();

	float deadTimer;//���S����


	VECTOR3 areaCenter;//�T���G���A�̒��S

	/// <summary>
	/// �^�[�Q�b�g�֌������Ċ��炩�Ɉړ�����֐�
	/// </summary>
	/// <param name="�^�[�Q�b�g�̈ʒu"></param>
	void moveToTarget(VECTOR3 target);
	
	/// <summary>
	/// �^�[�Q�b�g�֌������Ċ��炩�Ɉړ�����֐�
	/// </summary>
	/// <param name="�^�[�Q�b�g�̈ʒu"></param>
	/// <param name="�����X�s�[�h"></param>
	/// <param name="��]�p(Deg)"></param>
	void moveToTarget(VECTOR3 target,float moveSpeed, float rot);
	
	int aroundID;
};