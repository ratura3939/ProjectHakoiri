#pragma once
#include"SceneBase.h"
#include<string>
#include<memory>

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

	void SetMode(const MODE mode);	//�Q�[�����[�h�ύX
	const MODE GetMode(void)const;			//�Q�[�����[�h�擾

private:

	//�C���X�^���X
	std::unique_ptr<Pazzle> pzl_;
	std::unique_ptr<Stealth> stl_;

	MODE mode_;	//���݂̃Q�[���̃��[�h��ێ�

	bool isPlate_;	//�v���[�g���o�����ǂ���
	bool goToNext_;	//�X�e���X�ɃV�[���J�ڂ��悤�Ƃ��Ă���
	std::string str_;	//�v���[�g�ɕ\�����镶��
};