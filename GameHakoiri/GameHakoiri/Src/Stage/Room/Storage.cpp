#include<DxLib.h>
#include"RoomBase.h"
#include "Storage.h"

//パラメータの設定
void Storage::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::STORAGE;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame.png");

	//テスト用
	dbgColor_ = 0x4b0082;
}