#include "DXUT.h"
#include "SequenceBase.h"
#include "../../Support/Camera.h"


SequenceBase::SequenceBase()
{
    m_Camera.reset(new Camera());
}