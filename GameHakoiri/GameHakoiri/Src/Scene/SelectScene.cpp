#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"SelectScene.h"


//コンストラクタ
//********************************************************
SelectScene::SelectScene(void)
{

}
//デストラクタ
//********************************************************
SelectScene::~SelectScene(void)
{

}
//初期化
//********************************************************
bool SelectScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void SelectScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
	}
}
//描画
//********************************************************
void SelectScene::Draw(void)
{
	DrawString(0, 0, "SelectScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xff00ff, true);
}
//解放
//********************************************************
bool SelectScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}