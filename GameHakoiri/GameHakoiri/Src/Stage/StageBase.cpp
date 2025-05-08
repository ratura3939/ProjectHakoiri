#include<DxLib.h>
#include<iostream>

#include"../Application.h"
#include"../Utility/Utility.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/StageManager.h"
#include"Room/RoomBase.h"
#include"Room/None.h"
#include"Room/Own.h"
#include"Room/Wasitu.h"
#include"Room/Living.h"
#include"Room/Bath.h"
#include"Room/Storage.h"
#include"Room/Kitchen.h"
#include"Room/Entrance.h"
#include"Room/Wall.h"
#include"Room/Goal.h"


#include"StageBase.h"

//コンストラクタ
//********************************************************
StageBase::StageBase(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
	std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
	int* roomImg, int* mapchip[])
{
	pzlCsv_ = pzlIt;
	size_.x = pzlSizeX;
	size_.y = pzlSizeY;

	mapCsv_ = map;
	objCsv_ = obj;
	roomImg_ = roomImg;
	mapchip_ = mapchip;

	roomKey_ = "00";
	doorSpare_ = StageManager::DOOR_Y::NONE;
}
//デストラクタ
//********************************************************
StageBase::~StageBase(void)
{

}

//初期化
//********************************************************
bool StageBase::Init(void)
{
	frameAnim_ = 0;
	//フラグの初期化
	SetFrameFlash(false);
	SetIsMoveRoom(true);
	SetIsSecondRoom(false);
	SetIsGoal(false);

	//各ステージによる設定
	SetParam();
	//パズル配置の読み込み
	//LoadPazzle();
	//画像読み込み
	LoadImgs();

	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 4),
		static_cast<float>(Application::SCREEN_SIZE_Y / 8) };

	goalPos_ = { 0,0 };

	std::unique_ptr<RoomBase>createRoom;

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{

			switch (static_cast<RoomBase::TYPE>(pzlCsv_[y][x]))
			{
			//空きスペース
			case RoomBase::TYPE::NONE: 
				createRoom = std::make_unique<None>(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
				createRoom->Init();
				break;

			//自室
			case RoomBase::TYPE::OWN: 
				createRoom = std::make_unique<Own>(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)],
					StageManager::OBLONG_2_MAP_X, StageManager::OBLONG_2_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)],
					objCsv_[static_cast<int>(RoomBase::TYPE::OWN)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				createRoom->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, *createRoom))createRoom = std::move(GetSecondRoomInstance(*createRoom));
				break;
			//和室
			case RoomBase::TYPE::WASITU:
				createRoom = std::make_unique<Wasitu>(roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)],
					objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				createRoom->Init();
				break;
			//居間
			case RoomBase::TYPE::LIVING:
				createRoom = std::make_unique<Living>(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)],
					StageManager::OBLONG_MAP_X, StageManager::OBLONG_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)],
					objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				createRoom->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, *createRoom))createRoom = std::move(GetSecondRoomInstance(*createRoom));
				break;
			//風呂
			case RoomBase::TYPE::BATH: 
				createRoom = std::make_unique<Bath>(roomImg_[static_cast<int>(RoomBase::TYPE::BATH)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)],
					objCsv_[static_cast<int>(RoomBase::TYPE::BATH)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::BATH)]);
				createRoom->Init();
				break;
			//物置
			case RoomBase::TYPE::STORAGE:
				createRoom = std::make_unique<Storage>(roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				createRoom->Init();
				break;
			//台所
			case RoomBase::TYPE::KITCHEN: 
				createRoom = std::make_unique<Kitchen>(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					StageManager::OBLONG_MAP_X, StageManager::OBLONG_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				createRoom->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, *createRoom))createRoom = std::move(GetSecondRoomInstance(*createRoom));
				break;
			//玄関
			case RoomBase::TYPE::ENTRANCE: 
				createRoom = std::make_unique<Entrance>(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					StageManager::OBLONG_2_MAP_X, StageManager::OBLONG_2_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::EXTERIA)]);
				createRoom->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, *createRoom)) { createRoom = GetSecondRoomInstance(*createRoom); }
				break;
			//壁
			case RoomBase::TYPE::WALL:	
				createRoom = std::make_unique<Wall>(roomImg_[static_cast<int>(RoomBase::TYPE::WALL)]);
				createRoom->Init();
				break;
			//ゴール
			case RoomBase::TYPE::GOAL:
				createRoom = std::make_unique<Goal>(roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)]);
				createRoom->Init();
				goalPos_ = { x,y };
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = std::move(createRoom);//配列内に格納
			resetRoom_[roomKey_] = roomMng_[roomKey_]->GetRoomType();
			resetRoomClone_[roomKey_] = roomMng_[roomKey_]->IsClone();
			pzlPos_[roomKey_] = pos;

			//座標の更新
			pos.x += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X);
		}
		pos.x = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y);
	}

	//初期のカーソル設定
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (!IsDontMoveBlock(roomKey_) &&
				roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::NONE)
			{
				roomMng_[roomKey_]->SetIsCursor(true);
				//正しく処理が終了したので
				return true;
			}
		}
	}
	//正しく処理が終了したので
	return true;
}

