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
	if (!isSelect_)
	{
		//カーソルの移動受付
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::RIGHT);
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

		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_Q))
		{
			ChangeIsSelect(false);
		}
	}
}

// ゲームパッドの操作
//********************************************************
void Pazzle::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
}

//IsSelectの変更
//********************************************************
void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}
