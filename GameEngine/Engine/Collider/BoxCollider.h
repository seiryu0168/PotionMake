#pragma once
#include "../Components/Collider.h"


class BoxCollider : public Collider
{
private:
	XMFLOAT3     size_;			//‘å‚«‚³
public:

	BoxCollider();
	BoxCollider(const XMFLOAT3& basePos, const XMFLOAT3& size);
	~BoxCollider();
	void SetSize(const XMFLOAT3& size) { size_ = size; }
	XMFLOAT3 GetSize() const { return size_; }
};