#pragma once

class SceneBase
{
public:
	SceneBase(void);	//�R���X�g���N�^
	virtual ~SceneBase(void);	//�f�X�g���N�^

	virtual bool Init(void);	//������
	virtual void Update(void);	//�X�V
	virtual void Draw(void);	//�`��
	virtual bool Release(void);	//���
};