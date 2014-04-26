#pragma once
#include <vector>

#define Beam (10) 

class C2D ;

class UINumber
{
private:
	C2D* m_Number ;
	D3DXVECTOR3 m_BasePos ;
	float m_Interval ;

public:
	UINumber( const std::string& _FileName, const D3DXVECTOR3& _BasePos, const float _Interval ) ;
	~UINumber(){ SAFE_DELETE( m_Number ) ; }

	void Draw( int _Num ) ;
};

