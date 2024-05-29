#include<DxLib.h>
#include"ResourceManager.h"
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
#include"../Stage/FirstStage.h"
#include"../Stage/SecondStage.h"
#include"../Stage/ThirdStage.h"


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

	LoadImg();
	LoadCsv();

	switch (num_)
	{
	case StageManager::STAGENUM::TUTORIAL:
		//stage_ = new TutorialStage();
		break;
	case StageManager::STAGENUM::FIRST:
		stage_ = new FirstStage(stageCsv_[static_cast<int>(STAGENUM::FIRST)].begin(),
			FIRST_PAZZLE_SIZE_X, FIRST_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
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
//�p�Y�����Z�b�g
void StageManager::PazzleReset(void)
{
	stage_->ResetPazzl();
}
//�t���[���_��
void StageManager::SetFlash(bool flag)
{
	stage_->SetFrameFlash(flag);
}
//�X�e���X������
void StageManager::ChangeModeInit(void)
{
	if (!stage_->InitStealth()) { OutputDebugString("�X�e���X���������s\n"); }
}
#pragma region �ǂݍ���

void StageManager::LoadImg(void)
{
	//����
	roomImg_[static_cast<int>(RoomBase::TYPE::BATH)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::GOAL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::NONE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::NONE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WALL)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WALL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_IMG).handleId_;

	//�}�b�v�`�b�v
	mapTile_[static_cast<int>(MAPCHIP::BATH)]=
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::EXTERIA)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::EXTERIA_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::INTERIA)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::INTERIA_MAPTHIP).handleIds_;
}

void StageManager::LoadCsv(void)
{
	//�p�Y��
	stageCsv_[static_cast<int>(STAGENUM::FIRST)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FIRST_PAZZLE_CSV).dmcHandleIds_;

	//�����imap&obj)
	mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BATH_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENTRANCE_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::KITCHEN_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::LIVING_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::OWN_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::STRAGE_OBJ_CSV).dmcHandleIds_;
	mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WASITU_OBJ_CSV).dmcHandleIds_;
}
#pragma endregion



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