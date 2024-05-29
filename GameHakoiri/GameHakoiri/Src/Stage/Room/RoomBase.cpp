#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//コンストラクタ
//********************************************************
RoomBase::RoomBase(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
{
	roomImg_ = roomImg;
	mapSize_.x_ = sizeX;
	mapSize_.y_ = sizeY;

	map_ = map;
	obj_ = obj;
	mapchip_ = mapchip;


	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };
	mapMaxSize_ = { 1.0f,1.0f };
	isCursor_ = false;
	isChange_ = false;
	isDrawRoom_ = false;
	isDrawStealth_ = true;	//マップの情報があるため描画する
}
RoomBase::RoomBase(int roomImg)
{
	roomImg_ = roomImg;

	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };

	isCursor_ = false;
	isChange_ = false;
	isDrawRoom_ = false;
	isDrawStealth_ = false;	//マップの情報がないため描画しない
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
	isChange_ = false;

	//各性質の設定
	SetParam();
	//駒の大きさの設定
	pieceSize_ = { pazzleSize_.x_ * static_cast<float>(UNIT_PAZZLE_SIZE_X),
		pazzleSize_.y_ * static_cast<float>(UNIT_PAZZLE_SIZE_Y) };

	//マップの大きさの設定
	mapMaxSize_ = { mapSize_.x_ * UNIT_STEALTH_SIZE_X,
		mapSize_.y_ * UNIT_STEALTH_SIZE_Y };


	//正しく処理が終了したので
	return true;
}



#pragma region 描画

//パズルシーンにおける部屋の描画
//********************************************************
void RoomBase::DrawPazzle(void)
{
	if (!isDrawRoom_) { return; }

	Vector2 pos = pzlPos_.ToVector2();
	DrawGraph(pos.x_, pos.y_,
		roomImg_, true);
}

//ステルスシーンにおける部屋の描画
//********************************************************
void RoomBase::DrawStealth(void)
{
	//マップを表示しないところは描画処理を行わない
	if (!isDrawStealth_) { return; }

	Vector2F pos = mapPos_;

	for (int y = 0; y < mapSize_.y_; y++)
	{
		for (int x = 0; x < mapSize_.x_; x++)
		{
			//mapレイヤーの描画
			int mapchip = map_[y][x];
			DrawGraph(pos.x_, pos.y_,
				mapchip_[mapchip],
				false);

			//objレイヤーの描画
			mapchip = obj_[y][x];
			if (mapchip != -1)		//画像が存在するとき
			{
				DrawGraph(pos.x_, pos.y_,
					mapchip_[mapchip],
					true);
			}
			pos.x_ += UNIT_STEALTH_SIZE_X;
		}
		pos.x_ = 0;
		pos.y_ += UNIT_STEALTH_SIZE_Y;
	}
	
}
#pragma endregion



//解放
//********************************************************
bool RoomBase::Release(void)
{

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
bool RoomBase::IsChange(void)
{
	return isChange_;
}
void RoomBase::SetIsChange(bool flag)
{
	isChange_ = flag;
}
void RoomBase::SetIsDrawRoom(bool flag)
{
	isDrawRoom_ = flag;
}
#pragma endregion

//部屋ごとのパラメータ設定
//********************************************************
void RoomBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}