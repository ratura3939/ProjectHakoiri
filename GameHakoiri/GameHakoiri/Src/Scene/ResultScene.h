//#pragma once
#include"SceneBase.h"

class ResultScene :public SceneBase
{
public:
	ResultScene(void);	//コンストラクタ
	~ResultScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:
	int resultImg_[2];
	int backSelectImg_;

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};