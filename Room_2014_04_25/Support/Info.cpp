#include "DXUT.h"
#include "Info.h"
#include "GlobalD3DDevice.h"

using namespace std;

Info::Info( const std::string& FileName )
{
	m_pd3dDevice = GlobalD3DDevice::m_pd3dDevice ;

	//----------------------------------------------------------------------------
	// �t�@�C������ WCHAR �ɕϊ�
	WCHAR buff_name[256] = {0} ;
	DXconvAnsiToWide( buff_name, FileName.c_str(), ( FileName.length()+1) ) ;

	//----------------------------------------------------------------------------
	// �e�N�X�`���̃��[�h
	D3DXCreateTextureFromFileEx( m_pd3dDevice,
		buff_name,			// �t�@�C���p�X
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DXCOLOR(0,0,0,0),	// �J���[�L�[�̐ݒ�( �����F )�@�� �S��0�w��ŃJ���[�L�[�Ȃ�
		&m_image_info,		// �摜���̎擾
		NULL,
		&m_texture			// �e�N�X�`���̎󂯎��
	);
}

HRESULT Info::DXconvAnsiToWide( WCHAR* wstrDest, const CHAR* strSrc, int ct )
{
    // ������*��NULL�̏ꍇ�ƁA��������1�ȉ��̏ꍇ�̓G���[
    if( wstrDest==NULL || strSrc==NULL || ct < 1 )
        return E_INVALIDARG;

    int nResult = MultiByteToWideChar( CP_ACP, 0, strSrc, -1, wstrDest, ct );
    wstrDest[ct-1] = 0;
    
    if( nResult == 0 )
        return E_FAIL;
    return S_OK;
}