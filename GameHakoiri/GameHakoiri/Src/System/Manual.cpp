#include<DxLib.h>
#include "Manual.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
#include"../Utility/Utility.h"

Manual* Manual::instance_ = nullptr;


bool Manual::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Manual;
	}

	instance_->Init();

	return true;
}

Manual& Manual::GetInstance(void)
{
	return *instance_;
}

void Manual::Init(void)
{
	auto& rsM = ResourceManager::GetInstance();

	manualImg_[static_cast<int>(GameScene::MODE::PAZZLE)][0]=
		rsM.Load(ResourceManager::SRC::PZL_MNL_1_IMG).handleId_;
	manualImg_[static_cast<int>(GameScene::MODE::PAZZLE)][1] =
		rsM.Load(ResourceManager::SRC::PZL_MNL_2_IMG).handleId_;
	manualImg_[static_cast<int>(GameScene::MODE::STEALTH)][0] =
		rsM.Load(ResourceManager::SRC::STL_MNL_1_IMG).handleId_;
	manualImg_[static_cast<int>(GameScene::MODE::STEALTH)][1] =
		rsM.Load(ResourceManager::SRC::STL_MNL_2_IMG).handleId_;

	cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::KEYBOARD)][static_cast<int>(GameScene::MODE::PAZZLE)]=
		rsM.Load(ResourceManager::SRC::KBD_PZL_IMG).handleId_;
	cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::KEYBOARD)][static_cast<int>(GameScene::MODE::STEALTH)] =
		rsM.Load(ResourceManager::SRC::KBD_STL_IMG).handleId_;
	cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::PAD)][static_cast<int>(GameScene::MODE::PAZZLE)] =
		rsM.Load(ResourceManager::SRC::PAD_PZL_IMG).handleId_;
	cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::PAD)][static_cast<int>(GameScene::MODE::STEALTH)] =
		rsM.Load(ResourceManager::SRC::PAD_STL_IMG).handleId_;

	okImg_ = rsM.Load(ResourceManager::SRC::SELECT_OK_IMG).handleId_;

	for (int i = 0; i < 3; i++)useImg_[i] = 0;
	useIdx_ = 0;
	isFinish_ = false;
	prevStick_ = 0;
	okPos_ = { 0,0 };
}

void Manual::Update(void)
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

void Manual::Draw(void)
{
	//マニュアル描画
	DrawGraph(0, 0, useImg_[useIdx_], false);
	//最終ページのみＯＫを描画
	if (useIdx_ == MANUAL_PAGE - 1)
	{
		DrawRotaGraph(okPos_.x, okPos_.y,
			1.0f,
			0.0f * Utility::DEG2RAD,
			okImg_,
			true,
			false);
	}
}

void Manual::SetManual(GameScene::MODE mode, SceneManager::CONTROLLER cnt)
{
	useImg_[0] = manualImg_[static_cast<int>(mode)][0];
	useImg_[1] = manualImg_[static_cast<int>(mode)][1];
	useImg_[2] = cntManualImg_[static_cast<int>(cnt)][static_cast<int>(mode)];
	useIdx_ = 0;
	isFinish_ = false;
	prevStick_ = 0;
	switch (cnt)
	{
	case SceneManager::CONTROLLER::KEYBOARD:
		okPos_ = { OK_KBD_X,OK_KBD_Y };
		break;
	case SceneManager::CONTROLLER::PAD:
		okPos_ = { OK_PAD_X,OK_PAD_Y };
		break;
	}
}

bool Manual::IsFinish(void)
{
	return isFinish_;
}

void Manual::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	//キーボードの動きによってページが進むか戻るかを決める
	if (ins.IsTrgDown(KEY_INPUT_LEFT))
	{
		useIdx_--;
		snd.PlaySndMove();
		if (useIdx_ < 0)useIdx_ = 0;
	}
	if (ins.IsTrgDown(KEY_INPUT_RIGHT))
	{
		useIdx_++;
		snd.PlaySndMove();
		if (useIdx_ >= MANUAL_PAGE)useIdx_ = MANUAL_PAGE - 1;
	}
	if (useIdx_ == MANUAL_PAGE - 1)
	{
		//マニュアルの終了
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			snd.PlaySndEnter(true);
			isFinish_ = true;
		}
	}
}

void Manual::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	// 左スティックの横軸
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	//前のフレームがニュートラルだった時
	if (prevStick_ == 0)
	{
		//コントローラーの動きによってページが進むか戻るかを決める
		if (leftStickX < 0)
		{
			useIdx_--;
			snd.PlaySndMove();
			if (useIdx_ < 0)useIdx_ = 0;
		}
		if (leftStickX > 0)
		{
			useIdx_++;
			snd.PlaySndMove();
			if (useIdx_ >= MANUAL_PAGE)useIdx_ = MANUAL_PAGE - 1;
		}
	}
	if (useIdx_ == MANUAL_PAGE - 1)
	{
		//マニュアルの終了
		if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
		{
			snd.PlaySndEnter(true);
			isFinish_ = true;
		}
	}
	

	prevStick_ = leftStickX;
}

Manual::Manual(void)
{
}

void Manual::Destroy(void)
{
	delete instance_;
}
