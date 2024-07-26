#include<DxLib.h>
#include<memory>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
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
	isPlate_ = false;
	str_ = "NONE";

	SoundManager::GetInstance().PlayBgmOfPazzle();
	//マニュアルのセット
	SceneManager::GetInstance().SetManual(MODE::PAZZLE);

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

	//プレートの描画が終了し次に行く状態だったら
	if (!isPlate_ && goToNext_)
	{
		//フラッシュの停止
		stage.SetFlash(false);

		//BGM
		SoundManager::GetInstance().StopBgmOfPazzle();
		SoundManager::GetInstance().PlayBgmOfStealth();

		//ステルスシーンの初期化
		SetMode(MODE::STEALTH);
		stl_->Init();
		SceneManager::GetInstance().SetManual(MODE::STEALTH);
		goToNext_ = false;
		Update();	//見え方調整のため
	}

	if (!isPlate_)
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
					str_ = "この状態で進めますか？\n※進めるとパズル操作には戻れません。";
					goToNext_ = true;
					isPlate_ = true;
				}
				else
				{
					pzl_->ChangeIsFinish(false);
					str_ = "この状態ではクリアできません。";
					isPlate_ = true;
				}
			}
			break;
		case GameScene::MODE::STEALTH:
			stl_->Update();
			auto& mng = SceneManager::GetInstance();
			if (stage.IsClear())	//クリアしてたら
			{
				mng.ClearStage(mng.GetStageNum() - 1);	//フラグセット
				if (mng.CheckAllClear())
				{
					SoundManager::GetInstance().StopBgmOfStealth();
					mng.ChangeScene(SceneManager::SCENEID::ENDING, true);	//シーン遷移
				}
				else
				{
					SoundManager::GetInstance().StopBgmOfStealth();
					mng.ChangeScene(SceneManager::SCENEID::RESULT, true);	//シーン遷移
				}
				return;
			}
			if (stl_->IsFailde())	//クリアしてたら
			{
				SoundManager::GetInstance().StopBgmOfStealth();
				mng.ChangeScene(SceneManager::SCENEID::RESULT, true);	//シーン遷移
			}
			camera.Update();
			break;
		}
	}
	else
	{
		auto& plate = Plate::GetInstance();
		if (goToNext_)
		{
			plate.Update(Plate::TYPE::SELECT);
		}
		else
		{
			plate.Update(Plate::TYPE::CHECK);
		}
		if (plate.IsFinish())
		{
			isPlate_ = false;
			if (plate.GetAnswer() == Plate::ANSWER::NO)
			{
				pzl_->ChangeIsFinish(false);
				goToNext_ = false;
			}
		}
	}
}
//描画
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw(GetMode());
	if (mode_ == MODE::STEALTH) { stl_->Draw(); }
	if (isPlate_ && !goToNext_) Plate::GetInstance().Draw(Plate::TYPE::CHECK, str_, false);
	if (isPlate_ && goToNext_) Plate::GetInstance().Draw(Plate::TYPE::SELECT, str_, false);
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
