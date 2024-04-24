#include <DxLib.h>
#include "../Application.h"
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

//	// �^�C�g�����S
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG, 
//		Application::PATH_IMAGE + "Title1.png"
//	);
//	resourcesMap_.emplace(SRC::TITLE_IMG, move(res));
//
//	//res = make_unique<Resource>(
//	//	Resource::TYPE::IMGS,
//	//	Application::PATH_IMAGE + "CrowV2_Fly_01.png"
//	//	,2788 / 694,2400 / 800, 2788 / 4, 2400 / 3
//	//	);
//
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "eagle_2.png"
//		);
//	resourcesMap_.emplace(SRC::BIRD_IMG, move(res));
//
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "fish.png"
//		);
//	resourcesMap_.emplace(SRC::FISH_IMG, move(res));
//
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "Crab/Idle/crab.png"
//		);
//	resourcesMap_.emplace(SRC::CRAB_IMG, move(res));
//
//	// �J�G���̈ړ��摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "FrogMove.png"
//		,8,1,64,64
//	);
//	resourcesMap_.emplace(SRC::FROG_MOVE_IMG, move(res));
//
//	// �J�G���̈ړ��摜2
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "FrogMove2.png"
//		, 8, 1, 64, 64
//	);
//	resourcesMap_.emplace(SRC::FROG_MOVE_IMG2, move(res));
//
//	// �J�G���̃W�����v�摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogJump.png"
//		);
//	resourcesMap_.emplace(SRC::FROG_JUMP_IMG, move(res));
//
//	// �J�G���̃W�����v�摜2
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogJump2.png"
//	);
//	resourcesMap_.emplace(SRC::FROG_JUMP_IMG2, move(res));
//
//	// �J�G���̍U���摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogAttack.png"
//		);
//	resourcesMap_.emplace(SRC::FROG_ATTACK_IMG, move(res));
//
//	// �J�G���̍U���\�����摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogAttackHelp.png"
//	);
//	resourcesMap_.emplace(SRC::FROG_ATTACK_HELP_IMG, move(res));
//
//	// �}�b�v�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "map.png", 7, 1, 32, 32
//	);
//	resourcesMap_.emplace(SRC::STAGE_IMG, move(res));
//
//	//���A�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "bubble.png"
//	);
//	resourcesMap_.emplace(SRC::BUBBLE_IMG, move(res));
//
//	//��̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "rock.png"
//	);
// 	resourcesMap_.emplace(SRC::ROCK_IMG, move(res));
//
//	//�C���̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "seaweed.png"
//	);
//	resourcesMap_.emplace(SRC::SEAWEED_IMG, move(res));
//
//	//���̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "egg.png"
//	);
//	resourcesMap_.emplace(SRC::EGG_IMG, move(res));
//
//	// �������ׂĔj�󂳂�Ă��܂����I�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "eggBreakText.png"
//	);
//	resourcesMap_.emplace(SRC::EGG_BREAK_TEXT_IMG, move(res));
//
//	// �v���C���[�������Ƃ��C�₵�Ă��܂����I�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "playerDeathText.png"
//	);
//	resourcesMap_.emplace(SRC::PLAYER_DEATH_TEXT_IMG, move(res));
//
//	// �a������Ȃ��Ȃ��Ă��܂����I�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "baitText.png"
//	);
//	resourcesMap_.emplace(SRC::BAIT_TEXT_IMG, move(res));
//
//	// �Q�[���I�[�o�[�̔w�i�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "gameOverBack.png"
//	);
//	resourcesMap_.emplace(SRC::GAMEOVER_BACK_IMG, move(res));
//
//	// ���U���g�̔w�i�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "resultBack.png"
//	);
//	resourcesMap_.emplace(SRC::RESULT_BACK_IMG, move(res));
//
//	// �R���e�B�j���[�H�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "continue.png"
//	);
//	resourcesMap_.emplace(SRC::CONTINUE_IMG, move(res));
//
//	// ����ڂɖ߂�H�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "returnToDayOne.png"
//	);
//	resourcesMap_.emplace(SRC::RETURN_ONEDAY_IMG, move(res));
//
//	// �^�C�g���ɖ߂�H�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "returnToTitle.png"
//	);
//	resourcesMap_.emplace(SRC::RETURN_TITLE_IMG, move(res));
//
//	// �e�L�X�g�{�b�N�X�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "textBox.png"
//	);
//	resourcesMap_.emplace(SRC::TEXT_BOX_IMG, move(res));
//
//	// �e�L�X�g�{�b�N�X2�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "textBox2.png"
//	);
//	resourcesMap_.emplace(SRC::TEXT_BOX2_IMG, move(res));
//
//	// �o�ߓ����̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "elapsedDays.png"
//	);
//	resourcesMap_.emplace(SRC::ELAPSED_DAYS_IMG, move(res));
//
//	// ���̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "arrow.png"
//	);
//	resourcesMap_.emplace(SRC::ARROW_IMG, move(res));
//
//	// �L�[�{�[�h�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "keyBoad.png"
//	);
//	resourcesMap_.emplace(SRC::KEYBOAD_IMG, move(res));
//
//	// �Q�[���p�b�h�̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "gamePad.png"
//	);
//	resourcesMap_.emplace(SRC::GAMEPAD_IMG, move(res));
//
//	// �Q�[�������̉摜
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "operation.PNG"
//	);
//	resourcesMap_.emplace(SRC::OPERATION_IMG, move(res));
//
//	//���ʉ�
//	// ���艹
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "push_enter.mp3"
//	);
//	resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));
//
//	// �J�[�\���ړ���
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "move_cursor.mp3"
//	);
//	resourcesMap_.emplace(SRC::MOVE_CURSOR_SND, move(res));
//
//	// �V�[���؂�ւ�
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "change_scene.mp3"
//	);
//	resourcesMap_.emplace(SRC::CHANGE_SCENE_SND, move(res));
//
//	// �W�����v��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "jump.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_JUMP_SND, move(res));
//
//	// ����
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "cry.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_CRY_SND, move(res));
//
//	// ��_���i������j
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "damage_player.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_DAMAGE_SND, move(res));
//
//	// �a�l���i������j
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "get_bait.mp3"
//	);
//	resourcesMap_.emplace(SRC::GET_BAIT_SND, move(res));
//
//	// �a�l���i�G�j
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "deprived_bait.mp3"
//	);
//	resourcesMap_.emplace(SRC::DEPRIVED_BAIT_SND, move(res));
//
//	// ��_���i�G�j
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "damage_enemy.mp3"
//	);
//	resourcesMap_.emplace(SRC::ENEMY_DAMAGE_SND, move(res));
//
//	// ��j��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "break_rock.mp3"
//	);
//	resourcesMap_.emplace(SRC::BREAK_ROCK_SND, move(res));
//
//	//BGM
//	//�^�C�g��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Title_2.mp3"
//	);
//	resourcesMap_.emplace(SRC::TITLE_BGM, move(res));
//
//	//�T��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Search_3.mp3"
//	);
//	resourcesMap_.emplace(SRC::SEARCH_BGM, move(res));
//
//	//�T���ŏI��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Search.mp3"
//	);
//	resourcesMap_.emplace(SRC::SEARCH_FINAL_BGM, move(res));
//
//	//���s��
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Failed_2.mp3"
//	);
//	resourcesMap_.emplace(SRC::FAILED_BGM, move(res));
//
//	//������
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Success_3.mp3"
//	);
//	resourcesMap_.emplace(SRC::SUCCESS_BGM, move(res));
//
//	// �q�b�g�G�t�F�N�g
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "HitEffect.png"
//		,8,1,64,64
//	);
//	resourcesMap_.emplace(SRC::HIT_EFFECT, move(res));
//
//	// �W�����v���G�t�F�N�g
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "JumpSmoke.png"
//		, 8, 1, 130, 32
//	);
//	resourcesMap_.emplace(SRC::JUMP_SMOKE_EFFECT, move(res));
//
//	// �_�b�V�����G�t�F�N�g
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "DashSmoke.png"
//		, 8, 1, 41, 32
//	);
//	resourcesMap_.emplace(SRC::DASH_SMOKE_EFFECT, move(res));
//
//	// �_���[�W�G�t�F�N�g
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "DamageEffect.png", 5, 1, 32, 32
//	);
//	resourcesMap_.emplace(SRC::DAMAGE_EFFECT, move(res));
//
//	// ���j��G�t�F�N�g
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "EggBreak.png"
//		, 8, 1, 64, 64
//	);
//	resourcesMap_.emplace(SRC::EGG_BREAK_EFFECT, move(res));
//
//#pragma region �V�F�[�_�[�p
//
//	//128x128
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "NoiseTex/Noise128.png"
//		);
//	resourcesMap_.emplace(SRC::NOISETEX_128, move(res));
//
//	//512x512
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "NoiseTex/Noise512.png"
//		);
//	resourcesMap_.emplace(SRC::NOISETEX_512, move(res));
//
//#pragma endregion


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
