//#pragma once
#include"SceneBase.h"
#include"../Common/Vector2.h"



class SelectScene :public SceneBase
{
public:
	enum class FRAME_TYPE {
		NOMAL,
		OBLONG,
		MAX
	};

	//定数
	static constexpr int STAGE_NUM = 3;
	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr float ROT_MAX = 10.0f;
	static constexpr float ROT_MIN = -10.0f;
	static constexpr float ROT_UNIT = 0.5f;
	static constexpr float BACK_FRAME_EX = 4.0f;

	SelectScene(void);	//コンストラクタ
	~SelectScene(void);	//デストラクタ

	bool Init(void);	//初期化
	void Update(void);	//更新
	void Draw(void);	//描画
	bool Release(void);	//解放

private:
	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作

	/// <summary>
	///タイトルに戻るを選択しているか設定
	/// </summary>
	/// <param name="flag">true=している/false=していない</param>
	void SetSelectBack(const bool flag);

	/// <summary>
	/// 回転リセット
	/// </summary>
	/// <param name=""></param>
	void ResetRot(void);

	int selectNum_;					//カーソル上のステージナンバーを保持
	int stageNumImg_[STAGE_NUM];	//ステージ選択の画像
	float stageNumRot_[STAGE_NUM];	//ステージ選択の画像
	bool rotDecre_;
	Vector2 stageNumPos_[STAGE_NUM];//位置

	int checkImg_;		//チェックマーク

	int backTitleImg_;	//タイトルに戻る
	bool selectBack_;	//タイトルに戻るにカーソルを当てているか

	int frame_[static_cast<int>(FRAME_TYPE::MAX)];	//フレーム画像

	Vector2 prevStick_;	//1フレーム前のスティックの移動を保持

};