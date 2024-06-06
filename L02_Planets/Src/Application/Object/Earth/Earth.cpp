#include "Earth.h"

void Earth::Init()
{
	m_objType = ObjectType::Earth;
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");
}

void Earth::Update()
{
	static float _yAng;
	_yAng += 0.5f;
	while (_yAng >= 360.0f)
	{
		_yAng -= 360.0f;
	}
	static float _yAng2;
	_yAng2 +=2.5f;
	while (_yAng2 >= 360.0f)
	{
		_yAng2 -= 360.0f;
	}

	//大きさ
	Math::Matrix _mScale = Math::Matrix::CreateScale(1);

	//どれだけ傾けているか
	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng));
	Math::Matrix _mRotationY2 = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_yAng2));

	//基準点(ターゲットからどれだけ離れているか)
	Math::Matrix _mTransPos = Math::Matrix::CreateTranslation(5, 0, 0);

	//カメラのワールド行列を作成、適応させる(行列の親子関係)	
	m_mWorld = (_mScale * _mRotationY2 * _mTransPos * _mRotationY);
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}
