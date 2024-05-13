#pragma once
#include<memory>
#include"../Utility/Utility.h"

class GameScene;
class StageBase;

class StageManager
{
public:

	//�񋓌^
	//��������X�e�[�W
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	bool Init(STAGENUM);	//������
	void Update(std::shared_ptr<GameScene> scn);	//�X�V
	void Draw(std::shared_ptr<GameScene> scn);	//�`��
	bool Release(void);	//���

	void MoveCursor(Utility::DIR dir);	//�J�[�\���̈ړ�
	void MovePiece(Utility::DIR dir);	//��̈ړ�
	void PazzleReset(void);		//�Ֆʃ��Z�b�g
	void SetFlash(bool flag);	//�g�_��
	

	//�V���O���g����
	static bool CreateInstance(STAGENUM);	//�O������ÓI�C���X�^���X�𐶐�
	static StageManager& GetInstance(void);	//�C���X�^���X�̎擾
	
private:

	//�C���X�^���X
	StageBase* stage_;

	STAGENUM num_;	//��������X�e�[�W�ԍ���ێ�

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];


	//�V���O���g����
	StageManager(void);	//�R���X�g���N�^
	StageManager(const StageManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static  StageManager* instance_;	//���̂��m��
};