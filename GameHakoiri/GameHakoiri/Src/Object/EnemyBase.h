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
	static constexpr float VIEW_RANGE = 320.0f;	// ����̍L��(10�}�X)
	static constexpr float VIEW_ANGLE = 45.0f;	// ����p
	static constexpr float VIEW_DELTA = 90.0f;	// ����p�덷���킹�p�i���ʂ͉E��0��������p�͏ォ��Ȃ̂�)

	EnemyBase(void);
	~EnemyBase(void)override;

	void Init(void)override;
	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;

	bool FindPlayer(Vector2F pPos)const;	//�������player�����邩

	void SetIsUse(bool flag);	//�G���g�p���Ă��邩���Z�b�g
	bool IsUse(void);			//�G���g�p�ς݂����m�F
	TYPE GetType(void);			//�G�̎�ނ��l��
	void SetIsMove(bool flag);	//�����Ă��邩���Z�b�g	
	void SetVisionState(VISION_STATE state);	//�G�̎��o��Ԃ��Z�b�g
	void SetColObject(const Vector2 obj);	//���E���Ղ�I�u�W�F�N�g�̈ʒu�i�z��w���j���Z�b�g
	void ResetColObject(void);				//���E���Ղ�I�u�W�F�N�g�̈ʒu�i�z��w���j�����Z�b�g
	Vector2 GetColObject(void)const;		//���E���Ղ�I�u�W�F�N�g�̈ʒu�i�z��w���j���Q�b�g

protected:
	TYPE type_;	//�G�̃^�C�v��ێ�
	bool isUse_;//���łɎg�p����Ă��邩��ێ�
	Vector2F moveStartPos_;
	int moveLimit_;	//���ł̈ړ��}�X�ʌ��x
	VECTOR moveDir_;	//���������̃x�N�^�[
	float speed_;		//�����̑���

private:
	//���E
	int visionImg_[static_cast<int>(VISION_STATE::MAX)];	//����摜
	double drawVisionRot_;	//����p�̕`��̂ݎg�p
	VISION_STATE state_;	//�G�̔������

	bool isMove_;	//�����Ă��邩
	Vector2 colObject_;	//�G�̎��E���Ղ�I�u�W�F�N�g��ۑ�

	void DrawVision(Vector2F cameraPos);	//���E�̕`��
	void DecideDir(void);					//��������
					
};

