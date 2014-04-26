#include "DXUT.h"
#include "SequenceManager.h"
#include "Play/Play.h"
#include "Title/Title.h"
#include "../../Support/Fade.h"
#include "../../Support/Camera.h"

SequenceManager* SequenceManager::SharedInstance ;

SequenceManager::SequenceManager()
{
	m_NowSequence = Title::GetInstance() ;
}

SequenceManager::~SequenceManager()
{
    m_NowSequence->DeleteInstance();

    if(m_NextSequence != NULL)
        m_NextSequence = NULL ;
}

void SequenceManager::SetNextSequence(SequenceBase* NextSequence)
{
	//	シーケンス移動フラグをon
	m_ChangeSequence = true;

	//	次のシーケンスを予約
	m_NextSequence = NextSequence;

	//	フェードアウトスタート
	Fade::GetInstance()->Start();
}

void SequenceManager::ChangeSequence()
{
	//	現在シーケンス変動中のためフェードインはしない
	Fade::GetInstance()->GetNewDelete(false);

	//	現在のシーケンスを解放
	m_NowSequence->DeleteInstance() ;

	//	予約さてれいたシーケンスに移行
	m_NowSequence = m_NextSequence ;

	//	シーケンスを初期化
	m_NowSequence->Init();

	//	全ての入れ替えが終わったならフェードインをする
	Fade::GetInstance()->GetNewDelete( true ) ;

	//	予約シーケンス中身をカラにする
	m_NextSequence = NULL ;

	//	シーケンス移動フラグをfalseに
	m_ChangeSequence = false ;
}

void SequenceManager::Draw()
{
	m_NowSequence->Draw();

    if(Fade::GetInstance()->AlphaComplate() && m_ChangeSequence )
        ChangeSequence() ;

    //  カメラのアップデート
    m_NowSequence->GetCamera()->UpData() ;
}

void SequenceManager::Logic()
{
    m_NowSequence = m_NowSequence->Logic();

}
