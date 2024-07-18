#pragma once

#include"../Scene/GameScene.h"

//�O���錾
class Fader;
class SceneBase;
class Camera;

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
	

	//�R���g���[���[
	enum class CONTROLLER
	{
		KEYBOARD,
		PAD,
		MAX
	};
	
	//�����o�֐�
	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

	void ChangeScene(SCENEID,bool);		//�V�[���؂�ւ�(�t�F�[�h�L��)

	void SetStageNum(int);		//�X�e�[�W�i���o�[�̕ۊ�
	int GetStageNum(void);		//�X�e�[�W�i���o�[�̏��n

	void SetController(CONTROLLER cnt);
	void ChangeController(void);	//�R���g���[���[�̐؂�ւ�
	CONTROLLER GetController(void)const;

	// �J�����̎擾
	Camera& GetCamera(void) const;

	//�V���O���g����
	static bool CreateInstance(void);	//�O������ÓI�C���X�^���X�𐶐�
	static SceneManager& GetInstance(void);	//�C���X�^���X�̎擾
	
	void ClearStage(int stageNum);
	bool IsClearStage(int stageNum);

	void SetManual(GameScene::MODE mode);
	void Reset(void);

private:
	SCENEID sceneID_;	//�V�[���؂�ւ�
	SCENEID nextSceneID_;	//���̃V�[����ێ�
	CONTROLLER controller_;	//�g�p���̃R���g���[���[��ێ�
	
	bool isChangeScene_;	//�V�[���؂�ւ��p�̘_���^

	//�C���X�^���X�̓��I�m��
	SceneBase* scene_;	//�V�[���J��
	Fader* fader_;	//�t�F�[�h
	Camera& camera_;	//�J����


	int stageNum_;	//�I�������X�e�[�W�i���o�[�ۑ��p
	bool clearStage_[3];	//�N���A�����X�e�[�W��ۑ�


	//�}�j���A���֌W
	bool isManual_;	//�}�j���A�����o�����ǂ���
	bool firstManual_[static_cast<int>(GameScene::MODE::MAX)];

	//�����o�֐�
	void DoChangeScene(void);		//�V�[���؂�ւ�(�t�F�[�h�Ȃ�)
	void Fade(void);	//�t�F�[�h���{�p�֐�
	void ReleaseScene(SCENEID);	//�V�[���̉��

	void SetChangeScene(const bool flag);

	//�V���O���g����
	SceneManager(Camera& _camera);	//�R���X�g���N�^
	SceneManager(const SceneManager&, Camera& _camera);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static SceneManager* instance_;	//���Ԃ��m��
};