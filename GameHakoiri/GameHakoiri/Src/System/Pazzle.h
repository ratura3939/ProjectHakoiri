//#pragma once
#include<memory>

class GameScene;
class StageManager;

class Pazzle
{
public:
	Pazzle(void);	//コンストラクタ
	~Pazzle(void);	//デストラクタ

	void Update(void);	//更新

	
	bool IsSelect(void);	//IsSelectの取得
	bool IsNeutral(void);	//IsSelectの取得
	bool IsFinish(void);
	void ChangeIsFinish(bool flag);	//IsNeutralの変更

private:
	bool isFinish_;		//パズルが完了したかどうか
	bool isSelect_;		//選択中かどうか
	bool isNeutral_;	//スティックがニュートラル状態か
	Vector2 neutralStick_;	//スティックのニュートラル状態を示す
	

	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作

	void ChangeIsSelect(bool flag);	//IsSelectの変更
	void ChangeIsNeutral(bool flag);	//IsNeutralの変更
	bool IsStickNeutral(Vector2 stick);	//スティックのニュートラルを返す
	Utility::DIR MoveStick(Vector2 stick);	//どの方向にスティックが動いたかを返却
};