bool StageBase::InitStealth(void)
{
	//現在のカーソルを解除
	roomMng_[roomKey_]->SetIsCursor(false);

	//パズル描画の位置変更
	Vector2F pos = { 0.0f,0.0f };

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			pzlPos_[roomKey_] = pos;
			//座標の更新
			pos.x += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X);
		}
		pos.x = 0.0f;
		pos.y += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y);
	}


	//以前のカーソルを非表示に
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->SetIsCursor(false);
		}
	}

	//初期位置の場所を示すルームキーを生成
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::OWN)
			{
				//現在地にカーソルセット
				roomMng_[roomKey_]->SetIsCursor(true);
				//正しく処理が終了したので
				return true;
			}
		}
	}

	//処理未遂
	return false;
}

void StageBase::DrawObject(void)
{
	roomMng_[roomKey_]->DrawStealthObject();
}

#pragma region 更新

void StageBase::Update(GameScene::MODE mode)
{
	
}

#pragma endregion



#pragma region 描画

void StageBase::Draw(GameScene::MODE mode)
{
	switch (mode)
	{
	case GameScene::MODE::PAZZLE:
		DrawPazzle();
		break;
	case GameScene::MODE::STEALTH:
		DrawStealth();
		break;
	default:
		break;
	}
}
#pragma region パズルシーン

	void StageBase::DrawPazzle(void)
	{		
		frameAnim_++;

		//駒の描画
		for (int y = 0; y < size_.y; y++)
		{
			for (int x = 0; x < size_.x; x++)
			{
				CreateKey(y, x);
				roomMng_[roomKey_]->SetPzlPos(pzlPos_[roomKey_]);
				roomMng_[roomKey_]->DrawPazzle();
			}
			
		}
 		if (frameFlash_)
		{
			if (frameAnim_ % (Application::FPS / 2) < FRAME_INTERVAL)
			{
				//枠の描画
				DrawCursor();
			}
		}
		else
		{
			//枠の描画
			DrawCursor();
		}
	}

	#pragma endregion

#pragma region カーソル

	void StageBase::DrawCursor(void)
	{
		Vector2 key = GetNowCursorPos();

		CreateKey(key.y, key.x);
		switch (roomMng_[roomKey_]->GetRoomType())
		{
			// 空きスペース
		case RoomBase::TYPE::NONE:
			//和室
		case RoomBase::TYPE::WASITU:
			//風呂
		case RoomBase::TYPE::BATH:
			//物置
		case RoomBase::TYPE::STORAGE:
			//壁
		case RoomBase::TYPE::WALL:
			//ゴール
		case RoomBase::TYPE::GOAL:
			SetCursorType(CURSOR::NORMAL);
			break;
			//縦長
			//居間
		case RoomBase::TYPE::LIVING:
			//台所
		case RoomBase::TYPE::KITCHEN:
			SetCursorType(CURSOR::OBLONG);
			break;

			//横長
			//自室
		case RoomBase::TYPE::OWN:
			//玄関
		case RoomBase::TYPE::ENTRANCE:
			SetCursorType(CURSOR::OBLONG_2);
			break;
		}
		if (roomMng_[roomKey_]->GetIsCursor())
		{
			//枠の描画
			DrawGraph(pzlPos_[roomKey_].x, pzlPos_[roomKey_].y,
				frame_[static_cast<int>(type_)], true);
		}
	}

	
	
#pragma endregion

#pragma region ステルス

	void StageBase::DrawStealth(void)
	{
		roomMng_[roomKey_]->DrawStealth();
	}
#pragma endregion


#pragma endregion

//解放
//********************************************************
bool StageBase::Release(void)
{
	//駒

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
		}
	}

	//正しく処理が終了したので
	return true;
}

