#pragma once
#include"../Manager/SceneManager.h"
#include"../Scene/GameScene.h"
#include"../Common/Vector2.h"


class Manual
{
public:

	//定数
	static constexpr int MANUAL_PAGE = 3;

	//場所（スクリーンサイズからボックスのサイズ引く）
	static constexpr int OK_KBD_X = 1280 - 256 / 2;
	static constexpr int OK_KBD_Y = 780 - 128;
	static constexpr int OK_PAD_X = 1280 - 256 / 2;
	static constexpr int OK_PAD_Y = 780 / 2 - 128;

	//シングルトン化
	static bool CreateInstance(void);		//インスタンスの生成
	static Manual& GetInstance(void);	//インスタンスの取得

	void Init(void);
	void Update(void);
	void Draw(void);

	void SetManual(GameScene::MODE mode, SceneManager::CONTROLLER cnt);
	bool IsFinish(void);

private:

	bool isFinish_;
	int prevStick_;
	Vector2 okPos_;

	int manualImg_[static_cast<int>(GameScene::MODE::MAX)][2];	//シーン別のマニュアル
	//コントローラー別+シーン別のマニュアル
	int cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::MAX)][static_cast<int>(GameScene::MODE::MAX)];
	int okImg_;//OKBOXのIMG
	int useImg_[3];	//描画に必要なものだけを入れる
	int useIdx_;


	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作

	//シングルトン化
	Manual(void);
	void Destroy(void);

	static Manual* instance_;
};

