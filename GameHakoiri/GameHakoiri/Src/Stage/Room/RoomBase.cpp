#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//コンストラクタ
//********************************************************
RoomBase::RoomBase(void)
{
	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };
	mapSize_ = { 1.0f,1.0f };
	isCursor_ = false;
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
	isCursor_ = false;

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

#pragma region 描画

void RoomBase::Draw(void)
{
	DrawPazzle();
}
#pragma endregion


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

#pragma region 部屋の種類のSetGet

void RoomBase::SetRoomType(TYPE type)
{
	type_ = type;
}

RoomBase::TYPE RoomBase::GetRoomType(void)
{
	return type_;
}
#pragma endregion



#pragma region パズルのSetGet

void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
Vector2F RoomBase::GetPzlPos(void)
{
	return pzlPos_;
}
#pragma endregion

#pragma region マップのSetGet

void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

Vector2F RoomBase::GetMapPos(void)
{
	return mapPos_;
}
#pragma endregion

#pragma region カーソルのSetGet

void RoomBase::SetIsCursor(bool flag)
{
	isCursor_ = flag;
}

bool RoomBase::GetIsCursor(void)
{
	return isCursor_;
}
#pragma endregion





#pragma region いずれ消すもの

void RoomBase::SetColor(int col)
{
	dbgColor_ = col;
}
int RoomBase::GetColor(void)
{
	return dbgColor_;
}
#pragma endregion


//部屋ごとのパラメータ設定
//********************************************************
void RoomBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}