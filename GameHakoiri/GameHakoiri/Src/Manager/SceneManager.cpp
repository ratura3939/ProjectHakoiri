#include<DxLib.h>
#include"SceneManager.h"
#include"../Scene/SceneBase.h"
#include"../Scene/TitleScene.h"
#include"../Scene/SelectScene.h"
#include"../Scene/GameScene.h"
#include"../Scene/ResultScene.h"
#include"../Scene/EndingScene.h"
#include"../Common/Fader.h"


//シングルトン化(インスタンスの初期化)
SceneManager* SceneManager::instance_ = nullptr;

//コンストラクタ
//********************************************************
SceneManager::SceneManager(void)
{
	sceneID_ = SCENEID::NONE;
	nextSceneID_ = SCENEID::NONE;
	space_.now = 0;
	space_.old = 0;
	isChangeScene_ = false;
	scene_ = nullptr;
	fader_ = nullptr;
}
//コピーコンストラクタ
//********************************************************
SceneManager::SceneManager(const SceneManager& ins)
{

}
//デストラクタ
//********************************************************
void SceneManager::Destroy(void)
{
	delete instance_;
}
//初期化
//********************************************************
bool SceneManager::Init(void)
{
	//シーン管理
	sceneID_ = SCENEID::NONE;
	nextSceneID_ = SCENEID::TITLE;

	DoChangeScene();

	//フェード
	fader_ = new Fader;
	fader_->Init();

	//トリガー
	space_.now = 0;
	space_.old = 0;

	//タイトルをフェードインで表示
	fader_->SetFade(Fader::STATE::FADE_IN);
	isChangeScene_ = true;

	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void SceneManager::Update(void)
{
	//フェード処理
	fader_->Update();
	if (isChangeScene_)
	{
		//フェード中
		Fade();
	}
	else
	{
		scene_->Update();
	}
}
//描画
//********************************************************
void SceneManager::Draw(void)
{
	
	scene_->Draw();
	//フェード
	fader_->Draw();
}
//解放
//********************************************************
bool SceneManager::Release(void)
{
	//インスタンスの解放
	ReleaseScene(sceneID_);

	delete fader_;
	fader_ = nullptr;
	instance_ = nullptr;
	//正しく処理が終了したので
	return true;
}

//スペースキーが押されたかどうか
//********************************************************
bool SceneManager::SpaceHit(void)
{
	space_.old = space_.now;
	space_.now = CheckHitKey(KEY_INPUT_SPACE);
	if (space_.now == 1 && space_.old == 0)
	{
		return true;
	}
	return false;
}
//シーン切り替え
//********************************************************
void SceneManager::ChangeScene(SCENEID next,bool isToFade)
{
	nextSceneID_ = next;
	if (isToFade)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isChangeScene_ = true;
	}
	else
	{
		DoChangeScene();
	}
}
//シーン切り替え(フェードなし)
//********************************************************
void SceneManager::DoChangeScene(void)
{
	//現在のシーンを解放する
	ReleaseScene(sceneID_);
	//次のシーンを生成する
	sceneID_ = nextSceneID_;

	switch (sceneID_)
	{
	case SCENEID::TITLE:
		//タイトル
		scene_ = new TitleScene;
		scene_->Init();
		break;

	case SCENEID::SELECT:
		//ステージ選択
		scene_ = new SelectScene;
		scene_->Init();
		break;

	case SCENEID::GAME:
		//ゲーム
		scene_ = new GameScene;
		scene_->Init();
		break;

	case SCENEID::RESULT:
		//リザルト
		scene_ = new ResultScene;
		scene_->Init();
		break;

	case SCENEID::ENDING:
		//エンディング
		scene_ = new EndingScene;
		scene_->Init();
		break;
	}
	nextSceneID_ = SCENEID::NONE;
}
//フェード実施用関数
//********************************************************
void SceneManager::Fade(void)
{
	//現在のフェード状態を取得
	Fader::STATE fState = fader_->GetState();

	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd() == true)
		{
			//シーン切り替え
			DoChangeScene();
			//明転
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd() == true)
		{
			//フェードの終了
			fader_->SetFade(Fader::STATE::NONE);
			//切り替え終了
			isChangeScene_ = false;
		}
		break;
	}
}
//指定したシーンの解放
//********************************************************
void SceneManager::ReleaseScene(SCENEID sceneID)
{
	if (sceneID != SCENEID::NONE)	//NONE以外だったら
	{
		//現在のシーンを解放する
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}
//外部から静的インスタンスを生成
//********************************************************
bool SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();	//インスタンス生成
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
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}