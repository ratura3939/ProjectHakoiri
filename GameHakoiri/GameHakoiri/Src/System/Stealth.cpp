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
	prevPlayerPos_ = player_->GetPos();
	
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

	prevPlayerPos_ = player_->GetPos();
	player_->Update();

	Collision();
}
//�`��
//********************************************************
void Stealth::Draw(void)
{
	player_->Draw();
	//StageManager::GetInstance().DrawObject();
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
	//�X�e�[�W�}�l�[�W���擾
	auto& stage = StageManager::GetInstance();

	//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	//--------------------------------------------------------
	//�v���C���[�̓����蔻����W���}�b�v�̔z��ԍ��ɕϊ�
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
	OutputDebugString("�C�x���g�I�u�W�F�N�g\n");
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

