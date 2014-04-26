#pragma once

//	�����p
struct Ray
{
	D3DXVECTOR3 p ;	// ������ɑ��݂���_
	D3DXVECTOR3 v ; // �����̌���
} ;

class HitJudgments
{
private:
	HitJudgments(){};
	~HitJudgments(){};

	HitJudgments( const HitJudgments& obj ) ;
	HitJudgments& operator = ( const HitJudgments& obj ) ;

	static HitJudgments* SharedInstance ;

public:
	static inline HitJudgments* GetInstance()
	{
		if( SharedInstance == NULL )
			SharedInstance = new HitJudgments() ;
		return SharedInstance ;
	}

	static inline void DeleteInstance(){ SAFE_DELETE(SharedInstance) ; }

	//---------------------------------------------------------------------------------------------------------
	//										�~�Ɛ��̏Փ˔���
	//	�߂�l: bool�^ 
	//	<����>
	//	_center		���̒����̍��W
	//	_rad		���̔��a
	//	_Spos		���̃X�^�[�g���C��
	//	_Epos		���̃G���h���C��
	//static bool CircleLineCollide( const D3DXVECTOR3 _center, const float _rad, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//---------------------------------------------------------------------------------------------------------
	//										�����Ɠ_�̍ŋߐړ_
	//	�߂�l: 
	static D3DXVECTOR3 ClosestPtPointSegment( const D3DXVECTOR3 _center, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//---------------------------------------------------------------------------------------------------------
	//										�~�Ɛ��̏Փ˔���ƕ␳
	//	�߂�l: bool�^ 
	//	<����>
	//	_center		���̒����̍��W
	//	_rad		���̔��a
	//	_Spos		���̃X�^�[�g���C��
	//	_Epos		���̃G���h���C��
	static D3DXVECTOR3 CircleLineCollideCompensation( const D3DXVECTOR3 _center, const float _rad, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//===========================================================================================
	// ���Ɩ������C�̏Փ˔���
	// arg1... ���̔��a
	// arg2... ���̒��S���W
	// arg3... ���C��ɑ��݂�����W
	// arg4... ���C�̕����x�N�g��
	// ret.... [ �Փ˂��Ă��� : true ] [ �Փ˂��Ă��Ȃ�: true ]
	//===========================================================================================
	bool IntersectSphereRay( float _sr, D3DXVECTOR3 _sp, D3DXVECTOR3 _rp, D3DXVECTOR3 _rv ) ;


	//===========================================================================================
	// name... ScreenToRay
	// work... �X�N���[�����W�̎w��Ń��C���쐬����
	// arg1... �X�N���[����̍��W X
	// arg2... �X�N���[����̍��W Y
	// arg5... �J�����̃r���[�s��
	// arg6... �J�����̃v���W�F�N�V�����s��
	// arg7... DirectX �ւ̃f�o�C�X
	// ret.... ���Z����
	// note... none
	//===========================================================================================
	Ray ScreenToRay( int _sx, int _sy, D3DXMATRIX _view, D3DXMATRIX _proj, IDirect3DDevice9* _p_deviece ) ;
};

