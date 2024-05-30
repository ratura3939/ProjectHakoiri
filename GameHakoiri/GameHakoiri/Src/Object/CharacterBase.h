#pragma once

#include"../Common/Vector2F.h"

class CharacterBase
{
public:

	enum class DIR
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		MAX
	};

	//定数
	static constexpr float ANIM_SPEED = 5.0f;
	static constexpr int ANIM_NUM = 3;
	static constexpr int ANIM_TYPE = 4;
	static constexpr int ANIM_CENTER = 1;
	static constexpr int ANIM_RIGHT = 2;
	static constexpr int ANIM_SWITCH_TIME = 15;

	CharacterBase(void);
	~CharacterBase(void);

	void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	void SetPos(Vector2F pos);
	Vector2F GetPos(void)const;

private:
	void Anim(void);


protected:

	//画像
	int* img_;
	//位置
	Vector2F pos_;
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
	DIR GetDir(void)const;		//方向の取得
	virtual void SetParam(void);//各パラメータ設定
};

