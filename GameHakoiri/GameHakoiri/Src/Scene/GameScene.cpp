#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/StageManager.h"
#include"../System/Pazzle.h"
#include"../System/Stealth.h"
#include"GameScene.h"


//コンストラクタ
//********************************************************
GameScene::GameScene(void)
{

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
	if (!StageManager::CreateInstance())
	{
		return false;	//初期化失敗のためシステム終了
	}

	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void GameScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::RESULT, true);
	}
}
//描画
//********************************************************
void GameScene::Draw(void)
{
	StageManager::GetInstance().Draw();
	DrawString(0, 0, "GameScene", 0xffffff, true);
	//DrawBox(50, 50, 500, 500, 0x0000ff, true);
}
//解放
//********************************************************
bool GameScene::Release(void)
{
	StageManager::GetInstance().Release();
	//正常に処理が行われたので
	return true;
}