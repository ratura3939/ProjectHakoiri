#include<DxLib.h>

#include"../Manager/InputManager.h"
#include "Pazzle.h"

//�R���X�g���N�^
//********************************************************
Pazzle::Pazzle(void)
{

}
//�f�X�g���N�^
//********************************************************
Pazzle::~Pazzle(void)
{

}
//�X�V
//********************************************************
void Pazzle::Update(void)
{
	//StageMng�o�R��roomMng�̕ύX���s��
	//���͌n
	KeyboardContoroller();
	GamePadController();
}

// �L�[�{�[�h�̑���
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
}

// �Q�[���p�b�h�̑���
void Pazzle::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
}
