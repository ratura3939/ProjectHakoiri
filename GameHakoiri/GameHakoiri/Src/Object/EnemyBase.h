#pragma once
#include "CharacterBase.h"
class EnemyBase :
    public CharacterBase
{
public:
	EnemyBase(void);
	~EnemyBase(void)override;

	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;
};

