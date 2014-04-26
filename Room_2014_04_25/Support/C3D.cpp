#include "DXUT.h"
#include "C3D.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "C3DTexture.h"
#include "Mesh.h"
#include "../Support/GlobalD3DDevice.h"

#include <sstream>

D3DXVECTOR4 C3D::m_AllDirLight ;
bool C3D::m_LightFlg = true ;

C3D::~C3D()
{
	CGraphicsManager::Erase( this ) ;
}

C3D* C3D::Create( const std::string& _path )
{
	C3D* p =  new C3D() ;
	p->Load( _path ) ;

	//	�����_�����O���X�g�ւ̓o�^
	CGraphicsManager::m_RenderList.push_back( p ) ;
	return p ;
}

void C3D::Load( const std::string &_path ) 
{
	//-------------------------------------------------------------------------
	// X �t�@�C�� �ƃe�N�X�`���̃��[�h
	m_Mesh = Mesh::m_pMesh->Create( _path ) ;

	C3DTexture *Tex = NULL ;

	// �}�e���A�����̎擾
	D3DXMATERIAL *pMaterials = ( D3DXMATERIAL* )( m_Mesh->m_MaterialBuff->GetBufferPointer() ) ;

	//	�Ǝ��e�N�X�`���N���X�Ƃ��Đ���
	std::stringstream ss ;
	WCHAR wcBuff[ 255 ] = { 0 } ;

	for( int i =0; i < (int)m_Mesh->m_MaterialNum ; i++ ) {
		memset( wcBuff, 0, sizeof(WCHAR) * 255 ) ;
		ss.str("") ;
		if( NULL == pMaterials[ i ].pTextureFilename ) {
			Tex = NULL ;
			m_Texs.push_back( NULL ) ;
			continue ;
		}
		ss << "mesh/" << pMaterials[ i ].pTextureFilename ;

		//	�Ǝ��e�N�X�`���N���X�Ƃ��Đ���
		std::string str = ss.str().c_str() ;
		Tex = C3DTexture::m_pC3DTexture->Create( str ) ;

		m_Texs.push_back(Tex) ;
	}
}

D3DXMATRIX C3D::BillBord( D3DXVECTOR3 _Look, D3DXVECTOR3 _Up )
{
	D3DXMATRIX Inv;
    D3DXMatrixIdentity(&Inv);
	//���[�J����0,0,0�̈ʒu���猩�Ă���r���[�s����쐬
    D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0,0,0), &_Look, &_Up);
	//�t�s��쐬
    D3DXMatrixInverse(&Inv, NULL, &Inv);

    return Inv;
}
/*
void C3D::Render( const Camera *_camear )
{
	HRESULT hr ;

	//-------------------------------------------------------------------------
	//
	// ���[���h�}�g���N�X�ݒ�
	//
	D3DXMATRIX SclMtx, RotMtx, PosMtx, WldMtx ;
	D3DXMatrixScaling( &SclMtx, m_Scl.x, m_Scl.y, m_Scl.z ) ;

	if( m_BillFlg ){
		RotMtx = m_RotMtx ;
	}else{
		//	(Y,X,Z�̏���)
		D3DXMatrixRotationYawPitchRoll( &RotMtx, m_Rot.y, m_Rot.x, m_Rot.z ) ;
	}

	D3DXMatrixTranslation( &PosMtx, m_Pos.x, m_Pos.y, m_Pos.z ) ;

	WldMtx = ( SclMtx * RotMtx * PosMtx ) * _camear->m_view * _camear->m_proj ;

	//	�V�F�[�_�ݒ�
	CGraphicsManager::m_sdr->SetTechnique( CGraphicsManager::m_sdr_technique ) ;

	//	�V�F�[�_�Ƀ��[���h�s����킽��
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_wvmp, &WldMtx ) ;

	//	���C�g�v�Z�p��]�s����킽��
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_rot, &RotMtx ) ;
	
	//	���C�g�ݒ�( ���s���� )
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_DirLight ) ;

	//	�V�F�[�_�ɃJ���[���킽��
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &m_Col ) ;

	//-------------------------------------------------------------------------
	//
    // �`�揈��
	//
	// 3D ���f���̃p�[�c�����[�v���ĕ`��
	for( int i = 0; i < m_Mesh->m_MaterialNum; i++ ) {
		//	�e�p�[�c�ɑΉ�����e�N�X�`����ݒ�
		//	�V�F�[�_�Ƀe�N�X�`�����킽��
		if( NULL != m_Texs[ i ] ) {
			CGraphicsManager::m_sdr->SetTexture( CGraphicsManager::m_sdr_tex, m_Texs[ i ]->m_DirecxTex ) ;
		}else{
			CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &D3DXVECTOR4( 0,0,0,0 ) ) ;
		}

		//	�V�F�[�_�̎g�p�J�n
		CGraphicsManager::m_sdr->Begin( NULL, 0 ) ;

		//	�V�F�[�_�̃p�X�ݒ�
		if( !m_IsAddBlend ){
			CGraphicsManager::m_sdr->BeginPass( 0 ) ;
		}else{
			CGraphicsManager::m_sdr->BeginPass( 1 ) ;
		}

		if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
		{
			//	�p�[�c�̕`��
			m_Mesh->m_DirectxMesh->DrawSubset( i ) ;
			V( GlobalD3DDevice::m_pd3dDevice->EndScene() ) ;
		}

		//	�p�X�I��
		CGraphicsManager::m_sdr->EndPass() ;

		//	�V�F�[�_�I��
		CGraphicsManager::m_sdr->End() ;
	}
}
*/

