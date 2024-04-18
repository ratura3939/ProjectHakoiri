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
}
//デストラクタ
//********************************************************
void StageManager::Destroy(void)
{
	delete instance_;
}

//初期化
//********************************************************
bool StageManager::Init(void)
{
	stage_ = new TutorialStage();
	if (!stage_->Init())
	{
		OutputDebugString("チュートリアルの初期化失敗");
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
	stage_->Draw();
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
//外部から静的インスタンスを生成
//********************************************************
bool StageManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new StageManager();	//インスタンス生成
	}
	if (!instance_->Init())	//初期化に失敗したら
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