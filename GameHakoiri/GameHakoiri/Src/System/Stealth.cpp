#include<DxLib.h>
#include<math.h>

#include"../Application.h"

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"../Object/CharacterBase.h"
#include"../Object/Enemy/Housemaid.h"
#include"../Object/Enemy/Seneschal.h"
#include"../Object/Enemy/Oldman.h"
#include"Stealth.h"

//コンストラクタ
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
	enemyMng_[0] = nullptr;
	enemyMng_[1] = nullptr;
	enemyMng_[2] = nullptr;
	enemyMng_[3] = nullptr;
	enemyMng_[4] = nullptr;
	enemyMng_[5] = nullptr;

	isEnemyMove_ = false;
}
//デストラクタ
//********************************************************
Stealth::~Stealth(void)
{

}



//初期化
//********************************************************
bool Stealth::Init(void)
{
	StageManager::GetInstance().ChangeModeInit();
	//カメラにマップのサイズを設定
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
	player_ = new Player;
	player_->Init();

	EnemyInit();
	SetEnemy();
	
	isFailed_ = false;

	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void Stealth::Update(void)
{
	//カメラをプレイヤーに設定
	auto& camera = SceneManager::GetInstance().GetCamera();
	camera.SetTargetPos(player_->GetPos());

	//enemy
	for (auto& e : useEnemy_)
	{
		e->Update();
	}

	//player
	player_->Update();


	Collision();

	if (player_->GetHp() <= 0.0f)
	{
		isFailed_ = true;
	}
}
//描画
//********************************************************
void Stealth::Draw(void)
{
	
	//StageManager::GetInstance().DrawObject();
	for (auto& e : useEnemy_)
	{
		e->Draw();
	}

	player_->Draw();

	//DrawDebug();

	if (player_->IsDrawMap())
	{
		StageManager::GetInstance().Draw(GameScene::MODE::PAZZLE);
	}
}
//解放
//********************************************************
bool Stealth::Release(void)
{
	player_->Release();
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		enemyMng_[i]->Release();
	}
	useEnemy_.clear();
	memorizePos_.clear();
	memorizeType_.clear();
	//正しく処理が終了したので
	return true;
}

bool Stealth::IsFailde(void)
{
	return isFailed_;
}



#pragma region 当たり判定

//当たり判定総括
void Stealth::Collision(void)
{
	//部屋移動フラグリセット
	isMoveRoom_ = false;

	//プレイヤー
	//--------------------------------------------------------
	//toマップチップ
	CollisionMapchip(player_,true);

	//クリアしているか部屋の移動があったならこの後の当たり判定は行わない
	if (StageManager::GetInstance().IsClear()||isMoveRoom_)
	{
    		return;
	}
	
	
	//敵
	//--------------------------------------------------------
	auto pPos = player_->GetPos();
	for (auto& e : useEnemy_)
	{
		//toマップチップ
		CollisionMapchip(e, false);
		

		e->SetVisionState(EnemyBase::VISION_STATE::MISSING);
		//敵がplayerを発見できていないとき
		if (!e->FindPlayer(pPos))
		{
			//敵が衝突しているとき
			if (IsEnemyMove())
			{
				//敵を動き終了の状態に
				e->SetIsMove(false);
			}
		}
		else
		{
			auto ePos = e->GetPos();
			auto EtoP = pPos - ePos;
			auto PtoE = ePos - pPos;

			//間にさえぎるオブジェクトがある時
			if (CheckObjectPToE(pPos, e))
			{
				//見つかっていないのでその時の動きを行う
				//敵が衝突しているとき
				if (IsEnemyMove())
				{
					//敵を動き終了の状態に
					e->SetIsMove(false);
				}
			}
			else
			{
				e->SetVisionState(EnemyBase::VISION_STATE::FIND);
				player_->Damage();
			}
		}
		
	}
}


