#include<DxLib.h>
#include"RoomBase.h"
#include "Wall.h"

//パラメータの設定
void Wall::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::WALL;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/frame.png");

	//テスト用
	dbgColor_ = 0x8b4513;
}