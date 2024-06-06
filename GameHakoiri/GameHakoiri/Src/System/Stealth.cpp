#include<DxLib.h>

#include"../Application.h"

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
	//カメラにマップのサイズを設定
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
	player_ = new Player;
	player_->Init();
	prevPlayerPos_ = player_->GetPos();
	
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

	prevPlayerPos_ = player_->GetPos();
	player_->Update();

	Collision();
}
//描画
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	//StageManager::GetInstance().DrawObject();
	DrawDebug();
}
//解放
//********************************************************
bool Stealth::Release(void)
{
	player_->Release();
	//正しく処理が終了したので
	return true;
}

#pragma region 当たり判定

void Stealth::Collision(void)
{
	//ステージマネージャ取得
	auto& stage = StageManager::GetInstance();

	//プレイヤーとオブジェクトの当たり判定
	//--------------------------------------------------------
	//プレイヤーの当たり判定座標をマップの配列番号に変換
	auto pCol = stage.GetVector2MapPos(player_->GetCollisionPos().ToVector2());
	
	if (stage.IsCollisionObject(pCol))
	{
		auto type = stage.GetObjectType(pCol);
		if (type == StageManager::OBJECT::OBSTACLE) { CollisionObstacle(); }
		if (type == StageManager::OBJECT::THROUGH) { CollisionTrough(pCol); }
		if (type == StageManager::OBJECT::EVENT) { CollisionEvent(pCol); }
	}
	if (stage.IsCollisionWall(pCol))
	{
		CollisionObstacle();
	}
}

void Stealth::CollisionObstacle(void)
{
	player_->SetPos(prevPlayerPos_);
}

void Stealth::CollisionTrough(Vector2 pCol)
{
	if(StageManager::GetInstance().IsBottomObject(pCol)){ player_->SetPos(prevPlayerPos_); }
}

void Stealth::CollisionEvent(Vector2 pCol)
{
	OutputDebugString("イベントオブジェクト\n");
}

#pragma endregion


void Stealth::ChangeRoom(void/*いずれかは動く部屋の指定数をいれる*/)
{

	//カメラにマップのサイズを設定
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
}

void Stealth::DrawDebug(void)
{
	//objectPos
	auto cameraPos = Camera::GetInstance().GetPos();
	auto pPos = player_->GetPos();

	auto diff = pPos - cameraPos;
	Vector2F scr = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };
	Vector2F scrCenter = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };

	auto cameraDir = scrCenter - cameraPos;

	DrawFormatString(0, 0, 0xff0000,
		"カメラ座標(%.1f,%.1f)\nプレイヤー座標(%.1f,%.1f)\n中心との距離(%.1f,%.1f)\nプレイヤーとの距離(%.1f,%.1f)",
		cameraPos.x_, cameraPos.y_,
		pPos.x_, pPos.y_,
		cameraDir.x_,cameraDir.y_,
		diff.x_,diff.y_);


}

