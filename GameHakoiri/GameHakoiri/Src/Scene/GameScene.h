#pragma once
#include"SceneBase.h"
#include<string>

class Pazzle;
class Stealth;
class StageManager;

class GameScene :public SceneBase
{
public:

	enum class MODE
	{
		PAZZLE,
		STEALTH,
		MAX
	};

	GameScene(void);	//コンストラクタ
	~GameScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

	void SetMode(MODE mode);	//ゲームモード変更
	MODE GetMode(void);			//ゲームモード取得

private:

	//インスタンス
	Pazzle* pzl_;
	Stealth* stl_;

	MODE mode_;	//現在のゲームのモードを保持

	bool isCheck_;	//プレートを出すかどうか
	std::string str_;
};