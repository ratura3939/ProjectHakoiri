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

	//ÉJÅ[É\Éã
	// ÉtÉåÅ[ÉÄÅ@ÇPÅ~ÇP
	res = make_unique<Resource>(
		Resource::TYPE::IMG, 
		Application::PATH_IMAGE + "System/frame.png"
	);
	resourcesMap_.emplace(SRC::FRAME_IMG, move(res));
	// ÉtÉåÅ[ÉÄÅ@ÇPÅ~ÇQ
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_IMG, move(res));
	// ÉtÉåÅ[ÉÄÅ@ÇQÅ~ÇP
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong_2.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_2_IMG, move(res));

	//ïîâÆÅiÉpÉYÉãÅj
	//ïóòC
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Bath.png"
		);
	resourcesMap_.emplace(SRC::BATH_IMG, move(res));
	//å∫ä÷
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Entrance.png"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_IMG, move(res));
	//ÉSÅ[Éã
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Goal.png"
		);
	resourcesMap_.emplace(SRC::GOAL_IMG, move(res));
	//ë‰èä
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Kitchen.png"
		);
	resourcesMap_.emplace(SRC::KITCHEN_IMG, move(res));
	//ãèä‘
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Living.png"
		);
	resourcesMap_.emplace(SRC::LIVING_IMG, move(res));
	//Ç»Çµ
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/None.png"
		);
	resourcesMap_.emplace(SRC::NONE_IMG, move(res));
	//é©é∫
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Own.png"
		);
	resourcesMap_.emplace(SRC::OWN_IMG, move(res));
	//ï®íu
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Strage.png"
		);
	resourcesMap_.emplace(SRC::STRAGE_IMG, move(res));
	//ï«
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Wall.png"
		);
	resourcesMap_.emplace(SRC::WALL_IMG, move(res));
	//òaé∫
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Wasitu.png"
		);
	resourcesMap_.emplace(SRC::WASITU_IMG, move(res));


	

	////å¯â âπ
	//// åàíËâπ
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_SOUND + "push_enter.mp3"
	//);
	//resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));

	

	////BGM
	////É^ÉCÉgÉã
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
		//ñ¢ìoò^
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
		// ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢
		return unregistered;
	}

	rPair->second->Load();


	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
