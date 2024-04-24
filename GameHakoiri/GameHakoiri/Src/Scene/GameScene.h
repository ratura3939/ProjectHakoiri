//#pragma once
#include"SceneBase.h"

class Pazzle;
class Stealth;

class GameScene :public SceneBase
{
public:

	enum class MODE
	{
		PAZZLE
		, STEALTH
		,MAX
	};

	GameScene(void);	//コンストラクタ
	~GameScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:

	//インスタンス
	Pazzle* pzl_;
	Stealth* stl_;

	MODE mode_;	//現在のゲームのモードを保持

};