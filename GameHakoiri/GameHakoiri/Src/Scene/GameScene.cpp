#include<DxLib.h>
#include<memory>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/Camera.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"../System/Plate.h"
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
	isCheck_ = false;
	str_ = "NONE";

	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto& camera = SceneManager::GetInstance().GetCamera();
	auto& stage = StageManager::GetInstance();

	stage.Update(GetMode());

	if (!isCheck_)
	{
		switch (mode_)
		{
		case GameScene::MODE::PAZZLE:
			pzl_->Update();
			if (pzl_->IsFinish())	//パズル終了したら
			{
				//クリア可能なら
				if (stage.CanGoal())
				{
					//ステルスシーンの初期化
					SetMode(MODE::STEALTH);
					stl_->Init();
					Update();	//見え方調整のため
				}
				else
				{
					pzl_->ChangeIsFinish(false);
					str_ = "この状態ではクリアできません。";
					isCheck_ = true;
				}
			}
			break;
		case GameScene::MODE::STEALTH:
			stl_->Update();
			if (stage.IsClear())	//クリアしてたら
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);	//シーン遷移
			}
			if (stl_->IsFailde())	//クリアしてたら
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);	//シーン遷移
			}
			camera.Update();
			break;
		}
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::CHECK);
		if (plate.IsFinish() && plate.GetAnswer() == Plate::ANSWER::OK)	isCheck_ = false;
	}

}
//描画
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw(GetMode());
	if (mode_ == MODE::STEALTH) { stl_->Draw(); }
	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::CHECK, str_);

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