//ステージごとのパラメータ設定
//********************************************************
void StageBase::SetParam(void)
{
	//この関数は派生先ごとのものなので関係なし
}
//連想配列のキー生成
//********************************************************
void StageBase::CreateKey(int y, int x)
{
	std::string key= std::to_string(y) + std::to_string(x);
	roomKey_ = key;
}

std::string StageBase::GetKey(void) const
{
	return roomKey_;
}

#pragma region ステルスのいろいろ

//現在描画しているマップの最大サイズを取得
//********************************************************
Vector2F StageBase::GetNowDrawMapSize(void)
{
	Vector2F mapMax = roomMng_[roomKey_]->GetRoomSize() *
		Vector2F {
		StageManager::UNIT_STEALTH_SIZE_X, StageManager::UNIT_STEALTH_SIZE_Y
	};
	return mapMax;
}

//指定した座標はオブジェクトがあるか
//********************************************************
const bool StageBase::IsMapObj(const Vector2 pMapPos)
{
	if (roomMng_[roomKey_]->GetObj(pMapPos) != -1)	//指定した場所にオブジェクトがあったら
	{
		return true;
	}
	return false;
}
const bool StageBase::IsMoveRoom(void)const
{
	return isMoveRoom_;
}
//指定された場所のオブジェクト取得
//********************************************************
const int StageBase::GetObjNum(const Vector2 pMapPos)
{
	return roomMng_[roomKey_]->GetObj(pMapPos);
}
//指定された場所のマップチップ取得
//********************************************************
const int StageBase::GetMapNum(const Vector2 pMapPos)
{
	return roomMng_[roomKey_]->GetMapchip(pMapPos);
}
//現在の部屋が使用するマップチップの種類を返す。
//********************************************************
const StageManager::MAPCHIP StageBase::GetMapchipType(void)
{
	auto type = roomMng_[roomKey_]->GetRoomType();
	//Bathのマップチップを使用するのはBathRoomのみ
	if (type == RoomBase::TYPE::BATH)
	{
		return StageManager::MAPCHIP::BATH;
	}
	//Exteriaのマップチップを使用するのはEntranceRoomのみ
	if (type == RoomBase::TYPE::ENTRANCE)
	{
		return StageManager::MAPCHIP::EXTERIA;
	}

	return StageManager::MAPCHIP::INTERIA;
}
const RoomBase::ROOM_SHAPE StageBase::GetNowShape(void)
{
	return GetRoomShape(roomKey_);
}
//一つ下にオブジェクトがあるかを調べる
//********************************************************
const bool StageBase::CheckOneDownObject(const Vector2 pMapPos)
{
	return roomMng_[roomKey_]->IsOneDownObj(pMapPos);
}
//部屋を変える
//********************************************************
void StageBase::ChangeRoom(const Vector2 pMapPos)
{
	//ドアの位置取得
	door_ = SearchDoor(pMapPos);
	//部屋の移動量
	Vector2 move = { 0,0 };
	//移動後の部屋を保持
	Vector2 afterRoom;
	//現在の部屋を保持
	auto nowRoom = roomKey_;
	//現在の部屋をroomKeyから逆算
	//roomKey=(yx)なので10で割った時の商がY,余りがXを表す
	afterRoom.y = stoi(nowRoom) / STRING_TO_INT;
	afterRoom.x = stoi(nowRoom) % STRING_TO_INT;
	
	//扉の位置による部屋の移動量を計算
	if (door_.y == StageManager::DOOR_Y::TOP) 
	{ 
		//一つ上の部屋に
		move.y--; 

		//現在の場所が長方形だった場合
		if (GetRoomShape(nowRoom)!=RoomBase::ROOM_SHAPE::NOMAL)	
		{
			//現在部屋が横長で、右上の扉だった場合
			if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
			{
				//左右移動
				move += MoveLeftOrRight(door_.x);
			}
			//現在部屋が縦長で、左右の扉(上の下)だった場合
			if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG && doorSpare_ == StageManager::DOOR_Y::BOTTOM)
			{
				//上への移動ではないため高さを戻す
				move.y++;
				//左右移動
				move += MoveLeftOrRight(door_.x);
			}
		}
	}	

	else if (door_.y == StageManager::DOOR_Y::BOTTOM) 
	{
		//一つ下の部屋に
		move.y++;

		//現在部屋が横長で、右上の扉だった場合
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
		{
			//左右移動
			move += MoveLeftOrRight(door_.x);
		}
		//現在部屋が縦長
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG )
		{
			if (doorSpare_ == StageManager::DOOR_Y::BOTTOM)
			{
				//縦ニマスの部屋の下への移動なのでニマス分下げるため
				move.y++;
			}
			//左右の扉(下の上)だった場合
			if (doorSpare_ == StageManager::DOOR_Y::TOP)
			{
				//左右移動
				move += MoveLeftOrRight(door_.x);
			}
		}
	}	
	else if (door_.y == StageManager::DOOR_Y::MIDDLE)
	{
		//左右移動
		move += MoveLeftOrRight(door_.x);
		//現在部屋が横長で、右上の扉だった場合
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
		{
			//左右移動
			move += MoveLeftOrRight(door_.x);
		}
	}

	afterRoom += move;
	MoveRoom(afterRoom, nowRoom);
}
//出るのに使用したドアの位置を渡す
const StageManager::DOOR StageBase::GetDoorPos(void) const
{
	return door_;
}
const StageManager::DOOR_Y StageBase::GetDoorPosSecond(void) const
{
	return doorSpare_;
}
const bool StageBase::IsSecondRoom(void)const
{
	return isSecondRoom_;
}
const bool StageBase::IsGoal(void) const
{
	return isGoal_;
}
//ゴールにつながる部屋があるかどうか
const bool StageBase::CanGoal(void)
{
	auto pos = goalPos_;
	//ゴールマスの一つ上に部屋があるかを確認
	pos.y--;
	CreateKey(pos.y, pos.x);
	if (roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::NONE)
	{
		//上にマスがあった場合
		//そのマスの左右と上の➂方向のいずれかに部屋があるかを確認（全てのパズルは空きがニマスなので）
		auto flag = CheckAroundRoomAnything(pos);

		//念のため元に戻す
		pos.y++;
		CreateKey(pos.y, pos.x);
		return flag;
	}
	//念のため元に戻す
	pos.y++;
	CreateKey(pos.y, pos.x);

	return false;
}
void StageBase::MoveRoom(const Vector2 after, const std::string prvKey)
{
	SetIsMoveRoom(true);	//フラグリセット 移動できる前提
	SetIsSecondRoom(false);
	roomMng_[roomKey_]->SetIsCursor(false);

	auto moveAfter = after;
	

	//移動先の部屋の鍵生成
	CreateKey(moveAfter.y, moveAfter.x);
	auto type = roomMng_[roomKey_]->GetRoomType();

	//移動先がゴールだったら
	if (type == RoomBase::TYPE::GOAL)
	{
		SetIsGoal(true);
		return;
	}

	//移動先が部屋ではなかったら
	if (type == RoomBase::TYPE::NONE ||
		type == RoomBase::TYPE::WALL)
	{
		roomKey_ = prvKey;
		SetIsMoveRoom(false);	//フラグセット
		roomMng_[roomKey_]->SetIsCursor(true);

		return;
	}

	//長方形で実体ではないほうに出たとき
	if (GetRoomShape(roomKey_) != RoomBase::ROOM_SHAPE::NOMAL)
	{
		
		auto r = CreateInstance4Confirmation(type);
		//縦長の実体調整
		if (GetRoomShape(type) == RoomBase::ROOM_SHAPE::OBLONG)
		{
			if (CheckInstanceUp(moveAfter.y, moveAfter.x, r))
			{
				moveAfter.y--;
				CreateKey(moveAfter.y, moveAfter.x);
				SetIsSecondRoom(true);
			}
		}
		//横長の実体調整
		if (GetRoomShape(type) == RoomBase::ROOM_SHAPE::OBLONG_SIDE)
		{
			if (CheckInstanceLeft(moveAfter.y, moveAfter.x, r))
			{
				moveAfter.x--;
				CreateKey(moveAfter.y, moveAfter.x);
				SetIsSecondRoom(true);
			}
		}
	}

	//移動先にカーソルセット
	roomMng_[roomKey_]->SetIsCursor(true);
}
//左右移動
//********************************************************
const Vector2 StageBase::MoveLeftOrRight(const StageManager::DOOR_X door)const
{
	if (door == StageManager::DOOR_X::LEFT) { return { -1,0 }; }	//一つ左に
	if (door == StageManager::DOOR_X::RIGHT) { return { 1,0 }; }	//一つ右に
}
//ドアの位置検索
//********************************************************
const StageManager::DOOR StageBase::SearchDoor(const Vector2 pMapPos)
{
	StageManager::DOOR retDoorPos;
	Vector2 pPos = pMapPos;
	//判定スペアのリセット
	doorSpare_ = StageManager::DOOR_Y::NONE;

	//扉の位置を見つけるため部屋を分割。
	auto size = roomMng_[roomKey_]->GetRoomSize().ToVector2();

	size.x /= StageManager::SPLIT_ROOM_X;
	size.y /= StageManager::SPLIT_ROOM_Y;

	//探索初期位置
	Vector2 startPos = { 0,0 };

	retDoorPos = SplitRoom(pPos, size,startPos);

	//縦長の場合は二回目の判定が必要
	if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::KITCHEN ||
		roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::LIVING)
	{
		//二回目の判定は一回目で分割した上中下をさらに分割し扉を特定する(部屋の一部をズームする感じ)
		//プレイヤーの場所は一回目の分割の影響を受ける

		//判定初期位置を一回目のSplitRoomと同じにする用の変数(縦長マスなので気にかけるのはY軸だけ)
		StageManager::DOOR firstSplitDoor = retDoorPos;
		firstSplitDoor.y = static_cast<StageManager::DOOR_Y>(static_cast<int>(retDoorPos.y) - 1);

		//playerを上限からの距離に設定
		pPos.y -= size.y * static_cast<int>(firstSplitDoor.y);

		//移動の下限設定
		size.y /= static_cast<int>(StageManager::DOOR_Y::BOTTOM);	//サイズを三分割

		//判定初期位置を一回目のY部分基準(構造体の都合上-1でスタート位置にする）
		startPos.y = StageManager::SPLIT_ROOM_Y * static_cast<int>(firstSplitDoor.y);
		StageManager::DOOR oblongSecond = SplitRoom(pPos, size, startPos);

		doorSpare_ = oblongSecond.y;
	}
		
	return retDoorPos;
}
//マップを六分割したときplayerがどこにイルカを返却
const StageManager::DOOR StageBase::SplitRoom(const Vector2 pMapPos, const Vector2 size, const Vector2 startPos)const
{
	StageManager::DOOR ret;

	//左右の区別
	if (pMapPos.x < size.x) { ret.x = StageManager::DOOR_X::LEFT; }
	else { ret.x = StageManager::DOOR_X::RIGHT; }

	//上中下の判断（数の大きい下から行う
	//必ず下にはいるので初期値は下から
	ret.y = StageManager::DOOR_Y::BOTTOM;

	if (pMapPos.y < size.y * static_cast<int>(StageManager::DOOR_Y::MIDDLE))
	{
		ret.y = StageManager::DOOR_Y::MIDDLE;
	}
	if (pMapPos.y < size.y * static_cast<int>(StageManager::DOOR_Y::TOP))
	{
		ret.y = StageManager::DOOR_Y::TOP;
	}

	return ret;
}
#pragma endregion


