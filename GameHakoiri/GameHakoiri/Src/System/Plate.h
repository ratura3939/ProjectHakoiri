#pragma once
#include"../Common/Vector2F.h"
#include"../Utility/Utility.h"

class Plate
{
public:
	//定数
	static constexpr float FRAME_EX = 2.0f;

	//プレートの状態
	enum class STATE
	{
		GO,
		STOP,
		BACK
	};

	//プレートの種類
	enum class TYPE
	{
		SELECT,
		CHECK,
		MAX
	};

	enum class INPUT
	{
		NONE,
		MOVE,
		SELECT
	};

	enum class ANSWER
	{
		NO,
		OK,
		MAX
	};

	//定数
	static constexpr float PLATE_SIZE = 512.0f;
	static constexpr float BOX_SIZE_X = 256.0f;
	static constexpr float BOX_SIZE_Y = 128.0f;
	static constexpr float PLATE_SPEED = 20.0f;
	static constexpr float DELTA_X = BOX_SIZE_X / 2;
	static constexpr float DELTA_Y = PLATE_SIZE / 2 - BOX_SIZE_Y / 2;
	static constexpr float EXCEPTION = PLATE_SIZE * 2;
	static constexpr int   FLASH = 20;

	//シングルトン化
	static bool CreateInstance(void);		//インスタンスの生成
	static Plate& GetInstance(void);	//インスタンスの取得

	void Init(void);
	bool Update(TYPE type);
	void UpdateGo(TYPE type);
	void UpdateStop(TYPE type);
	void UpdateBack(TYPE type);
	void Draw(TYPE type,std::string str,bool strLong);


	void Release(void);

	ANSWER GetAnswer(void);		//OK/NOを返す
	bool IsSelect(void);		//選択を完了させたかを返す
	bool IsFinish(void);		//一連の動作が終了したかを返す
	void SetState(STATE st);	//状態のセット
	void Reset(void);			//リセット

private:
	//遷移
	STATE state_;
	//画像
	int plateImg_[static_cast<int>(TYPE::MAX)];
	int boxImg_[static_cast<int>(ANSWER::MAX)];
	int frameImg_;

	//位置
	Vector2F platePos_;
	Vector2F boxPos_[static_cast<int>(TYPE::MAX)][static_cast<int>(ANSWER::MAX)];

	int frameAnim_;
	int prevStick_;


	ANSWER answer_;	//OK/NOどっちを選んだか
	bool isFinish_;	//プレートの一連の動作が終わったかどうか
	bool isSelect_;	//選択を確定させたか

	void ChangeAnswer(void);	//OK/NOの選択を変更
	void SetIsFinish(bool flag);	//一連の動作が終了したかのboolをセット
	void SetIsSelect(bool flag);	//選択終了したかのboolをセット
	INPUT KeyboardContoroller(void);	// キーボードの操作
	INPUT GamePadController(void);	// ゲームパッドの操作

	

	//シングルトン化
	Plate(void);
	void Destroy(void);

	static Plate* instance_;
};

