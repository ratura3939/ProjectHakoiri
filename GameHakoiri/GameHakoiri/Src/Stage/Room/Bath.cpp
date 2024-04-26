#include<DxLib.h>
#include"RoomBase.h"
#include "Bath.h"

//パラメータの設定
void Bath::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::BATH;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame.png");

	//テスト用
	dbgColor_ = 0x4169e1;
}