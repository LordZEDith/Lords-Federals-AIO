#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Olaf
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Federal Olaf");

		RSettings = MainMenu->AddMenu("R CC Settings");
		{
			CCedR = RSettings->CheckBox("Auto R on CC", true);
			useRTF = RSettings->CheckBox("Enemys > Allys and 4x4+", true);
			rStun = RSettings->CheckBox("Stun", true);
			rBlind = RSettings->CheckBox("Blind", true);
			rCharm = RSettings->CheckBox("Charm", true);
			rFear = RSettings->CheckBox("Fear", true);
			rKnockback = RSettings->CheckBox("Knockback", true);
			rKnockup = RSettings->CheckBox("Knockup", true);
			rTaunt = RSettings->CheckBox("Taunt", true);
			rSlow = RSettings->CheckBox("Slow", false);
			rSilence = RSettings->CheckBox("Silence", true);
			rDisarm = RSettings->CheckBox("Disarm", true);
			rSnare = RSettings->CheckBox("Snare", true);
		}

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			gotoAxeC = ComboSettings->CheckBox("Catch axe", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			gotoAxeH = HarassSettings->CheckBox("Catch axe", false);
			HarassE = HarassSettings->CheckBox("Use E", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 40);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", true);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			QGapCloser = fedMiscSettings->CheckBox("Automatically Q GapCloser", true);
			CCedQ = fedMiscSettings->CheckBox("Auto Use Q on CC", true);
			gotoAxeRange = fedMiscSettings->AddInteger("Max dist to catch axe", 200, 800, 500);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);
			RangeQ = LastHitSettings->CheckBox("Only use Q if far from minions", true);
			LastHitE = LastHitSettings->CheckBox("Use E to last hit minions", true);
			LastHitMana = LastHitSettings->AddInteger("Minimum MP% to lasthit", 1, 100, 40);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			gotoAxelc = LaneClearSettings->CheckBox("Catch axe", false);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 3);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", false);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 6);
			HealthW = LaneClearSettings->AddInteger("Minimum HP% to use W to laneclear", 1, 100, 100);
			LaneClearE = LaneClearSettings->CheckBox("Use E in laneclear", true);
			LaneClearELast = LaneClearSettings->CheckBox("Use E only kill minion", true);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			gotoAxeJ = JungleClearSettings->CheckBox("Catch axe", true);
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", true);
			JungleHealth = JungleClearSettings->AddInteger("Minimum HP% to use W to jungle", 1, 100, 100);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawAxe = DrawingSettings->CheckBox("Draw Axe position", true);
			DrawTemp = DrawingSettings->CheckBox("Draw Axe Time", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.20f, 75.f, 1600.f, 1000.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(325.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
	}	

	static void Automatic()
	{
		// Killsteal
		if (Killsteal->Enabled())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(hero))
				{
					// With Q
					if (KillstealQ->Enabled() && Q->IsReady() && hero->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
					{
						auto delay = 0.25f + GetDistance(GEntityList->Player(), hero) / 1600;
						auto damage = GHealthPrediction->GetKSDamage(hero, kSlotQ, delay, false);

						if (damage + 50 > hero->GetHealth()) {

							Vec3 position;							
							GPrediction->GetFutureUnitPosition(hero, delay, true, position);

							Q->CastOnPosition(position);
						}
					}

					// With E
					else if (KillstealE->Enabled() && E->IsReady() && hero->IsValidTarget(GEntityList->Player(), E->Range()))
					{
						auto damage = GHealthPrediction->GetKSDamage(hero, kSlotE, E->GetDelay(), false);

						if (damage + 50 > hero->GetHealth())							
						{
							E->CastOnUnit(hero);
						}
					}
				}
			}
		}

		// Auto Q in Target CC
		if (CCedQ->Enabled() && Q->IsReady())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(hero))
				{
					if (!CanMove(hero) && hero->IsValidTarget(GEntityList->Player(), Q->Range()))
					{
						Q->CastOnTarget(hero, kHitChanceHigh);
					}
				}
			}
		}

		// Auto R in CC
		if (CCedR->Enabled() && R->IsReady())
		{
			if (useRTF->Enabled())
			{
				if (CountAlly(GEntityList->Player()->GetPosition(), 2000) + 1 > CountEnemy(GEntityList->Player()->GetPosition(), 3000)) { return; }
				if (CountAlly(GEntityList->Player()->GetPosition(), 2000) + 1 < 4 && CountEnemy(GEntityList->Player()->GetPosition(), 3000) < 4) { return; }
			}

			if (rStun->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Stun) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rBlind->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Blind) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rCharm->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Charm) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rFear->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Fear) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rKnockback->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Knockback) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rKnockup->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Knockup) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rTaunt->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Taunt) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rSlow->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Slow) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rSilence->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Silence) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rDisarm->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Disarm) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
			else if (rSnare->Enabled() && GEntityList->Player()->HasBuffOfType(BUFF_Snare) && FoundEnemies(GEntityList->Player(), 2000))
			{
				R->CastOnPlayer();
			}
		}
	}

	static void GotoAxe(Vec3 target)
	{
		auto maxDist = gotoAxeRange->GetInteger();
		//entretorres
		if (GetDistanceVectors(GEntityList->Player()->GetPosition(), target) < maxDist)
		{
			GOrbwalking->SetOverridePosition(lastQpos);
		}
	}

	static void CastQ()
	{
		if (Q->IsReady())
		{
			auto qTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range() - 30);

			if (CheckTarget(qTarget))
			{
				float Distance = GetDistance(GEntityList->Player(), qTarget);

				float Extend = 0;

				if (Distance < 300) { Extend = 40; }
				else if (Distance >= 300 && Distance < 500){ Extend = 60; }
				else if (Distance >= 500 && Distance < 700){ Extend = 80; }
				else if (Distance >= 700 && Distance < Q->Range()){ Extend = 100; }

				Vec3 position;
				auto delay = Q->GetDelay() + Distance / Q->Speed();
				GPrediction->GetFutureUnitPosition(qTarget, delay, true, position);

				Vec3 PositionTarget = position.Extend(GEntityList->Player()->GetPosition(), -Extend);

				if (Distance < Q->Range())
				{
					Q->CastOnPosition(PositionTarget);
				}
			}
		}
	}

	static void CastE()
	{
		if (E->IsReady())
		{
			auto eTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

			if (CheckTarget(eTarget))
			{
				if (GetDistance(GEntityList->Player(), eTarget) <= E->Range())
				{
					E->CastOnUnit(eTarget);
				}
			}
		}
	}

	static void Combo()
	{
		if (ComboQ->Enabled())
		{
			CastQ();
		}

		if (ComboE->Enabled())
		{
			CastE();
		}

		if (gotoAxeC->Enabled())
		{
			GotoAxe(lastQpos);
		}
	}

	static void Harass()
	{
		if (HarassQ->Enabled() && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			CastQ();
		}

		if (HarassE->Enabled() && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			CastE();
		}

		if (gotoAxeH->Enabled())
		{
			GotoAxe(lastQpos);
		}
	}

	static void LastHit()
	{
		if (LastHitQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LastHitMana->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto delay = Q->GetDelay() + GetDistance(GEntityList->Player(), minion) / Q->Speed();
					//auto damage = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ);
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, delay, true);					

					if (CheckTarget(minion) && damage > minion->GetHealth())
					{
						if (RangeQ->Enabled() && GetDistance(GEntityList->Player(), minion) > 400)
						{
							Q->CastOnUnit(minion);
						}
						else if (!RangeQ->Enabled())
						{
							GOrbwalking->ResetAA();
							Q->CastOnUnit(minion);
						}
					}
				}
			}
		}

		if (LastHitE->Enabled() && E->IsReady() && GEntityList->Player()->ManaPercent() >= LastHitMana->GetInteger())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto damage = GHealthPrediction->GetKSDamage(minion, kSlotE, E->GetDelay(), true);

					if (CheckTarget(minion) && damage > minion->GetHealth())
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
		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

		if (Minion.Any())
		{			
			if (gotoAxeJ->Enabled() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
			{
				GotoAxe(lastQpos);
			}

			if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
			{
				Vec3 posQ;
				int hitQ;

				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), true, true, false, posQ, hitQ);

				if (hitQ > 1)
				{
					Q->CastOnPosition(posQ);
				}
				else
				{
					Q->CastOnUnit(Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); }));
				}
			}

			else if (JungleE->Enabled() && E->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
			{
				for (auto jMonster : Minion.ToVector())
				{
					if (GEntityList->Player()->IsValidTarget(jMonster, E->Range()))
					{
						// Save E to combo with Smite
						if (strstr(jMonster->GetObjectName(), "Dragon") && jMonster->GetHealth() < 2000 ||
							strstr(jMonster->GetObjectName(), "Baron") && jMonster->GetHealth() < 2000 ||
							strstr(jMonster->GetObjectName(), "RiftHerald") && jMonster->GetHealth() < 2000)
						{
							return;
						}
						else
						{
							E->CastOnUnit(jMonster);
						}
					}
				}
			}
		}
	}

	static void LaneClear()
	{

		if (gotoAxelc->Enabled() && !FoundMinionsNeutral(E->Range() + 100))
		{
			GotoAxe(lastQpos);
		}

		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100) && CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
		{
			Vec3 pos;
			int count;
			Q->FindBestCastPosition(true, true, pos, count);

			if (MinionsQ->GetInteger() >= 3)
			{
				if (count >= 3 && Q->CastOnPosition(pos))
				{
					return;
				}
			}
			else
			{
				if (count >= MinionsQ->GetInteger() && Q->CastOnPosition(pos))
				{
					return;
				}

			}
		}

		if (LaneClearW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger())
		{
			if (GEntityList->Player()->HealthPercent() <= HealthW->GetInteger() && CountMinions(GEntityList->Player()->GetPosition(), 500) >= MinionsW->GetInteger())
			{
				W->CastOnPlayer();				
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100))
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					if (LaneClearELast->Enabled())
					{
						auto damage = GHealthPrediction->GetKSDamage(minion, kSlotE, E->GetDelay(), true);

						if (damage > minion->GetHealth())
						{
							GOrbwalking->ResetAA();
							E->CastOnUnit(minion);
						}
					}
					else 
					{
						E->CastOnUnit(minion);
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
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}

		if (lastQpos.x > 0 && lastQpos.y > 0)
		{
			if (DrawAxe->Enabled()) {
				GRender->DrawOutlinedCircle(lastQpos, Vec4(255, 255, 0, 255), 100);

				Vec2 mypos;
				Vec2 axepos;
				GGame->Projection(GEntityList->Player()->GetPosition(), &mypos);
				GGame->Projection(lastQpos, &axepos);
				GRender->DrawLine(mypos, axepos, Vec4(255, 255, 0, 255));

				if (DrawTemp->Enabled())
				{
					int temptotal = tempaxe - GGame->Time();

					Vec2 temppox;
					GGame->Projection(lastQpos, &temppox);
					static auto message = GRender->CreateFontW("Comic Sans", 20.f, kFontWeightBold);
					message->SetColor(Vec4(0, 255, 0, 255));
					message->SetOutline(true);
					message->Render(temppox.x, temppox.y, std::to_string(temptotal).c_str());
				}
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (QGapCloser->Enabled() && Q->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < Q->Range())
		{
			if (args.Source != nullptr && args.Source->IsValidTarget(GEntityList->Player(), Q->Range()) && !args.Source->IsInvulnerable() && !args.Source->IsDead())
			{
				auto Distance = GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition);

				Vec3 position;
				auto delay = 0.25f + Distance / 1600;
				GPrediction->GetFutureUnitPosition(args.Source, delay, true, position);

				if (Distance < Q->Range() && Q->CastOnPosition(position))
				{
					return;
				}
			}
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source != GEntityList->Player() || target == nullptr)
			return;

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			if (ComboW->Enabled() && W->IsReady())
			{
				W->CastOnPlayer();
			}
			break;
		case kModeLaneClear:
			if (JungleW->Enabled() && W->IsReady() && FoundMinionsNeutral(GEntityList->Player()->GetRealAutoAttackRange(target) + 65))
			{
				if (GEntityList->Player()->HealthPercent() <= JungleHealth->GetInteger())
				{
					W->CastOnPlayer();
				}
			}
			break;
		default:;
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Olaf_Base_Q_Axe_Ally"))
		{
			lastQpos = Source->GetPosition();

			temp = true;
			tempaxe = GGame->Time() + 9;
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Olaf_Base_Q_Axe_Ally"))
		{
			lastQpos = Vec3(0, 0, 0);
			GOrbwalking->SetOverridePosition(lastQpos);

			temp = false;
			tempaxe = 0;
		}
	}
};

