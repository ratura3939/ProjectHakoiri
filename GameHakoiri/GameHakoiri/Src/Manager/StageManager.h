#pragma once

class StageBase;

class StageManager
{
public:

	//�񋓌^
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	bool Init(STAGENUM);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

	

	//�V���O���g����
	static bool CreateInstance(STAGENUM);	//�O������ÓI�C���X�^���X�𐶐�
	static StageManager& GetInstance(void);	//�C���X�^���X�̎擾
	
private:

	//�C���X�^���X
	StageBase* stage_;

	STAGENUM num_;	//��������X�e�[�W�ԍ���ێ�


	//�V���O���g����
	StageManager(void);	//�R���X�g���N�^
	StageManager(const StageManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static  StageManager* instance_;	//���̂��m��
};