#include<DxLib.h>
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
#include"StageManager.h"

//�V���O���g����(�C���X�^���X�̏�����)
StageManager* StageManager::instance_ = nullptr;

//�R���X�g���N�^
//********************************************************
StageManager::StageManager(void)
{
	stage_ = nullptr;
	num_ = STAGENUM::MAX;
	dir_[static_cast<int>(Utility::DIR::UP)] = { 0,-1 };
	dir_[static_cast<int>(Utility::DIR::DOWN)] = { 0,1 };
	dir_[static_cast<int>(Utility::DIR::LEFT)] = { -1,0 };
	dir_[static_cast<int>(Utility::DIR::RIGHT)] = { 1,0 };
}
//�f�X�g���N�^
//********************************************************
void StageManager::Destroy(void)
{
	delete instance_;
}

//������
//********************************************************
bool StageManager::Init(STAGENUM num)
{
	num_ = num;

	switch (num_)
	{
	case StageManager::STAGENUM::TUTORIAL:
		stage_ = new TutorialStage();
		break;
	case StageManager::STAGENUM::FIRST:

		break;
	case StageManager::STAGENUM::SECOND:

		break;
	case StageManager::STAGENUM::THIRD:

		break;
	default:
		break;
	}

	if (!stage_->Init())
	{
		OutputDebugString("�X�e�[�W�̏��������s");
		return false;
	}

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void StageManager::Update(GameScene::MODE mode)
{
	stage_->Update(mode);
}
//�`��
//********************************************************
void StageManager::Draw(GameScene::MODE mode)
{
	stage_->Draw(mode);
}
//���
//********************************************************
bool StageManager::Release(void)
{
	stage_->Release();
	delete stage_;
	stage_ = nullptr;
	//�������������I�������̂�
	return true;
}

//�J�[�\���̈ړ�
//********************************************************
void StageManager::MoveCursor(Utility::DIR dir)
{
	stage_->SetCursor(dir_[static_cast<int>(dir)],dir);
}

//��̈ړ�
//********************************************************
void StageManager::MovePiece(Utility::DIR dir)
{
	stage_->SetPiece(dir_[static_cast<int>(dir)],dir);
}

void StageManager::PazzleReset(void)
{
	stage_->ResetPazzl();
}

void StageManager::SetFlash(bool flag)
{
	stage_->SetFrameFlash(flag);
}


//�O������ÓI�C���X�^���X�𐶐�
//********************************************************
bool StageManager::CreateInstance(STAGENUM num)
{
	if (instance_ == nullptr)
	{
		instance_ = new StageManager();	//�C���X�^���X����
	}
	if (!instance_->Init(num))	//�������Ɏ��s������
	{
		OutputDebugString("�X�e�[�W�}�l�[�W�����������s");
		return false;
	}
	//�������������I�������̂�
	return true;
}
//�C���X�^���X�̎擾
//********************************************************
StageManager& StageManager::GetInstance(void)
{
	return *instance_;
}