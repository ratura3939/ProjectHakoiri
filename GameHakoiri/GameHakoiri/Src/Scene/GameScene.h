//#pragma once
#include"SceneBase.h"

class GameScene :public SceneBase
{
public:
	GameScene(void);	//�R���X�g���N�^
	~GameScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

};