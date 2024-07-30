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

	//システム
	// フレーム　１×１
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame.png"
		);
	resourcesMap_.emplace(SRC::FRAME_IMG, move(res));
	// フレーム　１×２
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame_oblong.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_IMG, move(res));
	// フレーム　２×１
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "frame_oblong_2.png"
		);
	resourcesMap_.emplace(SRC::FRAME_OBLONG_2_IMG, move(res));

	// 視覚
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
	//選択
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "plate_Select.png"
		);
	resourcesMap_.emplace(SRC::PLATE_SELECT_IMG, move(res));
	//操作方法変更部分
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "plate_Check.png"
		);
	resourcesMap_.emplace(SRC::PLATE_CHECK_IMG, move(res));

	//HP表示の下地
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpBase.png"
		);
	resourcesMap_.emplace(SRC::HP_BASE_IMG, move(res));

	//HPを表す円
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpCircle.png"
		);
	resourcesMap_.emplace(SRC::HP_CIRCLE_IMG, move(res));

	//HPのテキスト
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "HpText.png"
		);
	resourcesMap_.emplace(SRC::HP_TEXT_IMG, move(res));

	//セレクトステージ１
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Stage1.png"
		);
	resourcesMap_.emplace(SRC::STAGE_1_IMG, move(res));

	//セレクトステージ２
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Stage2.png"
		);
	resourcesMap_.emplace(SRC::STAGE_2_IMG, move(res));

	//セレクトステージ３
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Stage3.png"
		);
	resourcesMap_.emplace(SRC::STAGE_3_IMG, move(res));

	//タイトルに戻る
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "BackTitle.png"
		);
	resourcesMap_.emplace(SRC::BACK_TITLE_IMG, move(res));

	//チェック
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Check.png"
		);
	resourcesMap_.emplace(SRC::CHECK_IMG, move(res));

	//タイトル
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "Title.png"
		);
	resourcesMap_.emplace(SRC::TITLE_IMG, move(res));

	//Thanks
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "thanks.png"
		);
	resourcesMap_.emplace(SRC::THANK_IMG, move(res));

	//スタート
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "start.png"
		);
	resourcesMap_.emplace(SRC::START_IMG, move(res));

	//セレクトへ戻る
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "BackSelect.png"
		);
	resourcesMap_.emplace(SRC::BACK_SELECT_IMG, move(res));

	//成功
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "clear.png"
		);
	resourcesMap_.emplace(SRC::CLEAER_IMG, move(res));

	//失敗
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_SYSTEM + "failde.png"
		);
	resourcesMap_.emplace(SRC::FAILD_IMG, move(res));

	//操作説明
	//パズル１
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Pazzle_1.png"
		);
	resourcesMap_.emplace(SRC::PZL_MNL_1_IMG, move(res));

	//パズル②
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Pazzle_2.png"
		);
	resourcesMap_.emplace(SRC::PZL_MNL_2_IMG, move(res));

	//ステルス①
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Stealth_1.png"
		);
	resourcesMap_.emplace(SRC::STL_MNL_1_IMG, move(res));

	//ステルス②
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Stealth_2.png"
		);
	resourcesMap_.emplace(SRC::STL_MNL_2_IMG, move(res));

	//キーボードパズル
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Keybord_Pazzle.png"
		);
	resourcesMap_.emplace(SRC::KBD_PZL_IMG, move(res));

	//キーボードステルス
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Keybord_Stealth.png"
		);
	resourcesMap_.emplace(SRC::KBD_STL_IMG, move(res));

	//キーボードパズル時文章
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Keybord_Pazzle_String.png"
		);
	resourcesMap_.emplace(SRC::KBD_PZL_STR_IMG, move(res));

	//パッドパズル
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Pad_Pazzle.png"
		);
	resourcesMap_.emplace(SRC::PAD_PZL_IMG, move(res));

	//パッドステルス
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Pad_Stealth.png"
		);
	resourcesMap_.emplace(SRC::PAD_STL_IMG, move(res));

	//パッドパズル時文章
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_MANUAL + "Pad_Pazzle_String.png"
		);
	resourcesMap_.emplace(SRC::PAD_PZL_STR_IMG, move(res));


	//部屋（パズル）
	//風呂
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Bath.png"
		);
	resourcesMap_.emplace(SRC::BATH_IMG, move(res));
	//玄関
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Entrance.png"
		);
	resourcesMap_.emplace(SRC::ENTRANCE_IMG, move(res));
	//ゴール
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Goal.png"
		);
	resourcesMap_.emplace(SRC::GOAL_IMG, move(res));
	//台所
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Kitchen.png"
		);
	resourcesMap_.emplace(SRC::KITCHEN_IMG, move(res));
	//居間
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Living.png"
		);
	resourcesMap_.emplace(SRC::LIVING_IMG, move(res));
	//なし
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "None.png"
		);
	resourcesMap_.emplace(SRC::NONE_IMG, move(res));
	//自室
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Own.png"
		);
	resourcesMap_.emplace(SRC::OWN_IMG, move(res));
	//物置
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Strage.png"
		);
	resourcesMap_.emplace(SRC::STRAGE_IMG, move(res));
	//壁
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Wall.png"
		);
	resourcesMap_.emplace(SRC::WALL_IMG, move(res));
	//和室
	res = make_unique<Resource>(
		Resource::TYPE::IMG,
		Application::PATH_ROOM + "Wasitu.png"
		);
	resourcesMap_.emplace(SRC::WASITU_IMG, move(res));
#pragma endregion


