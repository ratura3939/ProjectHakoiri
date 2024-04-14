//#pragma once

class Application
{
public:
	//�萔
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

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