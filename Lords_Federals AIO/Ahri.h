#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <string>
#include "HpBarIndicator.h"

class Ahri
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ahri");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R KS Combo", true);
			RMax = ComboSettings->CheckBox("Auto R fight logic + aim Q", true);
			inUnderTower = ComboSettings->CheckBox("Dont Dash To Enemy Turret", false);
			RWall = ComboSettings->CheckBox("Dont Dash to Wall", false);
			EnemyCheck = ComboSettings->AddInteger("Block Dash in x enemies", 1, 5, 3);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassW = HarassSettings->CheckBox("Use W", false);
			HarassE = HarassSettings->CheckBox("Use E", false);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		KillstealSettings = MainMenu->AddMenu("Killsteal Settings");
		{
			Killsteal = KillstealSettings->CheckBox("Activate KillSteal", true);
			KillstealQ = KillstealSettings->CheckBox("Use Q to KillSteal", true);
			KillstealW = KillstealSettings->CheckBox("Use W to KillSteal", true);
			KillstealE = KillstealSettings->CheckBox("Use E to KillSteal", true);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 4);
			LaneClearW = LaneClearSettings->CheckBox("Use W in laneclear", false);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W in laneclear", 1, 10, 6);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 60);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", false);
			JungleBig = JungleClearSettings->CheckBox("Use E only BigMobs", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Skills Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			EGapCloser = fedMiscSettings->CheckBox("Auto E GapCloser", true);
			EInterrupter = fedMiscSettings->CheckBox("Auto E Interrupt Spell", true);
			EUnderTowerAttack = fedMiscSettings->CheckBox("Auto E Under Turret", true);
			CCedQ = fedMiscSettings->CheckBox("Auto Q When Enemies Cant Move", true);
			CheckShield = fedMiscSettings->CheckBox("No Charm (BlackShield, Banshee)", true);
			AimMissile = fedMiscSettings->CheckBox("Aim Return Missile", true);
		}

		FleeMode = fedMiscSettings->AddMenu("::Flee Mode");
		{
			FleeQ = FleeMode->CheckBox("Use Q in Flee Mode", true);
			FleeE = FleeMode->CheckBox("Use E in Flee Mode", true);
			FleeR = FleeMode->CheckBox("Use R in Flee Mode", true);
			FleeKey = FleeMode->AddKey("Flee Mode Key", 90);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawAxe = DrawingSettings->CheckBox("Draw Q Aim", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawTemp = DrawingSettings->CheckBox("Draw Passive", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25f, 90.f, 1550.f, 870.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W->SetOverrideRange(580);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25f, 60.f, 1550.f, 950.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(600);
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

	static int PassiveCount()
	{
		if (GEntityList->Player()->HasBuff("ahrisoulcrusher"))
		{
			return 99;
		}
		
		return GEntityList->Player()->GetBuffCount("ahrisoulcrushercounter");
	}	 

	static void FleeKeyMode()
	{
		if (IsKeyDown(FleeKey))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

			if (FleeQ->Enabled())
			{
				if (Q->IsReady() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					Q->CastOnTarget(target, PredicChange());
				}
			}

			if (FleeE->Enabled())
			{
				if (E->IsReady() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					E->CastOnTarget(target, PredicChange());
				}
			}

			if (FleeR->Enabled() && R->IsReady())
			{
				R->CastOnPosition(GGame->CursorPosition());
			}
		}
	}

	static void AimMissileHelp()
	{
		if (AimMissile->Enabled())
		{
			if (AimQ != Vec3(0, 0, 0) && QMissile != nullptr)
			{
				GOrbwalking->SetOverridePosition(AimQ);
			}
			else
			{
				GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
			}
		}		
	}

	static Vec3 ReturnPosMissile(IUnit* Target)
	{
		if (QMissile != nullptr && Target->IsValidTarget())
		{
			auto ePosition = MissileEndPos;
			auto missileToMe = GetDistanceVectors(ePosition, GEntityList->Player()->GetPosition());
			auto distance = GetDistanceVectors(Target->GetPosition(), GEntityList->Player()->GetPosition());			

			if (missileToMe > distance)
			{
				auto missileTarget = GetDistanceVectors(Target->GetPosition(), ePosition);

				if (missileTarget < Q->Range() && missileTarget > 50)
				{
					auto pPos = GEntityList->Player()->GetPosition();

					auto cursor = GetDistanceVectors(pPos.Extend(GGame->CursorPosition(), 100), Target->GetPosition());
					extz = ePosition.Extend(Target->ServerPosition(), cursor + missileTarget);

					if (GetDistanceVectors(pPos, extz) < 800 && CountEnemy(extz, 400) < 2)
					{
						AimQ = extz;
						return extz;
					}
				}
			}
		}

		AimQ = Vec3(0, 0, 0);
		return Vec3(0, 0, 0);
	}

	static void RLogic()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 450 + R->Range());

		Vec3 dashPosition;
		auto pPos = GEntityList->Player()->ServerPosition();
		dashPosition = pPos.Extend(GGame->CursorPosition(), 450);

		if (GetDistanceVectors(GGame->CursorPosition(), GEntityList->Player()->GetPosition()) < 450)
		{
			dashPosition = GGame->CursorPosition();
		}

		if (CountEnemy(dashPosition, 800) >= EnemyCheck->GetInteger() || inUnderTower->Enabled() && IsUnderTurret(target) || RWall->Enabled() && GNavMesh->IsPointWall(dashPosition))
		{
			return;
		}

		if (RMax->Enabled())
		{
			if (GEntityList->Player()->HasBuff("AhriTumble"))
			{
				auto BuffTime = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("AhriTumble")) - GGame->Time();

				if (BuffTime < 4)
				{
					R->CastOnPosition(dashPosition);
				}

				auto posPred = ReturnPosMissile(target);

				if (posPred != Vec3(0,0,0))
				{
					if (strstr(GMissileData->GetName(QMissile), "AhriOrbReturn") && GetDistanceVectors(GEntityList->Player()->GetPosition(), posPred) > 200)
					{
						R->CastOnPosition(posPred);
					}
				}
			}
		}

		if (ComboR->Enabled())
		{
			auto rtarget = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 450 + R->Range());

			if (rtarget->IsValidTarget())
			{
				auto comboDmg = GetDamageTeste(target, false);

				if (CountAlly(rtarget->GetPosition(), 600) < 2 && comboDmg > rtarget->GetHealth() && GetDistanceVectors(rtarget->GetPosition(), GGame->CursorPosition()) < GetDistanceVectors(GEntityList->Player()->GetPosition(), rtarget->GetPosition()) &&
					GetDistanceVectors(rtarget->ServerPosition(), dashPosition) < 500)
				{
					R->CastOnPosition(dashPosition);
				}

				for (auto hero : GEntityList->GetAllHeros(false, true))
				{
					if (hero != nullptr && hero->IsValidTarget() && !hero->IsInvulnerable() && !hero->IsDead() && GetDistance(GEntityList->Player(), hero) <= 300 && hero->IsMelee())
					{
						R->CastOnPosition(dashPosition);
					}
				}
			}
		}
	}

	static void Automatic()
	{		
		auto tTarget = Q->FindTarget(SpellDamage);
		if (tTarget != nullptr)
		{
			ReturnPosMissile(tTarget);
		}

		AimMissileHelp();
		FleeKeyMode();
		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{				
				if (!target->HasBuff("ChronoShift") && Killsteal->Enabled())
				{
					if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
					{
						Q->CastOnTarget(target, PredicChange());						
					}

					if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
					{
						W->CastOnPlayer();						
					}

					if (KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
					{
						E->CastOnTarget(target, PredicChange());
					}
				}

				if (AutoHarass->Enabled() && Q->IsReady() && HarassMana->GetInteger() < GEntityList->Player()->ManaPercent() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
				{
					Q->CastOnTarget(target, PredicChange());					
				}

				if (CCedQ->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) && GEntityList->Player()->GetMana() > Q->ManaCost())
				{
					Q->CastOnTarget(target, PredicChange());
				}
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 900);

		if (!CheckTarget(target)) return;

		if (ComboR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), 900))
		{
			RLogic();
		}

		if (ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
		{
			if (CheckShield->Enabled())
			{
				if (CheckShielded(target))
				{
					E->CastOnTarget(target, PredicChange());
				}
			}
			else
			{
				E->CastOnTarget(target, PredicChange());
			}
		}

		if (ComboW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), R->Range()) && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost() + W->ManaCost())
		{
			W->CastOnPlayer();
		}

		if (ComboQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && GEntityList->Player()->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			if (EMissile == nullptr || !EMissile->IsValidObject())
			{
				Q->CastOnTarget(target, PredicChange());
			}
		}
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 900);

		if (!CheckTarget(target)) return;

		if (HarassE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
		{
			if (CheckShield->Enabled())
			{
				if (CheckShielded(target))
				{
					E->CastOnTarget(target, PredicChange());
				}
			}
			else
			{
				E->CastOnTarget(target, PredicChange());
			}
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), R->Range()))
		{
			W->CastOnPlayer();
		}

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
		{
			Q->CastOnTarget(target, PredicChange());
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				auto jMonster = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{
					E->CastOnTarget(jMonster);
				}

				else if (JungleQ->Enabled() && Q->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
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
						if (jMonster->IsValidTarget(GEntityList->Player(), Q->Range()))
						{
							Q->CastOnUnit(Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); }));
						}
					}
				}
			}

			if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(W->Range()))
			{
				W->CastOnPlayer();
			}
		}
	}	

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			if (LaneClearQ->Enabled() && Q->IsReady() && !FoundMinionsNeutral(E->Range() + 100) && GetMinionsInRange(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
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

			if (LaneClearW->Enabled() && W->IsReady() && GetMinionsInRange(GEntityList->Player()->GetPosition(), W->Range() - 50) >= MinionsW->GetInteger() && !FoundMinionsNeutral(E->Range() + 100))
			{
				W->CastOnPlayer();
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

		if (DrawAxe->Enabled())
		{
			if (QMissile != nullptr)
			{
				if (AimQ != Vec3(0, 0, 0))
				{
					GRender->DrawOutlinedCircle(AimQ, Vec4(255, 255, 255, 255), 100);
				}

				auto rect = Geometry::Rectangle(QMissile->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), Q->Radius());

				if (AimQ != Vec3(0, 0, 0) && GetDistanceVectors(AimQ, GEntityList->Player()->GetPosition()) > 150)
				{
					rect.Draw(Vec4(255, 0, 0, 255), 3);
					GRender->DrawOutlinedCircle(QMissile->GetPosition(), Vec4(255, 0, 0, 255), 80);
				}
				else
				{
					rect.Draw(Vec4(255, 255, 255, 255), 3);
					GRender->DrawOutlinedCircle(QMissile->GetPosition(), Vec4(255, 255, 255, 255), 80);
				}
			}
		}

		if (DrawTemp->Enabled())
		{
			Vec2 pos;
			GGame->Projection(GEntityList->Player()->GetPosition(), &pos);

			static auto messageTimer = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
			messageTimer->SetLocationFlags(kFontLocationCenter);
			messageTimer->SetOutline(true);

			if (PassiveCount() == 99)
			{
				messageTimer->SetColor(Vec4(0, 255, 0, 255));
				messageTimer->Render(pos.x, pos.y, "Passive: Ready!");
			}
			else
			{
				if (PassiveCount() > 0)
				{
					messageTimer->SetColor(Vec4(255, 255, 0, 255));
					messageTimer->Render(pos.x, pos.y, "Passive: %i", PassiveCount());
				}
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (!CheckTarget(args.Source)) return;
		
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())
		{
			E->CastOnTarget(args.Source, PredicChange());
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (!CheckTarget(Args.Source)) return;

		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Source) < E->Range())
		{
			E->CastOnTarget(Args.Source, PredicChange());
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == GEntityList->Player()->GetNetworkId())
		{
			if (strstr(GMissileData->GetName(Source), "AhriOrbMissile") || strstr(GMissileData->GetName(Source), "AhriOrbReturn"))
			{
				QMissile = Source;
			}

			if (strstr(GMissileData->GetName(Source), "AhriSeduceMissile"))
			{
				EMissile = Source;
			}			

			GUtility->LogConsole("Nome: %s", GMissileData->GetName(Source));

			if (strstr(GMissileData->GetName(Source), "AhriOrbMissile"))
			{
				MissileEndPos = GMissileData->GetEndPosition(Source);
			}
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (Source->IsMissile() && GMissileData->GetCaster(Source)->GetNetworkId() == GEntityList->Player()->GetNetworkId())
		{
			if (strstr(GMissileData->GetName(Source), "AhriOrbReturn"))
			{
				QMissile = nullptr;
				GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));
			}

			if (strstr(GMissileData->GetName(Source), "AhriSeduceMissile"))
			{
				EMissile = nullptr;
			}		
		}
	}

	static void GetBuffName()
	{
		std::vector<void*> vecBuffs;
		GEntityList->Player()->GetAllBuffsData(vecBuffs);

		for (auto i : vecBuffs)
		{
			GBuffData->GetBuffName(i);
			GGame->PrintChat(GBuffData->GetBuffName(i));

			/*if (GEntityList->Player()->HasBuff("AhriTumble"))
			{
			auto buffTime = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("AhriTumble"));


			GGame->PrintChat("Tenho Buff do Ult");
			GGame->PrintChat(std::to_string(buffTime - GGame->Time()).data());
			}*/
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (strstr(Args.Name_, "AhriOrbofDeception"))
		{
			//MissileEndPos = Args.EndPosition_;
		}		

		if (EUnderTowerAttack->Enabled() && E->IsReady() && Args.Caster_->IsTurret() && Args.Target_->IsEnemy(GEntityList->Player()) && Args.Target_->IsHero())
		{
			if (Args.Target_->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				E->CastOnTarget(Args.Target_, PredicChange());
			}
		}
	}

	static void OnBuffRemove(IUnit* Source, void* BuffData)
	{
		if (GetDistance(GEntityList->Player(), Source) < 500)
		{
			//GGame->PrintChat(GBuffData->GetBuffName(BuffData));
			//GUtility->LogConsole("Nome %s", GBuffData->GetBuffName(BuffData));
		}
	}
};
