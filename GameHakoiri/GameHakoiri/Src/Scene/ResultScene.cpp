#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Application.h"
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
	auto& rsM = ResourceManager::GetInstance();
	backSelectImg_= rsM.Load(ResourceManager::SRC::BACK_SELECT_IMG).handleId_;
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
	DrawGraph(Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y - 256, backSelectImg_, true);
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
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}

void ResultScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
