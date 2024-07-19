//#pragma once
#include"SceneBase.h"

class EndingScene :public SceneBase
{
public:


	static constexpr float EX_S = 1.0f;
	static constexpr float EX_F = 1.3f;

	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr int THANK_SIZE = 512;

	EndingScene(void);	//コンストラクタ
	~EndingScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:

	int endImg_;
	int backTitleImg_;
	float endEx_;

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};