#pragma region IMGS
	//キャラクター
	//プレイヤー

	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_CHARACTER + "Player_1.png",
		CHARACTER_ORIGIN_SIZE_X / CharacterBase::CHARACTER_SIZE_X,
		CHARACTER_ORIGIN_SIZE_Y_2 / CharacterBase::CHARACTER_SIZE_Y,
		CharacterBase::CHARACTER_SIZE_X,
		CharacterBase::CHARACTER_SIZE_Y
		);
	resourcesMap_.emplace(SRC::PLAYER_IMGS, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_CHARACTER + "Hayate.png",
		CHARACTER_ORIGIN_SIZE_X / CharacterBase::CHARACTER_SIZE_X,
		CHARACTER_ORIGIN_SIZE_Y_2 / CharacterBase::CHARACTER_SIZE_Y,
		CharacterBase::CHARACTER_SIZE_X,
		CharacterBase::CHARACTER_SIZE_Y
		);


	resourcesMap_.emplace(SRC::SENESCHAI_IMGS, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_CHARACTER + "Oldman.png",
		CHARACTER_ORIGIN_SIZE_X / CharacterBase::CHARACTER_SIZE_X,
		CHARACTER_ORIGIN_SIZE_Y_2 / CharacterBase::CHARACTER_SIZE_Y,
		CharacterBase::CHARACTER_SIZE_X,
		CharacterBase::CHARACTER_SIZE_Y
		);


	resourcesMap_.emplace(SRC::OLDMAN_IMGS, move(res));

	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_CHARACTER + "maid.png",
		CHARACTER_ORIGIN_SIZE_X / CharacterBase::CHARACTER_SIZE_X,
		CHARACTER_ORIGIN_SIZE_Y_2 / CharacterBase::CHARACTER_SIZE_Y,
		CharacterBase::CHARACTER_SIZE_X,
		CharacterBase::CHARACTER_SIZE_Y
		);


	resourcesMap_.emplace(SRC::MAID_IMGS, move(res));


	//風呂マップチップ
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_MAPCHIP + "Bath.png",
		BATH_MAPTHIP_X / StageManager::UNIT_STEALTH_SIZE_X,
		BATH_MAPTHIP_Y / StageManager::UNIT_STEALTH_SIZE_Y,
		StageManager::UNIT_STEALTH_SIZE_X,
		StageManager::UNIT_STEALTH_SIZE_Y
		);
	resourcesMap_.emplace(SRC::BATH_MAPTHIP, move(res));

	//外装マップチップ
	res = make_unique<Resource>(
		Resource::TYPE::IMGS,
		Application::PATH_MAPCHIP + "Exteria.png",
		EXTERIA_MAPTHIP_X / StageManager::UNIT_STEALTH_SIZE_X,
		EXTERIA_MAPTHIP_Y / StageManager::UNIT_STEALTH_SIZE_Y,
		StageManager::UNIT_STEALTH_SIZE_X,
		StageManager::UNIT_STEALTH_SIZE_Y
		);
	resourcesMap_.emplace(SRC::EXTERIA_MAPTHIP, move(res));

	//内装マップチップ
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

	//パズル
	//ステージ①
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_PAZZLE + "Stage_First.csv"
		);
	resourcesMap_.emplace(SRC::FIRST_PAZZLE_CSV, move(res));

	//ステージ②
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_PAZZLE + "Stage_Third.csv"
		);
	resourcesMap_.emplace(SRC::SECOND_PAZZLE_CSV, move(res));

	//ステージ➂
	res = make_unique<Resource>(
		Resource::TYPE::CSV,
		Application::PATH_PAZZLE + "Stage_Second.csv"
		);
	resourcesMap_.emplace(SRC::THIRD_PAZZLE_CSV, move(res));


	//マップ
	//風呂
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

	//玄関
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

	//台所
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

	//居間
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

	//自室
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

	//物置
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

	//和室
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

	//障害物判定用のやつ
	//風呂
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

	//内装
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

	//外装
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

	////効果音
	// 決定音
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_SOUND + "enter.mp3"
	);
	resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));

	// キャンセル音
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_SOUND + "cansel.mp3"
		);
	resourcesMap_.emplace(SRC::PUSH_CANSEL_SND, move(res));

	// カーソル移動音
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_SOUND + "move.mp3"
		);
	resourcesMap_.emplace(SRC::MOVE_COSOR_SND, move(res));

	// カーソル移動音
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_SOUND + "reset.mp3"
		);
	resourcesMap_.emplace(SRC::RESET_SND, move(res));

	// 駒選択音
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_SOUND + "pazzleSelect.mp3"
		);
	resourcesMap_.emplace(SRC::PAZZLE_SELECT_SND, move(res));


	////BGM
	//タイトル
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "Title.mp3"
	);
	resourcesMap_.emplace(SRC::TITLE_BGM, move(res));

	//セレクト
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "Select.mp3"
		);
	resourcesMap_.emplace(SRC::SELECT_BGM, move(res));

	//パズル
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "Pazzle.mp3"
		);
	resourcesMap_.emplace(SRC::PAZZLE_BGM, move(res));

	//ステルス
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "Stealth.mp3"
		);
	resourcesMap_.emplace(SRC::STEALTH_BGM, move(res));

	//成功時
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "success.mp3"
		);
	resourcesMap_.emplace(SRC::SUCCESS_BGM, move(res));

	//失敗時
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "failed.mp3"
		);
	resourcesMap_.emplace(SRC::FAILED_BGM, move(res));

	//エンディング
	res = make_unique<Resource>(
		Resource::TYPE::SOUND,
		Application::PATH_BGM + "ending.mp3"
		);
	resourcesMap_.emplace(SRC::ENDING_BGM, move(res));
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
