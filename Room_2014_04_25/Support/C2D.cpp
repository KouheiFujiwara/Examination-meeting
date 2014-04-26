#include "DXUT.h"
#include "C2D.h"
#include "Texture.h"
#include "GlobalD3DDevice.h"

using namespace std;

C2D::C2D( const string& FileName,int num ) 
{
	//	���W
	m_pos = D3DXVECTOR3( 0,0,0 ) ;

	m_sclFloat = 1.0f ;
	m_pd3dDevice = GlobalD3DDevice::m_pd3dDevice ;

	Texture* pObj ;
	pObj = new Texture() ;
	m_texture = pObj->Load( FileName ) ;

	// �e�N�X�`������T�[�t�F�C�X���擾
	IDirect3DSurface9 *pSurface;
	m_texture->GetSurfaceLevel( 0, &pSurface );

	// �T�[�t�F�C�X��񂩂�摜�T�C�Y���擾
	D3DSURFACE_DESC SurfaceInfo;
	pSurface->GetDesc( &SurfaceInfo );

	// �摜�̂ǂ͈̔͂�`�悷�邩���w��( �摜�S�̂��w�� )
	m_rect.left = 0 ;
	m_rect.top = 0 ;
	m_rect.right = SurfaceInfo.Width / num ;
	m_rect.bottom = SurfaceInfo.Height ;

	// �T�[�t�F�C�X�̃T�C�Y( 2 �̗ݏ�T�C�Y )
	m_suf_size = D3DXVECTOR3( (float)SurfaceInfo.Width / num , (float)SurfaceInfo.Height, 0.0f ) ;

	// �摜�{���̃T�C�Y
	m_img_size = D3DXVECTOR3( (float)pObj->m_image_info.Width / num , (float)pObj->m_image_info.Height, 0.0f ) ;

	// 2D �̒��S
	m_center = D3DXVECTOR3( ( m_suf_size.x * 0.5f ), ( m_suf_size.y * 0.5f ), 0.0f ) ;
	//m_center = D3DXVECTOR3(  m_suf_size.x * 0.5f, m_suf_size.y, 0.0f ) ;
	// 2 �̗ݏ�T�C�Y���� �{���̉摜�T�C�Y�ɂ���̂ɕK�v�Ȕ{��
	m_scale_ofs = D3DXVECTOR3( ( m_img_size.x / m_suf_size.x), ( m_img_size.y / m_suf_size.y), 1.0f ) ;

	// �X�P�[��
	m_scl = D3DXVECTOR3( 1 * m_sclFloat, 1 * m_sclFloat, 1 * m_sclFloat ) ;

	// ��]�p�x( �f�O���[ )
	m_rot = 0.0f ;

	// �����x
	m_alpha = 255.0f ;

	// ���Z�������t���O
	m_is_add_alpha = false ;

	// �g�k�t���O
	m_scl_flg = true ;

	// �g���I������̂ŃT�[�t�F�C�X���͊J��
	SAFE_RELEASE( pSurface ) ;

	// �X�v���C�g�̐���
	D3DXCreateSprite( m_pd3dDevice, &m_sprite ) ;
	delete pObj ;
}

C2D::~C2D()
{
	//	�X�v���C�g�̉��
	SAFE_RELEASE( m_sprite ) ;
	//	�e�N�X�`���̉��
	SAFE_RELEASE( m_texture ) ;
}

void C2D::Draw( bool AnimeFlg , int num )
{

	m_scl = D3DXVECTOR3( 1 * m_sclFloat, 1 * m_sclFloat, 1 * m_sclFloat ) ;

	//	��񒆌p������
	RECT m_masu;

	//	num���������ăA�j���[�V����������
	if( AnimeFlg ) {
		m_masu.top = m_rect.top ;
		m_masu.bottom = m_rect.bottom ;
		m_masu.left = m_rect.right * num ;
		m_masu.right = m_rect.right * ( num + 1 ) ;
	}

	//---------------------------------------------------------------------------------
	//
	// ���[���h�s��Ɋւ�����
	//
	D3DXMATRIX wm, tm, sm, rm ;

	// �g�����X���[�V����( ���s�ړ� ) �s��̍쐬
	D3DXMatrixTranslation( &tm, m_pos.x, m_pos.y, m_pos.z ) ;

	// �X�P�[��( �g�k ) �s��̍쐬
	D3DXMatrixScaling( &sm, ( m_scl.x * m_scale_ofs.x ), ( m_scl.y * m_scale_ofs.y ), 1.0f ) ;

	// ���[�e�[�V����( ��] ) �s��̍쐬 
	// �� ����� 2D�Ȃ̂� Z��]�̂�
	D3DXMatrixRotationZ( &rm, D3DXToRadian( m_rot ) ) ;

	//�y !�d�v! �z���[���h�s��̎Z�o 
	// DirectX �ł� ���[���h�s��̎Z�o��
	// �X�P�[�� * ���[�e�[�V���� * �g�����X���[�V���� �̏��ōs��
	wm = sm * rm * tm ;

	// �X�v���C�g�Ƀ��[���h�s���ݒ�
	m_sprite->SetTransform( &wm ) ;

	//----------------------------------------------------------------------------------
	//
	// ���Z�u�����h�̐ݒ�
	//
	if( m_is_add_alpha ){
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ) ;
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 ) ;
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ;
		m_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD ) ;
		m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
		m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE ) ;
	}
	//----------------------------------------------------------------------------------
	//
	// �ŏI�I�ȕ`��
	//

	// �f�o�C�X�̕`�揀��
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
		// �X�v���C�g�̕`�揀��
		m_sprite->Begin( D3DXSPRITE_ALPHABLEND ) ;
		if( AnimeFlg ){
			// �X�v���C�g�̕`�施��
			m_sprite->Draw(	m_texture,	// �`��Ɏg�p����e�N�X�`��
							&m_masu,		// �摜�̕`��͈�
							&m_center,	// �T�[�t�F�C�X�̒��S
							&D3DXVECTOR3(0,0,0),	// �`����W( �s��Ő��䂷��̂� 0,0,0 �łn�j )
							D3DCOLOR_ARGB( (int)( m_alpha ), 255, 255, 255 )	// �F
						)  ;
		}else{
			m_sprite->Draw(	m_texture,	// �`��Ɏg�p����e�N�X�`��
							&m_rect,		// �摜�̕`��͈�
							&m_center,	// �T�[�t�F�C�X�̒��S
							&D3DXVECTOR3(0,0,0),	// �`����W( �s��Ő��䂷��̂� 0,0,0 �łn�j )
							D3DCOLOR_ARGB( (int)( m_alpha ), 255, 255, 255 )	// �F
						)  ;
		}

		// ���Z�؂�ւ�
		if( m_is_add_alpha ){
			m_sprite->Flush() ;
		}else{
			m_sprite->End() ;
		}

		// �`��I��
        ( m_pd3dDevice->EndScene() );
	}
}