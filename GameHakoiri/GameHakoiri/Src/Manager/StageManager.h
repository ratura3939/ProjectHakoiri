#pragma once

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
		,MAX
	};

	

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	//シングルトン化
	static bool CreateInstance(void);	//外部から静的インスタンスを生成
	static StageManager& GetInstance(void);	//インスタンスの取得
	
private:

	//シングルトン化
	StageManager(void);	//コンストラクタ
	StageManager(const StageManager&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static  StageManager* instance_;	//実体を確保
};