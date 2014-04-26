//	�v���C�V�[�P���X(SequenceBase�p��,�V���O���g��)
#pragma once
#include "DXUT.h"
#include "../SequenceBase.h"

class Play : public SequenceBase
{
private:
	Play();
	~Play();
	//	�R�s�[�֎~
	Play(const Play& obj);
	Play& operator = (const Play& obj);
	static Play* SharedInstance ;

public:
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

	void Logic(){}
	void Draw(){}
	void Init(){}
};

