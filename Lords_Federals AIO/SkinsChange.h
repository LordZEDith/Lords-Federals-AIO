#pragma once
#include "BaseMenu.h"

IMenuOption* SkinID = 0;

class Skins
{
public:

	static void Menu()
	{
		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			fedMiscSkinON = SkinsChange->CheckBox("Usar Skins Change?", true);
			fedMiscSkin = SkinsChange->AddInteger("Skins", 1, 20, 1);
		}
	}

	static void fedSkinChanger()
	{
		if (fedMiscSkinON->Enabled())
		{
			if (GEntityList->Player()->GetSkinId() != fedMiscSkin->GetInteger())
			{
				GEntityList->Player()->SetSkinId(fedMiscSkin->GetInteger());
			}
		}
		else
		{
			GEntityList->Player()->SetSkinId(GEntityList->Player()->GetSkinId());
		}
	}

};
