#pragma once
#include "CharacterBase.h"
#include <DxLib.h>

class EnemyBase :
    public CharacterBase
{
public:

	enum class TYPE
	{
		HOUSEMADE,
		SENESCHAL,
		MAX
	};

	enum class VISION_STATE
	{
		MISSING,
		FIND,
		MAX
	};

	//定数
	static constexpr int MOVE_UNIT = 32;	//敵の基礎移動量

	EnemyBase(void);
	~EnemyBase(void)override;

	void Init(void)override;
	void SetParam(void)override;
	void Draw(void)override;
	void Move(void)override;

	void SetIsUse(bool flag);	//敵を使用しているかをセット
	bool IsUse(void);			//敵が使用済みかを確認
	TYPE GetType(void);			//敵の種類を獲得
	void SetIsMove(bool flag);	//動いているかをセット	
	void SetVisionState(VISION_STATE state);	//敵の視覚状態をセット

protected:
	TYPE type_;	//敵のタイプを保持
	bool isUse_;//すでに使用されているかを保持
	Vector2F moveStartPos_;
	int moveLimit_;	//一回での移動マス量
	VECTOR moveDir_;	//動く方向のベクター
	float speed_;

private:
	//視界
	int visionImg_[static_cast<int>(VISION_STATE::MAX)];
	VISION_STATE state_;
	float visionRot_;

	bool isMove_;	//動いているか

	void DrawVision(Vector2F cameraPos);	//視界の描画
	void DecideDir(void);					//方向決め
					
};

