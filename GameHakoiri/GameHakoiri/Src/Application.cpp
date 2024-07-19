#include<DxLib.h>
#include"Application.h"
#include"Manager/SceneManager.h"
#include"Manager/InputManager.h"
#include"Manager/ResourceManager.h"

Application* Application::instance_ = nullptr;


const std::string Application::PATH_ANIM = "Data/Anim/";
const std::string Application::PATH_MAP = "Data/Csv/Map/";
const std::string Application::PATH_OBSTACLE = "Data/Csv/Map/Mapchip/";
const std::string Application::PATH_PAZZLE = "Data/Csv/Pazzle/";
const std::string Application::PATH_CHARACTER = "Data/Img/Character/";
const std::string Application::PATH_MAPCHIP = "Data/Img/Map/";
const std::string Application::PATH_ROOM = "Data/Img/Room/";
const std::string Application::PATH_SYSTEM = "Data/Img/System/";
const std::string Application::PATH_MANUAL = "Data/Img/Manual/";
const std::string Application::PATH_SOUND = "Data/Snd/";
const std::string Application::PATH_BGM = "Data/Snd/Bgm/";

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
	SetWindowText("ProjectHakoiri");	//�Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);			//�Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);				//�Q�[���E�B���h�E�̕\�����@�ifalse : �t���X�N���[���j
	if (DxLib_Init() == -1)				//DX���C�u�����̏���������
	{
		return false;						//DX���C�u�����̏��������s�̂��߃V�X�e���I��
	}
	
	//���͊Ǘ�������
	InputManager::CreateInstance();
	//���\�[�X�Ǘ�������
	ResourceManager::CreateInstance();

	//�C���X�^���X�̐���
	if (!SceneManager::CreateInstance())
	{
		return false;	//���������s�̂��߃V�X�e���I��
	}

	currentFrame_ = 0;
	lastFrame_ = 0;
	//�������������I�������̂�
	return true;
}
//�N��
//********************************************************
void Application::Run(void)
{
	SceneManager& instance = SceneManager::GetInstance();
	//�Q�[�����[�v
	//------------------------------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�Q�[�����C������
		//------------------------------------------------------------------------

		Sleep(1);	//�V�X�e���ɏ�����Ԃ�
		currentFrame_ = GetNowCount();


		if (currentFrame_ - lastFrame_ >= frameRate)
		{
			lastFrame_ = currentFrame_;
			InputManager::GetInstance().Update();
			instance.Update();	//�X�V
		}

		//�`�揈��
		//------------------------------------------------------------------------
		SetDrawScreen(DX_SCREEN_BACK);	//�`�悷���ʂ𗠂̉�ʂɐݒ�
		ClearDrawScreen();				//�`�悷���ʂ̓��e������

		instance.Draw();	//�`��

		ScreenFlip();					//���̉�ʂ�\�̉�ʂɏu�ԃR�s�[
	}
}

//���
//********************************************************
bool Application::Release(void)
{
	instance_ = nullptr;
	SceneManager::GetInstance().Release();
	ResourceManager::GetInstance().Destroy();
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