//#pragma once
#include"SceneBase.h"

class Pazzle;
class Stealth;

class GameScene :public SceneBase
{
public:

	enum class MODE
	{
		PAZZLE
		, STEALTH
		,MAX
	};

	GameScene(void);	//�R���X�g���N�^
	~GameScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���
private:

	//�C���X�^���X
	Pazzle* pzl_;
	Stealth* stl_;

	MODE mode_;	//���݂̃Q�[���̃��[�h��ێ�

};