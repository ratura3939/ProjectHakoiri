#include<DxLib.h>
#include"SceneManager.h"
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
SceneManager::SceneManager(void)
{
	sceneID_ = SCENEID::NONE;
	nextSceneID_ = SCENEID::NONE;
	space_.now = 0;
	space_.old = 0;
	isChangeScene_ = false;
	scene_ = nullptr;
	fader_ = nullptr;
}
//�R�s�[�R���X�g���N�^
//********************************************************
SceneManager::SceneManager(const SceneManager& ins)
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

	//�g���K�[
	space_.now = 0;
	space_.old = 0;

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

	delete fader_;
	fader_ = nullptr;
	instance_ = nullptr;
	//�������������I�������̂�
	return true;
}

//�X�y�[�X�L�[�������ꂽ���ǂ���
//********************************************************
bool SceneManager::SpaceHit(void)
{
	space_.old = space_.now;
	space_.now = CheckHitKey(KEY_INPUT_SPACE);
	if (space_.now == 1 && space_.old == 0)
	{
		return true;
	}
	return false;
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
		instance_ = new SceneManager();	//�C���X�^���X����
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