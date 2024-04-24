#pragma once

class StageBase;

class StageManager
{
public:

	//列挙型
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	bool Init(STAGENUM);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	

	//シングルトン化
	static bool CreateInstance(STAGENUM);	//外部から静的インスタンスを生成
	static StageManager& GetInstance(void);	//インスタンスの取得
	
private:

	//インスタンス
	StageBase* stage_;

	STAGENUM num_;	//生成するステージ番号を保持


	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};