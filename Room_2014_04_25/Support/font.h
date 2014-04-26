#pragma once
#include <string>
#include <vector>
#include <memory>

class CFont{
private:
	

	// フォント
	LPD3DXFONT m_font ;

	// フォント情報( この情報を元にフォントを作る )
	D3DXFONT_DESC m_font_info ;
	
	RECT m_rect;

	D3DCOLOR m_color ;

	//コンストラクタ
	CFont( int _x_size, int _y_size, const LPCWSTR _fontname ) ;
	

public:

	//デストラクタ
	~CFont(){SAFE_RELEASE(m_font) ;}

	void Destroy(){
		SAFE_RELEASE(m_font) ;
	}

	//文字サイズ縦横、フォント名
	static std::shared_ptr<CFont> Create( int _x_size, int _y_size, const LPCWSTR _fontname ) ;

	//描画座標、カラpー
	void setPosCol( int x, int y, D3DCOLOR col ) ;
	
	//描画
	void Draw( std::string _string );

	////テキスト描画
	//void DrawFontText(int x, int y, D3DCOLOR col,
	//	const wchar_t* pFormat, ...);	
};
