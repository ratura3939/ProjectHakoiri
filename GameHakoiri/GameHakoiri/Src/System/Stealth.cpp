#include<DxLib.h>

#include"../Application.h"

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"../Object/Enemy/Housemaid.h"
#include"../Object/Enemy/Seneschal.h"
#include"Stealth.h"

//コンストラクタ
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
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
	prevPlayerPos_ = player_->GetPos();

	EnemyInit();
	SetEnemy();
	
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

	prevPlayerPos_ = player_->GetPos();
	player_->Update();


	Collision();
}
//描画
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	//StageManager::GetInstance().DrawObject();
	DrawDebug();

	auto& ins = InputManager::GetInstance();
	if (ins.IsNew(KEY_INPUT_M))
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

#pragma region 当たり判定

//当たり判定総括
void Stealth::Collision(void)
{
	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();

	//プレイヤーとオブジェクトの当たり判定
	//--------------------------------------------------------
	//プレイヤーの当たり判定座標をマップの配列番号に変換
	auto pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	
	if (stage.IsCollisionWall(pCol))
	{
		CollisionObstacle();
	}
	else if (stage.IsCollisionObject(pCol))
	{
	 	auto type = stage.GetObjectType(pCol);
		if (type == StageManager::OBJECT::OBSTACLE) { CollisionObstacle(); }
		if (type == StageManager::OBJECT::THROUGH) { CollisionTrough(pCol); }
		if (type == StageManager::OBJECT::EVENT) { CollisionEvent(pCol); }

		//pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	}
	
}
//通り抜け不可なオブジェクト
void Stealth::CollisionObstacle(void)
{
	player_->SetPos(prevPlayerPos_);
}
//最下段以外は通り抜け可能なオブジェクト
void Stealth::CollisionTrough(Vector2 pCol)
{
	if(StageManager::GetInstance().IsBottomObject(pCol)){ player_->SetPos(prevPlayerPos_); }
}
//扉などのイベントが起こるオブジェクト
void Stealth::CollisionEvent(Vector2 pCol)
{
	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();
	auto prevKey = stage.GetKey();

	stage.ChangeMap(pCol);	//部屋の移動処理

	if (stage.IsClear())
	{
		return;	//ゴールしてたら処理中断
	}

	if (!stage.IsMove())		//移動できないとき
	{
		player_->SetPos(prevPlayerPos_);
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
					pos = { DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };	//マップ下方に出る
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
						pos = { mapSize.x_ - DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };
					}
					else if (door.y == StageManager::DOOR_Y::BOTTOM)
					{
						//右側の上に出る
						pos = { mapSize.x_ - DOOR_DISTANCE,INIT_ROOM_POS };
					}
				}
				else 
				{
					if (door.y == StageManager::DOOR_Y::TOP)
					{
						//左側の下に出る
						pos = { DOOR_DISTANCE,mapSize.y_ - INIT_ROOM_POS };
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
					pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//右に設定
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
						pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,mapSize.y_ - DOOR_DISTANCE };	//右下に設定
					}
					else if (door.x == StageManager::DOOR_X::RIGHT)
					{
						pos = { INIT_ROOM_POS_SIDE,mapSize.y_ - DOOR_DISTANCE };	//左下に設定
					}
				}
				else
				{
					//playerがどっちから来たかを判断
					if (door.x == StageManager::DOOR_X::LEFT)
					{
						pos = { mapSize.x_ - INIT_ROOM_POS_SIDE,DOOR_DISTANCE };	//右上に設定
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


void Stealth::ChangeRoom(void/*いずれかは動く部屋の指定数をいれる*/)
{

	//カメラにマップのサイズを設定
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
}

void Stealth::DrawDebug(void)
{
	auto pos = player_->GetCollisionPos();
	auto pPos = player_->GetPos();
	

	DrawFormatString(0, 0, 0xffffff,
		"playerの座標＝(%.1f,%.1f)\nplayerの当たり判定＝(%.1f,%.1f)\n",
		pPos.x_,pPos.y_,pos.x_,pos.y_);


}

void Stealth::EnemyInit(void)
{
	for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)
	{
		//敵を三体ずつ生成
		if (i < OBLONG_ENEMY_NUM)
		{
			enemyMng_[i] = new Housemaid;
		}
		else
		{
			enemyMng_[i] = new Seneschal;
		}
	}

	initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::NOMAL)][1] =
	{ (StageManager::NOMAL_MAP_X * StageManager::UNIT_STEALTH_SIZE_X) / 4,
	(StageManager::NOMAL_MAP_Y * StageManager::UNIT_STEALTH_SIZE_Y) / 2 };
}

void Stealth::CreateEnemy(void)
{
	int rnd;
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

void Stealth::SetEnemyPos(void)
{

}

void Stealth::SetEnemy(void)
{

	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();
	auto key = stage.GetKey();

	//現在の部屋に敵の生成記録がなかった時
	if (memorizePos_[key].empty())
	{
		//敵の生成
		if (stage.GetShape() == RoomBase::ROOM_SHAPE::NOMAL)	
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
	}
	else
	{
		//生成記録があった場合
		auto size = memorizePos_[key].size();
		for (int m = 0; m < size; m++)	//敵の生成数分回す
		{
			for (int i = 0; i < OBLONG_ENEMY_NUM * static_cast<int>(EnemyBase::TYPE::MAX); i++)//敵の管理全体
			{
				if (memorizeType_[key][m] == enemyMng_[i]->GetType() &&	//保存されている種類と同じだったら
					!enemyMng_[i]->IsUse())	//まだ使用されてなかったら
				{
					//敵のフラグ管理と位置の設定
					enemyMng_[i]->SetPos(memorizePos_[key][m]);
					enemyMng_[i]->SetIsUse(true);
					//敵の格納
					useEnemy_.push_back(enemyMng_[i]);
					
					return;
				}
			}
		}
	}
}

void Stealth::MemorizeEnemy(std::string key)
{
	auto size = useEnemy_.size();
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

