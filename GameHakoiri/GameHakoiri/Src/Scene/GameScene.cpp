#include<DxLib.h>
#include"../Manager/SceneManager.h"
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
	DrawString(0, 0, "GameScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0x0000ff, true);
}
//解放
//********************************************************
bool GameScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}