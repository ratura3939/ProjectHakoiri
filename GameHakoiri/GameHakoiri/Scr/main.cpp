//�Q�[������F�����薺�̒E�o
//�����F���i�ȉ�
//-----------------------------------------------------

#include<DxLib.h>	//DX���C�u�����̎g�p
#include"Application.h"

int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	if (Application::CreateInstance() == false)	//������
	{
		return -1;	//���������s�ŏI��
	}

	Application& instance = Application::GetInstance();

	instance.Run();		//�Q�[�����[�v�J�n

	instance.Release();	//���

	return 0;			//�Q�[���̏I��
}