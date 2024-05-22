#pragma once

#include <memory>
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	//�g�p���镡�����̉摜�i�A�j���[�V�����j�Ȃǂ̒萔�o�^
	static constexpr int PAZZLE_IMG_UNIT_X = 64;
	static constexpr int PAZZLE_IMG_UNIT_Y = 64;
	static constexpr int MAP_IMG_UNIT_X = 32;
	static constexpr int MAP_IMG_UNIT_Y = 32;
	static constexpr int MAP_TILE_SIZE_UNIT = 30;

	// ���\�[�X��
	enum class SRC
	{
		//�摜
		//�J�[�\��
		FRAME_IMG,
		FRAME_OBLONG_IMG,
		FRAME_OBLONG_2_IMG,
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

