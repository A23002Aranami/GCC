#pragma once
//ResultScene.h
#include "SceneBase.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
	void Update() override;
	void Draw() override;
private: // �N���X�̃����o�[�ϐ���private�ɂ���
	int positionX;
	int speedX;
};