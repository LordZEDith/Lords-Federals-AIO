#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class Galio
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Galio Beta");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboChange = ComboSettings->AddSelection("Combo Mode", 0, std::vector<std::string>({ "Combo Normal", "Gank Mode" }));
			GankComboKey = ComboSettings->AddKey("Change Combo Mode", 84);
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);			
		}

		GankSettings = MainMenu->AddMenu("Gank Settings");
		{			
			GankR = GankSettings->CheckBox("Gank with R (Enemy in Ally Range)", false);
			Gankward = GankSettings->AddSelection("E Mode", 1, std::vector<std::string>({ "Gapcloser", "Attack Target" }));
			ChangetoCombo = GankSettings->CheckBox("Auto Change to Normal Combo", true);
			DrawGankCombo = GankSettings->CheckBox("Draw Text Gank", true);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);				
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{			
			Predic = fedMiscSettings->AddSelection("Q Prediction ->", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);			
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.5f, 250.f, 1200.f, 825.f);

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
		W->SetSkillshot(0.5f, 200.f, 3000.f, 450.f);		
		W->SetCharged(200.f, 450.f, 1.0f);

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 200, 1200, 650);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetOverrideRange(5000);
	}

	static int PredicChange()
	{
		if (Predic->GetInteger() == 0)
		{
			return mypredic = kHitChanceMedium;
		}
		if (Predic->GetInteger() == 1)
		{
			return mypredic = kHitChanceHigh;
		}
		if (Predic->GetInteger() == 2)
		{
			return mypredic = kHitChanceVeryHigh;
		}

		return mypredic = kHitChanceLow;
	}

	static void Automatic()
	{
		KeyPressComboMode();		
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (ComboW->Enabled() && W->IsReady() && (!Q->IsReady() && GGame->TickCount() - LastQTick > 1500 || !ComboQ->Enabled()) && (!E->IsReady() && GGame->TickCount() - LastETick > 1500 || !ComboE->Enabled()))
		{
			if (W->IsReady())
			{
				if (W->IsCharging())
				{
					W->FindTarget(SpellDamage);
					{
						if (target->IsValidTarget(target, W->Range()) && GetEnemiesInRange(W->Range()) >= 1)
						{
							W->CastOnPlayer();
						}
					}
				}
				else
				{
					if (GetDistance(GEntityList->Player(), target) <= 450)
					{
						W->StartCharging();
					}
				}				
			}
		}

		if (ComboQ->Enabled() && Q->IsReady())
		{
			if (GetDistance(GEntityList->Player(), target) <= Q->Range())
			{
				Q->CastOnTarget(target, PredicChange());
			}
		}

		if (ComboE->Enabled() && E->IsReady() && GetDistance(GEntityList->Player(), target) <= E->Range())
		{
			E->CastOnTarget(target, PredicChange());
		}		
	}

	static void GankMode()
	{
		ComboTarget = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range() + Q->Range());

		if (!CheckTarget(ComboTarget)) return;

		if (Gankward->GetInteger() == 0)
		{
			if (E->IsReady() && GetDistance(ComboTarget, GEntityList->Player()) <= E->Range() + ComboTarget->BoundingRadius() + 400)
			{
				if (GetDistance(ComboTarget, GEntityList->Player()) > E->Range())
				{
					E->CastOnUnit(ComboTarget);
				}
				else
				{
					E->CastOnTarget(ComboTarget, PredicChange());
				}
			}
		}
		else
		{
			if (E->IsReady() && GetDistance(ComboTarget, GEntityList->Player()) <= E->Range() + ComboTarget->BoundingRadius())
			{
				E->CastOnTarget(ComboTarget, PredicChange());
			}

		}		

		if (Q->IsReady() && !E->IsReady() && ComboTarget->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnTarget(ComboTarget, PredicChange());
		}

		if (!Q->IsReady() && !E->IsReady() && ChangetoCombo->Enabled())
		{
			ComboChange->UpdateInteger(0);
		}
	}

	static void KeyPressComboMode()
	{
		keystate3 = GetAsyncKeyState(GankComboKey->GetInteger());

		if (keystate3 < 0 && LastPress < GGame->TickCount())
		{
			if (harassKeyWasDown == false)
			{
				if (ComboChange->GetInteger() == 0)
				{
					ComboChange->UpdateInteger(1);
					LastPress = GGame->TickCount() + 300;
				}
				else
				{
					ComboChange->UpdateInteger(0);
					LastPress = GGame->TickCount() + 300;
				}

				harassKeyWasDown = true;
			}
		}
		else
		{
			harassKeyWasDown = false;
			//LastPress = 0;
		}
	}

	static void ComboSelected()
	{
		if (ComboChange->GetInteger() == 0)
		{
			Combo();
		}
		else
		{
			GankMode();
		}
	}

	static void Harass()
	{
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
	}

	static void LaneClear()
	{
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}

		if (ComboChange->GetInteger() == 1 && DrawGankCombo->Enabled())
		{
			Vec2 gPos;
			if (GEntityList->Player()->GetHPBarPosition(gPos))
			{
				auto altura = -30;
				auto comprimento = 15;

				static auto message2 = GRender->CreateFontW("Impact", 25.f, kFontWeightNormal);
				message2->SetColor(Vec4(255, 0, 0, 255));
				message2->SetOutline(true);
				message2->Render(gPos.x + 10 + comprimento, gPos.y + altura, "GANK ACTIVE!");
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			{
				LastQTick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotE)
			{
				LastETick = GGame->TickCount();
			}
		}
	}

	static void OnCreateObject(IUnit* Source)
	{

	}

	static void OnDeleteObject(IUnit* Source)
	{

	}
};