void Stealth::CollisionMapchip(CharacterBase* character, bool isPlayer)
{
	//敵用のフラグリセット
	SetIsEnemyMove(false);

	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();
	//判定するキャラクター座標をマップ座標に変換
	auto mapPos = stage.GetVector2MapPos(character->GetCollisionPos().ToVector2());

	if (stage.IsCollisionWall(mapPos))
	{
		CollisionObstacle(character);
	}
	else if (stage.IsCollisionObject(mapPos))
	{
		auto type = stage.GetObjectType(mapPos);
		if (type == StageManager::OBJECT::OBSTACLE) { CollisionObstacle(character); }
		if (type == StageManager::OBJECT::THROUGH) { CollisionTrough(mapPos, character); }
		//イベントマップチップはプリやーしか処理しない
		if (type == StageManager::OBJECT::EVENT)
		{
			if (isPlayer)
			{
				CollisionEvent(mapPos);
			}
			else
			{
				CollisionObstacle(character);
			}
		}
	}
}
//通り抜け不可なオブジェクト
void Stealth::CollisionObstacle(CharacterBase* character)
{
	character->SetPos(character->GetPrevPos());
	//敵用のフラグセット
	SetIsEnemyMove(true);
}
//最下段以外は通り抜け可能なオブジェクト
void Stealth::CollisionTrough(Vector2 pCol, CharacterBase* character)
{
	if(StageManager::GetInstance().IsBottomObject(pCol))
	{ 
		character->SetPos(character->GetPrevPos()); 
		//敵用のフラグセット
		SetIsEnemyMove(true);
	}
}
//扉などのイベントが起こるオブジェクト
void Stealth::CollisionEvent(Vector2 pCol)
{
	//ステージマネージャ取得
     auto& stage = StageManager::GetInstance();
	auto prevKey = stage.GetKey();

	stage.ChangeMap(pCol);	//部屋の移動処理
	isMoveRoom_ = true;

	if (stage.IsClear())
	{
		return;	//ゴールしてたら処理中断
	}

	if (!stage.IsMoveMap())		//移動できないとき
	{
		player_->SetPos(player_->GetPrevPos());
	}
	else
	{
		//とりあえず移動したらステージの真ん中に（テスト用）
		//カメラにマップのサイズを設定
		auto& camera = Camera::GetInstance();
		auto mapSize = stage.GetMapMaxSize().ToVector2();
		camera.SetMapSize(mapSize.ToVector2F());

		//playerの移動後の位置設定
		Vector2 pos;
		auto door = stage.GetDoor();
		auto doorSec = stage.GetDoorSecond();
		//行き先の形を示す
		auto shape = stage.GetShape();

		//上または下の方向の扉から来た場合。（行き先の下または上側に出る）
		//縦長が上下に移動しているときはdoorYとdoorSecが同じ場合。その他二つのときはdoorSecはNONEなので下記の記述

		if (door.y != StageManager::DOOR_Y::MIDDLE &&		//移動が真ん中ではないとき
			(door.y == doorSec || doorSec == StageManager::DOOR_Y::NONE)	//doorSecでの確認
			)
		{
			switch (shape)	//移動先の形により場所を設定
			{
			case RoomBase::ROOM_SHAPE::NOMAL:
			case RoomBase::ROOM_SHAPE::OBLONG:
				if (door.y == StageManager::DOOR_Y::TOP)
				{
					pos = { DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };	//マップ下方に出る
				}
				else if (door.y == StageManager::DOOR_Y::BOTTOM)
				{
					pos = { DOOR_DISTANCE, INIT_ROOM_POS };	//マップ上方に出る
				}

				break;
			case RoomBase::ROOM_SHAPE::OBLONG_SIDE:
				//長方形の二コマ目に出た形跡があった場合
				if (stage.IsSecondEvidence())
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//右側の下出る
						pos = { mapSize.x - DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//右側の上に出る
						pos = { mapSize.x - DOOR_DISTANCE,INIT_ROOM_POS };
					}
				}
				else 
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//左側の下に出る
						pos = { DOOR_DISTANCE,mapSize.y - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//左側の上に出る
						pos = { DOOR_DISTANCE,INIT_ROOM_POS };
					}
					
				}	
				break;
			}
		}
		else
		{
			//左右の移動のとき
			switch (shape)
			{
			case RoomBase::ROOM_SHAPE::NOMAL:
			case RoomBase::ROOM_SHAPE::OBLONG_SIDE:
				//playerがどっちから来たかを判断
				if (door.x == StageManager::DOOR_X::LEFT)
				{
					pos = { mapSize.x - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//右に設定
				}
				else if (door.x == StageManager::DOOR_X::RIGHT)
				{
					pos = { INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//左に設定
				}

				break;
			case RoomBase::ROOM_SHAPE::OBLONG:
				//長方形の二コマ目に出た形跡があった場合
				if (stage.IsSecondEvidence())
				{
					//playerがどっちから来たかを判断
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x - INIT_ROOM_POS_SIDE,mapSize.y - DOOR_DISTANCE };	//右下に設定
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,mapSize.y - DOOR_DISTANCE };	//左下に設定
					}
				}
				else
				{
					//playerがどっちから来たかを判断
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//右上に設定
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//左上に設定
					}
				}
				break;
			}
		}

		//敵情報の保存
		MemorizeEnemy(prevKey);
		//敵の設定
		SetEnemy();

		//ターゲット設定
		camera.SetTargetPos(pos.ToVector2F());
		player_->SetPos(pos.ToVector2F());
	}
}


