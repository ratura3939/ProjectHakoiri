//#pragma once

class StageManager;

class Pazzle
{
public:
	Pazzle(void);	//コンストラクタ
	~Pazzle(void);	//デストラクタ

	void Update(void);	//更新

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
	bool IsSelect(void);	//IsSelectの取得

private:
	bool isSelect_;		//選択中かどうか
	
	void ChangeIsSelect(bool);	//IsSelectの変更
};

