//#pragma once
#include"SceneBase.h"



class SelectScene :public SceneBase
{
public:
	SelectScene(void);	//コンストラクタ
	~SelectScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	int selectNum_;	//カーソル上のステージナンバーを保持

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};