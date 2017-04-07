#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Ivern
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ivern");

		ESettings = MainMenu->AddMenu("E Shield Settings");
		{
			AutoE = ESettings->CheckBox("Auto Shield", true);
			ESafety = ESettings->CheckBox("Shield Pet near Enemy", true);
			HealthE = ESettings->AddInteger("Min %HP to Shield Ally", 1, 100, 20);
			EOrder = ESettings->AddSelection("Shield Priority", 0, std::vector<std::string>({ "Attack", "Tank", "AP" }));
			for (auto ally : GEntityList->GetAllHeros(true, false))
			{
				std::string szMenuName = "Use Shield on - " + std::string(ally->ChampionName());
				ChampionUse[ally->GetNetworkId()] = ESettings->CheckBox(szMenuName.c_str(), true);
			}
		}

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{			
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboQH = ComboSettings->CheckBox("Use Q2 1x1 or Allys >", false);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboWRengar = ComboSettings->CheckBox("W On Rengar to dash", true);			
			ComboWSelf = ComboSettings->CheckBox("W For AA range", true);
			ComboE = ComboSettings->CheckBox("Use E Near target", true);			
			ComboR = ComboSettings->CheckBox("Use R", true);
			REnemies = ComboSettings->AddInteger("Ult When Enemys E Range >=", 1, 5, 2);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use Q2 1x1 or Allys >", false);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{			
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);
			LaneClearW = LaneClearSettings->CheckBox("W laneclear", true);
			MinionsW = LaneClearSettings->AddInteger("Min Minions to W", 1, 5, 2);
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Min to E Near Me/Ally", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Skills Prediction ->", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			AutoR = fedMiscSettings->CheckBox("Pet Auto Control", true);
			KillstealQ = fedMiscSettings->CheckBox("Use Q to KillSteal", true);			
			CCedQ = fedMiscSettings->CheckBox("Auto Q When Enemies Cant Move", true);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", true);
			DrawE = DrawingSettings->CheckBox("Draw E", true);			
			DrawAxe = DrawingSettings->CheckBox("Notice When Jungle Mob Ready", false);
			DrawPetStatus = DrawingSettings->CheckBox("Draw Pet Status", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{		
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(1.0, 150, 3200, 1075);

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1450, 1650);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 750);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.5, 250, 850, 350);		
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

	static bool IvernPet()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotR) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotR), "IvernRRecast"))
			{
				return true;
			}
		}

		return false;
	}

	static void Automatic()
	{		
		AutoShield();
		LogicW();
		//GetBuffName();
		PetFollow();		

		if (AutoHarass->Enabled())
		{
			Harass();
		}		

		if (AutoE->Enabled() && ESafety->Enabled() && E->IsReady() && IvernPet())
		{
			if (CountEnemy(GEntityList->Player()->GetPet()->GetPosition(), 450) >= 1)
			{
				E->CastOnUnit(GEntityList->Player()->GetPet());
			}
		}

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{
				if (target->HasBuff("ChronoShift") || !CheckShielded(target)) return;

				if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && KillstealQ->Enabled() && Q->IsReady() &&
					GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth() &&
					!GEntityList->Player()->HasBuff("ivernqallyjump"))
				{
					Q->CastOnTarget(target, PredicChange());
				}

				if (CCedQ->Enabled() && target->IsHero() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) &&
					!GEntityList->Player()->HasBuff("ivernqallyjump"))
				{
					Q->CastOnTarget(target, PredicChange());
				}
			}
		}
	}

	static void AutoShield()
	{
		if (E->IsReady() && AutoE->Enabled())
		{
			SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
				!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) <= E->Range() &&
				Aliados->HealthPercent() <= HealthE->GetInteger() && CountEnemy(Aliados->GetPosition(), 1500) > 0 && ChampionUse[Aliados->GetNetworkId()]->Enabled(); });

			if (sAliados.Any())
			{
				if (EOrder->GetInteger() == 0)
				{
					E->CastOnUnit(sAliados.MinOrDefault<float>([](IUnit* i) {return i->TotalPhysicalDamage(); }));
				}
				else if (EOrder->GetInteger() == 1)
				{
					E->CastOnUnit(sAliados.MinOrDefault<float>([](IUnit* i) {return i->Armor(); }));
				}
				else
				{
					E->CastOnUnit(sAliados.MinOrDefault<float>([](IUnit* i) {return i->TotalMagicDamage(); }));
				}
			}
		}
	}

	static void PetFollow()
	{
		if (AutoR->Enabled() && IvernPet() && R->IsReady())
		{			
			auto target = GOrbwalking->GetLastTarget();

			if (target == nullptr)
			{
				target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());				
			}		

			if (CheckTarget(target))
			{
				if (GEntityList->Player()->IsValidTarget(target, 1000))
				{
					R->CastOnPosition(target->GetPosition());
					goUltimate = true;
				}
				else
				{
					R->CastOnPosition(GEntityList->Player()->GetPosition());
					goUltimate = false;
				}
			}
		}
	}

	static void castW(IUnit* t)
	{
		Vec3 pos;
		GPrediction->GetFutureUnitPosition(t, 0.1f, true, pos);
		W->CastOnPosition(pos);
	}

	static void WUnderTower()
	{
		for (auto t : GEntityList->GetAllTurrets(false, true))
		{
			if (CheckTarget(t))
			{
				if (W->IsReady() && !GEntityList->Player()->IsWindingUp() &&
					!GEntityList->Player()->HasBuff("ivernwpassive") && GEntityList->Player()->AttackRange() < 200 &&
					CountMinionsAlly(GEntityList->Player()->GetPosition(), 500) >= 2 &&
					!t->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) && t->IsValidTarget(GEntityList->Player(), 325) &&
					!GPrediction->IsPointGrass(GEntityList->Player()->GetPosition()))
				{
					if (IvernBush.Any())
					{
						for (auto b : IvernBush.ToVector())
						{
							if (GetDistance(GEntityList->Player(), b) >= 300)
							{
								castW(GEntityList->Player());
							}
						}
					}
					else
					{
						castW(GEntityList->Player());
					}
				}
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());

		if (!CheckTarget(target)) return;

		GetTarget = target;

		if (ComboQ->Enabled() && Q->IsReady() && !GEntityList->Player()->HasBuff("ivernqallyjump"))
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnTarget(target, PredicChange());
			}
		}

		if (ComboQH->Enabled() && Q->IsReady() && GEntityList->Player()->HasBuff("ivernqallyjump"))
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()) && 
				(CountEnemy(GEntityList->Player()->GetPosition(), 1500) == 1 || CountAlly(target->GetPosition(), 1500) > CountEnemy(target->GetPosition(), 1500)))
			{
				Q->CastOnPlayer();
			}
		}

		if (ComboE->Enabled() && E->IsReady())
		{			
			SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
				!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < E->Range() &&
				GetDistanceVectors(GetTarget->GetPosition(), Aliados->GetPosition()) < 400; });

			if (sAliados.Any())
			{
				E->CastOnUnit(sAliados.MinOrDefault<float>([](IUnit* i) {return i->GetHealth(); }));
			}					
		}

		if (ComboR->Enabled() && R->IsReady() && !IvernPet() &&
			(CountEnemy(GEntityList->Player()->GetPosition(), E->Range()) >= REnemies->GetInteger() ||
			(target->HasBuffOfType(BUFF_Snare) && GetDistance(GEntityList->Player(), target) < 750)))
		{			
			R->CastOnUnit(target);
		}
	}

	static void LogicW()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());

		if (CheckTarget(target))
		{
			GetTarget = target;

			if (ComboW->Enabled() && W->IsReady())
			{
				if (ComboWRengar->Enabled())
				{
					SArray<IUnit*> Rengar = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
						!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) < W->Range() &&
						GetDistanceVectors(GetTarget->GetPosition(), Aliados->GetPosition()) < 600 && GetDistanceVectors(GetTarget->GetPosition(), Aliados->GetPosition()) > 150 &&
						strstr(Aliados->ChampionName(), "Rengar") && !GPrediction->IsPointGrass(Aliados->GetPosition()); });

					if (Rengar.Any())
					{
						if (IvernBush.Any())
						{
							for (auto b : IvernBush.ToVector())
							{
								if (GetDistance(Rengar.FirstOrDefault(), b) >= 300)
								{									
									castW(Rengar.FirstOrDefault());
								}
							}
						}
						else
						{
							castW(Rengar.FirstOrDefault());
						}
					}
				}

				if ((GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeMixed) && ComboWSelf->Enabled() && !GEntityList->Player()->IsWindingUp() &&
					!GEntityList->Player()->HasBuff("ivernwpassive") && GEntityList->Player()->AttackRange() < 200 &&
					((!target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) && target->IsValidTarget(GEntityList->Player(), 325)) || !GEntityList->Player()->IsMoving()) &&
					!GPrediction->IsPointGrass(GEntityList->Player()->GetPosition()))
				{
					if (IvernBush.Any())
					{
						for (auto b : IvernBush.ToVector())
						{
							if (GetDistance(GEntityList->Player(), b) >= 300)
							{								
								castW(GEntityList->Player());
							}
						}
					}
					else
					{
						castW(GEntityList->Player());
					}
				}
			}
		}
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) return;
		
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

		if (!CheckTarget(target)) return;		

		if (HarassQ->Enabled() && Q->IsReady() && !GEntityList->Player()->HasBuff("ivernqallyjump"))
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnTarget(target, PredicChange());
			}
		}

		if (HarassE->Enabled() && Q->IsReady() && GEntityList->Player()->HasBuff("ivernqallyjump"))
		{
			if (target->IsValidTarget(GEntityList->Player(), Q->Range()) &&
				(CountEnemy(GEntityList->Player()->GetPosition(), 1500) == 1 || CountAlly(target->GetPosition(), 1500) > CountEnemy(target->GetPosition(), 1500)))
			{
				Q->CastOnPlayer();
			}
		}
	}
	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;		
		
		if (LaneClearQ->Enabled() && Q->IsReady())
		{
			Q->LastHitMinion();
		}
		
		if (LaneClearW->Enabled() && W->IsReady() && !GEntityList->Player()->IsWindingUp() &&
			!GEntityList->Player()->HasBuff("ivernwpassive") && GEntityList->Player()->AttackRange() < 200 && 
			CountMinions(GEntityList->Player()->GetPosition(), 350) >= MinionsW->GetInteger() &&
			!GPrediction->IsPointGrass(GEntityList->Player()->GetPosition()))
		{
			if (IvernBush.Any())
			{
				for (auto b : IvernBush.ToVector())
				{
					if (GetDistance(GEntityList->Player(), b) >= 300)
					{						
						castW(GEntityList->Player());
					}
				}
			}
			else
			{
				castW(GEntityList->Player());
			}
		}

		if (LaneClearE->Enabled() && E->IsReady())
		{
			SArray<IUnit*> sAliados = SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
				!Aliados->IsDead() && Aliados->IsVisible() && GetDistance(GEntityList->Player(), Aliados) <= E->Range() &&
				CountMinions(Aliados->GetPosition(), 400) >= MinionsE->GetInteger(); });

			if (sAliados.Any())
			{
				E->CastOnUnit(sAliados.FirstOrDefault());
			}

			if (IvernPet() && CountMinions(GEntityList->Player()->GetPet()->GetPosition(), 400) >= MinionsE->GetInteger())
			{
				E->CastOnUnit(GEntityList->Player()->GetPet());
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
			
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			
		}

		if (DrawPetStatus->Enabled() && IvernPet())
		{
			Vec2 gPos;
			if (GEntityList->Player()->GetHPBarPosition(gPos))
			{
				auto altura = -40;
				auto comprimento = 10;

				if (goUltimate)
				{
					static auto message2 = GRender->CreateFontW("Impact", 25.f, kFontWeightNormal);
					message2->SetColor(Vec4(255, 0, 0, 255));
					message2->SetOutline(true);
					message2->Render(gPos.x + 10 + comprimento, gPos.y + altura, "Pet: Engaging!");
				}
				else
				{
					static auto message2 = GRender->CreateFontW("Impact", 25.f, kFontWeightNormal);
					message2->SetColor(Vec4(255, 0, 0, 255));
					message2->SetOutline(true);
					message2->Render(gPos.x + 10 + comprimento, gPos.y + altura, "Pet: Following Player");
				}
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
		
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "IvernTotem"))
		{
			IvernBush.Add(Source);
		}

		if (strstr(Source->GetObjectName(), "Ivern_Base_P_FinishedGround.troy"))
		{
			// Team Red
			if (GetDistanceVectors(Source->GetPosition(), Vec3(7098.000000, 56.209999, 10896.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Red Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(10998.000000, 51.720001, 6992.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Blue Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(12652.000000, 54.000000, 6444.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Gromp Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(10978.000000, 62.389999, 8356.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Wolf Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(7860.000000, 52.000000, 9474.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Raptors Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(6450.000000, 56.000000, 12198.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(255, 0, 0, 255), 10, false, true, ("Krugs Jungle Camp is now ready."));
			}

			// Team Blue
			if (GetDistanceVectors(Source->GetPosition(), Vec3(7772.000000, 53.939999, 4006.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Red Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(3834.000000, 51.970001, 7926.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Blue Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(2212.000000, 54.000000, 8450.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Gromp Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(3814.000000, 52.459999, 6468.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Wolf Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(6970.000000, 52.000000, 5422.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Raptors Jungle Camp is now ready."));
			}
			if (GetDistanceVectors(Source->GetPosition(), Vec3(8390.000000, 51.000000, 2676.000000)) < 200)
			{
				GRender->NotificationEx(Vec4(51, 153, 255, 255), 10, false, true, ("Krugs Jungle Camp is now ready."));
			}
		}

		if (strstr(Source->GetObjectName(), "Ivern_Base_P_FinishedGround_scuttler.troy"))
		{
			GRender->NotificationEx(Vec4(255, 255, 255, 255), 10, false, true, ("Crab Jungle Camp is now ready."));
		}

		if (strstr(Source->GetObjectName(), "Ivern_Base_P_ChannelGround.troy") && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			GOrbwalking->SetAttacksAllowed(false);
			GOrbwalking->SetMovementAllowed(false);

		}

		if (strstr(Source->GetObjectName(), "Ivern_Base_P_ring_timer.troy"))
		{
			GOrbwalking->SetAttacksAllowed(true);
			GOrbwalking->SetMovementAllowed(true);			
		}

		if (GetDistance(Source, GEntityList->Player()) < 500)
		{
			//GUtility->LogConsole("Obj %s", Source->GetObjectName());
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Ivern_Base_W_Brush.troy"))
		{
			IvernBush.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == Source->GetNetworkId(); });
		}

		if (strstr(Source->GetObjectName(), "Ivern_Base_P_ChannelGround.troy"))
		{
			GOrbwalking->SetAttacksAllowed(true);
			GOrbwalking->SetMovementAllowed(true);
		}		
	}

	static void GetBuffName()
	{
		std::vector<void*> vecBuffs;
		GEntityList->Player()->GetAllBuffsData(vecBuffs);

		for (auto i : vecBuffs)
		{
			GBuffData->GetBuffName(i);
			//GGame->PrintChat(GBuffData->GetBuffName(i));
			//GUtility->LogConsole("Buff %s", GBuffData->GetBuffName(i));			
		}
	}
};
