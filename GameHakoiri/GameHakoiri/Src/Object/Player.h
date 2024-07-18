//#pragma once

#include"CharacterBase.h"

class Stealth;

class Player: public CharacterBase
{
public:

	//定数
	static constexpr float UNIT_DIR_DEG = 45.0f;
	static constexpr float HP = 100.0f;
	static constexpr float HP_SIZE = 128.0f;
	static constexpr float DASH = 2.0f;
	static constexpr float USE_STAMINA = 2.0f;
	static constexpr float STAMINA_MAX = 128.0f;
	static constexpr float STAMINA_BOX = 16.0f;
	static constexpr float STAMINA_RECOVERY = 0.5f;
	static constexpr int RED = 0xff0000;
	static constexpr int ORENGE = 0xffa500;

	Player(void);
	~Player(void)override;

	void SetParam(void)override;
	void Move(void)override;
	void Draw(void)override;

	bool IsDrawMap(void)const;
	float GetHp(void)const;
	void Damage(void);

private:
	void KeyboardContoroller(void);	// キーボードの操作
	void GamePadController(void);	// ゲームパッドの操作
	DIR CheckDir(float deg);					//方向決め

	void ChangeIsDrawMap(void);	//マップを描画するかの選択

	void RecoveryStamina(void);	//スタミナの回復

	bool isDash_;	//ダッシュが可能か
	float dash_;	//ダッシュの倍率
	float stamina_;//ダッシュに使用するスタミナ
	int staminaColor_;	//スタミナゲージのカラー

	//HPバー表示
	float hp_;
	Vector2F hpPos_;
	int hpBaseImg_;
	int hpCircleImg_;
	int hpText_;

	bool isDrawMap_;
};