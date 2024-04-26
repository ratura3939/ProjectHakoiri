#include<DxLib.h>
#include"RoomBase.h"
#include "None.h"

//パラメータの設定
void None::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 0.0f,0.0f };
	type_ = RoomBase::TYPE::NONE;
	//画像の格納
	frameImg_ = LoadGraph("Data/Img/waku.png");
	if (frameImg_ == -1)
	{
		OutputDebugString("NONEにて枠読み込み失敗");
	}

	//テスト用
	//dbgColor_ = 0x8b4513;
	dbgColor_ = 0x000000;
}