#pragma endregion

//プレイヤーと敵との間に通り抜け不可なオブジェクトはあるのか
bool Stealth::CheckObjectPToE(Vector2F pPos, EnemyBase* enemy)
{
	//双方向のベクトルを取得
	//この２つはxyの符号が逆なだけ
	auto ePos = enemy->GetPos();
	auto EtoP = pPos - ePos;
	auto PtoE = ePos - pPos;

	//まだ何も遮るものが見つかっていないときの処理
	//視野内のオブジェクトを取得（配列系）
	auto pMapPos = StageManager::GetInstance().GetVector2MapPos(pPos.ToVector2());
	auto eMapPos = StageManager::GetInstance().GetVector2MapPos(ePos.ToVector2());
	auto obj = GetWithinFieldOfViewObject(pMapPos, eMapPos);

	std::vector<Vector2> RightObjectOfPlayer;
	std::vector<Utility::DIR> ObjectToPlayerDir;
	std::vector<Vector2> RightObjectOfEnemy;
	std::vector<Utility::DIR> ObjectToEnemyDir;

	//全てのオブジェクトとキャラクターの位置関係を調べる
	//結果として得るのは内積をとって正の方向にあるものだけ
	for (auto& o : obj)
	{
		//オブジェクト位置を配列系から座標系に
		auto objWorldPos = o;
		objWorldPos.x *= StageManager::UNIT_STEALTH_SIZE_X;
		objWorldPos.y *= StageManager::UNIT_STEALTH_SIZE_Y;

		auto objPos = objWorldPos.ToVector2F();

		//キャラクターから見て右手前の位置は何かを決める
		//マップチップから見て敵とpプレイヤーがどこにいるかを調べる
		auto OtoP = pPos - objPos;
		auto OtoE = ePos - objPos;

		auto OtoPRad = atan2(OtoP.y, OtoP.x);
		auto OtoPDir = GetObjToCharacterDir(OtoPRad);

		auto OtoERad = atan2(OtoE.y, OtoE.x);
		auto OtoEDir = GetObjToCharacterDir(OtoERad);

		//自分から見てマップチップの右手前に当たるものとのベクトル
		auto PtoO = GetJudgementPos(objPos, OtoPDir) - pPos;
		auto EtoO = GetJudgementPos(objPos, OtoEDir) - ePos;

		//外積計算
		auto Pgaiseki = Utility::GetCrossProductF(PtoE, PtoO);
		auto Egaiseki = Utility::GetCrossProductF(EtoP, EtoO);	//おそらくこれ


		//例外なくす用

		Utility::DIR PspareDir = Utility::DIR::MAX;
		Utility::DIR EspareDir = Utility::DIR::MAX;

		PspareDir = CreateSpareLine(pPos, objWorldPos, OtoPDir);
		EspareDir = CreateSpareLine(ePos, objWorldPos, OtoEDir);

		if (PspareDir != Utility::DIR::MAX)
		{
			auto PtoO2 = GetJudgementPos(objWorldPos, PspareDir) - pPos;
			auto Pgaiseki2 = Utility::GetCrossProductF(PtoE, PtoO2);
			if (IsSameSign(Pgaiseki2, Egaiseki))
			{
				return true;
			}
		}
		if (EspareDir != Utility::DIR::MAX)
		{
			auto EtoO2 = GetJudgementPos(objWorldPos, EspareDir) - ePos;
			auto Egaiseki2 = Utility::GetCrossProductF(EtoP, EtoO2);
			if (IsSameSign(Pgaiseki, Egaiseki2))
			{
				return true;
			}
		}

		//お互い同じ方向に矩形がある時
		if (IsSameSign(Pgaiseki, Egaiseki))
		{
			return true;
		}
	}
	
	return false;
}


