
#include "Dancer.h"
#include"Player.h"
#include"Score.h"
Dancer::Dancer()
{
	animator = new Animator(); // �C���X�^���X���쐬

	mesh = new CFbxMesh();
	mesh->Load("Data/Dancer/Character.mesh");
	mesh->LoadAnimation(0, "Data/Dancer/Dancing.anmx", true);
	animator->SetModel(mesh); // ���̃��f���ŃA�j���[�V��������
	animator->Play(0);
	animator->SetPlaySpeed(1.0f);
	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);

	transform.position = VECTOR3(20, 0, 0);
	transform.rotation = VECTOR3(0, 0, 0);
	state = sNormal;
	hitPoint = 20;
	aroundID = 0;
}

Dancer::~Dancer()
{
}

void Dancer::Start()//update()�������O�Ɉ�x�����s���鏈��
{
	areaCenter = transform.position;
}

void Dancer::Update()
{
	switch (state)
	{
	case sNormal:
		updateNormal();
		break;
	case sReach:
	{
		updateReach();
		break;
	}
	case sBack:
		updateBack();
		break;

	case sDead:
		updateDead();
		break;
	}
	
}


SphereCollider Dancer::Collider()
{
	SphereCollider col;
	col.center = transform.position;
	col.radius = 0.5f;
	return col;
}

void Dancer::AddDamage(float damage, VECTOR3 pos)
{
	hitPoint -= damage;
	if (hitPoint > 0) {
		//��������G�ւ̌����̃x�N�g�������߂�
		VECTOR3 pushVec = transform.position - pos;
		pushVec.y = 0;
		//�x�N�g���̒�����1�ɂ���
		pushVec = XMVector3Normalize(pushVec);
		//�x�N�g���Ɉړ����������������|���ă|�W�V�����ɉ��Z����
		transform.position += pushVec * 0.5;
		transform.rotation.y = atan2f(-pushVec.x, -pushVec.z);
	}
	else
	{
		//��������G�ւ̃x�N�g�������߂�
		VECTOR3 pushVec = transform.position - pos;
		//���߂��x�N�g���̋t����������
		transform.rotation.y = atan2f(-pushVec.x, -pushVec.z);
		deadTimer = 0;//���S���Ă���̎��Ԃ�0�ŏ�����
		state = sDead;//�X�e�[�^�X�����S��Ԃ�
	}
}

void Dancer::updateNormal()
{
	animator->Update();
	//���񃋁[�g
	std::vector <VECTOR3> around =
	{
		VECTOR3(0,0,0),
		VECTOR3(0,0,2),
		VECTOR3(2,0,2),
		VECTOR3(0,0,2),
	};

	VECTOR3 target = around[aroundID] + areaCenter;
	moveToTarget(target, 0.01, 1);

	if ((target - transform.position).Length() < 0.5f)
	{
		aroundID = (aroundID + 1) % around.size();
	}
	
	//����ɓ�������A�v���C���[�Ɍ������ē���
	Player* player = ObjectManager::FindGameObject<Player>();
	VECTOR3 toPlayer = player->Position() - transform.position;//
	if (toPlayer.Length() < 10.0f)//����̋���
	{
		//�����̐��ʃx�N�g�������
		VECTOR3 front = VECTOR3(0, 0, 1) * XMMatrixRotationY(transform.rotation.y);
		//�����̉E���x�N�g�������
		VECTOR3 right = VECTOR3(1, 0, 0) * XMMatrixRotationY(transform.rotation.y);
		//�v���C���[�ւ̃x�N�g���̒���1�̂���(���������̏��ɂ���)
		VECTOR3 toPlayer1 = XMVector3Normalize(toPlayer);
		//���ς��Ƃ遫���ꂪcos���ɂȂ�
		float ip = Dot(front, toPlayer1);//Dot = ���ς��̃x�N�g���̓��ς����߂�֐�
		float ipR = Dot(right, toPlayer1);
		if (ip >= cosf(60.0f * DegToRad))//60�x�ȓ�(cos�Ƃ�60�ȓ��ł��鎞)
		{
			//����ɓ�������
			state = sReach;
		}
	}

}

void Dancer::updateReach()
{
	Player* player = ObjectManager::FindGameObject<Player>();
	

	moveToTarget(player->Position());

	//�G���A�̊O�ɏo����Astate��sBuck�ɕς���
	VECTOR3 toAreaCenter = areaCenter - transform.position;
	if (toAreaCenter.Length() > 5.0f)//�G���A�𒴂�����
	{
		state = sBack;
	}
}

void Dancer::updateBack()
{
	//�G���A�̒��S�ւ̃x�N�g��
	VECTOR3 toAreaCenter = areaCenter - transform.position;

	moveToTarget(areaCenter);
	//�G���A�Z���^�[�Ƃ̋��������ȉ��ɂȂ�����sNormal�ɖ߂�
	if (toAreaCenter.Length() < 1.0f)
	{
		state = sNormal;
	}


}


void Dancer::updateDead()
{
	deadTimer += SceneManager::DeltaTime();//1/60�b���Z

	if (deadTimer <= 2.0f)
	{
		//���X�ɓ|���
		float rate = deadTimer/2.0f;
		rate = rate * rate*rate;
		transform.rotation.x = -XM_PI / 2 * rate;
	}
	else if(deadTimer >= 4.0f)
	{
		//���S�t���O��true�ɂ���֐�
		sc = ObjectManager::FindGameObject<Score>();
		sc->AddScore(100);
		DestroyMe();
	}
}

void Dancer::moveToTarget(VECTOR3 target)
{
	moveToTarget(target, 0.01f, 0.5f);
}

void Dancer::moveToTarget(VECTOR3 target, float moveSpeed, float rot)
{
	//�p�x��ϊ�
	rot = rot * DegToRad;
	MATRIX4X4 myRot = XMMatrixRotationY(transform.rotation.y);
	VECTOR3 toTarget = target - transform.position;//
	//�����̐��ʃx�N�g�������
	VECTOR3 front = VECTOR3(0, 0, 1) * myRot;
	//�����̉E���x�N�g�������
	VECTOR3 right = VECTOR3(1, 0, 0) * myRot;
	//�v���C���[�ւ̃x�N�g���̒���1�̂���(���������̏��ɂ���)
	VECTOR3 toTarget1 = XMVector3Normalize(toTarget);

	//���ς��Ƃ遫���ꂪcos���ɂȂ�
	float ip = Dot(front, toTarget1);//Dot = ���ς��̃x�N�g���̓��ς����߂�֐�
	float ipR = Dot(right, toTarget1);

	transform.position += front * moveSpeed;

	if (ip >= cosf(3.0f * DegToRad))
	{
		transform.rotation.y = atan2f(toTarget.x, toTarget.z);
	}
	else if (ipR >= 0.0f)//�v���C���[�������̉E�ɂ��鎞
	{
		transform.rotation.y += rot;
	}
	else//�v���C���[�������̍��ɂ��鎞
	{
		transform.rotation.y -= rot;
	}
}
