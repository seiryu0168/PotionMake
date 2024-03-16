#pragma once
#include"../ECS/System.h"
#include"../Components/Particle.h"
class ParticleSystem : public System
{
public:
	ParticleSystem();
	~ParticleSystem() {};
	void Update() override;
	void Draw(int layerNum) override;
	void Release() override;
	void CheckRemove() override;
};

