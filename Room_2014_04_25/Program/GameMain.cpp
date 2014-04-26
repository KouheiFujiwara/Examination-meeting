#include "DXUT.h"
#include "GameMain.h"
#include "Sequence/SequenceManager.h"

//	���Ԃ̐錾
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