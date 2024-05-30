#include<DxLib.h>

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"Stealth.h"

//コンストラクタ
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
}
//デストラクタ
//********************************************************
Stealth::~Stealth(void)
{

}

//初期化
//********************************************************
bool Stealth::Init(void)
{
	StageManager::GetInstance().ChangeModeInit();
	player_ = new Player;
	player_->Init();
	//正しく処理が終了したので
	return true;
}
//更新
//********************************************************
void Stealth::Update(void)
{
	//カメラをプレイヤーに設定
	auto& camera = SceneManager::GetInstance().GetCamera();
	camera.SetTargetPos(player_->GetPos());

	player_->Update();
}
//描画
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
}
//解放
//********************************************************
bool Stealth::Release(void)
{
	player_->Release();
	//正しく処理が終了したので
	return true;
}