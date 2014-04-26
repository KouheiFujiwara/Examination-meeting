#include "DXUT.h"
#include "font.h"
#include "GlobalD3DDevice.h"
#include "DXconvAnsiToWide.h"


//std::vector<std::shared_ptr<CFont>> CFont::font_list ;

//LPD3DXFONT CFont::m_font ;

//■コンストラクタ
CFont::CFont( int _x_size, int _y_size, const LPCWSTR _fontname )
{
	// 描画範囲
	m_rect.left = 0 ;
	m_rect.top = 0 ;
	m_rect.right = 0 ;
	m_rect.bottom = 0 ;

	// フォントの情報を設定
	m_font_info.Height          = _x_size ;	// フォントの高さ
    m_font_info.Width           = _y_size ;	// フォントの幅
    m_font_info.Weight          = 0 ;
    m_font_info.MipLevels       = 0 ;
    m_font_info.Italic          = FALSE ;
    m_font_info.CharSet         = SHIFTJIS_CHARSET ;
    m_font_info.OutputPrecision = OUT_TT_ONLY_PRECIS ;
    m_font_info.Quality         = DEFAULT_QUALITY ;
    m_font_info.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    lstrcpy(m_font_info.FaceName, _fontname);

	// フォント生成
	D3DXCreateFontIndirect(GlobalD3DDevice::m_pd3dDevice, &m_font_info, &m_font );
	
	// 色情報の初期化
	m_color = 0xCAFFFFFF ;
}


//■生成関数
std::shared_ptr<CFont> CFont::Create( int _x_size, int _y_size, const LPCWSTR _fontname ){
	
	std::shared_ptr<CFont> pf;
	pf.reset( new CFont( _x_size, _y_size, _fontname ) );	
	return pf;

}


//■描画情報のセット
void CFont::setPosCol(  int x, int y, D3DCOLOR col  ){
	
	m_rect.left = x ;
	m_rect.top = y ;
	m_rect.right = 0 ;
	m_rect.bottom = 0 ;

	m_color = col ;
}


//■描画
void CFont::Draw( std::string _string ){
	
	HRESULT hr;

	WCHAR wcBuff[ 255 ] = { 0 } ;
	DXconvAnsiToWide::Change( wcBuff, _string.c_str(), 255 ) ;

	// Render the scene
    if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
    {
		// テキスト描画
		m_font->DrawText(
			NULL,
			wcBuff,	// 描画した文字列 ( WCHAR 指定 )
			-1,
			&m_rect,		// 描画範囲指定
			DT_LEFT | DT_NOCLIP,
			m_color	// 色指定
		);

        V( GlobalD3DDevice::m_pd3dDevice->EndScene() );
    }
	for( int i = 0; i < (int)_string.size(); i++ )
	{
		WCHAR ch = _string[i] ;

		if( ch == '\n' ) 
		{
			m_rect.top = m_rect.top* m_rect.top ;
		}
	}
}

//
//void CFont::DrawFontText(int x, int y, D3DCOLOR col,
//	const wchar_t* pFormat, ...)
//{
//	va_list valist;
//	va_start(valist, pFormat);
//	wchar_t buffer[256] = {0};
//	vswprintf_s(buffer, pFormat, valist);
//
//	m_rect.left = x ;
//	m_rect.top = y ;
//	m_rect.right = 800 ;
//	m_rect.bottom = 600 ;
//
//	sprite->Begin(0);
//	m_font->DrawText(NULL, buffer, -1, &m_rect, 0, col);
//	sprite->End();
//	va_end(valist);
//}