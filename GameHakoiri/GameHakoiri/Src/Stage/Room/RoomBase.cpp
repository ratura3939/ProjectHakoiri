#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//コンストラクタ
//********************************************************
RoomBase::RoomBase(void)
{

}
//デストラクタ
//********************************************************
RoomBase::~RoomBase(void)
{

}

//初期化
//********************************************************
bool RoomBase::Init(void)
{
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };

	//各性質の設定
	SetParam();
	//駒の大きさの設定
	pieceSize_ = { PazzleSize_.x_ * static_cast<float>(UNIT_PAZZLE_SIZE_X),
		PazzleSize_.y_ * static_cast<float>(UNIT_PAZZLE_SIZE_Y) };

	//マップの大きさの設定
	mapSize_ = { StealthSize_.x_ * UNIT_STEALTH_SIZE_X,
		StealthSize_.y_ * UNIT_STEALTH_SIZE_Y };


	//正しく処理が終了したので
	return true;
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
}
//ステルスシーンにおける部屋の描画
//********************************************************
void RoomBase::DrawStealth(void)
{
	//マップの描画カメラとの関係も必要
}
//解放
//********************************************************
bool RoomBase::Release(void)
{
	//画像の開放
	DeleteGraph(pieceImg_);

	//正しく処理が終了したので
	return true;
}

//パズル座標の設定
//********************************************************
void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
//マップの座標設定
//********************************************************
void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

//部屋ごとのパラメータ設定
//********************************************************
void RoomBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}