//#pragma once
#include"SceneBase.h"

class GameScene :public SceneBase
{
public:
	GameScene(void);	//コンストラクタ
	~GameScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:

};