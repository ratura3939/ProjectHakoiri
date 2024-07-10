#pragma once
#include"../Common/Vector2F.h"
class Plate
{
public:

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

	//定数
	static constexpr int PLATE_SIZE = 512;

	Plate(void);
	~Plate(void);

	void Init(void);
	bool Update(TYPE type);
	void UpdateGo(void);
	bool UpdateStop(TYPE type);
	void UpdateBack(void);
	void Draw(TYPE type);
	void Release(void);


private:

	STATE state_;

	int plateImg_[static_cast<int>(TYPE::MAX)];
	int frameImg_;

	Vector2F platePos_;
	float speed_;

	bool isFinishAnim_;
	bool isSelect_;

	INPUT KeyboardContoroller(void);	// キーボードの操作
	INPUT GamePadController(void);	// ゲームパッドの操作
};

