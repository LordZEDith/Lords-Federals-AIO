#pragma once

#include "BaseMenu.h"
#include "PluginSDK.h"
class AutoLeveler
{
public:

	void  Menu()
	{
		AutoLevelers = MainMenu->AddMenu("AutoLeveler Settings");
		AutoLevelerCheck = AutoLevelers->CheckBox("Enable Auto Leveler?", true);
		AutoLevelerStart = AutoLevelers->AddInteger("Auto Leveler Starts at Level:", 4, 4, 4);
		InfoText = AutoLevelers->AddMenu("INFO: (Q:1 W:2 E:3 R:4)");
		AutoLevel1 = InfoText->AddInteger("Max 1st:", 4, 4, 4);
		AutoLevel2 = InfoText->AddInteger("Max 2nd:", 1, 3, 0);
		AutoLevel3 = InfoText->AddInteger("Max 3rd:", 1, 3, 0);
		AutoLevel4 = InfoText->AddInteger("Max 4th:", 1, 3, 0);
	}
	//CREDS to Krohdo / Dewblackio2
	static void OnLevelUpAuto(IUnit* Source, int NewLevel)
	{
		//creds to Katten
		if (!AutoLevelerCheck->Enabled() || Source == nullptr || Source != GEntityList->Player() || NewLevel != GEntityList->Player()->GetLevel() || NewLevel < AutoLevelerStart->GetInteger())
			return;
		auto max1st = AutoLevel1->GetInteger();
		auto max2nd = AutoLevel2->GetInteger();
		auto max3rd = AutoLevel3->GetInteger();
		auto max4th = AutoLevel4->GetInteger();

		if (max2nd == 0 || max3rd == 0 || max4th == 0)
			return;

		if (max1st == max2nd || max2nd == max3rd || max3rd == max4th || max2nd == max4th || max3rd == max1st || max1st == max4th)
			return;

		max1st -= 1;
		max2nd -= 1;
		max3rd -= 1;
		max4th -= 1;

		if (NewLevel == 6 || NewLevel == 11)
		{
			GEntityList->Player()->LevelUpSpell(max1st);
		}
		else
		{
			if (GGame->CanLevelUpSpell(max2nd)) {
				GEntityList->Player()->LevelUpSpell(max2nd);
				return;
			}

			if (GGame->CanLevelUpSpell(max3rd))
			{
				GEntityList->Player()->LevelUpSpell(max3rd);
				return;
			}

			if (GGame->CanLevelUpSpell(max4th))
			{
				GEntityList->Player()->LevelUpSpell(max4th);
			}
		}
	}

	static void Draw()
	{
		if (GEntityList->Player()->GetLevel() == 1 && AutoLevelerCheck->Enabled())
		{
			if (AutoLevel2->GetInteger() == AutoLevel3->GetInteger() || AutoLevel3->GetInteger() == AutoLevel4->GetInteger() || AutoLevel2->GetInteger() == AutoLevel4->GetInteger() || AutoLevel2->GetInteger() == 0 || AutoLevel3->GetInteger() == 0 || AutoLevel4->GetInteger() == 0)
			{
				GGame->Projection(GEntityList->Player()->GetPosition(), &HeroCoordsVec2);
				auto champx = HeroCoordsVec2.x;
				auto champy = HeroCoordsVec2.y;
				static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
				message->SetColor(Vec4(255, 0, 0, 255));
				message->SetOutline(true);
				message->Render(champx - 55 * 5, champy - 200, "AutoSpellLeveler: Please Set Ability Level Prioritization!");
			}
		}
	}
};