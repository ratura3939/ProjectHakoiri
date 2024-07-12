#include <DxLib.h>
#include "../Application.h"
#include"StageManager.h"
#include"../Object/CharacterBase.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

using namespace std;
void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	unique_ptr<Resource> res;

#pragma region IMG

	//�V�X�e��
	// �t���[���@�P�~�P
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame.png"
		);
	resourcesMap_.emplace(SRC::FRAME_IMG, move(res));
	// �t���[���@�P�~�Q
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame_oblong.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_IMG, move(res));
	// �t���[���@�Q�~�P
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame_oblong_2.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_2_IMG, move(res));

	// ���o
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "vision.png"
		);
	resourcesMap_.emplace(SRC::VISION_FIND_IMG, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "vision_2.png"
		);
	resourcesMap_.emplace(SRC::VISION_MISSING_IMG, move(res));

	//OK
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Select_Ok.png"
		);
	resourcesMap_.emplace(SRC::SELECT_OK_IMG, move(res));
	//NO
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Select_No.png"
		);
	resourcesMap_.emplace(SRC::SELECT_NO_IMG, move(res));
	//�I��
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "plate_Select.png"
		);
	resourcesMap_.emplace(SRC::PLATE_SELECT_IMG, move(res));
	//������@�ύX����
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "plate_Check.png"
		);
	resourcesMap_.emplace(SRC::PLATE_CHECK_IMG, move(res));

	//HP�\���̉��n
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpBase.png"
		);
	resourcesMap_.emplace(SRC::HP_BASE_IMG, move(res));

	//HP��\���~
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpCircle.png"
		);
	resourcesMap_.emplace(SRC::HP_CIRCLE_IMG, move(res));

	//HP�̃e�L�X�g
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpText.png"
		);
	resourcesMap_.emplace(SRC::HP_TEXT_IMG, move(res));

	//�����i�p�Y���j
	//���C
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Bath.png"
		);
	resourcesMap_.emplace(SRC::BATH_IMG, move(res));
	//����
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Entrance.png"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_IMG, move(res));
	//�S�[��
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Goal.png"
		);
	resourcesMap_.emplace(SRC::GOAL_IMG, move(res));
	//�䏊
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Kitchen.png"
		);
	resourcesMap_.emplace(SRC::KITCHEN_IMG, move(res));
	//����
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Living.png"
		);
	resourcesMap_.emplace(SRC::LIVING_IMG, move(res));
	//�Ȃ�
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "None.png"
		);
	resourcesMap_.emplace(SRC::NONE_IMG, move(res));
	//����
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Own.png"
		);
	resourcesMap_.emplace(SRC::OWN_IMG, move(res));
	//���u
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Strage.png"
		);
	resourcesMap_.emplace(SRC::STRAGE_IMG, move(res));
	//��
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Wall.png"
		);
	resourcesMap_.emplace(SRC::WALL_IMG, move(res));
	//�a��
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Wasitu.png"
		);
	resourcesMap_.emplace(SRC::WASITU_IMG, move(res));
#pragma endregion


#pragma region IMGS
	//�L�����N�^�[
	//�v���C���[
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_CHARACTER + "player.png",
		CHARACTER_ORIGIN_SIZE_X / CharacterBase::CHARACTER_SIZE_X,
		CHARACTER_ORIGIN_SIZE_Y / CharacterBase::CHARACTER_SIZE_Y,
		CharacterBase::CHARACTER_SIZE_X,
		CharacterBase::CHARACTER_SIZE_Y
		);
	resourcesMap_.emplace(SRC::PLAYER_IMGS, move(res));


	//���C�}�b�v�`�b�v
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_MAPCHIP + "Bath.png",
		BATH_MAPTHIP_X / StageManager::UNIT_STEALTH_SIZE_X,
		BATH_MAPTHIP_Y / StageManager::UNIT_STEALTH_SIZE_Y,
		StageManager::UNIT_STEALTH_SIZE_X,
		StageManager::UNIT_STEALTH_SIZE_Y
		);
	resourcesMap_.emplace(SRC::BATH_MAPTHIP, move(res));

	//�O���}�b�v�`�b�v
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_MAPCHIP + "Exteria.png",
		EXTERIA_MAPTHIP_X / StageManager::UNIT_STEALTH_SIZE_X,
		EXTERIA_MAPTHIP_Y / StageManager::UNIT_STEALTH_SIZE_Y,
		StageManager::UNIT_STEALTH_SIZE_X,
		StageManager::UNIT_STEALTH_SIZE_Y
		);
	resourcesMap_.emplace(SRC::EXTERIA_MAPTHIP, move(res));

	//�����}�b�v�`�b�v
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_MAPCHIP + "Interia.png",
		INTERIA_MAPTHIP_X / StageManager::UNIT_STEALTH_SIZE_X,
		INTERIA_MAPTHIP_Y / StageManager::UNIT_STEALTH_SIZE_Y,
		StageManager::UNIT_STEALTH_SIZE_X,
		StageManager::UNIT_STEALTH_SIZE_Y
		);
	resourcesMap_.emplace(SRC::INTERIA_MAPTHIP, move(res));
