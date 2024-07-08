#include<DxLib.h>
#include"SceneManager.h"
#include"Camera.h"
#include"../Scene/SceneBase.h"
#include"../Scene/TitleScene.h"
#include"../Scene/SelectScene.h"
#include"../Scene/GameScene.h"
#include"../Scene/ResultScene.h"
#include"../Scene/EndingScene.h"
#include"../Common/Fader.h"


//�V���O���g����(�C���X�^���X�̏�����)
SceneManager* SceneManager::instance_ = nullptr;

//�R���X�g���N�^
//********************************************************
SceneManager::SceneManager(Camera& _camera) : camera_(_camera)
{
	sceneID_ = SCENEID::NONE;
	nextSceneID_ = SCENEID::NONE;
	isChangeScene_ = false;
	scene_ = nullptr;
	fader_ = nullptr;
}
//�R�s�[�R���X�g���N�^
//********************************************************
SceneManager::SceneManager(const SceneManager& ins, Camera& _camera) : camera_(_camera)
{
	
}
//�f�X�g���N�^
//********************************************************
void SceneManager::Destroy(void)
{
	delete instance_;
}
//������
//********************************************************
bool SceneManager::Init(void)
{
	//�V�[���Ǘ�
	sceneID_ = SCENEID::NONE;
	nextSceneID_ = SCENEID::TITLE;

	DoChangeScene();

	//�t�F�[�h
	fader_ = new Fader;
	fader_->Init();

	//�^�C�g�����t�F�[�h�C���ŕ\��
	fader_->SetFade(Fader::STATE::FADE_IN);
	isChangeScene_ = true;

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void SceneManager::Update(void)
{
	//�t�F�[�h����
	fader_->Update();
	if (isChangeScene_)
	{
		//�t�F�[�h��
		Fade();
	}
	else
	{
		scene_->Update();
	}
}
//�`��
//********************************************************
void SceneManager::Draw(void)
{
	
	scene_->Draw();
	//�t�F�[�h
	fader_->Draw();
}
//���
//********************************************************
bool SceneManager::Release(void)
{
	//�C���X�^���X�̉��
	ReleaseScene(sceneID_);
	camera_.Relese();

	delete fader_;
	fader_ = nullptr;
	instance_ = nullptr;
	//�������������I�������̂�
	return true;
}
//�X�e�[�W�i���o�[�̕ۊ�
//********************************************************
void SceneManager::SetStageNum(int num)
{
	stageNum_ = num;
}
//�X�e�[�W�i���o�[�̏��n
//********************************************************
int SceneManager::GetStageNum(void)
{
	return stageNum_;
}

void SceneManager::SetController(CONTROLLER cnt)
{
	controller_ = cnt;
}

void SceneManager::ChangeController(void)
{
	if (controller_ == CONTROLLER::KEYBOARD)controller_ = CONTROLLER::PAD;
	else controller_ = CONTROLLER::KEYBOARD;
}

SceneManager::CONTROLLER SceneManager::GetController(void) const
{
	return controller_;
}

//�J�����̎擾
Camera& SceneManager::GetCamera(void) const
{
	return camera_;
}


//�V�[���؂�ւ�
//********************************************************
void SceneManager::ChangeScene(SCENEID next,bool isToFade)
{
	nextSceneID_ = next;
	if (isToFade)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isChangeScene_ = true;
	}
	else
	{
		DoChangeScene();
	}
}
//�V�[���؂�ւ�(�t�F�[�h�Ȃ�)
//********************************************************
void SceneManager::DoChangeScene(void)
{
	//���݂̃V�[�����������
	ReleaseScene(sceneID_);
	//���̃V�[���𐶐�����
	sceneID_ = nextSceneID_;

	switch (sceneID_)
	{
	case SCENEID::TITLE:
		//�^�C�g��
		scene_ = new TitleScene;
		scene_->Init();
		break;

	case SCENEID::SELECT:
		//�X�e�[�W�I��
		scene_ = new SelectScene;
		scene_->Init();
		break;

	case SCENEID::GAME:
		//�Q�[��
		scene_ = new GameScene;
		scene_->Init();
		break;

	case SCENEID::RESULT:
		//���U���g
		scene_ = new ResultScene;
		scene_->Init();
		break;

	case SCENEID::ENDING:
		//�G���f�B���O
		scene_ = new EndingScene;
		scene_->Init();
		break;
	}
	nextSceneID_ = SCENEID::NONE;
}
//�t�F�[�h���{�p�֐�
//********************************************************
void SceneManager::Fade(void)
{
	//���݂̃t�F�[�h��Ԃ��擾
	Fader::STATE fState = fader_->GetState();

	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd() == true)
		{
			//�V�[���؂�ւ�
			DoChangeScene();
			//���]
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd() == true)
		{
			//�t�F�[�h�̏I��
			fader_->SetFade(Fader::STATE::NONE);
			//�؂�ւ��I��
			isChangeScene_ = false;
		}
		break;
	}
}
//�w�肵���V�[���̉��
//********************************************************
void SceneManager::ReleaseScene(SCENEID sceneID)
{
	if (sceneID != SCENEID::NONE)	//NONE�ȊO��������
	{
		//���݂̃V�[�����������
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}
//�O������ÓI�C���X�^���X�𐶐�
//********************************************************
bool SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		Camera::CreateInstance();
		instance_ = new SceneManager(Camera::GetInstance());	//�C���X�^���X����
	}
	if (!instance_->Init())	//�������Ɏ��s������
	{
		OutputDebugString("�V�[���}�l�[�W�����������s");
		return false;
	}
	//�������������I�������̂�
	return true;
}
//�C���X�^���X�̎擾
//********************************************************
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}