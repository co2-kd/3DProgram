#pragma once

class Earth : public KdGameObject
{
public:
	Earth() {}
	~Earth() override {}

	void Init() override;
	void Update() override;
	void DrawLit() override;

private:
	//ポリゴンデータ
	std::shared_ptr<KdModelData> m_spModel = nullptr;
};