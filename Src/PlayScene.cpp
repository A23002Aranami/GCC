#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Door.h"
#include "Dancer.h"
#include"camera.h"
#include"CsvReader.h"
#include<assert.h>
#include "Score.h"
#include "DrawScore.h"
#include "MochiTest.h"
#include "Map.h"

PlayScene::PlayScene()
{
	CsvReader* csv = new CsvReader("Data/map00.csv");
	
	assert(csv->GetLines() > 0);//�l�������Ă��Ȃ��ꍇ�G���[�ɂ��邽�߂̏���
	
	players = 0;//�v���C���[�̐l�����O�ŏ�����

	for (int i = 1; i < csv->GetLines(); i++)//���̂ȂǑ薼�̗���΂����߂�i��1����n�߂Ă���
	{
		std::string str = csv->GetString(i, 0);

		if (str.substr(0, 2) == "//") {}//�擪�Q������//���������΂�
		else {
			Object3D* obj = nullptr;//���ׂ�Object3D���p�����Ă���̂ŁAobj�œ���ł���

			if (str == "PLAYER") {//Player�̐��l����

				players++;
				//�v���C���[�ŗL�ϐ���ݒ肷�邽�߂Ƀ|�C���^�擾
				Player* p = Instantiate<Player>();

				//�L�[�o�C���h�̐ݒ�
				p->SetKeyBind(csv->GetKeyDef(i, 4), csv->GetKeyDef(i, 5), csv->GetKeyDef(i, 6), csv->GetKeyDef(i, 7), csv->GetKeyDef(i, 8),csv->GetKeyDef(i,9), csv->GetKeyDef(i, 10));
				//p->LoadMesh(csv->GetString(i,11));
				p->LoadColMesh(csv->GetString(i, 12));

				//�v���C���[�̔ԍ�������U��
				p->SetPlNo(players);
				obj = p;
			}
			else if (str == "DANCER") {//DANCER�̐��l����

				obj = Instantiate<Dancer>();
			}
			else if (str == "DOOR") {//DOOR�̐��l����
				obj = Instantiate<Door>();
			}
			else if (str == "GROUND") {//GROUND�̐��l����
				obj = Instantiate<Ground>();
			}
			else//������~�X�̎�
			{
				assert(false);//�����I��
			}
			float x = csv->GetFloat(i, 1);
			float y = csv->GetFloat(i, 2);
			float z = csv->GetFloat(i, 3);

			obj->SetPosition(x, y, z);
			obj->SetCsvLine(i);

			Instantiate<Camera>();
			Score* sc = ObjectManager::FindGameObject<Score>();
			if (sc == nullptr) {//�I�u�W�F�N�g���܂�����Ă��Ȃ���������
				sc = Instantiate<Score>();
				sc->DontDestroyMe();//�V�[���ؑւ��Ă��A�I�u�W�F�N�g��������Ȃ��悤�ɂ���
			}
			sc->Clear();

			Instantiate<ScoreDraw>();

#if 0
			Instantiate<Ground>();
			Door* door = Instantiate<Door>();
			door->SetPosition(40, 0, -40);
			// const�́A���������֎~�Ƃ����Ӗ�

			const VECTOR3 dancerPos[] = {
				VECTOR3(0,0,20),
				VECTOR3(20,0,0),
				VECTOR3(-20,0,-20),
				VECTOR3(-25,0,-25),
				VECTOR3(30,0,-25),
			};
			for (VECTOR3 p : dancerPos) {
				Dancer* d = Instantiate<Dancer>();
				d->SetPosition(p);
			}
#endif
		}
	}

	Instantiate<Map>();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	//Player���c���l�ɂȂ�����Q�[���I��
	std::list< Player* > pls = ObjectManager::FindGameObjects<Player>();
	if (pls.size() <= 1) {
		Score* sc = ObjectManager::FindGameObject<Score>();
		Player* pl = ObjectManager::FindGameObject<Player>();
		sc->SetWinner( pl->plNo);
		SceneManager::ChangeScene("ResultScene");
	}
}

void PlayScene::Draw()
{
}
