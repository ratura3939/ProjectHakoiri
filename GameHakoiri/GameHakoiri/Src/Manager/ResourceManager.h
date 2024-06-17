#pragma once

#include <memory>
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	//使用する複数枚の画像（アニメーション）などの定数登録
	//static constexpr int MAP_TILE_SIZE_UNIT = 30;

	static constexpr int CHARACTER_ORIGIN_SIZE_X = 96;
	static constexpr int CHARACTER_ORIGIN_SIZE_Y = 128;

	static constexpr int BATH_MAPTHIP_X = 512;
	static constexpr int BATH_MAPTHIP_Y = 1216;
	static constexpr int EXTERIA_MAPTHIP_X = 256;
	static constexpr int EXTERIA_MAPTHIP_Y = 3552;
	static constexpr int INTERIA_MAPTHIP_X = 256;
	static constexpr int INTERIA_MAPTHIP_Y = 2464;

	// リソース名
	enum class SRC
	{
		//画像
		//システム
		FRAME_IMG,
		FRAME_OBLONG_IMG,
		FRAME_OBLONG_2_IMG,
		VISION_IMG,
	
		//部屋
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

		//キャラクター
		PLAYER_IMGS,

		//マップ
		BATH_MAPTHIP,
		EXTERIA_MAPTHIP,
		INTERIA_MAPTHIP,

		//Csv
		//パズル
		FIRST_PAZZLE_CSV,

		//マップ
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


		//効果音
		PUSH_ENTER_SND,

		//BGM
		TITLE_BGM,

		//エフェクト
		HIT_EFFECT,
		

	};

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static ResourceManager& GetInstance(void);

	// 初期化
	void Init(void);

	// 解放(シーン切替時に一旦解放)
	void Release(void);

	// リソースの完全破棄
	void Destroy(void);

	// リソースのロード
	const Resource& Load(SRC src);

	// リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	// 静的インスタンス
	static ResourceManager* instance_;

	//未登録
	Resource unregistered;

	// リソース管理の対象
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;
	//std::map<SRC, Resource> resourcesMap_;
	 
	
	// 読み込み済みリソース
	std::map<SRC, Resource&> loadedMap_;
	//std::map<SRC, Resource*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	// デストラクタも同様
	~ResourceManager(void) = default;

	// 内部ロード
	Resource& _Load(SRC src);

};

