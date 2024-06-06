#include "Moon.h"

void Moon::Init()
{
	m_objType = ObjectType::Moon;
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
}

void Moon::Update()
{
	static float _yAng;
	_yAng += 3.5f;
	while (_yAng >= 360.0f)
	{
		_yAng -= 360.0f;
	}
	static float _yAng2;
	_yAng2 += 2.5f;
	while (_yAng2 >= 360.0f)
	{
		_yAng2 -= 360.0f;
	}
	//static float _zAng;
	//_zAng += 0.5f;
	//while (_zAng >= 360.0f)
	//{
	//	_zAng -= 360.0f;
	//}

	//大きさ
	Math::Matrix _mScale = Math::Matrix::CreateScale(1);

	//どれだけ傾けているか
	Math::Matrix _mErathRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng2));

	//基準点(ターゲットからどれだけ離れているか)
	Math::Matrix _mErathTransPos = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _mTransPos = Math::Matrix::CreateTranslation(2,0,0);


	//カメラのワールド行列を作成、適応させる(行列の親子関係)	
	m_mWorld = ((_mScale * _mTransPos * _mRotationY) /** _mErathRotationY*/ * _mErathTransPos);
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}