#pragma region 現在のカーソル位置取得

const Vector2 StageBase::GetNowCursorPos(void)
{
	//現在のカーソルの位置を取得
	Vector2 cursor;

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (roomMng_[roomKey_]->GetIsCursor())
			{
				cursor = { x,y };
			}
		}
	}
	return cursor;
}



void StageBase::SetCursorType(const CURSOR type)
{
	type_ = type;
}
const StageManager::DOOR_Y StageBase::GetDoorSpare(void)const
{
	return doorSpare_;
}
#pragma endregion


#pragma region カーソルの移動

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//現在のカーソル位置
	Vector2 cursor = GetNowCursorPos();

	//現在のカーソルの解除
	CreateKey(cursor.y, cursor.x);	
	//実行前の位置を保存
	std::string prevKey = roomKey_;
	roomMng_[prevKey]->SetIsCursor(false);

	//カーソル位置の現在地からの移動
	switch (roomMng_[prevKey]->GetRoomType())
	{
		//空きスペース
	case RoomBase::TYPE::NONE:
		//和室
	case RoomBase::TYPE::WASITU:
		//風呂
	case RoomBase::TYPE::BATH:
		//物置
	case RoomBase::TYPE::STORAGE:
		//壁
	case RoomBase::TYPE::WALL:
		//ゴール
	case RoomBase::TYPE::GOAL:
		cursor.y += move.y;
		cursor.x += move.x;
		break;

		//縦長
		//居間
	case RoomBase::TYPE::LIVING:
		//台所
	case RoomBase::TYPE::KITCHEN:
		if (dir == Utility::DIR::DOWN) {cursor.y += move.y * 2;}
		else{cursor.y += move.y;}

		cursor.x += move.x;
		break;

		//横長
		//自室
	case RoomBase::TYPE::OWN:

		//玄関
	case RoomBase::TYPE::ENTRANCE:
		if (dir == Utility::DIR::RIGHT) { cursor.x += move.x * 2; }
		else { cursor.x += move.x; }

		cursor.y += move.y;
		break;
	}
	

	//移動後
	CreateKey(cursor.y, cursor.x);	//移動後のroomKey_の生成
	std::string afterMoveKey = roomKey_;		//移動後のroomKey_の生成保存

	RoomBase::TYPE afterRoomType = roomMng_[afterMoveKey]->GetRoomType();

