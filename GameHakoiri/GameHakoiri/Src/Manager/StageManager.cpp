#include<DxLib.h>
#include"ResourceManager.h"
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
#include"../Stage/FirstStage.h"
#include"../Stage/SecondStage.h"
#include"../Stage/ThirdStage.h"


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

		break;
	case StageManager::STAGENUM::THIRD:

		break;
	default:
		break;
	}

	if (!stage_->Init())
	{
		OutputDebugString("ステージの初期化失敗");
		return false;
	}

	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void StageManager::Update(GameScene::MODE mode)
{
	stage_->Update(mode);
}
//描画
//********************************************************
void StageManager::Draw(GameScene::MODE mode)
{
	stage_->Draw(mode);
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
//ステルス初期化
void StageManager::ChangeModeInit(void)
{
	if (!stage_->InitStealth()) { OutputDebugString("ステルス初期化失敗\n"); }
}
#pragma region 読み込み

void StageManager::LoadImg(void)
{
	//部屋
	roomImg_[static_cast<int>(RoomBase::TYPE::BATH)] =
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

	//マップチップ
	mapTile_[static_cast<int>(MAPCHIP::BATH)]=
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::EXTERIA)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EXTERIA_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::INTERIA)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::INTERIA_MAPTHIP).handleIds_;
}

void StageManager::LoadCsv(void)
{
	//パズル
	stageCsv_[static_cast<int>(STAGENUM::FIRST)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRST_PAZZLE_CSV).dmcHandleIds_;

	//部屋（map&obj)
	mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_OBJ_CSV).dmcHandleIds_;
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