#pragma once
#include "GameObject.h"

class Score : public GameObject
{
public:

	Score();
	~Score();
	void Update()override;
	void Draw()override;
	int GetScore() { return score; }
	

	//�X�R�A���Z�b�g�֐�
	void Clear()
	{
		score = 0;
	}
	//�X�R�A���Z�֐�
	void AddScore(int val)
	{
		score += val;
	}

private:
	int score;//�X�R�A
	
};