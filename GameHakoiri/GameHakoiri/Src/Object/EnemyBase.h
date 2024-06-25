#pragma once
#include "CharacterBase.h"
class EnemyBase :
    public CharacterBase
{
public:

	enum class TYPE
	{
		HOUSEMADE,
		SENESCHAL,
		MAX
	};

	//定数
	static constexpr int MOVE_UNIT = 32;	//敵の基礎移動量

	EnemyBase(void);
	~EnemyBase(void)override;

	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;

	void SetIsUse(bool flag);
	bool IsUse(void);
	TYPE GetType(void);

protected:
	TYPE type_;	//敵のタイプを保持
	bool isUse_;//すでに使用されているかを保持
	int moveLimit_;	//一回での移動マス量

private:

	void DrawVision(Vector2F cameraPos);
};

