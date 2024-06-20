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
	TYPE type_;	//�G�̃^�C�v��ێ�
	bool isUse_;//���łɎg�p����Ă��邩��ێ�

private:

	void DrawVision(void);
};

