#include "CCVTCamera.h"

void CCVTCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.0f);
}

void CCVTCamera::PostUpdate()
{
}
