#include "Camera.h"

//�V���O���g����(�C���X�^���X�̏�����)
Camera* Camera::instance_ = nullptr;

void Camera::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Camera();	//�C���X�^���X����
	}
	instance_->Init();
}

Camera& Camera::GetInstance(void)
{
	return *instance_;
}

Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

bool Camera::Init(void)
{
	return true;
}

void Camera::Update(void)
{
	MoveCamera();
}

void Camera::Relese(void)
{
}

void Camera::SetTargetPos(Vector2F pPos)
{
	targetPos_ = pPos;
}

Vector2F Camera::GetPos(void) const
{
	return pos_;
}

void Camera::MoveCamera(void)
{

}
