#include<DxLib.h>
#include"StageManager.h"

//シングルトン化(インスタンスの初期化)
StageManager* StageManager::instance_ = nullptr;

//コンストラクタ
//********************************************************
StageManager::StageManager(void)
{

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

}
//解放
//********************************************************
bool StageManager::Release(void)
{

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
		OutputDebugString("シーンマネージャ初期化失敗");
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