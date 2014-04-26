//	シーケンスタイトル(SequenceBase継承,シングルトン)

#pragma once
#include "DXUT.h"
#include "../SequenceBase.h"

class Title : 
	public SequenceBase
{
private:
	Title() ;
	~Title();
	//	コピー禁止
	Title(const Title& obj) ;
	Title& operator = (const Title& obj);

	static Title* SharedInstance ;

public:
	inline static Title* GetInstance()
	{
		if(!SharedInstance)
			SharedInstance = new Title() ;
		return SharedInstance ;
	}
	inline void DeleteInstance() 
	{
		SAFE_DELETE(SharedInstance) ;
	}
	SequenceBase* Logic(){}
	void Draw(){}
	void Init(){}
};