#pragma region 移動後がNONEだった時,現在OFF
	//if (afterRoomType == RoomBase::TYPE::NONE)
	//{
	//	//追加で移動
	//	cursor.y_ += move.y_;
	//	cursor.x_ += move.x_;
	//	//追加移動先のキー関係
	//	CreateKey(cursor.y_, cursor.x_);	
	//	std::string afterMoveKey = roomKey_;
	//	afterRoomType = roomMng_[afterMoveKey]->GetRoomType();
	//}
#pragma endregion


#pragma region 長方形の二マス目だった時の処理
	if (GetRoomShape(afterRoomType)!=RoomBase::ROOM_SHAPE::NOMAL)
	{
		RoomBase& ret = CreateInstance4Confirmation(afterRoomType);

		//現在が長方形の本体かを確認
		if (roomMng_[afterMoveKey]->IsClone())
		{
			//保留のカーソルをキャンセル
			roomMng_[afterMoveKey]->SetIsCursor(false);
			//長方形に合わせた場所に移動
			if (afterRoomType == RoomBase::TYPE::KITCHEN || afterRoomType == RoomBase::TYPE::LIVING)
			{
				cursor.y--;
			}
			if (afterRoomType == RoomBase::TYPE::ENTRANCE ||afterRoomType == RoomBase::TYPE::OWN)
			{
				cursor.x--;
			}
			CreateKey(cursor.y, cursor.x);	//roomKey_の再生成
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		ret.Release();
	}
#pragma endregion

#pragma region 移動範囲外だった時

	if ((cursor.x >= size_.x)
		|| (cursor.y >= size_.y)
		|| IsDontMoveBlock(afterMoveKey))
	{
		//移動前に戻す
		roomMng_[prevKey]->SetIsCursor(true);
	}
	else
	{
		//長方形による変化があるかもなのでKEYは保留のものを使用
		roomMng_[roomKey_]->SetIsCursor(true);
	}
#pragma endregion
}
#pragma endregion

