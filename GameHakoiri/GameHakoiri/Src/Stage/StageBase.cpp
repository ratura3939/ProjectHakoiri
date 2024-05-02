#include<DxLib.h>


#include"../Application.h"
#include"../Utility/Utility.h"
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
StageBase::StageBase(void)
{
	roomKey_ = "00";
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
	frame_ = 0;
	frameImg_ = LoadGraph("Data/Img/frame.png");
	frameObImg_ = LoadGraph("Data/Img/frame_oblong.png");
	frameOb2Img_= LoadGraph("Data/Img/frame_oblong_2.png");

	//各ステージによる設定
	SetParam();
	//パズル配置の読み込み
	LoadPazzle();

	//初期化に必要な変数
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 4),
		static_cast<float>(Application::SCREEN_SIZE_Y / 4) };


	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			RoomBase* r = nullptr;

			switch (static_cast<RoomBase::TYPE>(pzlMap_[y][x+(pzlX*y)]))
			{
			//空きスペース
			case RoomBase::TYPE::NONE: 
				r = new None;
				r->Init();
				break;
			//自室
			case RoomBase::TYPE::OWN: 
				r = new Own();
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, r)){ r = GetSecondRoomInstance(r); }
				break;
			//和室
			case RoomBase::TYPE::WASITU:
				r = new Wasitu;;
				r->Init();
				break;
			//居間
			case RoomBase::TYPE::LIVING:
				r = new Living;
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//風呂
			case RoomBase::TYPE::BATH: 
				r = new Bath;
				r->Init();
				break;
			//物置
			case RoomBase::TYPE::STORAGE:
				r = new Storage;
				r->Init();
				break;
			//台所
			case RoomBase::TYPE::KITCHEN: 
				r = new Kitchen;
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//玄関
			case RoomBase::TYPE::ENTRANCE: 
				r = new Entrance;
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//壁
			case RoomBase::TYPE::WALL:	
				r = new Wall;
				r->Init();
				break;
			//ゴール
			case RoomBase::TYPE::GOAL:
				r = new Goal;
				r->Init();
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = r;//配列内に格納
			pzlPos_[roomKey_] = pos;

			//座標の更新
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		}
		pos.x_ = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_Y);
	}



	CreateKey(1, 1);
	roomMng_[roomKey_]->SetIsCursor(true);

	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void StageBase::Update(void)
{

}
#pragma region 描画

#pragma region パズルシーン

	void StageBase::PazzleDraw(void)
	{		
		size_t pzlY = pzlMap_.size();
		size_t pzlX = pzlX_.size();
	
		pzlX /= pzlY;


		//駒の描画
		for (int y = 0; y < pzlY; y++)
		{
			for (int x = 0; x < pzlX; x++)
			{
				CreateKey(y, x);
				roomMng_[roomKey_]->SetPzlPos(pzlPos_[roomKey_]);
				roomMng_[roomKey_]->DrawPazzle();
			}
			
		}
		//枠の描画
		DrawCursor();
	}
	#pragma endregion

#pragma region カーソル

	void StageBase::DrawCursor(void)
	{
		Vector2 key = GetNowCursorPos();

		DrawFormatString(0, 20, 0xffffff, "CURSOR={%d.%d}", key.x_, key.y_);

		CreateKey(key.y_, key.x_);
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
			frame_ = frameImg_;
			break;
			//縦長
			//居間
		case RoomBase::TYPE::LIVING:
			//台所
		case RoomBase::TYPE::KITCHEN:
			frame_ = frameObImg_;
			break;

			//横長
			//自室
		case RoomBase::TYPE::OWN:
			//玄関
		case RoomBase::TYPE::ENTRANCE:
			frame_ = frameOb2Img_;
			break;
		}
		if (roomMng_[roomKey_]->GetIsCursor())
		{
			//枠の描画
			DrawGraph(pzlPos_[roomKey_].x_, pzlPos_[roomKey_].y_,
				frame_, true);
		}
	}
#pragma endregion


#pragma endregion

//描画
//********************************************************

//解放
//********************************************************
bool StageBase::Release(void)
{
	//駒
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();

	pzlX /= pzlY;

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
			delete roomMng_[roomKey_];
			roomMng_[roomKey_] = nullptr;
		}
	}

	DeleteGraph(frameImg_);
	DeleteGraph(frameObImg_);
	DeleteGraph(frameOb2Img_);

	//正しく処理が終了したので
	return true;
}

#pragma region パズル読み込み

void StageBase::LoadPazzle(void)
{
	std::string loadName;
	//loadName = Application::PATH_PAZZLE + testName_;

	//std::ifstream ifs = std::ifstream(loadName);
	std::ifstream ifs = std::ifstream("Data/Csv/Pazzle/map_test.csv");

	if (!ifs)
	{
		OutputDebugString("地上ステージのifstreamの準備失敗");
		return;
	}

	int chipNo = 0;
	//列の先頭から保存する
	int x = 0;

	//行格納用領域
	std::string line;
	while (getline(ifs, line))	//行がある間
	{
		//Split関数戻り値受け取り用
		std::vector<std::string> strSplit;

		strSplit = Utility::Split(line, ',');	//関数の呼び出し

		//一文字の情報
		std::string chipData;
		//分割したマップデータを格納する
		for (int x = 0; x < strSplit.size(); x++)
		{
			chipNo = stoi(strSplit[x]);
			pzlX_.push_back(chipNo);	//配列内に格納
		}
		pzlMap_.push_back(pzlX_);	//配列内に格納
	}

}
#pragma endregion

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

#pragma region 現在のカーソル位置取得

