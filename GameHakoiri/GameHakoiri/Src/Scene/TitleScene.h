//#pragma once
#include<string>
#include"SceneBase.h"
#include"../Common/Vector2F.h"

class TitleScene :public SceneBase
{
public:


	static constexpr float START_EX_S = 0.7f;
	static constexpr float START_EX_F = 1.0f;

	TitleScene(void);	//コンストラクタ
	~TitleScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放
private:

	int titleImg_;
	int startImg_;
	float startEx_;
	bool isNext_;
	bool isCheck_;
	std::string str_;

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};