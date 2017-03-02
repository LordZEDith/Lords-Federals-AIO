#pragma once
#include "BaseMenu.h"

class Skins
{
public:

	static void Menu()
	{
		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkinON = SkinsChange->CheckBox("Usar Skins Change?", true);
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 20, 1);
		}
	}

	static void SkinChanger()
	{
		if (MiscSkinON->Enabled())
		{
			if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
			{
				GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
			}
		}
		else
		{
			GEntityList->Player()->SetSkinId(GEntityList->Player()->GetSkinId());
		}
	}

};
