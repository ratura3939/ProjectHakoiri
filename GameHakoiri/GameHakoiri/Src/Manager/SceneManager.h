//#pragma once

//�O���錾
class Fader;
class SceneBase;

class SceneManager
{
public:
	//�񋓌^
	//�V�[���Ǘ�
	enum class SCENEID
	{
		NONE
		, TITLE
		, SELECT
		, GAME
		, RESULT
		, ENDING
		, MAX
	};
	
	
	//�����o�֐�
	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

	void ChangeScene(SCENEID,bool);		//�V�[���؂�ւ�(�t�F�[�h�L��)

	void SetStageNum(int);		//�X�e�[�W�i���o�[�̕ۊ�
	int GetStageNum(void);		//�X�e�[�W�i���o�[�̏��n

	//�V���O���g����
	static bool CreateInstance(void);	//�O������ÓI�C���X�^���X�𐶐�
	static SceneManager& GetInstance(void);	//�C���X�^���X�̎擾
	

private:
	SCENEID sceneID_;	//�V�[���؂�ւ�
	SCENEID nextSceneID_;	//���̃V�[����ێ�
	
	bool isChangeScene_;	//�V�[���؂�ւ��p�̘_���^

	//�C���X�^���X�̓��I�m��
	SceneBase* scene_;	//�V�[���J��
	Fader* fader_;	//�t�F�[�h


	int stageNum_;	//�I�������X�e�[�W�i���o�[�ۑ��p

	//�����o�֐�
	void DoChangeScene(void);		//�V�[���؂�ւ�(�t�F�[�h�Ȃ�)
	void Fade(void);	//�t�F�[�h���{�p�֐�
	void ReleaseScene(SCENEID);	//�V�[���̉��

	//�V���O���g����
	SceneManager(void);	//�R���X�g���N�^
	SceneManager(const SceneManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static SceneManager* instance_;	//���Ԃ��m��
};