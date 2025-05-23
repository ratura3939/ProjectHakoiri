#include<DxLib.h>
#include"ResourceManager.h"
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
#include"../Stage/FirstStage.h"
#include"../Stage/SecondStage.h"
#include"../Stage/ThirdStage.h"
#include"../Application.h"
#include"../Utility/Utility.h"

#include"StageManager.h"

//シングルトン化(インスタンスの初期化)
StageManager* StageManager::instance_ = nullptr;



//コンストラクタ
//********************************************************
StageManager::StageManager(void)
{
	stage_ = nullptr;
	num_ = STAGENUM::MAX;
	dir_[static_cast<int>(Utility::DIR::UP)] = { 0,-1 };
	dir_[static_cast<int>(Utility::DIR::DOWN)] = { 0,1 };
	dir_[static_cast<int>(Utility::DIR::LEFT)] = { -1,0 };
	dir_[static_cast<int>(Utility::DIR::RIGHT)] = { 1,0 };
}
//デストラクタ
//********************************************************
void StageManager::Destroy(void)
{
	delete instance_;
}

//初期化
//********************************************************
bool StageManager::Init(STAGENUM num)
{
	num_ = num;

	LoadImg();
	LoadCsv();

	SetIsDrawPazzleManual(true);

	switch (num_)
	{
	case StageManager::STAGENUM::TUTORIAL:
		//stage_ = new TutorialStage();
		break;
	case StageManager::STAGENUM::FIRST:
		stage_ = new FirstStage(stageCsv_[static_cast<int>(STAGENUM::FIRST)].begin(),
			FIRST_PAZZLE_SIZE_X, FIRST_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
		break;
	case StageManager::STAGENUM::SECOND:
		stage_ = new SecondStage(stageCsv_[static_cast<int>(STAGENUM::SECOND)].begin(),
			SECOND_PAZZLE_SIZE_X, SECOND_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
		break;
	case StageManager::STAGENUM::THIRD:
		stage_ = new SecondStage(stageCsv_[static_cast<int>(STAGENUM::THIRD)].begin(),
			THIRD_PAZZLE_SIZE_X, THIRD_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
		break;
	default:
		break;
	}

	if (!stage_->Init())
	{
		OutputDebugString("ステージの初期化失敗");
		return false;
	}

	manualFlash_ = 0;

	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void StageManager::Update(GameScene::MODE mode)
{
	stage_->Update(mode);

	if (mode == GameScene::MODE::PAZZLE)
	{
		manualFlash_++;
		if (manualFlash_ > MANUAL_FLASH_MAX)manualFlash_ = 0;
	}
}
//描画
//********************************************************
void StageManager::Draw(GameScene::MODE mode)
{
	stage_->Draw(mode);

	if (mode == GameScene::MODE::PAZZLE && isDrawPazzleManual_)
	{
		auto cnt = SceneManager::GetInstance().GetController();

		if (manualFlash_ % Application::FPS < MANUAL_FLASH)
		{
			DrawRotaGraph(Application::SCREEN_SIZE_X - MANUAL_SIZE / 2, MANUAL_SIZE / 2,
				0.5f,
				0.0f * Utility::DEG2RAD,
				manualImg_[static_cast<int>(cnt)],
				true,
				false);
		}
	}
}
void StageManager::DrawObject(void)
{
	stage_->DrawObject();
}
//解放
//********************************************************
bool StageManager::Release(void)
{
	stage_->Release();
	delete stage_;
	stage_ = nullptr;
	//正しく処理が終了したので
	return true;
}

//カーソルの移動
//********************************************************
void StageManager::MoveCursor(Utility::DIR dir)
{
	stage_->SetCursor(dir_[static_cast<int>(dir)],dir);
}

//駒の移動
//********************************************************
void StageManager::MovePiece(Utility::DIR dir)
{
	stage_->SetPiece(dir_[static_cast<int>(dir)],dir);
}
//パズルリセット
void StageManager::PazzleReset(void)
{
	stage_->ResetPazzl();
}
//フレーム点滅
void StageManager::SetFlash(bool flag)
{
	stage_->SetFrameFlash(flag);
}
bool StageManager::CanGoal(void)
{
	return stage_->CanGoal();
}
//ステルス初期化
void StageManager::ChangeModeInit(void)
{
	if (!stage_->InitStealth()) { OutputDebugString("ステルス初期化失敗\n"); }
}
//部屋の切り替え
void StageManager::ChangeMap(Vector2 pMapPos)
{
	stage_->ChangeRoom(pMapPos);
}
Vector2F StageManager::GetMapMaxSize(void)const
{
	return stage_->GetNowDrawMapSize();
}



#pragma region 当たり判定に必要な奴

bool StageManager::IsCollisionObject(const Vector2 pMapPos) const
{
	if (stage_->IsMapObj(pMapPos)) { return true; }
	return false;
}
bool StageManager::IsCollisionWall(const Vector2 pMapPos) const
{
	auto map = stage_->GetMapNum(pMapPos);
	auto mapchip = stage_->GetMapchipType();
	auto sizeY = mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)].size();
	for (int y = 0; y < sizeY; y++)
	{
		auto sizeX = mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)][y].size();
		for (int x = 0; x < sizeX; x++)
		{
			if (map==mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)][y][x])
			{
				if (map != -1)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//座標をマップの配列に変換
Vector2 StageManager::GetVector2MapPos(const Vector2 pPos) const
{
	Vector2 ret;
	ret.x = pPos.x / UNIT_STEALTH_SIZE_X;
	ret.y = pPos.y / UNIT_STEALTH_SIZE_Y;
	return ret;
}
Vector2 StageManager::GetMapPos2Vector(const Vector2 pPos) const
{

	return Vector2{ pPos.x * UNIT_STEALTH_SIZE_X,pPos.y * UNIT_PAZZLE_SIZE_Y };
}
//オブジェクトのタイプを返却
StageManager::OBJECT StageManager::GetObjectType(const Vector2 pMapPos) const
{
	auto obj = stage_->GetObjNum(pMapPos);
	auto mapchip = stage_->GetMapchipType();
	OBJECT type = OBJECT::MAX;

	if (obj == -1)
	{
		return type;
	}

	//オブジェクトタイプ分のfor文
	for (int i = 0; i < static_cast<int>(OBJECT::MAX); i++)
	{
		//オブジェクト判定用のCSVを１個ずつ回す。
		auto sizeY = mapchipObj_[static_cast<int>(mapchip)][i].size();
		for (int y = 0; y < sizeY; y++)
		{
			auto sizeX = mapchipObj_[static_cast<int>(mapchip)][i][y].size();
			for (int x = 0; x < sizeX; x++)
			{
				if (obj == mapchipObj_[static_cast<int>(mapchip)][i][y][x])	//i=オブジェクト種類,x・y=CSV添字
				{
					return static_cast<OBJECT>(i);
				}
			}
		}
	}

	return type;
}
//オブジェクトの一番下かを判定
bool StageManager::IsBottomObject(const Vector2 pMapPos) const
{
	return stage_->CheckOneDownObject(pMapPos);
}
bool StageManager::IsMove(void)
{
	return stage_->IsMoveRoom();
}
RoomBase::ROOM_SHAPE StageManager::GetShape(void)
{
	return stage_->GetNowShape();
}
std::string StageManager::GetKey(void) const
{
	return stage_->GetKey();
}
StageManager::DOOR StageManager::GetDoor(void) const
{
	return stage_->GetDoorPos();
}
StageManager::DOOR_Y StageManager::GetDoorSecond(void) const
{
	return stage_->GetDoorPosSecond();
}
bool StageManager::IsSecondEvidence(void) const
{
	return stage_->IsSecondRoom();
}
bool StageManager::IsClear(void) const
{
	return stage_->IsGoal();
}
void StageManager::SetIsDrawPazzleManual(bool flag)
{
	isDrawPazzleManual_ = flag;
}
#pragma endregion




#pragma region 読み込み

void StageManager::LoadImg(void)
{
	auto& rsM = ResourceManager::GetInstance();

	//部屋
	roomImg_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)] =
		rsM.Load(ResourceManager::SRC::GOAL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::NONE)] =
		rsM.Load(ResourceManager::SRC::NONE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WALL)] =
		rsM.Load(ResourceManager::SRC::WALL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_IMG).handleId_;

	//マップチップ
	mapTile_[static_cast<int>(MAPCHIP::BATH)]=
		rsM.Load(ResourceManager::SRC::BATH_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::EXTERIA)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::INTERIA)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPTHIP).handleIds_;

	//パズル時操作方法
	manualImg_[static_cast<int>(SceneManager::CONTROLLER::KEYBOARD)] = 
		rsM.Load(ResourceManager::SRC::KBD_PZL_STR_IMG).handleId_;

	manualImg_[static_cast<int>(SceneManager::CONTROLLER::PAD)] =
		rsM.Load(ResourceManager::SRC::PAD_PZL_STR_IMG).handleId_;
}

