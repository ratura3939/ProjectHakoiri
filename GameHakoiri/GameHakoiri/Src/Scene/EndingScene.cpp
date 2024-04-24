#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"EndingScene.h"


//コンストラクタ
//********************************************************
EndingScene::EndingScene(void)
{
}
//デストラクタ
//********************************************************
EndingScene::~EndingScene(void)
{

}
//初期化
//********************************************************
bool EndingScene::Init(void)
{
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void EndingScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE , true);
	}
}
//描画
//********************************************************
void EndingScene::Draw(void)
{
	DrawString(0, 0, "EndingScene", 0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffffff, true);
}
//解放
//********************************************************
bool EndingScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}