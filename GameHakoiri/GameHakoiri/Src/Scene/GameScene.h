#pragma once
#include"SceneBase.h"
#include<string>

class Pazzle;
class Stealth;
class StageManager;

class GameScene :public SceneBase
{
public:

	enum class MODE
	{
		PAZZLE,
		STEALTH,
		MAX
	};

	GameScene(void);	//�R���X�g���N�^
	~GameScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

	void SetMode(MODE mode);	//�Q�[�����[�h�ύX
	MODE GetMode(void);			//�Q�[�����[�h�擾

private:

	//�C���X�^���X
	Pazzle* pzl_;
	Stealth* stl_;

	MODE mode_;	//���݂̃Q�[���̃��[�h��ێ�

	bool isCheck_;	//�v���[�g���o�����ǂ���
	std::string str_;
};