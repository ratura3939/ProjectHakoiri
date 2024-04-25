#include<DxLib.h>
#include"RoomBase.h"
#include"Wasitu.h"

//パラメータの設定
void Wasitu::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 30.0f,30.0f };
	type_ = RoomBase::TYPE::WASITU;

	//画像の格納
	frameImg_ = LoadGraph("Data/Img/waku.png");
	if (frameImg_ == -1)
	{
		OutputDebugString("NONEにて枠読み込み失敗");
	}

	//テスト用
	dbgColor_ = 0x00ff00;
}