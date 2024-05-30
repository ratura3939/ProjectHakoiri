#include<DxLib.h>
#include<memory>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"GameScene.h"


//コンストラクタ
//********************************************************
GameScene::GameScene(void)
{
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
	SetMode(MODE::PAZZLE);
	pzl_ = new Pazzle;
	stl_ = new Stealth;

	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto& camera = SceneManager::GetInstance().GetCamera();

	if (ins.IsTrgDown(KEY_INPUT_W))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);
	}

	StageManager::GetInstance().Update(GetMode());

	switch (mode_)
	{
	case GameScene::MODE::PAZZLE:
		pzl_->Update();
		if (pzl_->IsFinish())
		{
			SetMode(MODE::STEALTH);
			stl_->Init();
		}
		break;
	case GameScene::MODE::STEALTH:
		stl_->Update();
		camera.Update();
		break;
	}

}
//描画
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw(GetMode());
	if (mode_ == MODE::STEALTH) { stl_->Draw(); }

	DrawString(0, 0, "GameScene", 0xffffff, true);
}
//解放
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	delete pzl_;
	pzl_ = nullptr;
	stl_->Release();
	delete stl_;
	stl_ = nullptr;

	//正常に処理が行われたので
	return true;
}


void GameScene::SetMode(MODE mode)
{
	mode_ = mode;
}

GameScene::MODE GameScene::GetMode(void)
{
	return mode_;
}
