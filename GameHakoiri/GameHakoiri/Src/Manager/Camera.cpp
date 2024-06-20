#include"../Application.h"
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

void Camera::SetTargetPos(const Position pPos)
{
	targetPos_ = pPos;
}

void Camera::SetMapSize(const Position mapsize)
{
	mapSize_ = mapsize;
}

Position Camera::GetPos(void) const
{
	return pos_;
}

void Camera::MoveCamera(void)
{
	//�J��������i�n�_�j�ƃv���C���[�i�I�_�j�̃x�N�g��
	auto diff = targetPos_ - pos_;
	//���݂̃J�����ʒu���瑊�ΓI��
	auto scrCenter = pos_+localCenterPos_;

	auto cameraDir = scrCenter - pos_;

	//�J���������ړ�(�傫���[�������j
	//���ړ�
	if (diff.x_ < cameraDir.x_) { pos_.x_ -= cameraDir.x_ - diff.x_; }
	//�E�ړ�
	if (diff.x_ > cameraDir.x_) { pos_.x_ += diff.x_ - cameraDir.x_; }
	//��ړ�
	if (diff.y_ < cameraDir.y_) { pos_.y_ -= cameraDir.y_ - diff.y_; }
	//���ړ�
	if (diff.y_ > cameraDir.y_) { pos_.y_ += diff.y_ - cameraDir.y_; }

	//�ړ�����
	if (pos_.x_ < 0) { pos_.x_ = 0; }
	if (pos_.x_ + Application::SCREEN_SIZE_X > mapSize_.x_) { pos_.x_ = mapSize_.x_ - Application::SCREEN_SIZE_X; }
	if (pos_.y_ < 0) { pos_.y_ = 0; }
	if (pos_.y_ + Application::SCREEN_SIZE_Y > mapSize_.y_) { pos_.y_ = mapSize_.y_ - Application::SCREEN_SIZE_Y; }
}
