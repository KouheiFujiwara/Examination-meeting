//	���_���W

#pragma once

class CVertex 
{
public:
	CVertex(){} ;
	~CVertex();
	//-------------------------------------------------------------
	//	�錾�̏��Ԃ͂��̂Ƃ���(���W�A�@���AUV���W�A�J���[) 
	//
	D3DXVECTOR3	m_Pos ;			//	���W
	D3DXVECTOR3 m_NormalLine ;	//	�@��
	D3DXVECTOR2 m_UV ;			//	UV���W(��F�݂̂ł̃e�N�X�`��)
	D3DXVECTOR4 m_Color ;		//	�J���[		

	static CVertex* m_pCVertex ;
};

