#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Khazix
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Khazix");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);			
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("R in Spells in CD", true);
			//RGapCloser = ComboSettings->CheckBox("Use R after long gapcloses", true);
			ComboEA = ComboSettings->CheckBox("Use E To Gapclose for Q", true);
			AA = ComboSettings->CheckBox("Dont AA while Invisible", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);			
			HarassW = HarassSettings->CheckBox("Use W", true);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
			KillstealW = KillstealSettings->CheckBox("Use W to KillSteal", true);
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", false);
			KillstealR = KillstealSettings->CheckBox("Use E + Q to KillSteal", false);
		}

		LastHitSettings = MainMenu->AddMenu("LastHit Settings");
		{
			LastHitQ = LastHitSettings->CheckBox("Use Q to last hit minions", true);			
			LastHitMana = LastHitSettings->AddInteger("Minimum Energy % to lasthit", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQLast = LaneClearSettings->AddSelection("Q Mode", 0, std::vector<std::string>({ "Push", "LastHit" }));
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);			
			LaneClearW = LaneClearSettings->CheckBox("W laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 6, 3);
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			HealthW = JungleClearSettings->AddInteger("Health % to use W", 0, 100, 80);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", false);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
		}

		ESettings = MainMenu->AddMenu("Jump Safety");
		{			
			ESafety = ESettings->CheckBox("Enable Safety Checks", true);
			EUnderTowerAttack = ESettings->CheckBox("Jump Under Tower Attack", true);
			AutoE = ESettings->CheckBox("Jump to get out when low", true);
			ECountEnemy = ESettings->CheckBox("Allys >= Enemys", true);
			inUnderTower = ESettings->CheckBox("Avoid Tower Diving", true);
			EBypassTower = ESettings->CheckBox("Bypass Dive in Big Chances", true);
			HealthE = ESettings->AddInteger("Min Healthy %", 0, 100, 30);
			//EBypass = ESettings->CheckBox("Bypass Checks while Stealth", true);
		}

		/*Jump2Settings = MainMenu->AddMenu("Double Jumping");
		{
			dJumpEnabled = Jump2Settings->CheckBox("Enabled", true);
			JEDelay = Jump2Settings->AddInteger("Delay Jumps", 250, 500, 250);
			JumpMode = Jump2Settings->AddSelection("Jump Mode ->", 0, std::vector<std::string>({ "Default (Ur Nexus Pos)", "Custom - Settings Below" }));
			SaveH = Jump2Settings->CheckBox("Save Double Jump Abilities", false);
			Noauto = Jump2Settings->CheckBox("Wait for Q instead of autos", false);
			jCursor = Jump2Settings->CheckBox("Jump to Cursor", false);
			SecondJump = Jump2Settings->CheckBox("Do second Jump", true);
			jCursor2 = Jump2Settings->CheckBox("Second Jump to Cursor", true);
			JumpDraw = Jump2Settings->CheckBox("Enable Jump Drawinsg", true);
		}*/

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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25f, 50.f, 1400.f, 325.f);

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0.25f, 70.f, 1700.f, 1050.f);

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25f, 200.f, 1500.f, 700.f);
		
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25f, 0.f, 1000.f, FLT_MAX);
	}

	static void EvolutionCheck()
	{
		if (!EvolvedQ && GEntityList->Player()->HasBuff("khazixqevo"))
		{
			Q->SetOverrideRange(375.f);
			EvolvedQ = true;
		}
		if (!EvolvedW && GEntityList->Player()->HasBuff("khazixwevo"))
		{
			EvolvedW = true;			
			W->SetOverrideRadius(100.f);			
		}

		if (!EvolvedE && GEntityList->Player()->HasBuff("khazixeevo"))
		{
			E->SetOverrideRange(900.f);
			EvolvedE = true;
		}
	}

	static bool IsSafeHP()
	{
		if (GEntityList->Player()->HealthPercent() >= HealthE->GetInteger())
		{
			return true;
		}

		return false;
	}

	static bool ucanJump(Vec3 position, IUnit* target = nullptr, bool minion = false)
	{
		if (!ESafety->Enabled())
		{			
			return true;
		}

		if (minion)
		{
			if (IsUnderTurretPos(position) && (CountMinionsAlly(position, 500) <= 1 || CountEnemy(position, 600) >= 1))
			{				
				return false;
			}			
			return true;
		}

		if (inUnderTower->Enabled() && IsUnderTurretPos(position) && target != nullptr)
		{
			// Dive
			if (EBypassTower->Enabled() &&
				GEntityList->Player()->GetLevel() >= 6 && GEntityList->Player()->GetMana() > (E->ManaCost() * 2) + Q->ManaCost() + W->ManaCost())
			{
				if ((GetDamageKhazix(target, true, true, true, true, false) > target->GetHealth() && GEntityList->Player()->HealthPercent() > HealthE->GetInteger() &&
					CountEnemy(target->GetPosition(), 600) == 1 || CountAlly(target->GetPosition(), 1200) >= 1 && CountEnemy(target->GetPosition(), 800) <= CountAlly(GEntityList->Player()->GetPosition(), 800) + 1))
				{					
					return true;
				}
			}			
			return false;
		}

		else if (ESafety->Enabled())
		{
			if (GEntityList->Player()->HealthPercent() < HealthE->GetInteger() && GetDamageKhazix(target, true, true, true, true, false) < target->HealthPercent() && target != nullptr)
			{				
				return false;
			}

			if (!ECountEnemy->Enabled() || ECountEnemy->Enabled() && CountEnemy(target->GetPosition(), 800) <= CountAlly(target->GetPosition(), 1200) + 1)
			{				
				return true;
			}
			else
			{
				return false;
			}
		}		
		return true;
	}

	static void GetBuffName()
	{
		std::vector<void*> vecBuffs;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{

			if (enemy->IsValidTarget(GEntityList->Player(), W->Range()))
			{
				enemy->GetAllBuffsData(vecBuffs);
			}

			for (auto i : vecBuffs)
			{
				/*GBuffData->GetBuffName(i);
				GGame->PrintChat(enemy->ChampionName());
				GGame->PrintChat(GBuffData->GetBuffName(i));*/

				GUtility->LogConsole("Champion: %s - Buff Name: %s", enemy->ChampionName(), GBuffData->GetBuffName(i));

				/*if (GEntityList->Player()->HasBuff("AhriTumble"))
				{
				auto buffTime = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("AhriTumble"));


				GGame->PrintChat("Tenho Buff do Ult");
				GGame->PrintChat(std::to_string(buffTime - GGame->Time()).data());
				}*/
			}
		}
	}

	static bool ObjIsolado(IUnit* target)
	{
		if (!CheckTarget(target)) return false;

		if (CountEnemy(target->GetPosition(), 400) == 1 && CountMinions(target->GetPosition(), 400) == 0 && !IsUnderTurret(target))
		{
			return true;
		}

		return false;
	}

	static float GetDamageKhazix(IUnit* target, bool CalCulateAttackDamage = true,
		bool CalCulateQDamage = true, bool CalCulateWDamage = true,
		bool CalCulateEDamage = true, bool CalCulateRDamage = true)
	{
		if (CheckTarget(target))
		{
			double Damage = 0;
			std::string ChampionName = GEntityList->Player()->ChampionName();
			std::string TargetName = target->ChampionName();

			if (GEntityList->Player()->GetSpellSlot("SummonerDot") != kSlotUnknown)
			{
				Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("SummonerDot"), 600);
			}

			if (CalCulateAttackDamage)
			{
				Damage += GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false);
			}

			if (CalCulateQDamage)
			{
				if (ObjIsolado(target))
				{
					Damage += Q->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) * 1.5 : 0;
				}
				else
				{
					Damage += Q->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) : 0;
				}
			}

			if (CalCulateWDamage)
			{
				Damage += W->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW) : 0;
			}

			if (CalCulateEDamage)
			{
				Damage += E->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) : 0;
			}

			if (CalCulateRDamage)
			{
				Damage += R->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) : 0;				
			}

			if (GEntityList->Player()->GetSpellSlot("SummonerDot") != kSlotUnknown  && Ignite->IsReady())
			{
				Damage += 50 + 20 * GEntityList->Player()->GetLevel() - (target->HPRegenRate() / 5 * 3);
			}

			if (TargetName == "Moredkaiser")
				Damage -= target->GetMana();

			// exhaust
			if (GEntityList->Player()->HasBuff("SummonerExhaust"))
				Damage = Damage * 0.6f;

			// blitzcrank passive
			if (target->HasBuff("BlitzcrankManaBarrierCD") && target->HasBuff("ManaBarrier"))
				Damage -= target->GetMana() / 2;

			// kindred r
			if (target->HasBuff("KindredRNoDeathBuff"))
				Damage = 0;

			// tryndamere r
			if (target->HasBuff("UndyingRage") && GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("UndyingRage")) - GGame->Time() > 0.3)
				Damage = 0;

			// kayle r
			if (target->HasBuff("JudicatorIntervention"))
				Damage = 0;

			// zilean r
			if (target->HasBuff("ChronoShift") && GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("ChronoShift")) - GGame->Time() > 0.3)
				Damage = 0;

			// fiora w
			if (target->HasBuff("FioraW"))
				Damage = 0;

			return Damage;
		}
		return 0;
	}

	static void Automatic()
	{
		//GetBuffName();
		EvolutionCheck();
		//DoubleJump();

		if (AA->Enabled() && GEntityList->Player()->HasBuff("khazixrstealth"))
		{
			GOrbwalking->SetAttacksAllowed(false);			
		}
		else
		{
			GOrbwalking->SetAttacksAllowed(true);
		}		
		
		if (AutoHarass->Enabled())
		{
			Harass();
		}
		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{

				if (target->HasBuff("ChronoShift") || !Killsteal->Enabled() || !CheckShielded(target)) return;

				if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealR->Enabled() && E->IsReady() && Q->IsReady() &&
					GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) + GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth() &&
					GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
				{
					E->CastOnTarget(target, kHitChanceHigh);
					Q->CastOnUnit(target);
				}

				if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && KillstealQ->Enabled() && Q->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
				{
					Q->CastOnUnit(target);
				}

				if (target->IsValidTarget(GEntityList->Player(), W->Range()) && KillstealW->Enabled() && W->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
				{
					W->CastOnTarget(target, kHitChanceHigh);
				}

				if (target->IsValidTarget(GEntityList->Player(), E->Range()) && KillstealE->Enabled() && E->IsReady() && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
				{
					if (ucanJump(target->GetPosition(), target))
					{
						E->CastOnTarget(target, kHitChanceHigh);
					}
				}
			}
		}
	}

	static void AutoEscape()
	{
		if (ESafety->Enabled() && AutoE->Enabled())
		{
			SArray<IUnit*> sEnemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* e) {return e != nullptr &&
				!e->IsDead() && e->IsVisible() && GetDistance(GEntityList->Player(), e) < E->Range() && IsUnderTurretPos(e->GetPosition()); });

			if (sEnemys.Any())
			{
				GetTarget = sEnemys.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GEntityList->Player()->GetPosition()); });
			}

			auto enemyhp = 0.f;

			if (GetTarget != nullptr)
			{
				enemyhp = GetTarget->GetHealth();
			}
			
			if (CountEnemy(GEntityList->Player()->GetPosition(), 900) == 2 && !IsSafeHP() ||
				CountEnemy(GEntityList->Player()->GetPosition(), 900) > CountAlly(GEntityList->Player()->GetPosition(), 900) + 1 ||
				CountEnemy(GEntityList->Player()->GetPosition(), 900) == 1 && !IsSafeHP() && enemyhp > GEntityList->Player()->GetHealth())
			{
				SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr && Aliados != GEntityList->Player() &&
					!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < 2500 && Aliados->HealthPercent() > 40 && 
					CountEnemy(Aliados->GetPosition(), 400) == 0 && !IsUnderTurretPos(Aliados->GetPosition()); });				

				if (sAliados.Any())
				{
					AliadoPos = sAliados.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GEntityList->Player()->GetPosition()); });

					auto pPos = GEntityList->Player()->ServerPosition();
					auto jump = pPos.Extend(AliadoPos->ServerPosition(), E->Range());

					E->CastOnPosition(jump);
					//GUtility->LogConsole("Aquiiiiiiiiiii");
					return;
				}		
			}			
		}
	}

	static void Combo()
	{		
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() + Q->Range());

		if (!CheckTarget(target)) return;		

		if (ComboQ->Enabled() && Q->IsReady() && !Jumping)
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnUnit(target);
			}
		}		

		if (ComboE->Enabled() && E->IsReady() && !Jumping && GetDistance(GEntityList->Player(), target) < E->Range() && 
			GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
		{
			if (ucanJump(target->GetPosition(), target))
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, kHitChanceVeryHigh);
		}
		
		if ((ComboEA->Enabled() && Q->IsReady() && E->IsReady() && GetDistance(GEntityList->Player(), target) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()) &&
			GetDistance(GEntityList->Player(), target) <= E->Range() + Q->Range()))
		{
			if (ucanJump(target->GetPosition(), target))
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}

			/*if (RGapCloser->Enabled() && R->IsReady())
			{
				R->CastOnPlayer();
			}*/
		}
		
		if (R->IsReady() && !Q->IsReady() && !W->IsReady() && !E->IsReady() &&
			ComboR->Enabled() && CountEnemy(GEntityList->Player()->GetPosition(), 500) > 0)
		{
			R->CastOnPlayer();
		}		
	}	

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

		if (!CheckTarget(target)) return;

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			Q->CastOnUnit(target);
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			W->CastOnTarget(target, kHitChanceHigh);
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
					if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

						if (damage > minion->GetHealth())
						{
							GOrbwalking->ResetAA();
							Q->CastOnUnit(minion);
						}
					}
				}
			}
		}
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;
		if (FoundMinions(E->Range()) || !FoundMinionsNeutral(E->Range())) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), W->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

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

				if (JungleW->Enabled() && W->IsReady() && HealthW->GetInteger() > GEntityList->Player()->HealthPercent())
				{
					if (GEntityList->Player()->IsValidTarget(minion, W->Range()))
					{
						Vec3 posW;
						int hitW;

						if (strstr(minion->GetObjectName(), "Crab"))
						{
							GPrediction->FindBestCastPosition(W->Range() - 500, W->Radius(), true, true, false, posW, hitW);
						}
						else
						{
							GPrediction->FindBestCastPosition(W->Range() - 50, W->Radius(), true, true, false, posW, hitW);
						}

						if (hitW > 1)
						{
							W->CastOnPosition(posW);
						}
						else
						{
							W->CastOnUnit(minion);
						}
					}
				}

				if (JungleE->Enabled() && E->IsReady() && GetDistance(GEntityList->Player(), minion) > Q->Range() + (0.4 * GEntityList->Player()->MovementSpeed()))
				{
					if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						Vec3 posE;
						int hitE;

						if (strstr(minion->GetObjectName(), "Crab"))
						{
							GPrediction->FindBestCastPosition(E->Range() - 500, E->Radius(), false, true, false, posE, hitE);
						}
						else
						{
							GPrediction->FindBestCastPosition(E->Range() - 50, E->Radius(), false, true, false, posE, hitE);
						}

						if (hitE > 1)
						{
							E->CastOnPosition(posE);
						}
						else
						{
							E->CastOnUnit(minion);
						}
					}
				}
			}
		}
	}	

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;
		if (!FoundMinions(E->Range()) || FoundMinionsNeutral(E->Range())) return;

		if (LaneClearQ->Enabled() && Q->IsReady())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), W->Range()) && m->IsCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						if (LaneClearQLast->GetInteger() == 0)
						{
							Q->CastOnUnit(minion);
						}
						else
						{
							auto damage = GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false);

							if (damage > minion->GetHealth())
							{
								GOrbwalking->ResetAA();
								Q->CastOnUnit(minion);
							}
						}
					}
				}
			}
		}

		if (LaneClearW->Enabled() && W->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), W->Range()) >= MinionsW->GetInteger())
		{
			Vec3 pos;
			int count;
			W->FindBestCastPosition(true, true, pos, count);

			if ((!EvolvedW && count >= 2 || EvolvedW && count >= 3) && W->CastOnPosition(pos))
			{
				return;
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsE->GetInteger())
		{			
			Vec3 pos;
			int count;
			E->FindBestCastPosition(true, false, pos, count);

			if (!ucanJump(pos, nullptr, true)) return;
			
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
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}

		/*for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (ObjIsolado(enemys))
			{
				GRender->DrawOutlinedCircle(enemys->GetPosition(), Vec4(255, 0, 0, 255), 400);
			}
		}*/
	}
	
	/*static Vec3 GetDoubleJumpPoint(IUnit* Qtarget, bool firstjump = true)
	{
		if (JumpMode->GetInteger() == 0)
		{
			auto ppos = GEntityList->Player()->ServerPosition();
			return ppos.Extend(GEntityList->GetTeamNexus()->ServerPosition(), E->Range());
		}

		if (firstjump && jCursor->Enabled())
		{
			return GGame->CursorPosition();
		}

		if (!firstjump && jCursor2->Enabled())
		{
			return GGame->CursorPosition();
		}

		Vec3 Position = Vec3();
		IUnit* jumptarget = nullptr;
		GetTarget = Qtarget;
		
		if (IsSafeHP())
		{
			SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && !m->IsInvulnerable() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m != GetTarget; });

			jumptarget = Enemys.FirstOrDefault();
		}
		else
		{
			SArray<IUnit*> Allys = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m != GEntityList->Player(); });

			jumptarget = Allys.FirstOrDefault();
		}		

		if (jumptarget != nullptr)
		{
			Position = jumptarget->ServerPosition();
		}
		if (jumptarget == nullptr)
		{
			auto ppos = GEntityList->Player()->ServerPosition();
			return ppos.Extend(GEntityList->GetTeamNexus()->ServerPosition(), E->Range());
		}

		return Position;
	}	
	
	static void DoubleJump()
	{
		if (!E->IsReady() || !EvolvedE || !dJumpEnabled->Enabled())
		{
			return;
		}

		if (Q->IsReady() && E->IsReady())
		{

		SArray<IUnit*> tEnemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && !m->IsInvulnerable() && m->IsValidTarget(GEntityList->Player(), E->Range()); });

		CheckQKillable = nullptr;

		if (tEnemys.Any())
		{
			CheckQKillable = tEnemys.Where([](IUnit* i) {return GetDistance(i, GEntityList->Player()) < Q->Range() && GetDamageKhazix(i,false,true,false,false,false) > i->GetHealth(); }).FirstOrDefault();
		}
			if (CheckQKillable != nullptr)
			{
				Jumping = true;

				JumpPos1 = GetDoubleJumpPoint(CheckQKillable);
				E->CastOnPosition(JumpPos1);
				Q->CastOnUnit(CheckQKillable);
				auto oldpos = GEntityList->Player()->ServerPosition();

				GPluginSDK->DelayFunctionCall(JEDelay->GetInteger(), []() {

					if (E->IsReady())
					{
						JumpPos2 = GetDoubleJumpPoint(CheckQKillable, false);
						E->CastOnPosition(JumpPos2);
					}

					Jumping = false;

				});				
			}
		}
	}*/

	static void OnProcessSpell(CastedSpell const& Args)
	{
		/*if (EvolvedE && !SaveH->Enabled())
		{
			if (GSpellData->GetSlot(Args.Data_) == kSlotQ && Args.Target_->IsHero() && dJumpEnabled->Enabled())
			{
				if (!CheckTarget(Args.Target_)) return;

				auto qdmg = GetDamageKhazix(Args.Target_, false, true, false, false, false);
				auto dmg = (GetDamageKhazix(Args.Target_, true, false, false, false, false) * 2) + qdmg;
				if (Args.Target_->GetHealth() < dmg && Args.Target_->GetHealth() > qdmg)
				{
					GOrbwalking->SetAttacksAllowed(false);
				}
				else
				{
					GOrbwalking->SetAttacksAllowed(true);
				}
			}
		}*/

		if (EUnderTowerAttack->Enabled() && ESafety->Enabled() && Args.Caster_->IsTurret() && Args.Target_ == GEntityList->Player())
		{
			if ((CountAlly(GEntityList->Player()->GetPosition(), 900) == 0 &&
				CountEnemy(GEntityList->Player()->GetPosition(), 600) > 1 || !IsSafeHP() || CountEnemy(GEntityList->Player()->GetPosition(), 600) >= 1 && !Q->IsReady() && !W->IsReady()))
			{
				SArray<IUnit*> sTorres = SArray<IUnit*>(GEntityList->GetAllTurrets(true, false)).Where([](IUnit* Torres) {return Torres != nullptr &&
					GetDistance(GEntityList->Player(), Torres) < 5000; });

				if (sTorres.Any())
				{
					TorrePos = sTorres.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GEntityList->Player()->GetPosition()); });
				}
				else
				{
					TorrePos = GEntityList->GetTeamNexus();
				}

				auto pPos = GEntityList->Player()->ServerPosition();
				auto jump = pPos.Extend(TorrePos->ServerPosition(), E->Range());

				E->CastOnPosition(jump);				
			}
		}
	}

	/*static void OnBeforeAttack(IUnit* Target)
	{
		if (dJumpEnabled->Enabled() && Noauto->Enabled())
		{
			if (Target->GetHealth() < GetDamageKhazix(Target, false, true, false, false, false) &&
				GEntityList->Player()->ManaPercent() > 15)
			{
				GOrbwalking->SetAttacksAllowed(false);
			}
			else
			{
				GOrbwalking->SetAttacksAllowed(true);
			}
		}
	}*/
};
