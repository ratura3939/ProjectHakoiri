//#pragma once
#include"SceneBase.h"

class ResultScene :public SceneBase
{
public:

	static constexpr int RESULT_SIZE_X = 256;
	static constexpr int RESULT_SIZE_Y = 128;
	static constexpr int RESULT_FLASH = 30;
	static constexpr int RESULT_FLASH_MAX = 3000;

	ResultScene(void);	//コンストラクタ
	~ResultScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:
	bool result_;
	int resultImg_[2];
	int backSelectImg_;
	int flash_;

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};