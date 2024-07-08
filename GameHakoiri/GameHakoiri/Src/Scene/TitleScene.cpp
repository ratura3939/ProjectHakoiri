#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"TitleScene.h"


//コンストラクタ
//********************************************************
TitleScene::TitleScene(void)
{
}
//デストラクタ
//********************************************************
TitleScene::~TitleScene(void)
{

}
//初期化
//********************************************************
bool TitleScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void TitleScene::Update(void)
{
	KeyboardContoroller();
	GamePadController();
}
//描画
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);
}
//解放
//********************************************************
bool TitleScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}

void TitleScene::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
