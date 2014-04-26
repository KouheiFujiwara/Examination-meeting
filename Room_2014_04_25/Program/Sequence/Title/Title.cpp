#include "DXUT.h"
#include "Title.h"
#include "../Play/Play.h"
#include "../SequenceManager.h"
Title* Title::SharedInstance;

SequenceBase* Title::Logic()
{
    if(DXUTWasKeyPressed(VK_RETURN) )
        SequenceManager::GetInstance()->SetNextSequence(Play::GetInstance());
    return this ;
}