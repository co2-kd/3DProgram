#pragma once

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;
	void DrawSprite()		override;

	void SetCamera(std::shared_ptr<KdCamera>camera) { m_wpCamera = camera; }

private:
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
	std::weak_ptr<KdCamera> m_wpCamera;
	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Rectangle m_Rect;
	Math::Color m_Color;


};