//	全てのDraw,Logicを管理するクラス
#pragma once
#include "DXUT.h"

class GameMain
{
private:
	//	コピー禁止
	GameMain(const GameMain& obj);
	GameMain& operator = ( const GameMain& obj);
	
	GameMain();

	static GameMain* SharedInstance ;

public:
    ~GameMain();
	inline static GameMain* GetInstance()
	{
		if(!SharedInstance) SharedInstance = new GameMain() ;
		return SharedInstance ;
	}
	inline static void DeleteInstance()
	{
		SAFE_DELETE(SharedInstance) ;
	}

	void Draw(){}
	void Logic(){}
};

