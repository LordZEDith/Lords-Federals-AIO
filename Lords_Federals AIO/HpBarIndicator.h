#pragma once
#include "PluginSDK.h"
#include <vector>

class HpBarIndicator
{

public:

	static void drawDmg(IUnit* Target, double Damage, Vec4 Color)
	{
		Vec2 LifePos;

		if (Target->GetHPBarPosition(LifePos) && !Target->IsDead() && Target->IsVisible())
		{
			Vec2 Size = Vec2(103 * (Damage / Target->GetMaxHealth()), 8);

			if (Size.x > 103)
			{
				Size.x = 103;
			}

			LifePos = Vec2(LifePos.x + 10, LifePos.y += 20);

			Vec2 LinePos1 = Vec2(LifePos.x + Size.x, LifePos.y);
			Vec2 LinePos2 = Vec2(LifePos.x + Size.x - 5, LifePos.y - 7);

			GRender->DrawFilledBox(LifePos, Size, Color);
		}
	}
};