#pragma once
#include "CharacterBase.h"
#include <DxLib.h>

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

	enum class VISION_STATE
	{
		MISSING,
		FIND,
		MAX
	};

	//�萔
	static constexpr int MOVE_UNIT = 32;	//�G�̊�b�ړ���

	EnemyBase(void);
	~EnemyBase(void)override;

	void Init(void)override;
	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;

	void SetIsUse(bool flag);	//�G���g�p���Ă��邩���Z�b�g
	bool IsUse(void);			//�G���g�p�ς݂����m�F
	TYPE GetType(void);			//�G�̎�ނ��l��
	void SetIsMove(bool flag);	//�����Ă��邩���Z�b�g	
	void SetVisionState(VISION_STATE state);	//�G�̎��o��Ԃ��Z�b�g

protected:
	TYPE type_;	//�G�̃^�C�v��ێ�
	bool isUse_;//���łɎg�p����Ă��邩��ێ�
	Vector2F moveStartPos_;
	int moveLimit_;	//���ł̈ړ��}�X��
	VECTOR moveDir_;	//���������̃x�N�^�[
	float speed_;

private:
	//���E
	int visionImg_[static_cast<int>(VISION_STATE::MAX)];
	VISION_STATE state_;
	float visionRot_;

	bool isMove_;	//�����Ă��邩

	void DrawVision(Vector2F cameraPos);	//���E�̕`��
	void DecideDir(void);					//��������
					
};

