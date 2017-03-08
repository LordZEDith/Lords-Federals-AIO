#pragma once
#include "PluginSDK.h"
#include <vector>

int xOffset = 10;
int yOffset = 12;
int Width = 104;
int Height = 9;
Vec4 Color = Vec4(105, 198, 5, 255);
Vec4 FillColor = Vec4(198, 176, 5, 255);


class HpBarIndicator
{

public:
	
	static void drawDmg(float dmg)
	{
		if (dmg <= 0) { return; }

		for (auto hero : GEntityList->GetAllHeros(false, true))
		{
			auto barPos = Vec2();

			if (hero->GetHPBarPosition(barPos) && !hero->IsDead() && hero->IsVisible())
			{				
				auto damage = dmg;
				auto percentHealthAfterDamage = max(0, hero->GetHealth() - damage) / hero->GetMaxHealth();
				auto yPos = barPos.y + yOffset;
				auto xPosDamage = barPos.x + xOffset + Width * percentHealthAfterDamage;
				auto xPosCurrentHp = barPos.x + xOffset + Width * hero->GetHealth() / hero->GetMaxHealth();

				if (damage > hero->GetHealth())
				{
					GRender->DrawTextW(Vec2(barPos.x + xOffset, barPos.y + yOffset - 13), Color, "Killable");
				}

				GRender->DrawLine(Vec2(xPosDamage, yPos), Vec2(xPosDamage, yPos + Height), Color);

				auto differenceInHP = xPosCurrentHp - xPosDamage;
				auto pos1 = barPos.x + 9 + (107 * percentHealthAfterDamage);

				for (auto i = 0; i < differenceInHP; i++)
				{
					GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), FillColor);
				}

			}
		}
	}
};