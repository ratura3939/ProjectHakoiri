//#pragma once
#include"SceneBase.h"

class TitleScene :public SceneBase
{
public:
	TitleScene(void);	//コンストラクタ
	~TitleScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:
	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};