//これらの引数はそれぞれの位置をマップ配列に変換したもの
std::vector<Vector2> Stealth::GetWithinFieldOfViewObject(Vector2 pMapPos, Vector2 eMapPos)	
{
	//引数の座標を頂点に含む４角形を制作
	// この４角形の範囲にあるオブジェクトを精査する
	//４角形の始点（左上）と終点（右下）を制作
	//この中身は配列の番号とする
	Vector2 stPos = { 0,0 };
	Vector2 edPos = { 0,0 };

	//プレイヤーが敵より左側にいるとき
	if (pMapPos.x < eMapPos.x)
	{
		//始点のX座標にはプレイヤーのX座標を
		stPos.x = pMapPos.x;
		edPos.x = eMapPos.x;
	}
	else
	{
		//始点のX座標には敵のX座標を
		stPos.x = eMapPos.x;
		edPos.x = pMapPos.x;
	}

	//プレイヤーが敵より上にいるとき
	if (pMapPos.y < eMapPos.y)
	{
		//始点のY座標にはプレイヤーのY座標を
		stPos.y = pMapPos.y;
		edPos.y = eMapPos.y;
	}
	else
	{
		//始点のY座標には敵のY座標を
		stPos.y = eMapPos.y;
		edPos.y = pMapPos.y;
	}


	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();

	//始点から終点までの矩形の中でどこにオブジェクトがあるかを調べる
	//オブジェクトの位置全体保存用
	std::vector<Vector2> objectPos;
	//個別保存（for文)用
	Vector2 obPos;

	//始点から終点までのfor文
	for (int y = stPos.y; y <= edPos.y; y++)
	{
		for (int x = stPos.x; x <= edPos.x; x++)
		{
			obPos = { x,y };
			//通り抜け不可なものを記録していく
			if (stage.GetObjectType(obPos) == StageManager::OBJECT::OBSTACLE)
			{
				objectPos.push_back(obPos);
			}
			else if (stage.GetObjectType(obPos) == StageManager::OBJECT::THROUGH)
			{
				if (stage.IsBottomObject(obPos))
				{
					objectPos.push_back(obPos);
				}
			}
		}
	}

	return objectPos;
}
//角度に応じてキャラクターがどの方向にいるかを割り当てる
Utility::DIR Stealth::GetObjToCharacterDir(double rad)
{
	Utility::DIR ret = Utility::DIR::MAX;
	
	auto deg = Utility::Rad2DegF(static_cast<float>(rad));
	// 0度～360度以内に角度をおさめる
	deg = static_cast<float>(Utility::DegIn360(deg));

	//角度に応じてキャラクターがどの方向にいるかを割り当てる
	if (deg<=UNIT_DEG || deg> UNIT_DEG + (NOMAL_DEG * 3))
	{
		ret = Utility::DIR::RIGHT;
	}
	else if (deg > UNIT_DEG && deg <= UNIT_DEG + NOMAL_DEG)
	{
		ret = Utility::DIR::DOWN;
	}
	else if (deg > UNIT_DEG + NOMAL_DEG && deg <= UNIT_DEG + (NOMAL_DEG*2))
	{
		ret = Utility::DIR::LEFT;
	}
	else if (deg > UNIT_DEG + (NOMAL_DEG * 2) && deg <= UNIT_DEG + (NOMAL_DEG * 3))
	{
		ret = Utility::DIR::UP;
	}

	return ret;
}

