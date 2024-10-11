#include "Map.h"

Map::Map()
{
	CsvReader* csv = new CsvReader("Data/map01.csv");
	for (int i = 0; i < MAP_MAXSIZE; i++)
	{
		for (int j = 0; j < MAP_MAXSIZE; j++)
		{
			Block* block = Instantiate<Block>();
			 int type = csv->GetInt(i, j);
			block->SetStatus(i,0,j,type);
		}
	}
}

Map::~Map()
{
}

int Map::GetMAPSIZE()
{
	return MAP_MAXSIZE;
}


//�ȉ��u���b�N�̏���

Block::Block()
{
	//�u���b�N�̃^�C�v���u�����N�ɏ�����
	bType = Blank;
	//���W��0,0,0�ŏ���������
	transform.position = VECTOR3(0,0,0);
	transform.scale = VECTOR3(1.0f, 0.90f, 1.0f);

	//�^�O���Z�b�g����
	SetTag("STAGEOBJ");
}

Block::~Block()
{
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
}

void Block::SetStatus(float x, float y, float z, int type)
{
	SetPosition(x,y,z);
	bType = type;
	
	switch (type)//�w�肳�ꂽ�u���b�N�̎�ނ̃��b�V�������[�h
	{
	case NoBlock:
		DestroyMe();
		break;
	case Blank:
		SetMesh("Data/Map/wallStone01.mesh");
		break;
	default:
		break;
	}

	
}

void Block::SetMesh(const TCHAR* filepass)
{
	mesh = new CFbxMesh();
	mesh->Load(filepass);
	meshCol = new MeshCollider;
	meshCol->MakeFromMesh(mesh);
}
