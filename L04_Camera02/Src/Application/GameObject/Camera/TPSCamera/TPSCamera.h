#pragma once
#include"../CameraBase.h"

class TPSCamera : public CameraBase
{
public:
	TPSCamera() {}
	~TPSCamera()override {}

	void Init()override;
	void Update()override;

	void SetTerrain(std::shared_ptr<KdGameObject>terrain) { m_wpTerrain = terrain; }

private:
	Math::Vector3 m_pos = {};
	std::weak_ptr<KdGameObject> m_wpTerrain;
};