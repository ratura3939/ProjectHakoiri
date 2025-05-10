#include<DxLib.h>
#include"../../Application.h"
#include"../../Common/Vector2.h"
#include"../../Manager/SceneManager.h"
#include"../../Manager/StageManager.h"
#include"../../Manager/Camera.h"

#include"RoomBase.h"

//コンストラクタ
//********************************************************
RoomBase::RoomBase(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
{
	roomImg_ = roomImg;
	mapSize_.x = sizeX;
	mapSize_.y = sizeY;

	map_ = map;
	obj_ = obj;
	mapchip_ = mapchip;


	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
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
	isCursor_ = false;
	isChange_ = false;
	isClone_ = false;

	//各性質の設定
	SetParam();
	//駒の大きさの設定
	pieceSize_ = { pazzleSize_.x * static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X),
		pazzleSize_.y * static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y) };

	//マップの大きさの設定
	mapMaxSize_ = { mapSize_.x * StageManager::UNIT_STEALTH_SIZE_X,
		mapSize_.y * StageManager::UNIT_STEALTH_SIZE_Y };


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
	DrawGraph(pos.x, pos.y,
		roomImg_, true);
}

//ステルスシーンにおける部屋の描画
//********************************************************
void RoomBase::DrawStealth(void)
{
	//マップを表示しないところは描画処理を行わない
	if (!isDrawStealth_) { return; }

	//ステルス時の基本描画位置は{0,0}
	Vector2F pos = { 0.0f,0.0f };
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			//mapレイヤーの描画
			int mapchip = map_[y][x];
			DrawGraph(pos.x-cameraPos.x,
				pos.y-cameraPos.y,
				mapchip_[mapchip],
				false);

			mapchip = obj_[y][x];
			if (mapchip != -1)		//画像が存在するとき
			{
				DrawGraph(
					pos.x - cameraPos.x,
					pos.y - cameraPos.y,
					mapchip_[mapchip],
					true);
			}

			pos.x += StageManager::UNIT_STEALTH_SIZE_X;
		}
		pos.x = 0;
		pos.y += StageManager::UNIT_STEALTH_SIZE_Y;
	}
	
}
void RoomBase::DrawStealthObject(void)
{
	Vector2F pos = { 0.0f,0.0f };
	pos.x += StageManager::UNIT_STEALTH_SIZE_X / 2;
	pos.y += StageManager::UNIT_STEALTH_SIZE_Y / 2;
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			//objレイヤーの描画
			int mapchip = obj_[y][x];
			if (mapchip != -1)		//画像が存在するとき
			{
				DrawRotaGraph(
					pos.x - cameraPos.x,
					pos.y - cameraPos.y,
					1.0f,
					Utility::DEG2RAD,
					mapchip_[mapchip],
					true,
					false);
			}
			pos.x += StageManager::UNIT_STEALTH_SIZE_X;
		}
		pos.x = StageManager::UNIT_STEALTH_SIZE_X / 2;
		pos.y += StageManager::UNIT_STEALTH_SIZE_Y;
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

const RoomBase::TYPE RoomBase::GetRoomType(void)const
{
	return type_;
}
#pragma endregion



#pragma region パズルのSetGet

void RoomBase::SetPzlPos(const Vector2F pos)
{
	pzlPos_ = pos;
}
const Vector2F RoomBase::GetPzlPos(void)const
{
	return pzlPos_;
}
#pragma endregion

#pragma region カーソルのSetGet

void RoomBase::SetIsCursor(const bool flag)
{
	isCursor_ = flag;
}

const bool RoomBase::GetIsCursor(void)const
{
	return isCursor_;
}
const bool RoomBase::IsChange(void)const 
{
	return isChange_;
}
void RoomBase::SetIsChange(const bool flag)
{
	isChange_ = flag;
}
void RoomBase::SetIsDrawRoom(const bool flag)
{
	isDrawRoom_ = flag;
}
 Vector2F RoomBase::GetRoomSize(void) const
{
	return mapSize_;
}
const int RoomBase::GetObj(const Vector2 pos) const
{
	return obj_[pos.y][pos.x];
}
const int RoomBase::GetMapchip(const Vector2 pos) const
{
	return map_[pos.y][pos.x];
}
const bool RoomBase::IsOneDownObj(const Vector2 pos)const
{
	Vector2 serchPos = pos;

	//一つ下に
	serchPos.y++;

	if (obj_[serchPos.y][serchPos.x] == -1)	//オブジェクトが何も入っていなかったら
	{
		return true;
	}
	return false;
}
const bool RoomBase::IsClone(void) const
{
	return isClone_;
}
void RoomBase::SetIsClone(const bool flag)
{
	isClone_ = flag;
}
#pragma endregion

//部屋ごとのパラメータ設定
//********************************************************
void RoomBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}