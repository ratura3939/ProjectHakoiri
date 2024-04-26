#include<DxLib.h>
#include"RoomBase.h"
#include "Living.h"

//パラメータの設定
void Living::SetParam(void)
{
	PazzleSize_ = { 1.0f,2.0f };
	StealthSize_ = { 30.0f,60.0f };
	type_ = RoomBase::TYPE::LIVING;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame_oblong.png");

	//テスト用
	dbgColor_ = 0xffff00;
}