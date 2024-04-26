#include<DxLib.h>
#include"RoomBase.h"
#include "Own.h"

//パラメータの設定
void Own::SetParam(void)
{
	PazzleSize_ = { 2.0f,1.0f };
	StealthSize_ = { 60.0f,30.0f };
	type_ = RoomBase::TYPE::OWN;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame_oblong_2.png");

	//テスト用
	dbgColor_ = 0xff69b4;
}