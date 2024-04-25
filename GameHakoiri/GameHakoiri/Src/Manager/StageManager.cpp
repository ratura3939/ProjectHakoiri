#include<DxLib.h>
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
void StageManager::Update(void)
{

}
//描画
//********************************************************
void StageManager::Draw(void)
{
	stage_->PazzleDraw();
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
	switch (dir)
	{
	case Utility::DIR::UP:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetCursor(-1, 0);
		break;
	case Utility::DIR::RIGHT:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetCursor(0, 1);
		break;
	case Utility::DIR::DOWN:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetCursor(1, 0);
		break;
	case Utility::DIR::LEFT:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetCursor(0, -1);
		break;
	}
}

//駒の移動
//********************************************************
void StageManager::MovePiece(Utility::DIR dir)
{
	switch (dir)
	{
	case Utility::DIR::UP:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetPiece(-1, 0);
		break;
	case Utility::DIR::RIGHT:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetPiece(0, 1);
		break;
	case Utility::DIR::DOWN:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetPiece(1, 0);
		break;
	case Utility::DIR::LEFT:
		//カーソルの移動（縦方向の移動量、横方向の移動量）
		stage_->SetPiece(0, -1);
		break;
	}
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