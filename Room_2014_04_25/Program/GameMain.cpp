#include "DXUT.h"
#include "GameMain.h"
#include "Sequence/SequenceManager.h"

//	���Ԃ̐錾
GameMain* GameMain::SharedInstance;

GameMain::GameMain()
{
	SequenceManager::GetInstance() ;
}