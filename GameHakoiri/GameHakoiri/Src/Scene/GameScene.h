#pragma once
#include"SceneBase.h"
#include<string>
#include<memory>

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

	void SetMode(const MODE mode);	//ゲームモード変更
	const MODE GetMode(void)const;			//ゲームモード取得

private:

	//インスタンス
	std::unique_ptr<Pazzle> pzl_;
	std::unique_ptr<Stealth> stl_;

	MODE mode_;	//現在のゲームのモードを保持

	bool isPlate_;	//プレートを出すかどうか
	bool goToNext_;	//ステルスにシーン遷移しようとしている
	std::string str_;	//プレートに表示する文章
};