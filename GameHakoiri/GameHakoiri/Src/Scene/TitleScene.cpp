#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"TitleScene.h"


//コンストラクタ
//********************************************************
TitleScene::TitleScene(void)
{
}
//デストラクタ
//********************************************************
TitleScene::~TitleScene(void)
{

}
//初期化
//********************************************************
bool TitleScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void TitleScene::Update(void)
{
	if (SceneManager::GetInstance().SpaceHit() == true)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
//描画
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);
}
//解放
//********************************************************
bool TitleScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}