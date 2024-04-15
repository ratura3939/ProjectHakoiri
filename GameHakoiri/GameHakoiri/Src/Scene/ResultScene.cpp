#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"ResultScene.h"


//コンストラクタ
//********************************************************
ResultScene::ResultScene(void)
{

}
//デストラクタ
//********************************************************
ResultScene::~ResultScene(void)
{

}
//初期化
//********************************************************
bool ResultScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void ResultScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::ENDING, true);
	}
}
//描画
//********************************************************
void ResultScene::Draw(void)
{
	DrawString(0, 0, "ResultScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0x00ffff, true);
}
//解放
//********************************************************
bool ResultScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}