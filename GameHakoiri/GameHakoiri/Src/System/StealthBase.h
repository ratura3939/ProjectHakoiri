#pragma once

class StealthBase
{
public:
	StealthBase(void);	//�R���X�g���N�^
	virtual ~StealthBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void Draw(void);	//�`��
	virtual bool Release(void);	//���
};