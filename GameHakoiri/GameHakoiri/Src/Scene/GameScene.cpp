#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"GameScene.h"


//コンストラクタ
//********************************************************
GameScene::GameScene(void)
{
	mode_ = MODE::PAZZLE;
	pzl_ = nullptr;
	stl_ = nullptr;
}
//デストラクタ
//********************************************************
GameScene::~GameScene(void)
{
	
}
//初期化
//********************************************************
bool GameScene::Init(void)
{
	//インスタンスの生成
	if (!StageManager::CreateInstance(static_cast<StageManager::STAGENUM>(SceneManager::GetInstance().GetStageNum())))
	{
		return false;	//初期化失敗のためシステム終了
	}

	mode_ = MODE::PAZZLE;
	pzl_ = new Pazzle;

	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);
	}


	switch (mode_)
	{
	case GameScene::MODE::PAZZLE:
		pzl_->Update();
		break;
	case GameScene::MODE::STEALTH:

		break;
	}

}
//描画
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw();
	DrawString(0, 0, "GameScene", 0xffffff, true);
	DrawFormatString(0, 100, 0xffffff, "%d", pzl_->IsNeutral(), true);
}
//解放
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	delete pzl_;
	pzl_ = nullptr;
	delete stl_;
	stl_ = nullptr;

	//正常に処理が行われたので
	return true;
}