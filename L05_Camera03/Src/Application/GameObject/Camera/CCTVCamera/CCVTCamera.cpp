﻿#include "CCVTCamera.h"
void CCVTCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.f, -10.0f);

	//一旦行列を確定させる
	m_mWorld = m_mLocalPos;
}

void CCVTCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}
	
	//カメラの回転
	UpdateLookAtRotate(_targetMat.Translation());
}

void CCVTCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	Math::Matrix _shadowVP = DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);
	m_mWorld = _shadowVP.Invert();
}
