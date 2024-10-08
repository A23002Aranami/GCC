#include "ResultScore.h"

ResultScore::ResultScore()
{
	viewScore = 0;
	resultTimer = 0;
	endCntUp = 0;
	deray = 0.5f;
	strX = 50;
	strY = 150;
	Row = 150;
}

ResultScore::~ResultScore()
{
}

void ResultScore::Update()
{
	resultTimer+= SceneManager::DeltaTime() ;
	Score* sc = ObjectManager::FindGameObject<Score>();

	if (viewScore < sc->GetScore() && resultTimer > 0.5f)
	{
		viewScore++;
		if (viewScore == sc->GetScore())
		{
			endCntUp = 0;
		}
	}
	if (viewScore == sc->GetScore())
	{
		endCntUp += SceneManager::DeltaTime();
	}

}

void ResultScore::Draw()
{
	Score* sc = ObjectManager::FindGameObject<Score>();
	
	char str[64];//������
	//sprintf_s<64>(str, "SCORE: %06d", viewScore);//printf�̌`�ŕ�����ɓ���Ă����
	sprintf_s<64>(str, "WINNER: %dP!!!", sc->GetWinner());

	GameDevice()->m_pFont->Draw(
		strX, strY, "RESULT", 128, RGB(255, 255, 255));

	if (resultTimer > deray) {
		GameDevice()->m_pFont->Draw(
			strX, strY+Row, str, 128, RGB(255, 255, 255));
	}
	if (endCntUp > deray) {
		GameDevice()->m_pFont->Draw(
			strX, strY+Row*2, "PUSH 'T' KEY !!!", 128, RGB(255, 255, 255));

		if(GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_T))
		{
			SceneManager::ChangeScene("TitleScene");
		}
	}
}

void ResultScore::GetScore()
{
}
