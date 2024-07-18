//#pragma once
#include"SceneBase.h"
#include"../Common/Vector2.h"



class SelectScene :public SceneBase
{
public:

	//定数
	static constexpr int STAGE_NUM = 3;
	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr float ROT_MAX = 10.0f;
	static constexpr float ROT_MIN = -10.0f;
	static constexpr float ROT_UNIT = 0.5f;

	SelectScene(void);	//コンストラクタ
	~SelectScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	int selectNum_;	//カーソル上のステージナンバーを保持
	int stageNumImg_[STAGE_NUM];	//ステージ選択の画像
	float stageNumRot_[STAGE_NUM];	//ステージ選択の画像
	bool rotDecre_;
	Vector2 stageNumPos_[STAGE_NUM];//位置

	int checkImg_;	//チェックマーク

	int backTitleImg_;	//タイトルに戻る
	bool selectBack_;	//タイトルに戻るにカーソルを当てているか

	int frame_[2];	//フレーム画像

	Vector2 prevStick_;	//1フレーム前のスティックの移動を保持

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作

	void SetSelectBack(const bool flag);
	void ResetRot(void);
};