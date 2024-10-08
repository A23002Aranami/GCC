#include "camera.h"
#include"Player.h"

                                     //�O�l�̎��_		//�^�㎋�_
static const VECTOR3 CameraPos[] = { VECTOR3(0, 2, -5), VECTOR3(0, 10, -0.5) };
static const VECTOR3 LookPos[]   = { VECTOR3(0, 1,  5), VECTOR3(0,  1,    1) };
static const float ChangeTimeLimit = 1.0f;

Camera::Camera()
{
	//Draw���Ăԏ��Ԃ����߂�֐�(���l������������ɏ��������H)
	SetDrawOrder(-1000 );
	changeTime = ChangeTimeLimit;//�؂�ւ��Ȃ�
}

Camera::~Camera()
{
}

void Camera::Update()
{	
	//�J������LookPos���v���C���[���m�̒��_��
	//���ׂĂ�Player�I�u�W�F�N�g����������
	std::list<Player*> players = ObjectManager::FindGameObjects<Player>();

	VECTOR3 centroid =  VECTOR3(0,0,0);//�d�S
	//�����v���C���[�̒��ň�ԍ��[(�ŏ��̃v���C���[��X�ŏ�����)
	VECTOR3 minX = ObjectManager::FindGameObject<Player>()->Position();
	//�����v���C���[�̒��ň�ԉE�[(�ŏ��̃v���C���[��X�ŏ�����)
	VECTOR3 maxX = ObjectManager::FindGameObject<Player>()->Position();

	for (auto pl : players)
	{
		//���ׂẴv���C���[�̊e�����W�����Z
		centroid = centroid + pl->Position();


		//�[�̃L�����N�^�[��X��ێ�
		if (minX.x > pl->Position().x)
		{
			minX = pl->Position();
		}
		else if (maxX.x < pl->Position().x)
		{
			maxX = pl->Position();
		}
	}

	//�n�_�����炩�ɓ���������
	changePosStart = transform.position;
	changePosStart = lookPosition;

	//�e���̍��W�̕��ρi�d�S�����߂�j
	centroid = centroid / VECTOR3(players.size(), players.size(), players.size());
	Look = centroid;

	VECTOR3 disVec = maxX-minX;
	distance = fabsf(disVec.Length());
	CamPos = centroid - VECTOR3(0,0, 10 + distance);//�f�t�H���g�̃J�����ʒu
	CamPos.y = 5;

	changeTime += 1.0f / 60.0f;//60����1�b���Z�����
	float timeRate = changeTime / ChangeTimeLimit;//0.0�`0.1
	float rate = timeRate * timeRate;
	VECTOR3 position = (changePosGoal - changePosStart) * rate + changePosStart;
	VECTOR3 look = (changeLookGoal - changeLookStart) * rate + changeLookStart;
	transform.position = position ;
	lookPosition = look;

	//��̎��_��'L'�L�[�ɂ���Đ؂�ւ���
	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_L))
	{
		//�v�f�̍ŏ��̃f�[�^�T�C�Y�Ŕz��S�̂����邱�ƂŁA�v�f�������߂邱�Ƃ��ł���
		changePosStart = CameraPos[viewType];
		changeLookStart = LookPos[viewType];
		viewType++;
		if (viewType >= sizeof(CameraPos)/sizeof(CameraPos[0]))
		{
			viewType = 0;
		}
		changePosGoal = CameraPos[viewType];
		changeLookGoal = LookPos[viewType];
		changeTime = 0.0f;

	}


	// �v���C���[�̍s������߂�
	
	//�v���C���[�I�u�W�F�N�g���擾
	Player* player = ObjectManager::FindGameObject<Player>();
	//�v���C���[�̃��[�e�[�V�������s��ɓo�^
	MATRIX4X4 rotY = XMMatrixRotationY(player->Rotation().y);
	//�v���C���[�̃|�W�V�������s��ɓo�^
	MATRIX4X4 trans = XMMatrixTranslation(
		player->Position().x, 0.0f, player->Position().z);
	MATRIX4X4 m = rotY * trans;

	
	// �v���C���[����]�E�ړ����ĂȂ����̃J�����ʒu��
	// �v���C���[�̉�]�E�ړ��s����|����ƁA
	if (changeTime >= ChangeTimeLimit)//���_�ؑ֊���������
	{
		//transform.position = CameraPos[viewType] * m;
		//lookPosition = LookPos[viewType] * m;

		transform.position = CamPos;
		lookPosition = Look;
	}
	else//�ؑ֒�����
	{
		changeTime += 1.0f / 60.0f;//60����1�b���Z�����
		float timeRate = changeTime / ChangeTimeLimit;//0.0�`0.1
		float rate = timeRate*timeRate;
		VECTOR3 position = (changePosGoal - changePosStart) * rate + changePosStart;
		VECTOR3 look = (changeLookGoal - changeLookStart) * rate + changeLookStart;
		transform.position = position*m;
		lookPosition = look*m;
	}
	

	

	//�J�������߂荞�܂Ȃ��悤�ɂ��鏈��
	VECTOR3 start = player->Position()+VECTOR3(0,1.5f,0);
	
	VECTOR3 end = transform.position;
	VECTOR3 push = end-start;
	//�����蔻���0.2m���]���ɂƂ��Ă���
	push = XMVector3Normalize(push)*(push.Length() + 0.2f);

	std::list<Object3D*> objs = ObjectManager::FindGameObjectsWithTag<Object3D>("STAGEOBJ");
	
	for (auto obj : objs) {
		VECTOR3 hit;
		if (obj->HitLineToMesh(start, end, &hit))
		{
			//�������Ă���ۂ̏���
			//end��ǂ̏ꏊ�ɂ���
			end = hit;
		}
		
	}
	//(end-start).Length() = �ǂƃL�����̓��̋���
	//�J�����̈ʒu�ύX(�ǂ���PL�̓��܂ł̋��������߂āA��������0.2���������̂����߂āA�n�_���X�^�[�g�ɍ��킹��)
	transform.position = XMVector3Normalize(push)*((end-start).Length()-0.2f)+start;
}

void Camera::Draw()
{

	GameDevice()->m_mView = XMMatrixLookAtLH(
		transform.position,
		lookPosition,
		VECTOR3(0, 1, 0));
}