//オブジェクトのどこの点と判定するかを決める
Vector2F Stealth::GetJudgementPos(Vector2F pos, Utility::DIR dir)
{
	auto objPos = pos;

	switch (dir)
	{
	case Utility::DIR::UP:
		objPos += 
			Vector2F{ -StageManager::UNIT_STEALTH_SIZE_X / 2,-StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::RIGHT:
		objPos +=
			Vector2F{ StageManager::UNIT_STEALTH_SIZE_X / 2,-StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::DOWN:
		objPos +=
			Vector2F{ StageManager::UNIT_STEALTH_SIZE_X / 2,StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::LEFT:
		objPos +=
			Vector2F{ -StageManager::UNIT_STEALTH_SIZE_X / 2,StageManager::UNIT_STEALTH_SIZE_Y / 2 };
		break;
	case Utility::DIR::MAX:
		OutputDebugString("方向が設定されていません\n");
		break;
	default:
		break;
	}

	return objPos;
}

//当たり判定予備の線
Utility::DIR Stealth::CreateSpareLine(Vector2F charaPos, Vector2 obj, Utility::DIR dir)
{
	Utility::DIR ret = Utility::DIR::MAX;

	//例外をなくすための敵側に二本目のベクトルを制作
	if (charaPos.x < obj.x - (StageManager::UNIT_STEALTH_SIZE_X / 2))
	{
		if (dir != Utility::DIR::LEFT)
		{
			ret = Utility::DIR::LEFT;
		}
		else
		{
			if (charaPos.y < obj.y - (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::UP;
			}
			else if (charaPos.y > obj.y + (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::DOWN;
			}
		}
	}
	if (charaPos.x > obj.x + (StageManager::UNIT_STEALTH_SIZE_X / 2))
	{
		if (dir != Utility::DIR::RIGHT)
		{
			ret = Utility::DIR::RIGHT;
		}
		else
		{
			if (charaPos.y < obj.y - (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::UP;
			}
			else if (charaPos.y > obj.y + (StageManager::UNIT_STEALTH_SIZE_Y / 2))
			{
				ret = Utility::DIR::DOWN;
			}
		}
	}

	return ret;
}

void Stealth::ChangeRoom(void/*いずれかは動く部屋の指定数をいれる*/)
{

	//カメラにマップのサイズを設定
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
}

bool Stealth::IsSameSign(float v1, float v2) const
{
	if (v1 >= 0.0f)
	{
		if (v2 >= 0.0f)
		{
			return true;
		}
	}
	else
	{
		if (v2 < 0.0f)
		{
			return true;
		}
	}
	return false;
}

bool Stealth::IsStraght(Vector2F v1, Vector2F v2) const
{
	if (fabsf(v1.x) == fabs(v2.x) && fabs(v1.y) == fabs(v2.y))
	{
		return true;
	}
	return false;
}

void Stealth::DrawDebug(void)
{
	auto pos = player_->GetCollisionPos();
	auto pPos = player_->GetPos();
	auto pMapPos = StageManager::GetInstance().GetVector2MapPos(pPos.ToVector2());
	auto hp = player_->GetHp();
	

	DrawFormatString(0, 0, 0xff0000,
		"playerの座標＝(%.1f,%.1f)\nplayerの当たり判定＝(%.1f,%.1f)\nplayerの位置＝｛%d,%d}\nHP=%.1f",
		pPos.x,pPos.y,pos.x,pos.y,pMapPos.x,pMapPos.y,hp);


}

void Stealth::EnemyInit(void)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//敵を6体ずつ生成
		if (i < OBLONG_ENEMY_NUM)
		{
			enemyMng_[i] = new Housemaid;
		}
		else if (i < OBLONG_ENEMY_NUM * 2)
		{
			enemyMng_[i] = new Seneschal;
		}
		else
		{
			enemyMng_[i] = new Oldman;
		}
		enemyMng_[i]->Init();
	}

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][0] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][1] = { NX2,NY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][2] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][3] = { NX2,NY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][4] = { NX1,NY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][5] = { NX2,NY2 };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][0] = { OBX1,OBY1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][1] = { OBX2,OBY2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][2] = { OBX3,OBY3 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][3] = { OBX4,OBY4 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][4] = { OBX5,OBY5 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG)][5] = { OBX6,OBY6 };

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][0] = { OB2X1,OB2Y1 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][1] = { OB2X2,OB2Y2 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][2] = { OB2X3,OB2Y3 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][3] = { OB2X4,OB2Y4 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][4] = { OB2X5,OB2Y5 };
	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::OBLONG_SIDE)][5] = { OB2X6,OB2Y6 };
}