#pragma region 駒の入れ替え

//駒の入れかえ準備
void StageBase::SetPiece(Vector2 move, Utility::DIR dir)
{
	std::string nowCursorKey;	//現在のカーソル
	std::string nowCursorKey2;	//現在のカーソル(長方形用)
	std::string afterMoveKey;	//移動後のマス
	std::string afterMoveKey2;	//長方形の二コマ目の移動後を示す

	bool isSecondPvs = false;	//二コマ目の移動が優先か

	//現在のカーソル位置
	Vector2 cursor = GetNowCursorPos();
	Vector2 cursor2 = GetNowCursorPos();
	CreateKey(cursor.y, cursor.x);
	nowCursorKey = roomKey_;

	//長方形用の二マス目のカーソル位置
	if (GetRoomShape(nowCursorKey) != RoomBase::ROOM_SHAPE::NOMAL)	//長方形だった時
	{
		//縦長か横長かを判断
		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			cursor2.y++;	//長方形の下用
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			cursor2.x++;	//長方形の右用
			break;
		}
		CreateKey(cursor2.y, cursor2.x);
		nowCursorKey2 = roomKey_;
	}
	
	//移動したい場所の中身チェック
	cursor.y += move.y;
	cursor.x += move.x;
	CreateKey(cursor.y, cursor.x);
	afterMoveKey = roomKey_;

	//長方形の追加分や変位を対応(この時点でのroomKeyはカーソルの移動後のマス)
	if (GetRoomShape(nowCursorKey) != RoomBase::ROOM_SHAPE::NOMAL)
	{
		//移動したい場所の中身チェック
		cursor2.y += move.y;
		cursor2.x += move.x;
		CreateKey(cursor2.y, cursor2.x);
		afterMoveKey2 = roomKey_;

		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			if (dir == Utility::DIR::DOWN) { isSecondPvs = true; }
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			if (dir == Utility::DIR::RIGHT) { isSecondPvs = true; }
			break;
		}
	}

	///入れ替え
	switch (roomMng_[nowCursorKey]->GetRoomType())
	{
		//一マス
	case RoomBase::TYPE::NONE:
	case RoomBase::TYPE::WASITU:
	case RoomBase::TYPE::BATH:
	case RoomBase::TYPE::STORAGE:
	case RoomBase::TYPE::WALL:
	case RoomBase::TYPE::GOAL:

		MovePiece(cursor,nowCursorKey,afterMoveKey);
		break;

		//長方形
	case RoomBase::TYPE::LIVING:
	case RoomBase::TYPE::KITCHEN:
	case RoomBase::TYPE::OWN:
	case RoomBase::TYPE::ENTRANCE:

		if (isSecondPvs)
		{
			if (!MovePiece(cursor2, nowCursorKey2, afterMoveKey2)) { return; }	//移動が行われなかったので処理終了
			//長方形の二マス目が移動されなかった場合
			if (!MovePiece(cursor, nowCursorKey, afterMoveKey))
			{
				//ひとつ前の手順をなかったことに
				MovePiece(cursor2, afterMoveKey2, nowCursorKey2);
			}
		}
		else
		{
			if (!MovePiece(cursor, nowCursorKey, afterMoveKey)) { return; }		//移動が行われなかったので処理終了
			if (!MovePiece(cursor2, nowCursorKey2, afterMoveKey2))
			{
				//ひとつ前の手順をなかったことに
				MovePiece(cursor, afterMoveKey, nowCursorKey);
			}
		}
		break;
	}
}

