//	全てのシーケンスの親クラス(抽象)

#pragma once
#include <memory>
class Camera ;

class SequenceBase
{
protected:
    //  カメラ
    std::shared_ptr<Camera> m_Camera ;

public:
	SequenceBase();
	virtual ~SequenceBase(){};

	//	データの初期関数
	virtual void Init() = 0;

	//	破棄関数
	virtual void DeleteInstance() = 0;

	//	描画関数
	virtual void Draw()	= 0;

	//	処理関数
	virtual SequenceBase* Logic() = 0;    

    inline std::shared_ptr<Camera> GetCamera(){ return m_Camera ;}
};

