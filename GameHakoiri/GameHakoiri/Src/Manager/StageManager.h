#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"

class GameScene;
class StageBase;

class StageManager
{
public:

	//列挙型
	//生成するステージ
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	//定数
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 6;
	static constexpr int THIRD_PAZZLE_SIZE_X = 6;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 6;

	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	bool Init(STAGENUM);	//初期化
	void Update(GameScene::MODE mode);	//更新
	void Draw(GameScene::MODE mode);	//描画
	bool Release(void);	//解放

	void MoveCursor(Utility::DIR dir);	//カーソルの移動
	void MovePiece(Utility::DIR dir);	//駒の移動
	void PazzleReset(void);		//盤面リセット
	void SetFlash(bool flag);	//枠点滅
	

	//シングルトン化
	static bool CreateInstance(STAGENUM);	//外部から静的インスタンスを生成
	static StageManager& GetInstance(void);	//インスタンスの取得
	
private:

	//インスタンス
	StageBase* stage_;

	STAGENUM num_;	//生成するステージ番号を保持

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];
	
	std::vector<std::vector<int>>::iterator stageCsv_[static_cast<int>(STAGENUM::MAX)];

	void LoadCsv(void);


	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};