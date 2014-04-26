#include "DXUT.h"
#include "SequenceManager.h"
#include "Play/Play.h"
#include "Title/Title.h"
#include "../../Support/Fade.h"

SequenceManager* SequenceManager::SharedInstance ;

SequenceManager::SequenceManager()
{
	m_NowSequence = Title::GetInstance() ;
}

SequenceManager::~SequenceManager()
{
	SAFE_DELETE(m_NowSequence);
}

void SequenceManager::SetNextSequence(SequenceBase* NextSequence)
{
	//	�V�[�P���X�ړ��t���O��on
	m_ChangeSequence = true;

	//	���̃V�[�P���X��\��
	m_NextSequence = NextSequence;

	//	�t�F�[�h�A�E�g�X�^�[�g
	Fade::GetInstance()->Start();
}

void SequenceManager::ChangeSequence()
{
	//	���݃V�[�P���X�ϓ����̂��߃t�F�[�h�C���͂��Ȃ�
	Fade::GetInstance()->GetNewDelete(false);

	//	���݂̃V�[�P���X�����
	m_NowSequence->DeleteInstance() ;

	//	�\�񂳂Ăꂢ���V�[�P���X�Ɉڍs
	m_NowSequence = m_NextSequence ;

	//	�V�[�P���X��������
	m_NowSequence->Init();

	//	�S�Ă̓���ւ����I������Ȃ�t�F�[�h�C��������
	Fade::GetInstance()->GetNewDelete( true ) ;

	//	�\��V�[�P���X���g���J���ɂ���
	m_NextSequence = NULL ;

	//	�V�[�P���X�ړ��t���O��false��
	m_ChangeSequence = false ;
}

void SequenceManager::Draw()
{
	m_NowSequence->Draw();
}

void SequenceManager::Logic()
{
	m_NowSequence = m_NowSequence->Logic();
}
