#include<DxLib.h>
#include"RoomBase.h"
#include "Storage.h"

//パラメータの設定
void Storage::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::STORAGE;


	//テスト用
	dbgColor_ = 0x4b0082;
}