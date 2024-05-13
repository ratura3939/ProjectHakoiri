#include<DxLib.h>

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Scene/GameScene.h"
#include "Pazzle.h"	

//コンストラクタ
//********************************************************
Pazzle::Pazzle(void)
{
	isFinish_ = false;
	isSelect_ = false;
	isNeutral_ = true;
	neutralStick_ = { 0,0 };
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

#pragma region キーボード

// キーボードの操作
//********************************************************
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
	StageManager& stage = StageManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		ChangeIsFinish(true);
		return;
	}

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
#pragma endregion


#pragma region パッド操作

// ゲームパッドの操作
//********************************************************
void Pazzle::GamePadController(void)
{
	
	InputManager& ins = InputManager::GetInstance();
	StageManager& stage = StageManager::GetInstance();

	//パズル完了次のモードに移行
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		ChangeIsFinish(true);
		return;
	}




	// 左スティックの横軸
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	// 左スティックの縦軸
	auto leftStickY = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;
	//スティックの動きを合わせて保存
	Vector2 inputStick = { leftStickX,leftStickY };

	//ニュートラルに戻すか判定
	if (!isNeutral_)
	{
		//現在がニュートラルかを判断
		if (IsStickNeutral(inputStick))
		{
			ChangeIsNeutral(true);
		}
	}
	

	//スティックがニュートラル状態のとき
	if (isNeutral_)
	{
		//駒の選択中ではないとき
		if (!isSelect_)
		{
			//盤面リセット
			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP))
			{
				stage.PazzleReset();
			}

			//スティックが移動しているとき
			if (abs(leftStickY) > 0 ||
				abs(leftStickX) > 0)
			{
				stage.MoveCursor(MoveStick(inputStick));
			}
			
			//駒の選択
			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				ChangeIsSelect(true);
			}
		}
		else
		{
			//駒の移動受付
			//スティックが移動しているとき
			if (abs(leftStickY) > 0 ||
				abs(leftStickX) > 0)
			{
				stage.MovePiece(MoveStick(inputStick));
			}

			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				ChangeIsSelect(false);
			}
		}
	}
}
#pragma endregion


#pragma region フラグのゲッター

bool Pazzle::IsSelect(void)
{
	return isSelect_;
}

bool Pazzle::IsNeutral(void)
{
	return isNeutral_;
}

bool Pazzle::IsFinish(void)
{
	return isFinish_;
}
#pragma endregion

#pragma region フラグのセッター

void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}

void Pazzle::ChangeIsNeutral(bool flag)
{
	isNeutral_ = flag;
}

void Pazzle::ChangeIsFinish(bool flag)
{
	isFinish_ = flag;
}
#pragma endregion


#pragma region Lスティック関連

//ニュートラル状態の判定
bool Pazzle::IsStickNeutral(Vector2 stick)
{
	if (neutralStick_.x_ == stick.x_ &&
		neutralStick_.y_ == stick.y_)
	{
		return true;
	}
	return false;
}

//移動した方向
Utility::DIR Pazzle::MoveStick(Vector2 stick)
{

	//縦軸の方が移動量が多い時
	if (abs(stick.y_) > abs(stick.x_))
	{
		if (stick.y_ < 0)
		{
			ChangeIsNeutral(false);
			return Utility::DIR::UP;
		}
		else
		{
			ChangeIsNeutral(false);
			return Utility::DIR::DOWN;
		}
	}
	else
	{
		if (stick.x_ > 0)
		{
			ChangeIsNeutral(false);
			return Utility::DIR::RIGHT;
		}
		else
		{
			ChangeIsNeutral(false);
			return Utility::DIR::LEFT;
		}
	}
}

#pragma endregion

