﻿#pragma once
#include "../CameraBase.h"

class CCVTCamera : public CameraBase
{
public:
	CCVTCamera() {}
	~CCVTCamera()			override {}

	void Init()				override;
	void PostUpdate()		override;
};