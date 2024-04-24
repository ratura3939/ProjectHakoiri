#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"TitleScene.h"


//�R���X�g���N�^
//********************************************************
TitleScene::TitleScene(void)
{
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
	//����ɏ������s��ꂽ�̂�
	return true;
}
//�X�V
//********************************************************
void TitleScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
	}
}
//�`��
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);
}
//���
//********************************************************
bool TitleScene::Release(void)
{
	//����ɏ������s��ꂽ�̂�
	return true;
}