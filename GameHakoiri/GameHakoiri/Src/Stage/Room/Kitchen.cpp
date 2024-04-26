#include<DxLib.h>
#include"RoomBase.h"
#include "Kitchen.h"

//パラメータの設定
void Kitchen::SetParam(void)
{
	PazzleSize_ = { 1.0f,2.0f };
	StealthSize_ = { 30.0f,60.0f };
	type_ = RoomBase::TYPE::KITCHEN;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame_oblong.png");

	//テスト用
	dbgColor_ = 0xfaf0e6;
}