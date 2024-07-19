#include<DxLib.h>
#include"ResourceManager.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

SoundManager::SoundManager(void)
{
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
