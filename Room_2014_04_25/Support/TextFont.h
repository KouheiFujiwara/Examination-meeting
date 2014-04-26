//	テキストクラス
#pragma once
#include "DXUT.h"
#include <string>

class TextFont
{
private:
	LPD3DXFONT *m_pFont ;
public:
	static TextFont* m_pTextFont ;

	TextFont() :
	  m_pFont(NULL) {}
	~TextFont();

	void TextDraw(LPD3DXFONT _pFont, std::string _text, D3DXVECTOR3 _Pos ) ;
};

