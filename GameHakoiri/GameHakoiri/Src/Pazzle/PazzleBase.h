#pragma once
class PazzleBase
{
public:
	PazzleBase(void);	//�R���X�g���N�^
	virtual ~PazzleBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void Draw(void);	//�`��
	virtual bool Release(void);	//���
};