//入れ替え
const bool StageBase::MovePiece(const Vector2 csr,const std::string bfr, const std::string aft)
{
	//移動先が壁・ゴールでないか
	if (!IsDontMoveBlock(aft))
	{
		//移動先が範囲内であるか
		if ((csr.x >= 0) &&
			(csr.x < size_.x) &&
			(csr.y >= 0) &&
			(csr.y < size_.y))
		{
			//移動先がNONEだったら
			if (roomMng_[aft]->GetRoomType() == RoomBase::TYPE::NONE)
			{
				//部屋の入れ替え
				std::unique_ptr<RoomBase> change = std::move( roomMng_[bfr]);
				roomMng_[bfr] = std::move(roomMng_[aft]);
				roomMng_[aft] = std::move(change);
				//移動が行われたので
				return true;
			}
		}
	}
	//移動が行われなかったので
	return false;
}



#pragma endregion

#pragma region 長方形判定
//インスタンスの生成（初期化に使用）
const bool StageBase::CheckInstanceUp(int y, const int x, RoomBase& r)
{
	y--;
	CreateKey(y, x);	//配列一つ上のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r.GetRoomType())
	{
		return true;
	}
	y++;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
}
const bool StageBase::CheckInstanceDown(int y, const int x, RoomBase& r)
{
	y++;
	CreateKey(y, x);	//配列一つ上のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r.GetRoomType())
	{
		return true;
	}
	y--;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
	return false;
}
const bool StageBase::CheckInstanceLeft(const int y,int x, RoomBase& r)
{
	x--;
	CreateKey(y, x);	//配列一つ左のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r.GetRoomType())
	{
		return true;
	}
	x++;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
}

const bool StageBase::CheckInstanceRight(const int y, int x, RoomBase& r)
{
	x++;
	CreateKey(y, x);	//配列一つ左のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r.GetRoomType())
	{
		return true;
	}
	x--;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
	return false;
}



//部屋の形の種類を返却
const RoomBase::ROOM_SHAPE StageBase::GetRoomShape(const std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::KITCHEN || roomMng_[key]->GetRoomType() == RoomBase::TYPE::LIVING)
	{
		return RoomBase::ROOM_SHAPE::OBLONG;
	}

	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::OWN || roomMng_[key]->GetRoomType() == RoomBase::TYPE::ENTRANCE)
	{
		return RoomBase::ROOM_SHAPE::OBLONG_SIDE;
	}

	return RoomBase::ROOM_SHAPE::NOMAL;
}

const RoomBase::ROOM_SHAPE StageBase::GetRoomShape(const RoomBase::TYPE type)const
{
	if (type == RoomBase::TYPE::KITCHEN || type == RoomBase::TYPE::LIVING) 
	{ return RoomBase::ROOM_SHAPE::OBLONG; }

	if (type == RoomBase::TYPE::OWN || type == RoomBase::TYPE::ENTRANCE)
	{ return RoomBase::ROOM_SHAPE::OBLONG_SIDE; }

	return RoomBase::ROOM_SHAPE::NOMAL;
}



const bool StageBase::IsDontMoveBlock(const std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::GOAL ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::WALL)
	{
		//移動不可のブロックなので
		return true;
	}
	return false;
}

