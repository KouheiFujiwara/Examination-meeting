#include "DXUT.h"
#include "GameMain.h"
#include "Sequence/SequenceManager.h"

//	ŽÀ‘Ô‚ÌéŒ¾
GameMain* GameMain::SharedInstance;

GameMain::GameMain()
{
	SequenceManager::GetInstance() ;
}

GameMain::~GameMain()
{
    SequenceManager::DeleteInstance();
}

void GameMain::Draw()
{
    SequenceManager::GetInstance()->Draw();
}

void GameMain::Logic()
{
    SequenceManager::GetInstance()->Logic();
}