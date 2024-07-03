#include "TPSCamera.h"

#include"Application/main.h"
#include"../../Terrain/Terrain.h"
void TPSCamera::Init()
{
	//親クラスの初期化関数呼び出し
	CameraBase::Init();
	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -10.f);

	//マウスカーソルを画面中央に固定する
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

}

void TPSCamera::Update()
{
	m_pos = GetPos();

	//ターゲットの行列
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject>_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラの回転処理
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;

	//============================================================
	//============================================================
	//============================================================
	//↓めり込み防止のための座標補正計算（レイ判定）
	//①当たり判定(レイ判定)用の情報を作成
	KdCollider::RayInfo _rayInfo;
	//レイの発射位置を設定
	_rayInfo.m_pos = GetPos();
	//レイの発射方向を設定(仮)
	_rayInfo.m_dir = Math::Vector3::Down;//一旦初期値を入れている。
	//レイの長さを設定
	_rayInfo.m_range = 1000.f;//一旦初期値を入れている
	//レイの当たり判定をしたいタイプを設定
	_rayInfo.m_type = KdCollider::TypeGround;
	//レイの発射方向を設定
	if (_spTarget)
	{
		//目標地点（キャラクター座標）- 発射地点（カメラ座標）で発射方向を設定
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1f;//目標地点がキャラの足元になっているので少し上げる
		_rayInfo.m_dir = _targetPos - GetPos();
		//レイの長さを補正()
		_rayInfo.m_range = _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}
	//②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject>wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject>_spGameObj = wpGameObj.lock();
		if (_spGameObj)
		{
			std::list<KdCollider::CollisionResult>_retResultList;
			_spGameObj->Intersects(_rayInfo, &_retResultList);

			//③結果を利用して座標を補完する
			//レイに当たったリストから一番近いオブジェクトを検出
			float			_maxOverLap = 0;
			Math::Vector3	_hitPos		= {};
			bool			_hit		 = false;
			for (auto& ret : _retResultList)
			{
				//レイを遮断し、オーバーした長さが一番長い物を探す
				if (_maxOverLap < ret.m_overlapDistance)
				{
					_maxOverLap = ret.m_overlapDistance;
					_hitPos		= ret.m_hitPos;
					_hit		= true;
				}
			}
			//trueなら何かしらの障害物に当たっている
			if (_hit)
			{
				//カメラが地面にめり込んで地面が透けてしまわないように座標を補正
				Math::Vector3 _hoseiPos = _hitPos;
				_hoseiPos += _rayInfo.m_dir * 0.4f;
				SetPos(_hoseiPos);//上の処理で受け取った一番近い位置
			}
		}
	}


	//============================================================
	//============================================================
	//============================================================
	

	//親クラスの更新呼び出し
	CameraBase::Update();

}
