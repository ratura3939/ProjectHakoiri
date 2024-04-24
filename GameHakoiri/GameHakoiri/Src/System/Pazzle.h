//#pragma once
class Pazzle
{
public:
	Pazzle(void);	//コンストラクタ
	~Pazzle(void);	//デストラクタ

	void Update(void);	//更新
	// キーボードの操作
	void KeyboardContoroller(void);

	// ゲームパッドの操作
	void GamePadController(void);
};

