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

//	// タイトルロゴ
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
//	// カエルの移動画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "FrogMove.png"
//		,8,1,64,64
//	);
//	resourcesMap_.emplace(SRC::FROG_MOVE_IMG, move(res));
//
//	// カエルの移動画像2
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "FrogMove2.png"
//		, 8, 1, 64, 64
//	);
//	resourcesMap_.emplace(SRC::FROG_MOVE_IMG2, move(res));
//
//	// カエルのジャンプ画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogJump.png"
//		);
//	resourcesMap_.emplace(SRC::FROG_JUMP_IMG, move(res));
//
//	// カエルのジャンプ画像2
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogJump2.png"
//	);
//	resourcesMap_.emplace(SRC::FROG_JUMP_IMG2, move(res));
//
//	// カエルの攻撃画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogAttack.png"
//		);
//	resourcesMap_.emplace(SRC::FROG_ATTACK_IMG, move(res));
//
//	// カエルの攻撃予測線画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "FrogAttackHelp.png"
//	);
//	resourcesMap_.emplace(SRC::FROG_ATTACK_HELP_IMG, move(res));
//
//	// マップの画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_IMAGE + "map.png", 7, 1, 32, 32
//	);
//	resourcesMap_.emplace(SRC::STAGE_IMG, move(res));
//
//	//水泡の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "bubble.png"
//	);
//	resourcesMap_.emplace(SRC::BUBBLE_IMG, move(res));
//
//	//岩の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "rock.png"
//	);
// 	resourcesMap_.emplace(SRC::ROCK_IMG, move(res));
//
//	//海藻の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "seaweed.png"
//	);
//	resourcesMap_.emplace(SRC::SEAWEED_IMG, move(res));
//
//	//卵の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "egg.png"
//	);
//	resourcesMap_.emplace(SRC::EGG_IMG, move(res));
//
//	// 卵がすべて破壊されてしまった！の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "eggBreakText.png"
//	);
//	resourcesMap_.emplace(SRC::EGG_BREAK_TEXT_IMG, move(res));
//
//	// プレイヤーが両方とも気絶してしまった！の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "playerDeathText.png"
//	);
//	resourcesMap_.emplace(SRC::PLAYER_DEATH_TEXT_IMG, move(res));
//
//	// 餌が足りなくなってしまった！の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "baitText.png"
//	);
//	resourcesMap_.emplace(SRC::BAIT_TEXT_IMG, move(res));
//
//	// ゲームオーバーの背景の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "gameOverBack.png"
//	);
//	resourcesMap_.emplace(SRC::GAMEOVER_BACK_IMG, move(res));
//
//	// リザルトの背景の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "resultBack.png"
//	);
//	resourcesMap_.emplace(SRC::RESULT_BACK_IMG, move(res));
//
//	// コンティニュー？の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "continue.png"
//	);
//	resourcesMap_.emplace(SRC::CONTINUE_IMG, move(res));
//
//	// 一日目に戻る？の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "returnToDayOne.png"
//	);
//	resourcesMap_.emplace(SRC::RETURN_ONEDAY_IMG, move(res));
//
//	// タイトルに戻る？の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "returnToTitle.png"
//	);
//	resourcesMap_.emplace(SRC::RETURN_TITLE_IMG, move(res));
//
//	// テキストボックスの画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "textBox.png"
//	);
//	resourcesMap_.emplace(SRC::TEXT_BOX_IMG, move(res));
//
//	// テキストボックス2の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "textBox2.png"
//	);
//	resourcesMap_.emplace(SRC::TEXT_BOX2_IMG, move(res));
//
//	// 経過日数の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "elapsedDays.png"
//	);
//	resourcesMap_.emplace(SRC::ELAPSED_DAYS_IMG, move(res));
//
//	// 矢印の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "arrow.png"
//	);
//	resourcesMap_.emplace(SRC::ARROW_IMG, move(res));
//
//	// キーボードの画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "keyBoad.png"
//	);
//	resourcesMap_.emplace(SRC::KEYBOAD_IMG, move(res));
//
//	// ゲームパッドの画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "gamePad.png"
//	);
//	resourcesMap_.emplace(SRC::GAMEPAD_IMG, move(res));
//
//	// ゲーム説明の画像
//	res = make_unique<Resource>(
//		Resource::TYPE::IMG,
//		Application::PATH_IMAGE + "operation.PNG"
//	);
//	resourcesMap_.emplace(SRC::OPERATION_IMG, move(res));
//
//	//効果音
//	// 決定音
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "push_enter.mp3"
//	);
//	resourcesMap_.emplace(SRC::PUSH_ENTER_SND, move(res));
//
//	// カーソル移動音
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "move_cursor.mp3"
//	);
//	resourcesMap_.emplace(SRC::MOVE_CURSOR_SND, move(res));
//
//	// シーン切り替え
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "change_scene.mp3"
//	);
//	resourcesMap_.emplace(SRC::CHANGE_SCENE_SND, move(res));
//
//	// ジャンプ音
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "jump.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_JUMP_SND, move(res));
//
//	// 鳴き声
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "cry.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_CRY_SND, move(res));
//
//	// 被ダメ（かえる）
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "damage_player.mp3"
//	);
//	resourcesMap_.emplace(SRC::FROG_DAMAGE_SND, move(res));
//
//	// 餌獲得（かえる）
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "get_bait.mp3"
//	);
//	resourcesMap_.emplace(SRC::GET_BAIT_SND, move(res));
//
//	// 餌獲得（敵）
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "deprived_bait.mp3"
//	);
//	resourcesMap_.emplace(SRC::DEPRIVED_BAIT_SND, move(res));
//
//	// 被ダメ（敵）
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "damage_enemy.mp3"
//	);
//	resourcesMap_.emplace(SRC::ENEMY_DAMAGE_SND, move(res));
//
//	// 岩破壊
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_SOUND + "break_rock.mp3"
//	);
//	resourcesMap_.emplace(SRC::BREAK_ROCK_SND, move(res));
//
//	//BGM
//	//タイトル
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Title_2.mp3"
//	);
//	resourcesMap_.emplace(SRC::TITLE_BGM, move(res));
//
//	//探索
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Search_3.mp3"
//	);
//	resourcesMap_.emplace(SRC::SEARCH_BGM, move(res));
//
//	//探索最終日
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Search.mp3"
//	);
//	resourcesMap_.emplace(SRC::SEARCH_FINAL_BGM, move(res));
//
//	//失敗時
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Failed_2.mp3"
//	);
//	resourcesMap_.emplace(SRC::FAILED_BGM, move(res));
//
//	//成功時
//	res = make_unique<Resource>(
//		Resource::TYPE::SOUND,
//		Application::PATH_BGM + "Success_3.mp3"
//	);
//	resourcesMap_.emplace(SRC::SUCCESS_BGM, move(res));
//
//	// ヒットエフェクト
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "HitEffect.png"
//		,8,1,64,64
//	);
//	resourcesMap_.emplace(SRC::HIT_EFFECT, move(res));
//
//	// ジャンプ煙エフェクト
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "JumpSmoke.png"
//		, 8, 1, 130, 32
//	);
//	resourcesMap_.emplace(SRC::JUMP_SMOKE_EFFECT, move(res));
//
//	// ダッシュ煙エフェクト
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "DashSmoke.png"
//		, 8, 1, 41, 32
//	);
//	resourcesMap_.emplace(SRC::DASH_SMOKE_EFFECT, move(res));
//
//	// ダメージエフェクト
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "DamageEffect.png", 5, 1, 32, 32
//	);
//	resourcesMap_.emplace(SRC::DAMAGE_EFFECT, move(res));
//
//	// 卵破壊エフェクト
//	res = make_unique<Resource>(
//		Resource::TYPE::IMGS,
//		Application::PATH_EFFECT + "EggBreak.png"
//		, 8, 1, 64, 64
//	);
//	resourcesMap_.emplace(SRC::EGG_BREAK_EFFECT, move(res));
//
//#pragma region シェーダー用
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
