#include "TitleScene.h"
#include "GameMain.h"

TitleScene::TitleScene()
{
	positionX = 0;
	speedX = 1;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	positionX += speedX;
	if (positionX >= 60) {
		speedX *= -1;
	}
	else {
		if (positionX <= 0) {
			speedX *= -1;
		}
	}
	if (GameDevice()->m_pDI->
			CheckKey(KD_TRG, DIK_P)) {
		SceneManager::ChangeScene("PlayScene");
	}
}

void TitleScene::Draw()
{
	GameDevice()->m_pFont->Draw(250, 200, "HOPPING BATTLE", 128, RGB(255, 0, 0),1.0f);
	GameDevice()->m_pFont->Draw(310, 500, "PUSH P TO START", 100, RGB(255, 0, 0), 1.0f);

}