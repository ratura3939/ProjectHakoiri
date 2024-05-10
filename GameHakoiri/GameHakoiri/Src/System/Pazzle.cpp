#include<DxLib.h>

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include "Pazzle.h"

//コンストラクタ
//********************************************************
Pazzle::Pazzle(void)
{
	isSelect_ = false;
}
//デストラクタ
//********************************************************
Pazzle::~Pazzle(void)
{

}
//更新
//********************************************************
void Pazzle::Update(void)
{
	//
	StageManager& stage = StageManager::GetInstance();
	stage.SetFlash(isSelect_);
	//StageMng経由でroomMngの変更を行う
	//入力系
	KeyboardContoroller();
	GamePadController();
}

// キーボードの操作
//********************************************************
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
	StageManager& stage = StageManager::GetInstance();
	
	if (!isSelect_)
	{
		//盤面リセット
		if (ins.IsTrgDown(KEY_INPUT_R))
		{
			stage.PazzleReset();
		}
		//カーソルの移動受付
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{
			stage.MoveCursor(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			stage.MoveCursor(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			stage.MoveCursor(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			stage.MoveCursor(Utility::DIR::RIGHT);
		}
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ChangeIsSelect(true);
		}
	}
	else
	{
		//駒の移動受付
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{
			stage.MovePiece(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			stage.MovePiece(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			stage.MovePiece(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			stage.MovePiece(Utility::DIR::RIGHT);
		}
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ChangeIsSelect(false);
		}
	}
}

#pragma region パッド操作

// ゲームパッドの操作
//********************************************************
void Pazzle::GamePadController(void)
{
	//InputManager& ins = InputManager::GetInstance();
	//StageManager& stage = StageManager::GetInstance();

	//if (!isSelect_)
	//{
	//	//盤面リセット
	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.PazzleReset();
	//	}
	//	//カーソルの移動受付
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.MoveCursor(Utility::DIR::UP);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		stage.MoveCursor(Utility::DIR::DOWN);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
	//	{
	//		stage.MoveCursor(Utility::DIR::LEFT);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		stage.MoveCursor(Utility::DIR::RIGHT);
	//	}
	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		ChangeIsSelect(true);
	//	}
	//}
	//else
	//{
	//	//駒の移動受付
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.MovePiece(Utility::DIR::UP);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		stage.MovePiece(Utility::DIR::DOWN);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
	//	{
	//		stage.MovePiece(Utility::DIR::LEFT);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		stage.MovePiece(Utility::DIR::RIGHT);
	//	}

	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		ChangeIsSelect(false);
	//	}
	//}
}
#pragma endregion

bool Pazzle::IsSelect(void)
{
	return isSelect_;
}

//IsSelectの変更
//********************************************************
void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}
