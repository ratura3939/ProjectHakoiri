#include<DxLib.h>
#include"ResourceManager.h"
#include"../Scene/GameScene.h"
#include"../Stage/StageBase.h"
#include"../Stage/TutorialStage.h"
#include"../Stage/FirstStage.h"
#include"../Stage/SecondStage.h"
#include"../Stage/ThirdStage.h"
#include"../Application.h"
#include"../Utility/Utility.h"

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

	SetIsDrawPazzleManual(true);

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
		stage_ = new SecondStage(stageCsv_[static_cast<int>(STAGENUM::SECOND)].begin(),
			SECOND_PAZZLE_SIZE_X, SECOND_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
		break;
	case StageManager::STAGENUM::THIRD:
		stage_ = new SecondStage(stageCsv_[static_cast<int>(STAGENUM::THIRD)].begin(),
			THIRD_PAZZLE_SIZE_X, THIRD_PAZZLE_SIZE_Y,
			mapCsv_, objCsv_,
			roomImg_, mapTile_);
		break;
	default:
		break;
	}

	if (!stage_->Init())
	{
		OutputDebugString("�X�e�[�W�̏��������s");
		return false;
	}

	manualFlash_ = 0;

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void StageManager::Update(GameScene::MODE mode)
{
	stage_->Update(mode);

	if (mode == GameScene::MODE::PAZZLE)
	{
		manualFlash_++;
		if (manualFlash_ > MANUAL_FLASH_MAX)manualFlash_ = 0;
	}
}
//�`��
//********************************************************
void StageManager::Draw(GameScene::MODE mode)
{
	stage_->Draw(mode);

	if (mode == GameScene::MODE::PAZZLE && isDrawPazzleManual_)
	{
		auto cnt = SceneManager::GetInstance().GetController();

		if (manualFlash_ % Application::FPS < MANUAL_FLASH)
		{
			DrawRotaGraph(Application::SCREEN_SIZE_X - MANUAL_SIZE / 2, MANUAL_SIZE / 2,
				0.5f,
				0.0f * Utility::DEG2RAD,
				manualImg_[static_cast<int>(cnt)],
				true,
				false);
		}
	}
}
void StageManager::DrawObject(void)
{
	stage_->DrawObject();
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
bool StageManager::CanGoal(void)
{
	return stage_->CanGoal();
}
//�X�e���X������
void StageManager::ChangeModeInit(void)
{
	if (!stage_->InitStealth()) { OutputDebugString("�X�e���X���������s\n"); }
}
//�����̐؂�ւ�
void StageManager::ChangeMap(Vector2 pMapPos)
{
	stage_->ChangeRoom(pMapPos);
}
Vector2F StageManager::GetMapMaxSize(void)const
{
	return stage_->GetNowDrawMapSize();
}



#pragma region �����蔻��ɕK�v�ȓz

bool StageManager::IsCollisionObject(const Vector2 pMapPos) const
{
	if (stage_->IsMapObj(pMapPos)) { return true; }
	return false;
}
bool StageManager::IsCollisionWall(const Vector2 pMapPos) const
{
	auto map = stage_->GetMapNum(pMapPos);
	auto mapchip = stage_->GetMapchipType();
	auto sizeY = mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)].size();
	for (int y = 0; y < sizeY; y++)
	{
		auto sizeX = mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)][y].size();
		for (int x = 0; x < sizeX; x++)
		{
			if (map==mapchipObj_[static_cast<int>(mapchip)][static_cast<int>(OBJECT::OBSTACLE)][y][x])
			{
				if (map != -1)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//���W���}�b�v�̔z��ɕϊ�
Vector2 StageManager::GetVector2MapPos(const Vector2 pPos) const
{
	Vector2 ret;
	ret.x = pPos.x / UNIT_STEALTH_SIZE_X;
	ret.y = pPos.y / UNIT_STEALTH_SIZE_Y;
	return ret;
}
Vector2 StageManager::GetMapPos2Vector(const Vector2 pPos) const
{

	return Vector2{ pPos.x * UNIT_STEALTH_SIZE_X,pPos.y * UNIT_PAZZLE_SIZE_Y };
}
//�I�u�W�F�N�g�̃^�C�v��ԋp
StageManager::OBJECT StageManager::GetObjectType(const Vector2 pMapPos) const
{
	auto obj = stage_->GetObjNum(pMapPos);
	auto mapchip = stage_->GetMapchipType();
	OBJECT type = OBJECT::MAX;

	if (obj == -1)
	{
		return type;
	}

	//�I�u�W�F�N�g�^�C�v����for��
	for (int i = 0; i < static_cast<int>(OBJECT::MAX); i++)
	{
		//�I�u�W�F�N�g����p��CSV���P���񂷁B
		auto sizeY = mapchipObj_[static_cast<int>(mapchip)][i].size();
		for (int y = 0; y < sizeY; y++)
		{
			auto sizeX = mapchipObj_[static_cast<int>(mapchip)][i][y].size();
			for (int x = 0; x < sizeX; x++)
			{
				if (obj == mapchipObj_[static_cast<int>(mapchip)][i][y][x])	//i=�I�u�W�F�N�g���,x�Ey=CSV�Y��
				{
					return static_cast<OBJECT>(i);
				}
			}
		}
	}

	return type;
}
//�I�u�W�F�N�g�̈�ԉ����𔻒�
bool StageManager::IsBottomObject(const Vector2 pMapPos) const
{
	return stage_->CheckOneDownObject(pMapPos);
}
bool StageManager::IsMove(void)
{
	return stage_->IsMoveRoom();
}
RoomBase::ROOM_SHAPE StageManager::GetShape(void)
{
	return stage_->GetNowShape();
}
std::string StageManager::GetKey(void) const
{
	return stage_->GetKey();
}
StageManager::DOOR StageManager::GetDoor(void) const
{
	return stage_->GetDoorPos();
}
StageManager::DOOR_Y StageManager::GetDoorSecond(void) const
{
	return stage_->GetDoorPosSecond();
}
bool StageManager::IsSecondEvidence(void) const
{
	return stage_->IsSecondRoom();
}
bool StageManager::IsClear(void) const
{
	return stage_->IsGoal();
}
void StageManager::SetIsDrawPazzleManual(bool flag)
{
	isDrawPazzleManual_ = flag;
}
#pragma endregion




#pragma region �ǂݍ���

void StageManager::LoadImg(void)
{
	auto& rsM = ResourceManager::GetInstance();

	//����
	roomImg_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)] =
		rsM.Load(ResourceManager::SRC::GOAL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::NONE)] =
		rsM.Load(ResourceManager::SRC::NONE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WALL)] =
		rsM.Load(ResourceManager::SRC::WALL_IMG).handleId_;
	roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_IMG).handleId_;

	//�}�b�v�`�b�v
	mapTile_[static_cast<int>(MAPCHIP::BATH)]=
		rsM.Load(ResourceManager::SRC::BATH_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::EXTERIA)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPTHIP).handleIds_;
	mapTile_[static_cast<int>(MAPCHIP::INTERIA)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPTHIP).handleIds_;

	//�p�Y����������@
	manualImg_[static_cast<int>(SceneManager::CONTROLLER::KEYBOARD)] = 
		rsM.Load(ResourceManager::SRC::KBD_PZL_STR_IMG).handleId_;

	manualImg_[static_cast<int>(SceneManager::CONTROLLER::PAD)] =
		rsM.Load(ResourceManager::SRC::PAD_PZL_STR_IMG).handleId_;
}

