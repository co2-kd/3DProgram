#pragma once

class HamuHamu : public KdGameObject
{
public:
	HamuHamu();
	~HamuHamu() override;

	void Init() override;
	void Update() override;
	void DrawLit() override;

private:
	//ポリゴンデータ
	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
};