#pragma once

#include "Object3D.h"
#include "GameObject.h"
#include "CsvReader.h"

//�}�b�v�����N���X
class Map : public GameObject
{
public:
	Map();
	~Map();
	
	int GetMAPSIZE();
private:

	//�}�b�v�̍ő�T�C�Y
	static const int MAP_MAXSIZE = 10;

};

//�}�b�v�u���b�N�N���X

class Block : public Object3D
{
public:
	Block();
	~Block();


	/// <summary>
	/// �u���b�N�̏���ݒ肷��֐�
	/// </summary>
	/// <param name="x">�u���b�N��X���W</param>
	/// <param name="y">�u���b�N��Y���W</param>
	/// <param name="z">�u���b�N��Z���W</param>
	/// <param name="type">�u���b�N�̎��</param>
	void SetStatus(float x,float y, float z, int type);

	/// <summary>
	/// ���b�V���ƃ��b�V���R���C�_�[��ݒ肷��
	/// </summary>
	/// <param name="filepass">�t�@�C���̃p�X</param>
	void SetMesh(const TCHAR* filepass);
private:
	//�u���b�N�̎��
	static const enum State
	{
		NoBlock,	//�u���b�N����
		Blank ,		//�P�F�̃u���b�N
	};

	int bType;	//�u���b�N�̎��
};
