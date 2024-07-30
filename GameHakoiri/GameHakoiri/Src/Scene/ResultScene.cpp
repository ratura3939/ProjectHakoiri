#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/SoundManager.h"
#include"../Utility/Utility.h"
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
	result_ = SceneManager::GetInstance().IsClearStageNow();

	backSelectImg_= rsM.Load(ResourceManager::SRC::BACK_SELECT_IMG).handleId_;
	resultImg_[static_cast<int>(false)] = rsM.Load(ResourceManager::SRC::FAILD_IMG).handleId_;
	resultImg_[static_cast<int>(true)] = rsM.Load(ResourceManager::SRC::CLEAER_IMG).handleId_;

	if (result_)SoundManager::GetInstance().PlayBgmOfSuccess();
	else SoundManager::GetInstance().PlayBgmOfFailed();

	flash_ = 0;
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

	flash_++;
	if (flash_ > RESULT_FLASH_MAX)flash_ = 0;
}
//描画
//********************************************************
void ResultScene::Draw(void)
{
	DrawGraph(Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y - RESULT_SIZE_X, backSelectImg_, true);

	if (flash_ % Application::FPS < RESULT_FLASH)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2 - RESULT_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2 - RESULT_SIZE_Y / 2,
			1.0f,
			0.0f * Utility::DEG2RAD,
			resultImg_[static_cast<int>(result_)],
			true,
			false);
	}
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
	auto& snd = SoundManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		snd.PlaySndEnter(true);
		if (result_)snd.StopBgmOfSuccess();
		else snd.StopBgmOfFailed();
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}

void ResultScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		snd.PlaySndEnter(true);
		if (result_)snd.StopBgmOfSuccess();
		else snd.StopBgmOfFailed();
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
