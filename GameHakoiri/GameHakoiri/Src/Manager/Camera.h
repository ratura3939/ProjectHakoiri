#pragma once

#include"../Common/Vector2F.h"

class Camera
{
private:
	Camera(void);	//�R���X�g���N�^

public:
	~Camera(void);	//�f�X�g���N�^
	static void CreateInstance(void);
	static Camera& GetInstance(void);
	
	bool Init(void);
	void Update(void);
	void Relese(void);

	/// <summary>
	/// �����_�̐ݒ�
	/// </summary>
	/// <param name="pPos"></param>
	void SetTargetPos(const Vector2F pPos);

	/// <summary>
	/// �}�b�v�T�C�Y�Z�b�g
	/// </summary>
	/// <param name="mapsize"></param>
	void SetMapSize(const Vector2F mapsize);

	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Vector2F GetPos(void)const;

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void MoveCamera(void);

	static Camera* instance_;

	Vector2F pos_;
	Vector2F localCenterPos_;
	Vector2F targetPos_;
	Vector2F mapSize_;
};

