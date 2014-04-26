#include "DXUT.h"
#include "HitJudgments.h"

HitJudgments* HitJudgments::SharedInstance = 0 ;

D3DXVECTOR3 HitJudgments::ClosestPtPointSegment( const D3DXVECTOR3 _center, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos )
{
	D3DXVECTOR3 SEpos = _Epos - _Spos ;
	D3DXVECTOR3 CSpos = _center - _Spos ;

	float t = 0.0f ;
	//	�p�����[�^������Ă���ʒud(t) = a + t * ( b - a ) �̌v�Z�ɂ��ab���ˉe
	t = D3DXVec3Dot( &CSpos, &SEpos ) / D3DXVec3Dot( &SEpos, &SEpos ) ;

	//	�����̊O���ɂ���ꍇ�At(����������d)���ŋߐړ_�܂ŃN�����v
	if( t < 0.0f ) t = 0.0f ;
	if( t > 1.0f ) t = 1.0f ;

	//	�N�����v����Ă���t����̎ˉe����Ă���ʒu���v�Z
	return _Spos + t * SEpos ;
}

D3DXVECTOR3 HitJudgments::CircleLineCollideCompensation(
	 	const D3DXVECTOR3 _center,
		const float _rad, 
		const D3DXVECTOR3 _Spos, 
		const D3DXVECTOR3 _Epos
	)
{
	//	�X�^�[�g���W�ƃG���h���W�̃x�N�g��
	D3DXVECTOR3 StartEndVec		= _Epos - _Spos ;

	//	�x�N�g���𐳋K��
	D3DXVECTOR3 Dir ;
	D3DXVec3Normalize( &Dir, &StartEndVec ) ;

	//�@�X�^�[�g���W�Ƌ��̍��W�̃x�N�g��
	D3DXVECTOR3 StartCenterVec	= _Spos - _center ;

	float t = 0.0f ;
	D3DXVECTOR3 p = D3DXVECTOR3( 0,0,0 ) ;

	//	�ŋߐړ_�����
	D3DXVECTOR3 LineNear = ClosestPtPointSegment( _center, _Spos, _Epos ) ;
	D3DXVECTOR3 CompDir = _center - LineNear ;
	CompDir.y = 0.0f ;
	D3DXVec3Normalize( &CompDir, &CompDir ) ;

	float b = D3DXVec3Dot( &StartCenterVec, &Dir ) ;
	float c = D3DXVec3Dot( &StartCenterVec, &StartCenterVec ) - _rad * _rad;
	float Length = D3DXVec3Length( &StartEndVec ) ;

	if( c > 0.0f && b > 0.0f )  return _center ;
	float Discr = b * b - c ;

	if( Discr < 0.0f ) return _center ;
	t = -b - sqrt( Discr ) ;

	if( t < 0.0f ) t = 0.0f ;
	p = _Spos + t * Dir ;


	float length  = D3DXVec3Length( &StartEndVec ) ;
	if( t >= 0.0f && t <= Length )
	{
		return LineNear + ( CompDir * _rad ) ;
	}

	return _center ;

}


bool HitJudgments::IntersectSphereRay( float _sr, D3DXVECTOR3 _sp, D3DXVECTOR3 _rp, D3DXVECTOR3 _rv ) 
{
	D3DXVECTOR3 u = _rp - _sp;

    float a = D3DXVec3Dot( &_rv, &_rv );
    float b = D3DXVec3Dot( &_rv, &u );
    float c = D3DXVec3Dot( &u, &u ) - _sr ;

    if ( a - 0.00001f <= 0.0f ) {
        return false;
    }

    float isColli = b * b - a * c;
    if ( isColli < 0.0f ) {
        return false;
    }

    return true;
}

Ray HitJudgments::ScreenToRay( int _sx, int _sy, D3DXMATRIX _view, D3DXMATRIX _proj, IDirect3DDevice9* _p_deviece )
{
	// �r���[�|�[�g�s����쐬
    D3DXMATRIX vpMat;
    D3DXMatrixIdentity( &vpMat );

    D3DVIEWPORT9 vp;
    _p_deviece->GetViewport( &vp );

    vpMat._11 = (float)vp.Width * 0.5f ;
    vpMat._22 = -1.0f * (float)(vp.Height * 0.5f);
    vpMat._33 = (float)vp.MaxZ - vp.MinZ;
    vpMat._41 = (float)( vp.X + vp.Width * 0.5f );
    vpMat._42 = (float)( vp.Y + vp.Height * 0.5f );
    vpMat._43 = vp.MinZ;

    // �X�N���[���ʒu�����[���h��
	D3DXVECTOR3 vz0, vz1 ;
	vz0 = D3DXVECTOR3( _sx, _sy, 0.0f ) ;
	vz1 = D3DXVECTOR3( _sx, _sy, 1.0f ) ;

    D3DXMATRIX invMat, inv_proj, inv_view;
    D3DXMatrixInverse( &invMat, 0, &vpMat );
    D3DXMatrixInverse( &inv_proj, 0, &_proj );
    D3DXMatrixInverse( &inv_view, 0, &_view );
    invMat *= inv_proj * inv_view;

	D3DXVec3TransformCoord( &vz0, &vz0, &invMat );
	D3DXVec3TransformCoord( &vz1, &vz1, &invMat );

	Ray ret ;
	ret.p = vz0 ;
	D3DXVec3Normalize( &ret.v, &( vz1 - vz0 ) ) ;

    return ret ;
}