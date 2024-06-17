#pragma once

#include <memory>
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	//�g�p���镡�����̉摜�i�A�j���[�V�����j�Ȃǂ̒萔�o�^
	//static constexpr int MAP_TILE_SIZE_UNIT = 30;

	static constexpr int CHARACTER_ORIGIN_SIZE_X = 96;
	static constexpr int CHARACTER_ORIGIN_SIZE_Y = 128;

	static constexpr int BATH_MAPTHIP_X = 512;
	static constexpr int BATH_MAPTHIP_Y = 1216;
	static constexpr int EXTERIA_MAPTHIP_X = 256;
	static constexpr int EXTERIA_MAPTHIP_Y = 3552;
	static constexpr int INTERIA_MAPTHIP_X = 256;
	static constexpr int INTERIA_MAPTHIP_Y = 2464;

	// ���\�[�X��
	enum class SRC
	{
		//�摜
		//�V�X�e��
		FRAME_IMG,
		FRAME_OBLONG_IMG,
		FRAME_OBLONG_2_IMG,
		VISION_IMG,
	
		//����
		BATH_IMG,
		ENTRANCE_IMG,
		GOAL_IMG,
		KITCHEN_IMG,
		LIVING_IMG,
		NONE_IMG,
		OWN_IMG,
		STRAGE_IMG,
		WALL_IMG,
		WASITU_IMG,

		//�L�����N�^�[
		PLAYER_IMGS,

		//�}�b�v
		BATH_MAPTHIP,
		EXTERIA_MAPTHIP,
		INTERIA_MAPTHIP,

		//Csv
		//�p�Y��
		FIRST_PAZZLE_CSV,

		//�}�b�v
		BATH_MAP_CSV,
		BATH_OBJ_CSV,
		ENTRANCE_MAP_CSV,
		ENTRANCE_OBJ_CSV,
		KITCHEN_MAP_CSV,
		KITCHEN_OBJ_CSV,
		LIVING_MAP_CSV,
		LIVING_OBJ_CSV,
		OWN_MAP_CSV,
		OWN_OBJ_CSV,
		STRAGE_MAP_CSV,
		STRAGE_OBJ_CSV,
		WASITU_MAP_CSV,
		WASITU_OBJ_CSV,

		BATH_MAPCHIP_OBSTACLE_CSV,
		BATH_MAPCHIP_THROUGH_CSV,
		BATH_MAPCHIP_EVENT_CSV,
		INTERIA_MAPCHIP_OBSTACLE_CSV,
		INTERIA_MAPCHIP_THROUGH_CSV,
		INTERIA_MAPCHIP_EVENT_CSV,
		EXTERIA_MAPCHIP_OBSTACLE_CSV,
		EXTERIA_MAPCHIP_THROUGH_CSV,
		EXTERIA_MAPCHIP_EVENT_CSV,


		//���ʉ�
		PUSH_ENTER_SND,

		//BGM
		TITLE_BGM,

		//�G�t�F�N�g
		HIT_EFFECT,
		

	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	// ���\�[�X�̃��[�h
	const Resource& Load(SRC src);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* instance_;

	//���o�^
	Resource unregistered;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;
	//std::map<SRC, Resource> resourcesMap_;
	 
	
	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;
	//std::map<SRC, Resource*> loadedMap_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void) = default;

	// �������[�h
	Resource& _Load(SRC src);

};