void StageManager::LoadCsv(void)
{
	auto& rsM = ResourceManager::GetInstance();

	//パズル
	stageCsv_[static_cast<int>(STAGENUM::FIRST)] = 
		rsM.Load(ResourceManager::SRC::FIRST_PAZZLE_CSV).dmcHandleIds_;
	stageCsv_[static_cast<int>(STAGENUM::SECOND)] =
		rsM.Load(ResourceManager::SRC::SECOND_PAZZLE_CSV).dmcHandleIds_;
	stageCsv_[static_cast<int>(STAGENUM::THIRD)] =
		rsM.Load(ResourceManager::SRC::THIRD_PAZZLE_CSV).dmcHandleIds_;

	//部屋（map&obj)
	mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_OBJ_CSV).dmcHandleIds_;

	//当たり判定
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::OBSTACLE)]=
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_EVENT_CSV).dmcHandleIds_;

	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::OBSTACLE)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_EVENT_CSV).dmcHandleIds_;

	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::OBSTACLE)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_EVENT_CSV).dmcHandleIds_;
}

#pragma endregion



//外部から静的インスタンスを生成
//********************************************************
bool StageManager::CreateInstance(STAGENUM num)
{
	if (instance_ == nullptr)
	{
		instance_ = new StageManager();	//インスタンス生成
	}
	if (!instance_->Init(num))	//初期化に失敗したら
	{
		OutputDebugString("ステージマネージャ初期化失敗");
		return false;
	}
	//正しく処理が終了したので
	return true;
}
//インスタンスの取得
//********************************************************
StageManager& StageManager::GetInstance(void)
{
	return *instance_;
}