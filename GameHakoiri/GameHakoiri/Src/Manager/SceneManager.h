#pragma once
#include<memory>
#include"../Scene/GameScene.h"

//�O���錾
class Fader;
class SceneBase;
class Camera;

class SceneManager
{
public:
	//�񋓌^
	/// <summary>
	/// �V�[���Ǘ�
	/// </summary>
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
	
	/// <summary>
	/// �R���g���[���[
	/// </summary>
	enum class CONTROLLER
	{
		KEYBOARD,
		PAD,
		MAX
	};

	//�萔
	static constexpr int STAGE_ALL = 3;
	

	//�V���O���g����
	static bool CreateInstance(void);	//�O������ÓI�C���X�^���X�𐶐�
	static SceneManager& GetInstance(void);	//�C���X�^���X�̎擾

private:
	SceneManager(Camera& _camera);	//�R���X�g���N�^
	
public:
	void Destroy(void);	//�f�X�g���N�^
	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���


	// �J�����̎擾
	Camera& GetCamera(void) const;

#pragma region �V�[���Ǘ�
public:
	/// <summary>
	/// �V�[���؂芷����t
	/// </summary>
	/// <param name="next">�؂�ւ���</param>
	/// <param name="isToFade">true=�t�F�[�h����/false=�t�F�[�h���Ȃ�</param>
	void ChangeScene(const SCENEID next, const bool isToFade);

private:
	/// <summary>
	/// �V�[���؂芷��
	/// </summary>
	void DoChangeScene(void);

	/// <summary>
	/// �t�F�[�h
	/// </summary>
	/// <param name=""></param>
	void Fade(void);

	/// <summary>
	/// �V�[���̉��
	/// </summary>
	/// <param name="sceneID">�������V�[��</param>
	void ReleaseScene(const SCENEID sceneID);

	/// <summary>
	/// �V�[���ύX�t���O�ݒ�
	/// </summary>
	/// <param name="flag">true=�ύX��/false=�ύX���Ă��Ȃ�</param>
	void SetChangeScene(const bool flag);
#pragma endregion



#pragma region ���V�[���Ɉڍs���ׂ�����
public:
	//�X�e�[�W�ԍ�
	/// <summary>
	/// �ݒ�
	/// </summary>
	/// <param name="">�ԍ�</param>
	void SetStageNum(const int);

	/// <summary>
	/// �擾
	/// </summary>
	/// <returns>�X�e�[�W�ԍ�</returns>
	const int GetStageNum(void)const;

	//�R���g���[���[
	/// <summary>
	/// �ݒ�
	/// </summary>
	/// <param name="cnt">�R���g���[���[</param>
	void SetController(const CONTROLLER cnt);

	/// <summary>
	/// ���݂Ƃ͈Ⴄ�Е��ɕύX
	/// </summary>
	void ChangeController(void);

	/// <summary>
	/// �擾
	/// </summary>
	/// <returns>�R���g���[���[</returns>
	const CONTROLLER GetController(void)const;

#pragma endregion

#pragma region �N���A�֌W
public:
	void ClearStage(const int stageNum);
	const bool IsClearStage(const int stageNum)const;
	const bool IsClearStageNow(void)const;
	const bool CheckAllClear(void)const;

	void SetManual(const GameScene::MODE mode);
	void Reset(void);
	void CustomClearFlag(int num);
#pragma endregion


private:
	SCENEID sceneID_;		//�V�[���؂�ւ�
	SCENEID nextSceneID_;	//���̃V�[����ێ�
	CONTROLLER controller_;	//�g�p���̃R���g���[���[��ێ�
	
	bool isChangeScene_;	//�V�[���؂�ւ��p�̘_���^

	//�C���X�^���X�̓��I�m��
	SceneBase* scene_;				//�V�[���J��
	std::unique_ptr<Fader> fader_;	//�t�F�[�h
	Camera& camera_;				//�J����

	int stageNum_;					//�I�������X�e�[�W�i���o�[�ۑ��p
	bool clearStage_[STAGE_ALL];	//�N���A�����X�e�[�W��ۑ�

	//�}�j���A���֌W
	bool isManual_;												//�}�j���A�����o�����ǂ���
	bool firstManual_[static_cast<int>(GameScene::MODE::MAX)];	//�ŏ��̑������

	static SceneManager* instance_;	//���Ԃ��m��
};