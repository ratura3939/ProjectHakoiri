#pragma once
#include<memory>
#include"../Utility/Utility.h"

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

	bool Init(STAGENUM);	//初期化
	void Update(std::shared_ptr<GameScene> scn);	//更新
	void Draw(std::shared_ptr<GameScene> scn);	//描画
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


	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};