#pragma endregion


#pragma region CSV

	//�p�Y��
	//�X�e�[�W�@
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_PAZZLE + "Stage_First.csv"
		);
	resourcesMap_.emplace(SRC::FIRST_PAZZLE_CSV, move(res));


	//�}�b�v
	//���C
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Bath_Map.csv"
		);
	resourcesMap_.emplace(SRC::BATH_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Bath_Object.csv"
		);
	resourcesMap_.emplace(SRC::BATH_OBJ_CSV, move(res));

	//����
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Entrance_Map.csv"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Entrance_Object.csv"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_OBJ_CSV, move(res));

	//�䏊
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Kitchen_Map.csv"
		);
	resourcesMap_.emplace(SRC::KITCHEN_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Kitchen_Object.csv"
		);
	resourcesMap_.emplace(SRC::KITCHEN_OBJ_CSV, move(res));

	//����
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Living_Map.csv"
		);
	resourcesMap_.emplace(SRC::LIVING_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Living_Object.csv"
		);
	resourcesMap_.emplace(SRC::LIVING_OBJ_CSV, move(res));

	//����
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Own_Map.csv"
		);
	resourcesMap_.emplace(SRC::OWN_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Own_Object.csv"
		);
	resourcesMap_.emplace(SRC::OWN_OBJ_CSV, move(res));

	//���u
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Strage_Map.csv"
		);
	resourcesMap_.emplace(SRC::STRAGE_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Strage_Object.csv"
		);
	resourcesMap_.emplace(SRC::STRAGE_OBJ_CSV, move(res));

	//�a��
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Wasitu_Map.csv"
		);
	resourcesMap_.emplace(SRC::WASITU_MAP_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_MAP + "Wasitu_Object.csv"
		);
	resourcesMap_.emplace(SRC::WASITU_OBJ_CSV, move(res));

	//��Q������p�̂��
	//���C
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Bath/Obstacle.csv"
		);
	resourcesMap_.emplace(SRC::BATH_MAPCHIP_OBSTACLE_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Bath/Through.csv"
		);
	resourcesMap_.emplace(SRC::BATH_MAPCHIP_THROUGH_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Bath/Event.csv"
		);
	resourcesMap_.emplace(SRC::BATH_MAPCHIP_EVENT_CSV, move(res));

	//����
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Interia/Obstacle.csv"
		);
	resourcesMap_.emplace(SRC::INTERIA_MAPCHIP_OBSTACLE_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Interia/Through.csv"
		);
	resourcesMap_.emplace(SRC::INTERIA_MAPCHIP_THROUGH_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Interia/Event.csv"
		);
	resourcesMap_.emplace(SRC::INTERIA_MAPCHIP_EVENT_CSV, move(res));

	//�O��
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Exteria/Obstacle.csv"
		);
	resourcesMap_.emplace(SRC::EXTERIA_MAPCHIP_OBSTACLE_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Exteria/Through.csv"
		);
	resourcesMap_.emplace(SRC::EXTERIA_MAPCHIP_THROUGH_CSV, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_OBSTACLE + "Exteria/Event.csv"
		);
	resourcesMap_.emplace(SRC::EXTERIA_MAPCHIP_EVENT_CSV, move(res));
#pragma endregion

#pragma region SOUND

	////���ʉ�
	//// ���艹
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_SOUND + "push_enter.mp3"
	//);
	//resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));



	////BGM
	////�^�C�g��
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_BGM + "Title_2.mp3"
	//);
	//resourcesMap_.emplace(SRC::TITLE_BGM, move(res));
#pragma endregion
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
		//delete p.second;
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.resType_ == Resource::TYPE::NONE)
	{
		//���o�^
		return unregistered;
	}
	//Resource ret = *res;
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.resType_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// �o�^����Ă��Ȃ�
		return unregistered;
	}

	rPair->second->Load();


	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
