#include<DxLib.h>
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
void StageManager::Update(void)
{

}
//�`��
//********************************************************
void StageManager::Draw(void)
{
	stage_->PazzleDraw();
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
	switch (dir)
	{
	case Utility::DIR::UP:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetCursor(-1, 0);
		break;
	case Utility::DIR::RIGHT:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetCursor(0, 1);
		break;
	case Utility::DIR::DOWN:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetCursor(1, 0);
		break;
	case Utility::DIR::LEFT:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetCursor(0, -1);
		break;
	}
}

//��̈ړ�
//********************************************************
void StageManager::MovePiece(Utility::DIR dir)
{
	switch (dir)
	{
	case Utility::DIR::UP:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetPiece(-1, 0);
		break;
	case Utility::DIR::RIGHT:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetPiece(0, 1);
		break;
	case Utility::DIR::DOWN:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetPiece(1, 0);
		break;
	case Utility::DIR::LEFT:
		//�J�[�\���̈ړ��i�c�����̈ړ��ʁA�������̈ړ��ʁj
		stage_->SetPiece(0, -1);
		break;
	}
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