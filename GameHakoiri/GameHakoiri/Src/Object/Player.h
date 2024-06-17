//#pragma once

#include"CharacterBase.h"

class Player: public CharacterBase
{
public:

	Player(void);
	~Player(void)override;

	void SetParam(void)override;
	void Move(void)override;

private:
	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
};