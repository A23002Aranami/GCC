#pragma once
// Player.h
#include "Object3D.h"
//#include "Animator.h"

class Player : public Object3D {
public:
	Player();
	~Player();
	void Update() override;
	void Draw()override;
	//���������Ԗڂ̃v���C���[���𔻒肷�邽�߂̐��l��ݒ�
	void SetPlNo(int no) { plNo = no; }

	/// <summary>
	/// �L�[�o�C���h��ݒ肷�邽�߂̊֐�
	/// </summary>
	/// <param name="�O�Ɉړ����邽�߂̃L�[�ݒ�"></param>
	/// <param name="���Ɉړ����邽�߂̃L�[�ݒ�"></param>
	/// <param name="�E�Ɉړ����邽�߂̃L�[�ݒ�"></param>
	/// <param name="���Ɉړ����邽�߂̃L�[�ݒ�"></param>
	/// <param name="�W�����v���邽�߂̃L�[�ݒ�"></param>
	void SetKeyBind(DWORD inputForword, DWORD inputBack, DWORD inputLeft, DWORD inputRight, DWORD LeanL, DWORD LeanR, DWORD inputJump );
	DWORD GetKeyBind(char key);//�ݒ肵�Ă���L�[���擾����

	
	
	/// <summary>
	/// �i�s�����̃x�N�g�������߂�v�Z
	/// </summary>
	/// <param name="forward">�f�t�H���g�Ői�݂�������</param>
	/// <returns></returns>
	VECTOR3 CalcMoveVec( VECTOR3 forward);

	bool ThrouthCheckStoM(Object3D* obj, SphereCollider coll, VECTOR3* push, VECTOR3 speed, int per);
	void LoadMesh(std::string meshName);
	void LoadColMesh(std::string meshName);
	SphereCollider Collider() override;
	
	void SetVec(VECTOR3 vec) { speed = vec; }
	VECTOR3 GetVec() { return speed; }
	static int menNum;//�v���C���[�̐l��

	int plNo;//�v���C���[�ԍ�
private:
	float speedY; // Y�̑��x
	VECTOR3 speed;//�ړ����x
	float Timer;
	float boundTime;
	int airJump;

	//Animator* animator; // ���i�̃C���X�^���X���|�C���^�[�^�ŏ���
	enum AnimID {
		aIdle = 0,
		aRun = 1,
		aAttack1,
		aAttack2,
		aAttack3,

	};

	//�PP�QP�ő���̓��͂�ς��邽�߂̕ϐ�
	DWORD inputForward;
	DWORD inputBack;
	DWORD inputRight;
	DWORD inputLeft;
	DWORD inputJump;
	DWORD inputLeanR;
	DWORD inputLeanL;

	
	int number;
	enum State {
		sOnGround = 0,
		sJump,
	};
	State state;
	void UpdateOnGround();
	void UpdateJump();

	float KnockBackRate;//�ӂ��Ƃї�

	CFbxMesh* colMesh;
	//�댯�n�тɂ��鎞��
	int DengerTime;
	int frame; // �A�j���[�V�����̃t���[���𐔂���

	

};

