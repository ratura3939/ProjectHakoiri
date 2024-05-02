#include<DxLib.h>
#include"RoomBase.h"
#include "Own.h"

//パラメータの設定
void Own::SetParam(void)
{
	PazzleSize_ = { 2.0f,1.0f };
	StealthSize_ = { 60.0f,30.0f };
	type_ = RoomBase::TYPE::OWN;


	//テスト用
	dbgColor_ = 0xff69b4;
}