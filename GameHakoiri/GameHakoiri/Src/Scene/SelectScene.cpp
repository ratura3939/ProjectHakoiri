#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"SelectScene.h"


//コンストラクタ
//********************************************************
SelectScene::SelectScene(void)
{
	selectNum_ = 0;
}
//デストラクタ
//********************************************************
SelectScene::~SelectScene(void)
{

}
//初期化
//********************************************************
bool SelectScene::Init(void)
{
	selectNum_ = 1;
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void SelectScene::Update(void)
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
void SelectScene::Draw(void)
{
	DrawString(0, 0, "SelectScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xff00ff, true);
}
//解放
//********************************************************
bool SelectScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}

void SelectScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//ステージナンバーを受け渡しシーン切り替え
		SceneManager::GetInstance().SetStageNum(selectNum_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}

void SelectScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		//ステージナンバーを受け渡しシーン切り替え
		SceneManager::GetInstance().SetStageNum(selectNum_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}
