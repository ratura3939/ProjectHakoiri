#include<DxLib.h>


#include"../Application.h"
#include"../Utility/Utility.h"
#include"../Manager/ResourceManager.h"
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
	frameAnim_ = 0;
	SetFrameFlash(false);

	//各ステージによる設定
	SetParam();
	//パズル配置の読み込み
	LoadPazzle();
	//画像読み込み
	LoadImgs();

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
				r = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
				r->Init();
				break;
			//自室
			case RoomBase::TYPE::OWN: 
				r = new Own(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)]);
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, r)){ r = GetSecondRoomInstance(r); }
				break;
			//和室
			case RoomBase::TYPE::WASITU:
				r = new Wasitu(roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)]);
				r->Init();
				break;
			//居間
			case RoomBase::TYPE::LIVING:
				r = new Living(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)]);
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//風呂
			case RoomBase::TYPE::BATH: 
				r = new Bath(roomImg_[static_cast<int>(RoomBase::TYPE::BATH)]);
				r->Init();
				break;
			//物置
			case RoomBase::TYPE::STORAGE:
				r = new Storage(roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)]);
				r->Init();
				break;
			//台所
			case RoomBase::TYPE::KITCHEN: 
				r = new Kitchen(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)]);
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//玄関
			case RoomBase::TYPE::ENTRANCE: 
				r = new Entrance(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)]);
				r->Init();
				//もし生成したものが長方形の２コマ目だったら
				if (CheckInstanceLeft(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//壁
			case RoomBase::TYPE::WALL:	
				r = new Wall(roomImg_[static_cast<int>(RoomBase::TYPE::WALL)]);
				r->Init();
				break;
			//ゴール
			case RoomBase::TYPE::GOAL:
				r = new Goal(roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)]);
				r->Init();
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = r;//配列内に格納
			resetRoom_[roomKey_] = r->GetRoomType();
			pzlPos_[roomKey_] = pos;

			//座標の更新
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		}
		pos.x_ = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_Y);
	}

	//初期のカーソル設定
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
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

#pragma region 更新

void StageBase::Update(GameScene::MODE mode)
{
	switch (mode)
	{
	case GameScene::MODE::STEALTH:
		UpdateStealth();
		break;
	default:
		break;
	}
}

void StageBase::UpdateStealth(void)
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
		size_t pzlY = pzlMap_.size();
		size_t pzlX = pzlX_.size();
	
		pzlX /= pzlY;

		frameAnim_++;

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
			DrawGraph(pzlPos_[roomKey_].x_, pzlPos_[roomKey_].y_,
				frame_[static_cast<int>(type_)], true);
		}
	}

	
	
#pragma endregion

#pragma region ステルス

	void StageBase::DrawStealth(void)
	{

	}
#pragma endregion


#pragma endregion

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

	for (int i = 0; i < static_cast<int>(CURSOR::MAX); i++)
	{
		DeleteGraph(frame_[i]);
	}

	//正しく処理が終了したので
	return true;
}

#pragma region パズル読み込み

