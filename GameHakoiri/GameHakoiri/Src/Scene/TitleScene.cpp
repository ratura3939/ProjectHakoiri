#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/SoundManager.h"
#include"../System/Plate.h"
#include"../Application.h"
#include"../Utility/Utility.h"
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

	auto& rsM = ResourceManager::GetInstance();
	titleImg_= rsM.Load(ResourceManager::SRC::TITLE_IMG).handleId_;
	startImg_ = rsM.Load(ResourceManager::SRC::START_IMG).handleId_;
	startEx_ = 0.7f;

	SoundManager::GetInstance().PlayBgmOfTitle();
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

		startEx_ += 0.01f;
		if (startEx_ > START_EX_F)startEx_ = START_EX_S;
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::SELECT);
		if (plate.IsFinish())
		{

			//�v���[�g�̈�A�̏������I����Ă�����V�[���؂�ւ�
			if (plate.GetAnswer() == Plate::ANSWER::OK)
			{
				SoundManager::GetInstance().StopBgmOfTitle();
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
			}
				
			else isCheck_ = false;
		}
	}
}
//�`��
//********************************************************
void TitleScene::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 4,
		1.0,
		0.0 * Utility::DEG2RAD,
		titleImg_,
		true,
		false);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y -256,
		startEx_,
		0.0 * Utility::DEG2RAD,
		startImg_,
		true,
		false);

	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::SELECT, str_, true);
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
	auto& snd = SoundManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		snd.PlaySndEnter(true);
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		isCheck_ = true;
		Plate::GetInstance().SetState(Plate::STATE::GO);
		str_ = "������@�̓L�[�{�[�h�ŗǂ��ł����H\n\n��������@��ύX����ꍇ�͂��̃^�C�g���܂Ŗ߂�K�v������܂�";
	}

	//����Ґ�p�R�}���h
	//�N���A�󋵂̃��Z�b�g
	if (ins.IsNew(KEY_INPUT_R) &&
		ins.IsNew(KEY_INPUT_E) &&
		ins.IsNew(KEY_INPUT_S) &&
		ins.IsNew(KEY_INPUT_T))
	{
		snd.PlaySndReset();
		SceneManager::GetInstance().Reset();
	}
	//�e�X�e�[�W���N���A�����
	if (ins.IsNew(KEY_INPUT_LSHIFT))
	{
		if (ins.IsNew(KEY_INPUT_1))SceneManager::GetInstance().CustomClearFlag(1);
		if (ins.IsNew(KEY_INPUT_2))SceneManager::GetInstance().CustomClearFlag(2);
		if (ins.IsNew(KEY_INPUT_3))SceneManager::GetInstance().CustomClearFlag(3);
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		snd.PlaySndEnter(true);
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		isCheck_ = true;
		str_ = "������@�̓R���g���[���[�ŗǂ��ł����H\n\n��������@��ύX����ꍇ�͂��̃^�C�g���܂Ŗ߂�K�v������܂�";
	}
}
