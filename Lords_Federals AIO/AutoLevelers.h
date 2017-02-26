#pragma once
#include "BaseMenu.h"
#include "PluginSDK.h"
//CREDS TO Krohdo / Dewblackio2

void LevelMenu()
{
	AutoLeveler = MainMenu->AddMenu("AutoLeveler Settings");
	AutoLevelerCheck = AutoLeveler->CheckBox("Enable Auto Leveler?", true);
	AutoLevelerStart = AutoLeveler->AddInteger("Auto Leveler Starts at Level:", 4, 4, 4);
	InfoText = AutoLeveler->AddMenu("INFO: (Q:1 W:2 E:3 R:4)");
	AutoLevel1 = InfoText->AddInteger("Max 1st:", 4, 4, 4);
	AutoLevel2 = InfoText->AddInteger("Max 2nd:", 1, 3, 0);
	AutoLevel3 = InfoText->AddInteger("Max 3rd:", 1, 3, 0);
	AutoLevel4 = InfoText->AddInteger("Max 4th:", 1, 3, 0);
}

 
void LevelDraw()
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