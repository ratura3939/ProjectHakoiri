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

	//カーソル
	// フレーム　１×１
	res = make_unique<Resource>(
		Resource::TYPE::IMG, 
		Application::PATH_IMAGE + "System/frame.png"
	);
	resourcesMap_.emplace(SRC::FRAME_IMG, move(res));
	// フレーム　１×２
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_IMG, move(res));
	// フレーム　２×１
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "System/frame_oblong_2.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_2_IMG, move(res));

	//部屋（パズル）
	//風呂
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Bath.png"
		);
	resourcesMap_.emplace(SRC::BATH_IMG, move(res));
	//玄関
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Entrance.png"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_IMG, move(res));
	//ゴール
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Goal.png"
		);
	resourcesMap_.emplace(SRC::GOAL_IMG, move(res));
	//台所
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Kitchen.png"
		);
	resourcesMap_.emplace(SRC::KITCHEN_IMG, move(res));
	//居間
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Living.png"
		);
	resourcesMap_.emplace(SRC::LIVING_IMG, move(res));
	//なし
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/None.png"
		);
	resourcesMap_.emplace(SRC::NONE_IMG, move(res));
	//自室
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Own.png"
		);
	resourcesMap_.emplace(SRC::OWN_IMG, move(res));
	//物置
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Strage.png"
		);
	resourcesMap_.emplace(SRC::STRAGE_IMG, move(res));
	//壁
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Wall.png"
		);
	resourcesMap_.emplace(SRC::WALL_IMG, move(res));
	//和室
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_IMAGE + "Room/Wasitu.png"
		);
	resourcesMap_.emplace(SRC::WASITU_IMG, move(res));

	//CSV
	//パズルステージ①
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_PAZZLE + "Stage_First.csv"
		);
	resourcesMap_.emplace(SRC::FIRST_PAZZLE_CSV, move(res));
	

	////効果音
	//// 決定音
	//res = make_unique<Resource>(
	//	Resource::TYPE::SOUND,
	//	Application::PATH_SOUND + "push_enter.mp3"
	//);
	//resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));

	

	////BGM
	////タイトル
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
		//未登録
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
		// 登録されていない
		return unregistered;
	}

	rPair->second->Load();


	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
