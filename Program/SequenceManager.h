//	シーケンス入れ替えを管理するクラス(抽象)
#pragma once
#include "DXUT.h"
#include <memory>

class SequenceBase ;

class SequenceManager
{
private:
	SequenceManager();
	~SequenceManager();
	//	コピー禁止
	SequenceManager(const SequenceManager& obj);
	SequenceManager& operator = (const SequenceManager& obj);

	static SequenceManager* SharedInstance ;

	std::shared_ptr<SequenceBase> m_NowSequence;	//	現在のシーケンスオブジェクト
	std::shared_ptr<SequenceBase> m_NextSequence;	//	次のシーケンスオブジェクト

	bool m_ChangeSequence;	//	シーケンスを移動するか　true(移動する) false(移動しない)

public:
	inline static SequenceManager* GetInstance()
	{
		if(!SharedInstance) 
			SharedInstance = new SequenceManager();
		return SharedInstance ;
	}
	inline static void DeleteInstance()
	{
		SAFE_DELETE(SharedInstance) ;
	}

	void Logic();
	void Draw();

	//	次のシーケンスを決める関数
	//　arg1...次のシーケンスオブジェクト
	void SetNextSequence( const std::shared_ptr<SequenceBase> NextSequence ) ;

	//	シーケンスを入れ替える関数
	void ChangeSequence() ;

};

