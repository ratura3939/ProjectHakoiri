#include<DxLib.h>

#include"../Manager/InputManager.h"
#include "Pazzle.h"

//コンストラクタ
//********************************************************
Pazzle::Pazzle(void)
{

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
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
}

// ゲームパッドの操作
void Pazzle::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
}
