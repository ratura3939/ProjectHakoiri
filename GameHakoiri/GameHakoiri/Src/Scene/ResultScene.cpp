#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"ResultScene.h"


//コンストラクタ
//********************************************************
ResultScene::ResultScene(void)
{

}
//デストラクタ
//********************************************************
ResultScene::~ResultScene(void)
{

}
//初期化
//********************************************************
bool ResultScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void ResultScene::Update(void)
{
	auto cnt = SceneManager::GetInstance().GetController();

	switch (cnt)
	{
	case SceneManager::CONTROLLER::KEYBOARD:
		KeyboardContoroller();
		break;
	case SceneManager::CONTROLLER::PAD:
		GamePadController();
		break;
	}
}
//描画
//********************************************************
void ResultScene::Draw(void)
{
	DrawString(0, 0, "ResultScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0x00ffff, true);
}
//解放
//********************************************************
bool ResultScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}

void ResultScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}

void ResultScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}
