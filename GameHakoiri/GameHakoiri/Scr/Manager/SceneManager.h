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
		, GAME
		, GAMEOVER
		, MAX
	};
	//�\����
	struct TRG
	{
		int now;
		int old;
	};
	
	//�����o�֐�
	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

	bool SpaceHit(void);		//�X�y�[�X�L�[�������ꂽ���ǂ���
	void ChangeScene(SCENEID,bool);		//�V�[���؂�ւ�(�t�F�[�h�L��)

	//�V���O���g����
	static bool CreateInstance(void);	//�O������ÓI�C���X�^���X�𐶐�
	static SceneManager& GetInstance(void);	//�C���X�^���X�̎擾
	

private:
	SCENEID sceneID_;	//�V�[���؂�ւ�
	SCENEID nextSceneID_;	//���̃V�[����ێ�
	TRG space_;			//�g���K�[
	bool isChangeScene_;	//�V�[���؂�ւ��p�̘_���^

	//�C���X�^���X�̓��I�m��
	SceneBase* scene_;	//�V�[���J��
	Fader* fader_;	//�t�F�[�h

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