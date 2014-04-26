#include "DXUT.h"
#include "Info.h"
#include "GlobalD3DDevice.h"

using namespace std;

Info::Info( const std::string& FileName )
{
	m_pd3dDevice = GlobalD3DDevice::m_pd3dDevice ;

	//----------------------------------------------------------------------------
	// ファイル名を WCHAR に変換
	WCHAR buff_name[256] = {0} ;
	DXconvAnsiToWide( buff_name, FileName.c_str(), ( FileName.length()+1) ) ;

	//----------------------------------------------------------------------------
	// テクスチャのロード
	D3DXCreateTextureFromFileEx( m_pd3dDevice,
		buff_name,			// ファイルパス
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DXCOLOR(0,0,0,0),	// カラーキーの設定( 透明色 )　※ 全て0指定でカラーキーなし
		&m_image_info,		// 画像情報の取得
		NULL,
		&m_texture			// テクスチャの受け取り
	);
}

HRESULT Info::DXconvAnsiToWide( WCHAR* wstrDest, const CHAR* strSrc, int ct )
{
    // 引数の*がNULLの場合と、文字数が1以下の場合はエラー
    if( wstrDest==NULL || strSrc==NULL || ct < 1 )
        return E_INVALIDARG;

    int nResult = MultiByteToWideChar( CP_ACP, 0, strSrc, -1, wstrDest, ct );
    wstrDest[ct-1] = 0;
    
    if( nResult == 0 )
        return E_FAIL;
    return S_OK;
}