#pragma once
#include "GameObject.h"

class PlayerManager : public GameObject
{
public:

	PlayerManager(int num);//�v���C���[���������ɂ���
	~PlayerManager();

	void ReduceSurvivor( int plNo );

private:
	std::vector<int> survivor;

};