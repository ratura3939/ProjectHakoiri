//#pragma once
#include"SceneBase.h"

class EndingScene :public SceneBase
{
public:
	EndingScene(void);	//�R���X�g���N�^
	~EndingScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

};