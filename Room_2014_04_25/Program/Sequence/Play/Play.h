//	�v���C�V�[�P���X(SequenceBase�p��,�V���O���g��)
#pragma once
#include "DXUT.h"
#include "../SequenceBase.h"
#include <memory>

class Play : public SequenceBase
{
private:
    Play(){};
	//	�R�s�[�֎~
	Play(const Play& obj);
	Play& operator = (const Play& obj);
	static Play* SharedInstance ;

public:
	~Play(){}
	inline static Play* GetInstance()
	{		
		if(!SharedInstance)
			SharedInstance = new Play();
		return SharedInstance ;
	}

	inline void DeleteInstance()
	{
		SAFE_DELETE(SharedInstance) ;
	}

	SequenceBase* Logic(){return this;};
	void Draw(){}
	void Init(){}
};

