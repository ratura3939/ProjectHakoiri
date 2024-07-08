#pragma once

#include"../Common/Vector2F.h"

class CharacterBase
{
public:

	//8方向
	enum class DIR
	{
		BOTTOM,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		TOP_LEFT,
		TOP_RIGHT,
		MAX
	};

	//定数
	static constexpr float ANIM_SPEED = 5.0f;
	static constexpr int ANIM_NUM = 3;
	static constexpr int ANIM_TYPE = 4;
	static constexpr int ANIM_CENTER = 1;
	static constexpr int ANIM_RIGHT = 2;
	static constexpr int ANIM_SWITCH_TIME = 15;

	static constexpr int CHARACTER_SIZE_X = 32;
	static constexpr int CHARACTER_HALF_X = CHARACTER_SIZE_X / 2;
	static constexpr int CHARACTER_SIZE_Y = 32;
	static constexpr int CHARACTER_HALF_Y = CHARACTER_SIZE_Y / 2;

	static constexpr int VISION_SIZE_X = 454;
	static constexpr int VISION_SIZE_Y = 310;

	static constexpr int ROT_UNIT = 45;

	static constexpr int ROT_TOP=		0;
	static constexpr int ROT_TOP_RGH =	1;
	static constexpr int ROT_RGH =		2;
	static constexpr int ROT_BTM_RGH =	3;
	static constexpr int ROT_BTM =		4;
	static constexpr int ROT_BTM_LFT =	5;
	static constexpr int ROT_LFT =		6;
	static constexpr int ROT_TOP_LFT =	7;

	
	static constexpr int DIR_RGH =		0;
	static constexpr int DIR_BTM_RGH =	1;
	static constexpr int DIR_BTM =		2;
	static constexpr int DIR_BTM_LFT =	3;
	static constexpr int DIR_LFT =		4;
	static constexpr int DIR_TOP_LFT =	5;
	static constexpr int DIR_TOP =		6;
	static constexpr int DIR_TOP_RGH =	7;

	CharacterBase(void);
	virtual ~CharacterBase(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	void SetPos(Vector2F pos);
	Vector2F GetPos(void)const;
	void SetPrevPos(const Vector2F pos);
	Vector2F GetPrevPos()const;
	Vector2F GetCollisionPos(void)const;

private:
	void Anim(void);
	

protected:

	//画像
	int* img_;

	//位置
	Vector2F pos_;
	Vector2F prevPos_;

	//方向
	DIR dir_;
	//移動量
	float move_;
	//アニメーション関係
	int animIdx_;
	int prvAnimIdx_;
	int animCnt_;

	void ResetAnim(DIR dir);
	virtual void Move(void);	//動きの処理
	void SetDir(DIR dir);		//方向の変換

	DIR GetDir(void)const;
	virtual void SetParam(void);//各パラメータ設定
};

