//#pragma once

#include <string>

class Application
{
public:
	//�萔
	// �X�N���[���T�C�Y
	//-------------------------------------------
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	static constexpr int FPS = 60;
	static constexpr float SIE = 3.1415926535;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::string PATH_ANIM;

	static const std::string PATH_MAP;
	static const std::string PATH_OBSTACLE;
	static const std::string PATH_PAZZLE;

	static const std::string PATH_CHARACTER;
	static const std::string PATH_MAPCHIP;
	static const std::string PATH_ROOM;
	static const std::string PATH_SYSTEM;
	static const std::string PATH_SOUND;
	static const std::string PATH_BGM;

	//�����o�֐�
	bool Init(void);	//������
	void Run(void);		//�N��
	bool Release(void);	//���

	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static Application& GetInstance(void);	//�C���X�^���X�̎擾

private:

	//�V���O���g����
	Application(void);	//�R���X�g���N�^
	Application(const Application&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static Application* instance_;
};