//	�S�ẴV�[�P���X�̐e�N���X(����)

#pragma once
#include <memory>
class Camera ;

class SequenceBase
{
protected:
    //  �J����
    std::shared_ptr<Camera> m_Camera ;

public:
	SequenceBase();
	virtual ~SequenceBase(){};

	//	�f�[�^�̏����֐�
	virtual void Init() = 0;

	//	�j���֐�
	virtual void DeleteInstance() = 0;

	//	�`��֐�
	virtual void Draw()	= 0;

	//	�����֐�
	virtual SequenceBase* Logic() = 0;    

    inline std::shared_ptr<Camera> GetCamera(){ return m_Camera ;}
};