#pragma endregion

#pragma region 長方形の２コマ目のインスタンスを生成

//２コマ目のインスタンスはNONEで置きタイプをイジル
std::unique_ptr<RoomBase> StageBase::GetSecondRoomInstance(const RoomBase& r)
{
	std::unique_ptr<RoomBase> room;
	room = std::make_unique<None>(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
	room->Init();
	room->SetRoomType(r.GetRoomType());
	room->SetIsDrawRoom(false);
	room->SetIsClone(true);
	return room;
}
void StageBase::SetIsMoveRoom(const bool flag)
{
	isMoveRoom_ = flag;
}
void StageBase::SetIsSecondRoom(const bool flag)
{
	isSecondRoom_ = flag;
}
void StageBase::SetIsGoal(const bool flag)
{
	isGoal_ = flag;
}
//生成して取得したものは必ず用が終わったら消すこと！
RoomBase& StageBase::CreateInstance4Confirmation(const RoomBase::TYPE type)
{
	std::unique_ptr<RoomBase> retRoom = nullptr;

	switch (type)
	{
	case RoomBase::TYPE::LIVING:
		retRoom = std::make_unique<Living>(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)]);
		retRoom->Init();
		break;
	case RoomBase::TYPE::KITCHEN:
		retRoom = std::make_unique<Kitchen>(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)]);
		retRoom->Init();
		break;
	case RoomBase::TYPE::OWN:
		retRoom = std::make_unique<Own>(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)]);
		retRoom->Init();
		break;
	case RoomBase::TYPE::ENTRANCE:
		retRoom = std::make_unique<Entrance>(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)]);
		retRoom->Init();
		break;
	}
	return *retRoom;
}

void StageBase::SetFrameFlash(const bool flag)
{
	frameFlash_ = flag;
}
#pragma endregion

#pragma region リセット

void StageBase::ResetPazzl(void)
{
	//入れ替え処理用の現在位置保存
	std::string nowKey;
	

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;	
			auto type = roomMng_[nowKey]->GetRoomType();
			if (type != RoomBase::TYPE::WALL)
			{
				auto shape = GetRoomShape(resetRoom_[nowKey]);
				RoomBase* ret = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);

				//初期と部屋が違った場合
				if (type != resetRoom_[nowKey])
				{
					//入れ替え
					SwapPazzle(nowKey);
				}
				//初期の状態と違うとき（長方形の本体を置くべき場所に複製が来てしまったとき）
				while (resetRoomClone_[nowKey] != roomMng_[nowKey]->IsClone())
				{
					//入れ替え
					SwapPazzle(nowKey);
				}
			}
			//確定済みに変更
			roomMng_[nowKey]->SetIsChange(true);
		}
	}
	
	//確定を解除
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;
			roomMng_[nowKey]->SetIsChange(false);
		}
	}
}

void StageBase::SwapPazzle(const std::string nowKey)
{
	//現在の位置から初期のタイプの部屋があるかを確認
	for (int i = 0; i < size_.y; i++)
	{
		for (int n = 0; n < size_.x; n++)
		{
			CreateKey(i, n);
			//まだ確定していない場所で初期の部屋が見つかった場合
			if (!roomMng_[roomKey_]->IsChange() &&
				roomMng_[roomKey_]->GetRoomType() == resetRoom_[nowKey] &&
				roomKey_ != nowKey)
			{
				std::unique_ptr<RoomBase> r = std::move(roomMng_[nowKey]);
				roomMng_[nowKey] = std::move(roomMng_[roomKey_]);
				roomMng_[roomKey_] = std::move_if_noexcept(r);
				break;
			}
		}
	}
}

const bool StageBase::CheckAroundRoomAnything(const Vector2 nowPos)
{
	//現在の部屋保存用
	std::string nowKey = roomKey_;

	auto pos = nowPos;
	int i = 0;

	//上左右を確認
	do
	{
		pos = nowPos;
		if (i == 0)pos.y--;
		else if (i == 1)pos.x++;
		else if (i == 2)pos.x--;
		CreateKey(pos.y, pos.x);

		//ゴール＆壁＆NONE以外がある場合
		if (!IsDontMoveBlock(roomKey_) && roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::NONE)
		{
			return true;
		}
		i++;

	}while (i < 3);

	return false;
}

#pragma endregion



#pragma region 画像読み込み

void StageBase::LoadImgs(void)
{
	//カーソル
	frame_[static_cast<int>(CURSOR::NORMAL)]= 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG_2)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;
}

#pragma endregion

