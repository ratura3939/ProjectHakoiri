//#pragma once
#include"SceneBase.h"

class EndingScene :public SceneBase
{
public:
	EndingScene(void);	//コンストラクタ
	~EndingScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:

};