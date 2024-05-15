#include<DxLib.h>
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
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

	switch (num_)
	{
	case StageManager::STAGENUM::TUTORIAL:
		stage_ = new TutorialStage();
		break;
	case StageManager::STAGENUM::FIRST:

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

void StageManager::PazzleReset(void)
{
	stage_->ResetPazzl();
}

void StageManager::SetFlash(bool flag)
{
	stage_->SetFrameFlash(flag);
}


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