void C3D::Render( const Camera *_camear )
{
	HRESULT hr ;

	//-------------------------------------------------------------------------
	//
	// ���[���h�}�g���N�X�ݒ�
	//
	D3DXMATRIX SclMtx, RotMtx, PosMtx, WldMtx ;

	D3DXMatrixScaling( &SclMtx, m_Scl.x, m_Scl.y, m_Scl.z ) ;

	if( m_BillFlg )
	{
		//	�r���{�[�h
		RotMtx = m_RotMtx ;
	}
	else
	{
		//	XYZ�w��
		D3DXMatrixRotationYawPitchRoll( &RotMtx, m_Rot.y, m_Rot.x, m_Rot.z ) ;
	}

	D3DXMatrixTranslation( &PosMtx, m_Pos.x, m_Pos.y, m_Pos.z ) ;

	WldMtx = ( SclMtx * RotMtx * PosMtx ) * _camear->m_view * _camear->m_proj ;

	//	�V�F�[�_�ݒ�
	CGraphicsManager::m_sdr->SetTechnique( CGraphicsManager::m_sdr_technique ) ;

	//	�V�F�[�_�Ƀ��[���h�s����킽��
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_wvmp, &WldMtx ) ;

	//	���C�g�v�Z�p��]�s����킽��
	if( m_LightFlg )
		CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_rot, &RotMtx ) ;

	if( m_All_SubstanceFlg )
	{
		//	���C�g�ݒ�( ���s���� )
		CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_SubstanceDirLight ) ;
	}
	else
	{
		//	���C�g�ݒ�( ���s���� )
		CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_AllDirLight ) ;
	}

	//	�V�F�[�_�ɃJ���[���킽��
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &m_Col ) ;

	//-------------------------------------------------------------------------
	//
    // �`�揈��
	//
	// 3D ���f���̃p�[�c�����[�v���ĕ`��
	for( int i = 0; i < (int)m_Mesh->m_MaterialNum; i++ ) {
		//	�e�p�[�c�ɑΉ�����e�N�X�`����ݒ�
		//	�V�F�[�_�Ƀe�N�X�`�����킽��
		if( NULL != m_Texs[ i ] ) {
			CGraphicsManager::m_sdr->SetTexture( CGraphicsManager::m_sdr_tex, m_Texs[ i ]->m_DirecxTex ) ;
		}else{
			CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &D3DXVECTOR4( 0,0,0,0 ) ) ;
		}

		//	�V�F�[�_�̎g�p�J�n
		CGraphicsManager::m_sdr->Begin( NULL, 0 ) ;

		//	�V�F�[�_�̃p�X�ݒ�
		if( !m_IsAddBlend ){
			CGraphicsManager::m_sdr->BeginPass( 0 ) ;
		}else{
			CGraphicsManager::m_sdr->BeginPass( 1 ) ;
		}

		if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
		{
			//	�p�[�c�̕`��
			m_Mesh->m_DirectxMesh->DrawSubset( i ) ;
			V( GlobalD3DDevice::m_pd3dDevice->EndScene() ) ;
		}

		//	�p�X�I��
		CGraphicsManager::m_sdr->EndPass() ;

		//	�V�F�[�_�I��
		CGraphicsManager::m_sdr->End() ;
	}
}