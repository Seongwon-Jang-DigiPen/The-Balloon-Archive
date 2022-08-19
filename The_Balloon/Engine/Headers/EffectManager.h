/*
File Name: EffectManager.h
Project Name: The balloon
Author(s)
Main:Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <vector>
#include "Effect.h"
class EffectManager
{

public:
	~EffectManager()
	{
		Clear();
	}

	void UpdateAll(double dt)
	{
		for (int i = 0; i < effects.size(); ++i)
		{
			effects[i]->Update(dt);
			if (effects[i]->IsEnd())
			{
				delete effects[i];
				effects.erase(effects.begin() + i);
			}
		}
	}

	void DrawAll(const DOG::Camera& cam, double scale)
	{
		for (Effect* e : effects)
		{
			e->Draw(cam, scale);
		}
	}

	void Add(Effect* e)
	{
		effects.push_back(e);
	}
	
	void Clear()
	{
		for(auto e : effects)
		{
			delete e;
		}
		effects.clear();
	}
private:
	std::vector<Effect*> effects;
};

