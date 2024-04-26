#include<DxLib.h>
#include"../../Common/Vector2.h"
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

//パズルシーンにおける部屋の描画
//********************************************************
void RoomBase::DrawPazzle(void)
{
	Vector2 pos = pzlPos_.ToVector2();
	DrawBox(pos.x_, pos.y_,
		pos.x_ + static_cast<int>(pieceSize_.x_),
		pos.y_ + static_cast<int>(pieceSize_.y_),
		dbgColor_, true);

	//枠の描画
	if (isCursor_
		&& type_==RoomBase::TYPE::NONE)
	{
		DrawGraph(pos.x_, pos.y_, frameImg_, true);
	}
}

//長方形の駒の補助
void None::ChangeRole(RoomBase::TYPE type, int clr)
{
	type_ = type;
	dbgColor_ = clr;
}