void StageBase::LoadPazzle(void)
{
	//std::ifstream ifs = std::ifstream(Application::PATH_PAZZLE+file_Pzl.c_str());
	std::ifstream ifs = std::ifstream("Data/Csv/Pazzle/Stage_Tutorial.csv");

	if (!ifs)
	{
		OutputDebugString("パズルのifstreamの準備失敗");
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

void StageBase::SetCursorType(CURSOR type)
{
	type_ = type;
}
#pragma endregion


#pragma region カーソルの移動

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//現在のカーソル位置
	Vector2 cursor = GetNowCursorPos();

	//現在のカーソルの解除
	CreateKey(cursor.y_, cursor.x_);	
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
	std::string afterMoveKey = roomKey_;		//移動後のroomKey_の生成保存

	RoomBase::TYPE afterRoomType = roomMng_[afterMoveKey]->GetRoomType();

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

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
	if (IsOblong(afterRoomType))
	{
		RoomBase* r = nullptr;
		switch (afterRoomType)
		{
		case RoomBase::TYPE::LIVING:
			r = new Living(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)]);
			r->Init();
			break;
		case RoomBase::TYPE::KITCHEN:
			r = new Kitchen(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)]);
			r->Init();
			break;
		case RoomBase::TYPE::OWN:
			r = new Own(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)]);
			r->Init();
			break;
		case RoomBase::TYPE::ENTRANCE:
			r = new Entrance(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)]);
			r->Init();
			break;
		}
		//現在が長方形の本体かを確認
		if (CheckInstanceUp(cursor.y_, cursor.x_, r)||
			CheckInstanceLeft(cursor.y_, cursor.x_, r))
		{
			//保留のカーソルをキャンセル
			roomMng_[afterMoveKey]->SetIsCursor(false);
			//長方形に合わせた場所に移動
			if (afterRoomType == RoomBase::TYPE::KITCHEN || afterRoomType == RoomBase::TYPE::LIVING)//{ cursor.y_--; }
			{
				cursor.y_--;
			}
			if (afterRoomType == RoomBase::TYPE::ENTRANCE ||afterRoomType == RoomBase::TYPE::OWN)//{ cursor.x_--; }
			{
				cursor.x_--;
			}
			CreateKey(cursor.y_, cursor.x_);	//roomKey_の再生成
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
#pragma endregion

#pragma region 移動範囲外だった時

	if ((cursor.x_ >= pzlX)
		|| (cursor.y_ >= pzlY)
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
	CreateKey(cursor.y_, cursor.x_);
	nowCursorKey = roomKey_;

	//長方形用の二マス目のカーソル位置
	if (IsOblong(nowCursorKey))	//長方形だった時
	{
		//縦長か横長かを判断
		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			cursor2.y_++;	//長方形の下用
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			cursor2.x_++;	//長方形の右用
			break;
		}
		CreateKey(cursor2.y_, cursor2.x_);
		nowCursorKey2 = roomKey_;
	}
	
	//移動したい場所の中身チェック
	cursor.y_ += move.y_;
	cursor.x_ += move.x_;
	CreateKey(cursor.y_, cursor.x_);
	afterMoveKey = roomKey_;

	//長方形の追加分や変位を対応(この時点でのroomKeyはカーソルの移動後のマス)
	if (IsOblong(nowCursorKey))
	{
		//移動したい場所の中身チェック
		cursor2.y_ += move.y_;
		cursor2.x_ += move.x_;
		CreateKey(cursor2.y_, cursor2.x_);
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
bool StageBase::MovePiece(const Vector2 csr,const std::string bfr, const std::string aft)
{
	//配列要素数
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//移動先が壁・ゴールでないか
	if (!IsDontMoveBlock(aft))
	{
		//移動先が範囲内であるか
		if ((csr.x_ >= 0) &&
			(csr.x_ < pzlX) &&
			(csr.y_ >= 0) &&
			(csr.y_ < pzlY))
		{
			//移動先がNONEだったら
			if (roomMng_[aft]->GetRoomType() == RoomBase::TYPE::NONE)
			{
				//部屋の入れ替え
				RoomBase* change = roomMng_[bfr];
				roomMng_[bfr] = roomMng_[aft];
				roomMng_[aft] = change;
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

//長方形であるか
bool StageBase::IsOblong(std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::KITCHEN ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::LIVING ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::OWN ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::ENTRANCE)
	{
		return true;
	}
	return false;
}
bool StageBase::IsOblong(RoomBase::TYPE type)
{
	if (type == RoomBase::TYPE::KITCHEN ||
		type == RoomBase::TYPE::LIVING ||
		type == RoomBase::TYPE::OWN ||
		type == RoomBase::TYPE::ENTRANCE)
	{
		return true;
	}
	return false;
}

bool StageBase::IsDontMoveBlock(std::string key)
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
RoomBase* StageBase::GetSecondRoomInstance(RoomBase* r)
{
	RoomBase* room;
	room = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
	room->Init();
	room->SetRoomType(r->GetRoomType());
	room->SetColor(r->GetColor());
	room->SetIsDrawRoom(false);
	return room;
}

void StageBase::SetFrameFlash(bool flag)
{
	frameFlash_ = flag;
}
#pragma endregion

#pragma region リセット

void StageBase::ResetPazzl(void)
{
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//入れ替え処理用の現在位置保存
	std::string nowKey;

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;	

			//初期と部屋が違った場合
			if (roomMng_[nowKey]->GetRoomType() != resetRoom_[nowKey])
			{
				//現在の位置から初期のタイプの部屋があるかを確認
				for (int i = 0; i < pzlY; i++)
				{
					for (int n = 0; n < pzlX; n++)
					{
						CreateKey(i, n);
						//まだ確定していない場所で初期の部屋が見つかった場合
						if (!roomMng_[roomKey_]->IsChange() &&
							roomMng_[roomKey_]->GetRoomType() == resetRoom_[nowKey])
						{
							RoomBase* r = roomMng_[nowKey];
							roomMng_[nowKey] = roomMng_[roomKey_];
							roomMng_[roomKey_] = r;
						}
					}
				}
			}
			//確定済みに変更
			roomMng_[nowKey]->SetIsChange(true);
		}
	}
	
	//確定を解除
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;
			roomMng_[nowKey]->SetIsChange(false);
		}
	}
}
#pragma endregion

#pragma region 画像読み込み

void StageBase::LoadImgs(void)
{
	//カーソル
	frame_[static_cast<int>(CURSOR::NORMAL)]= ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG)] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG_2)] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;

	//部屋
	roomImg_[static_cast<int>(RoomBase::TYPE::BATH)]=
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::GOAL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::NONE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::NONE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WALL)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WALL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_IMG).handleId_;
}
#pragma endregion

