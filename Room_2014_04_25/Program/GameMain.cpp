#include "DXUT.h"
#include "GameMain.h"
#include "Sequence/SequenceManager.h"

//	À‘Ô‚ÌéŒ¾
GameMain* GameMain::SharedInstance;

GameMain::GameMain()
{
	SequenceManager::GetInstance() ;
}

GameMain::~GameMain()
{
    SequenceManager::DeleteInstance();
}