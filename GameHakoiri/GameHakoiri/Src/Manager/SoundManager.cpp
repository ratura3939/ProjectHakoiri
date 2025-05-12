#include<DxLib.h>
#include"ResourceManager.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

SoundManager::SoundManager(void)
{
	titleBgm_ = -1;
	selectBgm_ = -1;
	pazzleBgm_ = -1;
	stealthBgm_ = -1;
	successBgm_ = -1;
	failedBgm_ = -1;
	endingBgm_ = -1;

	enterSnd_ = -1;
	canselSnd_ = -1;
	moveSnd_ = -1;
	resetSnd_ = -1;
	selectSnd_ = -1;
}

void SoundManager::Destroy(void)
{
	DeleteSoundMem(titleBgm_);
	DeleteSoundMem(selectBgm_);
	DeleteSoundMem(pazzleBgm_);
	DeleteSoundMem(stealthBgm_);
	delete instance_;
}

bool SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager;
	}
	instance_->Init();
	//ê≥ÇµÇ≠èàóùÇ™èIóπÇµÇΩÇÃÇ≈
	return true;
}

SoundManager& SoundManager::GetInstance(void)
{
	return *instance_;
}

void SoundManager::Init(void)
{
	auto& rsM = ResourceManager::GetInstance();

	titleBgm_ = rsM.Load(ResourceManager::SRC::TITLE_BGM).handleId_;
	selectBgm_ = rsM.Load(ResourceManager::SRC::SELECT_BGM).handleId_;
	pazzleBgm_ = rsM.Load(ResourceManager::SRC::PAZZLE_BGM).handleId_;
	stealthBgm_ = rsM.Load(ResourceManager::SRC::STEALTH_BGM).handleId_;
	successBgm_ = rsM.Load(ResourceManager::SRC::SUCCESS_BGM).handleId_;
	failedBgm_ = rsM.Load(ResourceManager::SRC::FAILED_BGM).handleId_;
	endingBgm_ = rsM.Load(ResourceManager::SRC::ENDING_BGM).handleId_;

	enterSnd_ = rsM.Load(ResourceManager::SRC::PUSH_ENTER_SND).handleId_;
	canselSnd_ = rsM.Load(ResourceManager::SRC::PUSH_CANSEL_SND).handleId_;
	moveSnd_ = rsM.Load(ResourceManager::SRC::MOVE_COSOR_SND).handleId_;
	resetSnd_ = rsM.Load(ResourceManager::SRC::RESET_SND).handleId_;
	selectSnd_ = rsM.Load(ResourceManager::SRC::PAZZLE_SELECT_SND).handleId_;
}

void SoundManager::Relese(void)
{
	DeleteSoundMem(titleBgm_);
	DeleteSoundMem(pazzleBgm_);
	DeleteSoundMem(stealthBgm_);
	DeleteSoundMem(selectBgm_);
	DeleteSoundMem(successBgm_);
	DeleteSoundMem(failedBgm_);
	DeleteSoundMem(endingBgm_);

	DeleteSoundMem(enterSnd_);
	DeleteSoundMem(canselSnd_);
	DeleteSoundMem(moveSnd_);
	DeleteSoundMem(resetSnd_);
	DeleteSoundMem(selectSnd_);
}

void SoundManager::PlayBgmOfTitle(void)
{
	PlaySoundMem(titleBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfTitle(void)
{
	StopSoundMem(titleBgm_);
}

void SoundManager::PlayBgmOfSelect(void)
{
	PlaySoundMem(selectBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfSelect(void)
{
	StopSoundMem(selectBgm_);
}

void SoundManager::PlayBgmOfPazzle(void)
{
	PlaySoundMem(pazzleBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfPazzle(void)
{
	StopSoundMem(pazzleBgm_);
}

void SoundManager::PlayBgmOfStealth(void)
{
	PlaySoundMem(stealthBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfStealth(void)
{
	StopSoundMem(stealthBgm_);
}

void SoundManager::PlayBgmOfSuccess(void)
{
	PlaySoundMem(successBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfSuccess(void)
{
	StopSoundMem(successBgm_);
}

void SoundManager::PlayBgmOfFailed(void)
{
	PlaySoundMem(failedBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfFailed(void)
{
	StopSoundMem(failedBgm_);
}

void SoundManager::PlayBgmOfEnding(void)
{
	PlaySoundMem(endingBgm_, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBgmOfEnding(void)
{
	StopSoundMem(endingBgm_);
}

void SoundManager::PlaySndEnter(bool flag)
{
	if (flag)PlaySoundMem(enterSnd_, DX_PLAYTYPE_BACK);
	else PlaySoundMem(canselSnd_, DX_PLAYTYPE_BACK);
}


void SoundManager::PlaySndMove(void)
{
	PlaySoundMem(moveSnd_, DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySndReset(void)
{
	PlaySoundMem(resetSnd_, DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySndSelect(void)
{
	PlaySoundMem(selectSnd_, DX_PLAYTYPE_BACK);
}
