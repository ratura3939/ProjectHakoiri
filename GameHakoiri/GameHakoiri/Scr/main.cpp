//�Q�[������F�����薺�̒E�o
//�����F���i�ȉ�
//-----------------------------------------------------

#include<DxLib.h>	//DX���C�u�����̎g�p
#include"Application.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
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