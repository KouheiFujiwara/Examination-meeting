#pragma once
#include <memory>

class Camera ;

class BaseObj
{
public:
	//	���Z�t���O
	bool m_IsAddBlend ;

	//	���̂̔��a
	float		m_Rad ;

	D3DXVECTOR3 m_Pos ;		//	���W
	D3DXVECTOR3 m_Scl ;		//	�g��k��
	D3DXVECTOR3 m_Rot ;		//	XYZ�w��
	D3DXQUATERNION m_Qtn ;	//	�p��
	D3DXVECTOR4 m_Col ;

	D3DXMATRIX m_RotMtx ;	//	�r���{�[�h�ɂ̂ݎg��

	//	�����͂���ړ�����
	D3DXVECTOR3 m_Dir ;

	friend class CGraphicsManager ;

	//	�\�[�g�̊�ƂȂ�l(�J�����̋���)
	float m_CameraDistance ;

	//	�r���{�[�h
	bool m_BillFlg ;

	BaseObj() :
		m_IsAddBlend( false ),
		m_Pos( 0, 0, 0 ),
		m_Scl( 1, 1, 1 ),
		m_Col( 1, 1, 1, 1 ),
		m_BillFlg(false),
		m_Rot( 0, 0, 0 ) 
	{
		D3DXQuaternionIdentity( &m_Qtn ) ;
	}

	// �p������̂� virtual
	virtual ~BaseObj(){};

	// �������z�֐�
	virtual void Render( const Camera* _camera ) = 0 ;

	// std::list �̃\�[�g�Ŏg�p����
	static bool comp(const BaseObj* riLeft, const BaseObj* riRight){
		return ( riLeft->m_CameraDistance > riRight->m_CameraDistance ) ;
    }
};