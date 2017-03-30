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

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use E", true);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{		
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);			
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 4);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Skills Prediction ->", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			KillstealQ = fedMiscSettings->CheckBox("Use Q to KillSteal", true);
			KillstealE = fedMiscSettings->CheckBox("Use E to KillSteal", false);
			EInterrupter = fedMiscSettings->CheckBox("Automatically E Interrupt Spell", true);
			CCedE = fedMiscSettings->CheckBox("Auto E Enemy under Turrets", true);
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

		if (AutoHarass->Enabled())
		{
			Harass();
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) return;

			if (target->HasBuff("ChronoShift") || !CheckShielded(target)) return;			

			if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && KillstealQ->Enabled() && Q->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
			{
				Q->CastOnTarget(target, PredicChange());
			}

			if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealE->Enabled() && E->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
			{
				E->CastOnTarget(target, PredicChange());
			}			
		}
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
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnTarget(target, PredicChange());
		}

		if (HarassE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			E->CastOnTarget(target, PredicChange());
		}
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;

		if (FoundMinions(Q->Range()) || !FoundMinionsNeutral(Q->Range())) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()); });

		if (Minion.Any())
		{
			jMonster = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });
		}

		if (jMonster != nullptr && !jMonster->IsDead() && !jMonster->IsInvulnerable() && jMonster->IsVisible())
		{
			if (JungleE->Enabled() && E->IsReady())
			{
				if (GEntityList->Player()->IsValidTarget(jMonster, E->Range()))
				{
					E->CastOnUnit(jMonster);
				}
			}

			if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(jMonster, Q->Range()))
			{
				Q->CastOnUnit(jMonster);
			}
		}
	}

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;

		if (!FoundMinions(Q->Range()) || FoundMinionsNeutral(Q->Range())) return;		

		if (LaneClearQ->Enabled() && Q->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
		{
			Vec3 pos;
			int count;
			Q->FindBestCastPosition(true, true, pos, count);

			if (count >= 3 && Q->CastOnPosition(pos))
			{
				return;
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsE->GetInteger())
		{
			Vec3 pos;
			int count;
			E->FindBestCastPosition(true, true, pos, count);			

			if (count >= 3 && E->CastOnPosition(pos))
			{
				return;
			}
		}
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

		if (!CheckTarget(Args.Target_) || GetDistance(GEntityList->Player(), Args.Caster_) > Q->Range()) return;

		if (CCedE->Enabled() && E->IsReady() && Args.Caster_->IsTurret() && Args.Target_->IsEnemy(GEntityList->Player()) && Args.Target_->IsHero())
		{
			if (Args.Target_->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				E->CastOnTarget(Args.Target_, PredicChange());				
			}
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) <= E->Range() && E->IsReady())
		{
			E->CastOnTarget(Args.Target, PredicChange());
		}
	}
};