Vector2 StageBase::GetNowCursorPos(void)
{
	//現在のカーソルの位置を取得
	Vector2 cursor;

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
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
#pragma endregion


#pragma region カーソルの移動

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//現在のカーソル位置
	Vector2 cursor = GetNowCursorPos();

	//現在のカーソルの解除
	CreateKey(cursor.y_, cursor.x_);	//現在位置のroomKey_の生成
	roomMng_[roomKey_]->SetIsCursor(false);

	//実行前の位置を保存
	std::string prevKey = roomKey_;;

	//カーソル位置の現在地からの移動
	switch (roomMng_[roomKey_]->GetRoomType())
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
		cursor.y_ += move.y_;
		cursor.x_ += move.x_;
		break;

		//縦長
		//居間
	case RoomBase::TYPE::LIVING:
		//台所
	case RoomBase::TYPE::KITCHEN:
		if (dir == Utility::DIR::DOWN) {cursor.y_ += move.y_ * 2;}
		else{cursor.y_ += move.y_;}

		cursor.x_ += move.x_;
		break;

		//横長
		//自室
	case RoomBase::TYPE::OWN:
		//玄関
	case RoomBase::TYPE::ENTRANCE:
		if (dir == Utility::DIR::RIGHT) { cursor.x_ += move.x_ * 2; }
		else { cursor.x_ += move.x_; }

		cursor.y_ += move.y_;
		break;
	}
	

	//移動後
	CreateKey(cursor.y_, cursor.x_);	//移動後のroomKey_の生成
	std::string holdKey = roomKey_;		//長方形などの場合があるので保留とする

	RoomBase::TYPE roomType = roomMng_[roomKey_]->GetRoomType();

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;


#pragma region 長方形の二マス目だった時
	//縦長
	if (roomType == RoomBase::TYPE::KITCHEN ||
		roomType == RoomBase::TYPE::LIVING)
	{
		RoomBase* r = nullptr;
		switch (roomType)
		{
		case RoomBase::TYPE::LIVING:
			r = new Living;
			r->Init();
			break;
		case RoomBase::TYPE::KITCHEN:
			r = new Kitchen;
			r->Init();
			break;
		}
		//現在が長方形の本体かを確認
		if (CheckInstanceUp(cursor.y_, cursor.x_, r))
		{
			//保留のカーソルをキャンセル
			roomMng_[holdKey]->SetIsCursor(false);
			//長方形に合わせた場所に移動
			cursor.y_--;
			CreateKey(cursor.y_, cursor.x_);	//roomKey_の再生成
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
	//横長
	if (roomType == RoomBase::TYPE::ENTRANCE ||
		roomType == RoomBase::TYPE::OWN)
	{
		RoomBase* r = nullptr;
		switch (roomType)
		{
		case RoomBase::TYPE::OWN:
			r = new Own;
			r->Init();
			break;
		case RoomBase::TYPE::ENTRANCE:
			r = new Entrance;
			r->Init();
			break;
		}
		//現在が長方形の本体かを確認
		if (CheckInstanceLeft(cursor.y_, cursor.x_, r))
		{
			//保留のカーソルをキャンセル
			roomMng_[holdKey]->SetIsCursor(false);
			//長方形に合わせた場所に移動
			cursor.x_--;
			CreateKey(cursor.y_, cursor.x_);	//roomKey_の再生成
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
#pragma endregion

#pragma region 移動範囲外だった時

	if ((cursor.x_ >= pzlX)
		|| (cursor.y_ >= pzlY)
		|| (roomType == RoomBase::TYPE::WALL)
		|| (roomType == RoomBase::TYPE::GOAL))
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

void StageBase::SetPiece(Vector2 move, Utility::DIR dir)
{
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//現在のカーソル位置
	Vector2 cursor = GetNowCursorPos();
	CreateKey(cursor.y_, cursor.x_);
	std::string prevKey = roomKey_;
	
	//移動したい場所の中身チェック
	cursor.y_ += move.y_;
	cursor.x_ += move.x_;
	CreateKey(cursor.y_, cursor.x_);

	//移動先が壁・ゴールでないか
	if (roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::WALL ||
		roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::GOAL)
	{
		//移動先が範囲内であるか
		if ((cursor.x_ >= 0) &&
			(cursor.x_ < pzlX) &&
			(cursor.y_ >= 0) &&
			(cursor.y_ < pzlY))
		{
			//移動先がNONEだったら
			if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::NONE)
			{
				//部屋の入れ替え
				RoomBase* change = roomMng_[prevKey];
				roomMng_[prevKey] = roomMng_[roomKey_];
				roomMng_[roomKey_] = change;
			}
		}
	}
}
#pragma endregion

#pragma region 長方形駒の２マス目

//インスタンスの生成（初期化に使用）
bool StageBase::CheckInstanceUp(int y, int x, RoomBase* r)
{
	y--;
	CreateKey(y, x);	//配列一つ上のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	y++;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
}
bool StageBase::CheckInstanceLeft(int y, int x, RoomBase* r)
{
	x--;
	CreateKey(y, x);	//配列一つ左のキーを生成
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	x++;
	CreateKey(y, x);	//元の場所のキーを生成
	return false;
}

#pragma endregion

#pragma region 長方形の２コマ目のインスタンスを生成

//２コマ目のインスタンスはNONEで置きタイプをイジル
RoomBase* StageBase::GetSecondRoomInstance(RoomBase* r)
{
	RoomBase* room;
	room = new None;
	room->Init();
	room->SetRoomType(r->GetRoomType());
	room->SetColor(r->GetColor());
	return room;
}
#pragma endregion

