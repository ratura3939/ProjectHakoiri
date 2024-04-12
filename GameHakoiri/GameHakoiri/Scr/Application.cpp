#include"DxLib.h"
#include"Application.h"
#include"SceneManager.h"

Application* Application::instance_ = nullptr;

//�R���X�g���N�^
//********************************************************
Application::Application(void)
{
	
}
//�R�s�[�R���X�g���N�^
//********************************************************
Application::Application(const Application& ins)
{

}
//�f�X�g���N�^
//********************************************************
void Application::Destroy(void)
{
	delete instance_;
}

//������
//********************************************************
bool Application::Init(void)
{
	//�V�X�e������
	//------------------------------------------------------------
	SetWindowText("2316026 ���i�ȉ�");	//�Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);			//�Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);				//�Q�[���E�B���h�E�̕\�����@�ifalse : �t���X�N���[���j
	if (DxLib_Init() == -1)				//DX���C�u�����̏���������
	{
		return false;						//DX���C�u�����̏��������s�̂��߃V�X�e���I��
	}

	//�C���X�^���X�̐���
	if (!SceneManager::CreateInstance())
	{
		return false;	//���������s�̂��߃V�X�e���I��
	}

	//�������������I�������̂�
	return true;
}
//�N��
//********************************************************
void Application::Run(void)
{
	//�Q�[�����[�v
	//------------------------------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�Q�[�����C������
		//------------------------------------------------------------------------
		SceneManager::GetInstance().Update();	//�X�V

		//�`�揈��
		//------------------------------------------------------------------------
		SetDrawScreen(DX_SCREEN_BACK);	//�`�悷���ʂ𗠂̉�ʂɐݒ�
		ClearDrawScreen();				//�`�悷���ʂ̓��e������

		SceneManager::GetInstance().Draw();	//�`��

		ScreenFlip();					//���̉�ʂ�\�̉�ʂɏu�ԃR�s�[
	}
}

//���
//********************************************************
bool Application::Release(void)
{
	instance_ = nullptr;
	SceneManager::GetInstance().Release();
	//�V�X�e���I������
//------------------------------------------------------------
	DxLib_End();	//DX���C�u�����̏I������
	//�������������I�������̂�
	return true;
}

//�V���O���g����
//�C���X�^���X�̐���
//********************************************************
bool Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	if (!instance_->Init())
	{
		OutputDebugString("�A�v���P�[�V�������������s");
		return false;
	}
	//�������������I�������̂�
	return true;
}
//�C���X�^���X�̎擾
//********************************************************
Application& Application::GetInstance(void)
{
	return *instance_;
}