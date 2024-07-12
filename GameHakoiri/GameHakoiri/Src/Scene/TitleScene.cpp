#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../System/Plate.h"
#include"TitleScene.h"


//�R���X�g���N�^
//********************************************************
TitleScene::TitleScene(void)
{
	isNext_ = false;
}
//�f�X�g���N�^
//********************************************************
TitleScene::~TitleScene(void)
{

}
//������
//********************************************************
bool TitleScene::Init(void)
{
	isCheck_ = false;
	str_ = "NONE";
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void TitleScene::Update(void)
{
	if (!isCheck_)
	{
		KeyboardContoroller();
		GamePadController();
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::SELECT);
		if (plate.IsFinish())
		{

			//�v���[�g�̈�A�̏������I����Ă�����V�[���؂�ւ�
			if (plate.GetAnswer() == Plate::ANSWER::OK)
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
			else isCheck_ = false;
		}
			
	}
}
//�`��
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);

	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::SELECT,str_);
}
//���
//********************************************************
bool TitleScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}

void TitleScene::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		isCheck_ = true;
		Plate::GetInstance().SetState(Plate::STATE::GO);
		str_ = "������@�̓L�[�{�[�h�ŗǂ��ł����H";
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		isCheck_ = true;
		str_ = "������@�̓R���g���[���[�ŗǂ��ł����H";
	}
}
