#include<DxLib.h>
#include"RoomBase.h"
#include "Entrance.h"

//パラメータの設定
void Entrance::SetParam(void)
{
	PazzleSize_ = { 2.0f,1.0f };
	StealthSize_ = { 60.0f,30.0f };
	type_ = RoomBase::TYPE::ENTRANCE;

	

	//テスト用
	dbgColor_ = 0xff8c00;
}