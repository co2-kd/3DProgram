#pragma once

class Moon : public KdGameObject
{
public:
	Moon() {}
	~Moon() override {}

	void Init() override;
	void Update() override;
	void DrawLit() override;

	void SetPos(const Math::Vector3& pos) override { m_pos = pos; }

private:
	//ポリゴンデータ
	std::shared_ptr<KdModelData> m_spModel = nullptr;
	Math::Vector3 m_pos;
};