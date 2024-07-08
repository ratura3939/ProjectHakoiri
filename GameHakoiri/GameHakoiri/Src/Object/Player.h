//#pragma once

#include"CharacterBase.h"

class Stealth;

class Player: public CharacterBase
{
public:

	//定数
	static constexpr float UNIT_DIR_DEG = 45.0f;

	Player(void);
	~Player(void)override;

	void SetParam(void)override;
	void Move(void)override;

	bool IsDrawMap(void)const;

private:
	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
	DIR CheckDir(float deg);					//方向決め

	void ChangeIsDrawMap(void);	//マップを描画するかの選択

	bool isDrawMap_;
};