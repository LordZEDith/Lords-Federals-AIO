#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Rumble
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Rumble");

		QMenu = MainMenu->AddMenu("Heat Settings");
		{
			AutoQ = QMenu->CheckBox("Use Q", true);
			AutoW = QMenu->CheckBox("Use W", true);
			StackMune = QMenu->CheckBox("Heat Active!", false);
			SemiManualKey = QMenu->AddKey("ON|OFF key Toggle", 71);
		}

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R", true);			
			REnemies = ComboSettings->AddInteger("Enemies in range for R", 0, 5, 2);
			autoR = ComboSettings->CheckBox("Auto R ?", false);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use E", true);
			AutoHarass = HarassSettings->CheckBox("Auto Harass", false);
			StartComboKey = HarassSettings->AddKey("ON|OFF key Toggle", 84);			
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);			
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", false);
			KillstealR = KillstealSettings->CheckBox("Use R to KillSteal", false);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitE = LastHitSettings->CheckBox("Use E to last hit minions", true);			
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{			
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);			
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			LaneClearELast = LaneClearSettings->AddSelection("E Mode", 0, std::vector<std::string>({ "Push", "LastHit" }));			
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			HealthW = JungleClearSettings->AddInteger("Health % to use W", 0, 100, 80);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{		
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			AutoShielded = fedMiscSettings->CheckBox("Auto Shield Near Enemys", true);
			minAutoShield = fedMiscSettings->AddInteger("Auto Shield HP%", 1, 100, 40);
			EscapeKey = fedMiscSettings->AddKey("Panic Escape", 65);
			RinRisk = fedMiscSettings->AddInteger("R near Foot Hp%", 0, 50, 15);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);			
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kConeCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 600, 1000, 600);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);		

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 60, 2000, 850);		

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithNothing));
		R->SetSkillshot(0.4, 200, 1600, 1700);

		R2 = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithNothing));
		R2->SetSkillshot(0.4, 200, 1600, 1700);
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

	static void KeepHeat()
	{
		if (GEntityList->Player()->GetMana() < 50)
		{
			if (AutoQ->Enabled() && Q->IsReady())
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}

			if (AutoW->Enabled() && W->IsReady())
			{
				W->CastOnPlayer();
			}
		}
	}

	static void AutoShield()
	{
		if (AutoShielded->Enabled() && CountEnemy(GEntityList->Player()->GetPosition(), E->Range()) > 0 &&
			GEntityList->Player()->HealthPercent() < minAutoShield->GetInteger() && W->IsReady())
		{
			W->CastOnPlayer();
		}
	}

	static void KeyPressToggle()
	{
		keystate3 = GetAsyncKeyState(SemiManualKey->GetInteger());

		if (keystate3 < 0 && LastPress < GGame->TickCount())
		{
			if (comboKeyWasDown == false)
			{				
				if (StackMune->GetInteger() == 0)
				{
					StackMune->UpdateInteger(1);
					LastPress = GGame->TickCount() + 300;
				}
				else
				{
					StackMune->UpdateInteger(0);
					LastPress = GGame->TickCount() + 300;
				}

				comboKeyWasDown = true;
			}
		}
		else
		{
			comboKeyWasDown = false;
		}
	}

	static void KeyPressHarass()
	{
		keystate2 = GetAsyncKeyState(StartComboKey->GetInteger());

		if (keystate2 < 0 && LastPress < GGame->TickCount())
		{
			if (harassKeyWasDown == false)
			{
				//toggle smite
				if (AutoHarass->GetInteger() == 0)
				{
					AutoHarass->UpdateInteger(1);
					LastPress = GGame->TickCount() + 300;
				}
				else
				{
					AutoHarass->UpdateInteger(0);
					LastPress = GGame->TickCount() + 300;
				}

				harassKeyWasDown = true;
			}
		}
		else
		{
			harassKeyWasDown = false;
		}
	}

	static void Automatic()
	{
		KeyPressToggle();
		KeyPressHarass();
		AutoShield();
		Escape();

		if (autoR->Enabled() && R->IsReady())
		{
			TesteR();
		}

		if (RinRisk->GetInteger() > 0 && GEntityList->Player()->HealthPercent() <= RinRisk->GetInteger())
		{
			PanicR();
		}

		if (StackMune->Enabled())
		{
			KeepHeat();
		}

		if (AutoHarass->Enabled())
		{
			Harass();
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) return;

			if (target->HasBuff("ChronoShift") || !Killsteal->Enabled() || !CheckShielded(target)) return;			

			if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && GEntityList->Player()->IsFacing(target) && KillstealQ->Enabled() && Q->IsReady() && 
				GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
			{
				Q->CastOnUnit(target);
			}

			if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealE->Enabled() && E->IsReady() &&
				GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}

			if (target->IsValidTarget(GEntityList->Player(), R->Range()) && KillstealR->Enabled() && R->IsReady() &&
				GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth())
			{
				CastR();
			}
		}
	}

	static bool IsPassWall(Vec3 start, Vec3 end)
	{
		double count = GetDistanceVectors(start, end);
		for (int i = 0; i <= count; i += 25)
		{
			auto pos = start.Extend(GEntityList->Player()->ServerPosition(), -i);
			if (GPrediction->IsPointWall(pos))
			{
				return true;
			}
		}
		return false;
	}

	static void TesteR()
	{
		auto minREnemies = REnemies->GetInteger();

		for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (enemys != nullptr )
			{
				auto startPos = enemys->ServerPosition() - (enemys->ServerPosition() - GEntityList->Player()->ServerPosition()).VectorNormalize() * 180;
				auto pPos = GEntityList->Player()->GetPosition();
				auto endPos = pPos.Extend(startPos, GetDistance(enemys, GEntityList->Player()) + 1000);				

				R->SetFrom(startPos);

				AdvPredictionOutput out;
				R->RunPrediction(enemys, true, kCollidesWithYasuoWall, &out);

				auto cRect = Geometry::Rectangle(startPos.To2D(), endPos.To2D(), 150);				

				SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return cRect.IsInside(i); });

				if (Enemys.Count() >= minREnemies && CheckShielded(enemys))
				{
					if (enemys->IsValidTarget(GEntityList->Player(), R->Range()))
					{
						if (!IsPassWall(out.TargetPosition, startPos) && !IsPassWall(out.TargetPosition, out.CastPosition))
						{
							if (out.HitChance >= kHitChanceHigh)
							{
								R->CastFrom(startPos, endPos);
								R->SetFrom(Vec3(0, 0, 0));
							}
						}
					}
				}
			}
		}
	}

	static void PanicR()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1000);
		if (!CheckTarget(target)) return;

		R2->SetFrom(GEntityList->Player()->ServerPosition());

		AdvPredictionOutput out;
		R2->RunPrediction(target, true, kCollidesWithYasuoWall, &out);

		if (GetDistance(GEntityList->Player(), target) < 1000)
		{
			if (out.HitChance >= kHitChanceHigh)
			{
				R2->CastFrom(GEntityList->Player()->ServerPosition(), out.TargetPosition);
				R2->SetFrom(Vec3(0, 0, 0));
			}
		}
	}

	static void CastR()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());		

		if (!CheckTarget(target)) return;

		auto pos1 = target->ServerPosition() - (target->ServerPosition() - GEntityList->Player()->ServerPosition()).VectorNormalize() * 300;

		R2->SetFrom(pos1);

		AdvPredictionOutput out;
		R2->RunPrediction(target, true, kCollidesWithYasuoWall, &out);		

		if (GetDistance(GEntityList->Player(), target) < 400)
		{
			auto midpoint = (GEntityList->Player()->ServerPosition() + out.TargetPosition) / 2;
			pos1 = midpoint + (out.TargetPosition - GEntityList->Player()->ServerPosition()).VectorNormalize() * 800;
			auto pos2 = midpoint - (out.TargetPosition - GEntityList->Player()->ServerPosition()).VectorNormalize() * 300;

			if (!IsPassWall(out.TargetPosition, pos1) && !IsPassWall(out.TargetPosition, pos2))
			{
				if (out.HitChance >= kHitChanceHigh)
				{
					R2->CastFrom(pos1, pos2);
					R2->SetFrom(Vec3(0, 0, 0));
				}
			}
		}
		else if (!IsPassWall(out.TargetPosition, pos1) && !IsPassWall(out.TargetPosition, out.CastPosition))
		{
			if (out.HitChance >= kHitChanceHigh)
			{
				R2->CastFrom(pos1, out.CastPosition);
				R2->SetFrom(Vec3(0, 0, 0));				
			}
		}
	}	

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
		auto rtarget = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());		

		if (CheckTarget(target) && ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnUnit(target);
		}

		if (CheckTarget(target) && ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			E->CastOnTarget(target, PredicChange());
		}

		if (CheckTarget(target) && ComboW->Enabled() && W->IsReady())
		{
			W->CastOnPlayer();
		}

		if (CheckTarget(rtarget) && ComboR->Enabled() && R->IsReady())
		{
			TesteR();
		}		
	}

	static void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());		

		if (!CheckTarget(target)) return;

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnUnit(target);
		}

		if (ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			E->CastOnTarget(target, PredicChange());
		}		
	}

	static void LastHit()
	{
		if (LastHitE->Enabled() && E->IsReady())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotE, E->GetDelay(), false);

					if (damage > minion->GetHealth())
					{
						GOrbwalking->ResetAA();
						E->CastOnUnit(minion);
					}
				}
			}
		}
	}

	static void JungleClear()
	{		
		if (FoundMinions(E->Range()) || !FoundMinionsNeutral(E->Range())) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

		if (Minion.Any())
		{
			for (auto minion : Minion.ToVector())
			{

				if (JungleQ->Enabled() && Q->IsReady())
				{
					if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						Q->CastOnUnit(minion);
					}
				}

				if (JungleW->Enabled() && W->IsReady() && HealthW->GetInteger() < GEntityList->Player()->HealthPercent())
				{
					if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						W->CastOnPlayer();
					}
				}

				if (JungleE->Enabled() && E->IsReady())
				{
					if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						E->CastOnTarget(minion);
					}
				}
			}
		}
	}

	static void LaneClear()
	{		
		if (!FoundMinions(E->Range()) || FoundMinionsNeutral(E->Range())) return;

		if (LaneClearE->Enabled() && E->IsReady())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					if (LaneClearELast->GetInteger() == 0)
					{
						E->CastOnUnit(minion);
					}
					else
					{
						auto damage = GHealthPrediction->GetKSDamage(minion, kSlotE, E->GetDelay(), false);

						if (damage > minion->GetHealth())
						{
							GOrbwalking->ResetAA();
							E->CastOnUnit(minion);
						}
					}
				}
			}
		}		

		if (LaneClearQ->Enabled() && Q->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), Q->Range() + 50) >= MinionsW->GetInteger())
		{			
			Q->CastOnPosition(GGame->CursorPosition());
		}
	}

	static void Escape()
	{
		if (IsKeyDown(EscapeKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (W->IsReady())
			{
				W->CastOnPlayer();
			}

			if (E->IsReady())
			{
				for (auto hero : GEntityList->GetAllHeros(false, true))
				{
					if (CheckTarget(hero) && hero->IsValidTarget(GEntityList->Player(), E->Range() - 50))
					{
						E->CastOnTarget(hero, PredicChange());
					}
				}
			}
		}
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }			
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }			
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}		
	}
};
