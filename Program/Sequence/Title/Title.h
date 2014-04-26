//	�V�[�P���X�^�C�g��(SequenceBase�p��,�V���O���g��)

#pragma once
#include "DXUT.h"
#include "../SequenceBase.h"

class Title : 
	public SequenceBase
{
private:
	Title() ;
	~Title();
	//	�R�s�[�֎~
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
