//	�S�ẴV�[�P���X�̐e�N���X(����)

#pragma once
class SequenceBase
{
public:
	SequenceBase(){};
	virtual ~SequenceBase();

	//	�f�[�^�̏����֐�
	virtual void Init() = 0;

	//	�j���֐�
	virtual void DeleteInstance() = 0;

	//	�`��֐�
	virtual void Draw()	= 0;

	//	�����֐�
	virtual void Logic() = 0;
};

