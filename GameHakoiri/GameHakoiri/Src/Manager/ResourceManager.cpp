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

	// ƒtƒŒ[ƒ€@‚P~‚P
	res = make_unique<Resource>(
		Resource::TYPE::IMG, 
		Application::PATH_IMAGE + "System/frame.png"
	);
	resourcesMap_.emplace(SRC::FRAME_IMG, move(res));

	// ƒtƒŒ[ƒ€@‚P~‚Q
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_IMG, move(res));

	// ƒtƒŒ[ƒ€@‚Q~‚P
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong_2.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_2_IMG, move(res));

	

	////Œø‰Ê‰¹
	//// Œˆ’è‰¹
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_SOUND + "push_enter.mp3"
	//);
	//resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));

	

	////BGM
	////ƒ^ƒCƒgƒ‹
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_BGM + "Title_2.mp3"
	//);
	//resourcesMap_.emplace(SRC::TITLE_BGM, move(res));

	

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
		//–¢“o˜^
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
		// “o˜^‚³‚ê‚Ä‚¢‚È‚¢
		return unregistered;
	}

	rPair->second->Load();


	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
