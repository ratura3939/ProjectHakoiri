//#pragma once
#include"SceneBase.h"

class SelectScene :public SceneBase
{
public:
	SelectScene(void);	//�R���X�g���N�^
	~SelectScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

};