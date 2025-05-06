#include"../Application.h"
#include "Camera.h"

//シングルトン化(インスタンスの初期化)
Camera* Camera::instance_ = nullptr;

void Camera::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Camera();	//インスタンス生成
	}
	instance_->Init();
}

Camera& Camera::GetInstance(void)
{
	return *instance_;
}

Camera::Camera(void)
{
	pos_ = { 0.0f,0.0f };
	localCenterPos_ = { 0.0f,0.0f };
	targetPos_ = { 0.0f,0.0f };
	mapSize_ = { 0.0f,0.0f };
}

Camera::~Camera(void)
{
}

bool Camera::Init(void)
{
	localCenterPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
	return true;
}

void Camera::Update(void)
{
	MoveCamera();
}

void Camera::Relese(void)
{
}

void Camera::SetTargetPos(const Vector2F pPos)
{
	targetPos_ = pPos;
}

void Camera::SetMapSize(const Vector2F mapsize)
{
	mapSize_ = mapsize;
}

const Vector2F Camera::GetPos(void) const
{
	return pos_;
}

void Camera::MoveCamera(void)
{
	//カメラ左上（始点）とプレイヤー（終点）のベクトル
	Vector2F diff = targetPos_ - pos_;
	//現在のカメラ位置から相対的に
	Vector2F scrCenter = pos_+localCenterPos_;

	Vector2F cameraDir = scrCenter - pos_;

	//カメラ差分移動(大きいー小さい）
	//左移動
	if (diff.x < cameraDir.x) { pos_.x -= cameraDir.x - diff.x; }
	//右移動
	if (diff.x > cameraDir.x) { pos_.x += diff.x - cameraDir.x; }
	//上移動
	if (diff.y < cameraDir.y) { pos_.y -= cameraDir.y - diff.y; }
	//下移動
	if (diff.y > cameraDir.y) { pos_.y += diff.y - cameraDir.y; }

	//移動制限
	if (pos_.x < 0) { pos_.x = 0; }
	if (pos_.x + Application::SCREEN_SIZE_X > mapSize_.x) { pos_.x = mapSize_.x - Application::SCREEN_SIZE_X; }
	if (pos_.y < 0) { pos_.y = 0; }
	if (pos_.y + Application::SCREEN_SIZE_Y > mapSize_.y) { pos_.y = mapSize_.y - Application::SCREEN_SIZE_Y; }
}
