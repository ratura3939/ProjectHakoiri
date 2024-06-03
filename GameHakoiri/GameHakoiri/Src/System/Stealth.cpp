#include<DxLib.h>

#include"../Application.h"

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Object/Player.h"
#include"Stealth.h"

//�R���X�g���N�^
//********************************************************
Stealth::Stealth(void)
{
	player_ = nullptr;
}
//�f�X�g���N�^
//********************************************************
Stealth::~Stealth(void)
{

}

//������
//********************************************************
bool Stealth::Init(void)
{
	StageManager::GetInstance().ChangeModeInit();
	//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
	auto& camera = Camera::GetInstance();
	camera.SetMapSize(StageManager::GetInstance().GetMapMaxSize());
	player_ = new Player;
	player_->Init();
	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void Stealth::Update(void)
{
	//�J�������v���C���[�ɐݒ�
	auto& camera = SceneManager::GetInstance().GetCamera();
	camera.SetTargetPos(player_->GetPos());

	player_->Update();

	Collision();
}
//�`��
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	DrawDebug();
}
//���
//********************************************************
bool Stealth::Release(void)
{
	player_->Release();
	//�������������I�������̂�
	return true;
}

#pragma region �����蔻��

void Stealth::Collision(void)
{

}

#pragma endregion


void Stealth::ChangeRoom(void/*�����ꂩ�͓��������̎w�萔�������*/)
{

	//�J�����Ƀ}�b�v�̃T�C�Y��ݒ�
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
		"�J�������W(%.1f,%.1f)\n�v���C���[���W(%.1f,%.1f)\n���S�Ƃ̋���(%.1f,%.1f)\n�v���C���[�Ƃ̋���(%.1f,%.1f)",
		cameraPos.x_, cameraPos.y_,
		pPos.x_, pPos.y_,
		cameraDir.x_,cameraDir.y_,
		diff.x_,diff.y_);


}

