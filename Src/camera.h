#pragma once
//camera.h
#include"Object3D.h"

class Camera : public Object3D
{
public:
	Camera();
	~Camera();

	void Update() override;
	void Draw() override;
private:
	VECTOR3 lookPosition;

	float distance;//�Q�L�����̋���
	VECTOR3 Look;
	VECTOR3 CamPos;

	int viewType = 0; //���_�ؑւ̔ԍ�
	
	float changeTime;
	VECTOR3 changePosStart;//���_�ړ��̊J�n�_
	VECTOR3 changePosGoal;//���_�ړ��̏I���_
	VECTOR3 changeLookStart;//���_�ړ��̊J�n�_
	VECTOR3 changeLookGoal;//���_�ړ��̏I���_
};
