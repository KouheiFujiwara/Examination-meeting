//	�V�[�P���X����ւ����Ǘ�����N���X(����)
#pragma once
#include "DXUT.h"
#include <memory>

class SequenceBase ;

class SequenceManager
{
private:
	SequenceManager();
	~SequenceManager();
	//	�R�s�[�֎~
	SequenceManager(const SequenceManager& obj);
	SequenceManager& operator = (const SequenceManager& obj);

	static SequenceManager* SharedInstance ;

	std::shared_ptr<SequenceBase> m_NowSequence;	//	���݂̃V�[�P���X�I�u�W�F�N�g
	std::shared_ptr<SequenceBase> m_NextSequence;	//	���̃V�[�P���X�I�u�W�F�N�g

	bool m_ChangeSequence;	//	�V�[�P���X���ړ����邩�@true(�ړ�����) false(�ړ����Ȃ�)

public:
	inline static SequenceManager* GetInstance()
	{
		if(!SharedInstance) 
			SharedInstance = new SequenceManager();
		return SharedInstance ;
	}
	inline static void DeleteInstance()
	{
		SAFE_DELETE(SharedInstance) ;
	}

	void Logic();
	void Draw();

	//	���̃V�[�P���X�����߂�֐�
	//�@arg1...���̃V�[�P���X�I�u�W�F�N�g
	void SetNextSequence( const std::shared_ptr<SequenceBase> NextSequence ) ;

	//	�V�[�P���X�����ւ���֐�
	void ChangeSequence() ;

};

