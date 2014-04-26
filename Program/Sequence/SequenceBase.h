//	全てのシーケンスの親クラス(抽象)

#pragma once
class SequenceBase
{
public:
	SequenceBase(){};
	virtual ~SequenceBase();

	//	データの初期関数
	virtual void Init() = 0;

	//	破棄関数
	virtual void DeleteInstance() = 0;

	//	描画関数
	virtual void Draw()	= 0;

	//	処理関数
	virtual void Logic() = 0;
};