void StageManager::LoadCsv(void)
{
	auto& rsM = ResourceManager::GetInstance();

	//�p�Y��
	stageCsv_[static_cast<int>(STAGENUM::FIRST)] = 
		rsM.Load(ResourceManager::SRC::FIRST_PAZZLE_CSV).dmcHandleIds_;
	stageCsv_[static_cast<int>(STAGENUM::SECOND)] =
		rsM.Load(ResourceManager::SRC::SECOND_PAZZLE_CSV).dmcHandleIds_;
	stageCsv_[static_cast<int>(STAGENUM::THIRD)] =
		rsM.Load(ResourceManager::SRC::THIRD_PAZZLE_CSV).dmcHandleIds_;

	//�����imap&obj)
	mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::BATH)] =
		rsM.Load(ResourceManager::SRC::BATH_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)] =
		rsM.Load(ResourceManager::SRC::ENTRANCE_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)] =
		rsM.Load(ResourceManager::SRC::KITCHEN_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)] =
		rsM.Load(ResourceManager::SRC::LIVING_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::OWN)] =
		rsM.Load(ResourceManager::SRC::OWN_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)] =
		rsM.Load(ResourceManager::SRC::STRAGE_OBJ_CSV).dmcHandleIds_;

	mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_MAP_CSV).dmcHandleIds_;
	objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)] =
		rsM.Load(ResourceManager::SRC::WASITU_OBJ_CSV).dmcHandleIds_;

	//�����蔻��
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::OBSTACLE)]=
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::BATH)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::BATH_MAPCHIP_EVENT_CSV).dmcHandleIds_;

	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::OBSTACLE)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::EXTERIA)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::EXTERIA_MAPCHIP_EVENT_CSV).dmcHandleIds_;

	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::OBSTACLE)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_OBSTACLE_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::THROUGH)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_THROUGH_CSV).dmcHandleIds_;
	mapchipObj_[static_cast<int>(MAPCHIP::INTERIA)][static_cast<int>(OBJECT::EVENT)] =
		rsM.Load(ResourceManager::SRC::INTERIA_MAPCHIP_EVENT_CSV).dmcHandleIds_;
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