void Stealth::CreateEnemy(void)
{
	int rnd = 0;
	do
	{
		//乱数取得
		rnd = rand();

		//敵の総数で割った余りを取得
		rnd %= OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX);
	} while (enemyMng_[rnd]->IsUse());

	//敵のフラグ等管理
	enemyMng_[rnd]->SetIsUse(true);


	//使用する敵のセット
	useEnemy_.push_back(enemyMng_[rnd]);
	
}

void Stealth::InitEnemyPos(const RoomBase::ROOM_SHAPE type)
{
	for (int i = 0; i < useEnemy_.size(); i++)
	{
		useEnemy_[i]->SetPos(initPos_[static_cast<int>(type)][i]);
	}
}

void Stealth::SetEnemy(void)
{

	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();
	auto key = stage.GetKey();

	//現在の部屋に敵の生成記録がなかった時
	if (memorizePos_[key].empty())
	{
		auto type = stage.GetShape();
		//敵の生成
		if (type == RoomBase::ROOM_SHAPE::NOMAL)
		{
			//正方形の場合
			for (int i = 0; i < NOMAL_ENEMY_NUM; i++)
			{
				CreateEnemy();
			}
		}
		else
		{
			//長方形の場合
			for (int i = 0; i < OBLONG_ENEMY_NUM; i++)
			{
				CreateEnemy();
			}
		}
		InitEnemyPos(type);
	}
	else
	{
		//生成記録があった場合
		auto size = memorizePos_[key].size();
		for (int m = 0; m < size; m++)	//敵の生成数分回す
		{
			SearchSetEnemy(key, m);
		}
	}
}

void Stealth::SearchSetEnemy(std::string key, int num)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)//敵の管理全体
	{
		if (memorizeType_[key][num] == enemyMng_[i]->GetType() &&	//保存されている種類と同じだったら
			!enemyMng_[i]->IsUse())	//まだ使用されてなかったら
		{
			//敵のフラグ管理と位置の設定
			enemyMng_[i]->SetPos(memorizePos_[key][num]);
			enemyMng_[i]->SetIsUse(true);
			//敵の格納
			useEnemy_.push_back(enemyMng_[i]);

			return;
		}
	}
}

void Stealth::MemorizeEnemy(std::string key)
{
	auto size = useEnemy_.size();
	memorizePos_[key].clear();
	memorizeType_[key].clear();

	for (int i = 0; i < size; i++)
	{
		//タイプとポジションの記録
		memorizePos_[key].push_back(useEnemy_[i]->GetPos());
		memorizeType_[key].push_back(useEnemy_[i]->GetType());
		//役目を終えたので非使用に変換
		useEnemy_[i]->SetIsUse(false);
	}

	useEnemy_.clear();

	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//使用フラグを全てリセット
		enemyMng_[i]->SetIsUse(false);
	}
}

void Stealth::SetIsEnemyMove(bool flag)
{
	isEnemyMove_ = flag;
}

bool Stealth::IsEnemyMove(void) const
{
	return isEnemyMove_;
}

