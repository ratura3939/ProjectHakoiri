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

private:

	void DrawVision(void);
};

