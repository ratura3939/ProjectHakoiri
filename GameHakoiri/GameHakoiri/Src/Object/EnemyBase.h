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

	//�萔
	static constexpr int MOVE_UNIT = 32;	//�G�̊�b�ړ���

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
	int moveLimit_;	//���ł̈ړ��}�X��

private:

	void DrawVision(Vector2F cameraPos);
};

