#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <string>

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

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			EGapCloser = MiscSettings->CheckBox("Automatically E GapCloser", true);
			EInterrupter = MiscSettings->CheckBox("Automatically E Interrupt Spell", true);
			CCedQ = MiscSettings->CheckBox("Auto Q When Enemies Cant Move", true);			
		}
		
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawAxe = DrawingSettings->CheckBox("Draw Q Aim", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);			
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 14, 1);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25f, 90.f, 1550.f, 870.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W->SetOverrideRange(580);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 60.f, 1550.f, 950.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(600);
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
	}

	static Vec3 CalculateReturnPos(IUnit* Target)
	{
		if (QMissile != nullptr && QMissile->IsValidObject() && Target->IsValidTarget())

		{
			auto finishPosition = MissileEndPos;
			auto misToPlayer = GetDistanceVectors(finishPosition, GEntityList->Player()->GetPosition());
			auto tarToPlayer = GetDistanceVectors(Target->GetPosition(), GEntityList->Player()->GetPosition());

			if (misToPlayer > tarToPlayer)
			{

				auto misToTarget = GetDistanceVectors(Target->GetPosition(), finishPosition);

				if (misToTarget < Q->Range() && misToTarget > 50)

				{
					auto PlayerPos = GEntityList->Player()->GetPosition();					
					
					auto cursorToTarget = GetDistanceVectors(PlayerPos.Extend(GGame->CursorPosition(), 100), Target->GetPosition());
					extz = finishPosition.Extend(Target->ServerPosition(), cursorToTarget + misToTarget);

					if (GetDistanceVectors(PlayerPos, extz) < 800 && CountEnemy(extz, 400) < 2)
					{	
						return extz;
					}

				}

			}

		}

		return Vec3(0,0,0);
	}

	static void RLogic()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 450 + R->Range());
		
		Vec3 dashPosition;
		auto PlayerPos = GEntityList->Player()->ServerPosition();
		dashPosition = PlayerPos.Extend(GGame->CursorPosition(), 450);

		if (GetDistanceVectors(GGame->CursorPosition(), GEntityList->Player()->GetPosition()) < 450)

			dashPosition = GGame->CursorPosition();

		if (CountEnemy(dashPosition, 800) > 2 || inUnderTower->Enabled() && IsUnderTurret(target) || RWall->Enabled() && GNavMesh->IsPointWall(dashPosition))
			return;

		if (RMax->Enabled())
		{

			if (GEntityList->Player()->HasBuff("AhriTumble"))
			{
				auto BuffTime = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("AhriTumble"));

				if (BuffTime < 4)
				{
					R->CastOnPosition(dashPosition);
				}

				auto posPred = CalculateReturnPos(target);

				if (posPred.x > 0 && posPred.y > 0)
				{
					if (strstr(QMissile->GetObjectName(), "AhriOrbReturn") && GetDistanceVectors(GEntityList->Player()->GetPosition(), posPred) > 200)
					{
						R->CastOnPosition(posPred);
					}
				}
			}
		}

		if (ComboR->Enabled())
		{
			auto rtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 450 + R->Range());			

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
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) continue;

			if (!target->HasBuff("ChronoShift") && Killsteal->Enabled())
			{
				if (KillstealQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) > target->GetHealth())
				{
					Q->CastOnTarget(target, kHitChanceHigh);
					return;
				}

				if (KillstealW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), W->Range()) && GHealthPrediction->GetKSDamage(target, kSlotW, W->GetDelay(), false) > target->GetHealth())
				{
					W->CastOnPlayer();
					return;
				}

				if (KillstealE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()) && GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) > target->GetHealth())
				{
					E->CastOnTarget(target, kHitChanceHigh);
				}
			}

			if (AutoHarass->Enabled() && Q->IsReady() && HarassMana->GetInteger() < GEntityList->Player()->ManaPercent() && CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
			{
				Q->CastOnTarget(target, kHitChanceHigh);
				return;
			}
			
			if (CCedQ->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50) && Q->IsReady() && !CanMove(target) && !target->IsDead() && !target->IsInvulnerable() && GEntityList->Player()->GetMana() > Q->ManaCost())
			{
				Q->CastOnTarget(target, kHitChanceMedium);
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

		if (!CheckTarget(target)) return;

		if (ComboR->Enabled() && R->IsReady() && target->IsValidTarget(GEntityList->Player(), 900))
		{
			RLogic();
		}

		if (ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
		{
			if (!target->HasBuff("BlackShield"))
			{
				E->CastOnTarget(target, kHitChanceHigh);
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
				Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

		if (!CheckTarget(target)) return;

		if (HarassE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range() - 50))
		{
			if (!target->HasBuff("BlackShield"))
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}
		}

		if (HarassW->Enabled() && W->IsReady() && target->IsValidTarget(GEntityList->Player(), R->Range()))
		{
			W->CastOnPlayer();
		}

		if (HarassQ->Enabled() && Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range() - 50))
		{
			Q->CastOnTarget(target, kHitChanceHigh);
		}
	}		

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{

				if (JungleE->Enabled() && E->IsReady() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{

					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							if (GEntityList->Player()->IsValidTarget(minion, 400))
							{
								E->CastOnUnit(minion);
							}
						}
						else
						{
							E->CastOnUnit(minion);
						}
					}
				}

				else if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						Vec3 posQ;
						int hitQ;

						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							GPrediction->FindBestCastPosition(Q->Range() - 500, Q->Radius(), true, true, false, posQ, hitQ);
						}
						else
						{
							GPrediction->FindBestCastPosition(Q->Range() - 50, Q->Radius(), true, true, false, posQ, hitQ);
						}

						if (hitQ > 1)
						{
							Q->CastOnPosition(posQ);
						}
						else
						{
							Q->CastOnUnit(minion);
						}
					}
				}

				if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(W->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()))
					{
						W->CastOnPlayer();
					}
				}
			}
		}
	}

	static void LaneClear()
	{		
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (LaneClearQ->Enabled() && Q->IsReady() && !FoundMinionsNeutral(E->Range() + 100) && GetMinionsInRange(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
				{
					Vec3 pos;
					int count;
					Q->FindBestCastPosition(true, true, pos, count);

					if (count >= MinionsQ->GetInteger() && Q->CastOnPosition(pos))
					{
						return;
					}					
				}

				if (LaneClearW->Enabled() && W->IsReady() && GetMinionsInRange(GEntityList->Player()->GetPosition(), W->Range() - 100) >= MinionsW->GetInteger() && !FoundMinionsNeutral(E->Range() + 100))
				{
					W->CastOnPlayer();
				}
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
			if (extz.x > 0 && extz.y > 0)
			{
				GRender->DrawOutlinedCircle(extz, Vec4(255, 255, 255, 255), 100);
			}
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())

			{
				E->CastOnTarget(args.Sender, kHitChanceMedium);
			}			
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < E->Range())
		{			
				E->CastOnTarget(Args.Target, kHitChanceHigh);
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (Source->IsEnemy(GEntityList->Player())) { return; }

		if (strstr(Source->GetObjectName(), "AhriOrbMissile") || strstr(Source->GetObjectName(), "AhriOrbReturn"))
		{
			QMissile = Source;
		}

		if (strstr(Source->GetObjectName(), "AhriSeduceMissile"))
		{
			EMissile = Source;
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (Source->IsEnemy(GEntityList->Player())) { return; }

		if (strstr(Source->GetObjectName(), "AhriOrbReturn"))
		{
			QMissile = nullptr;
		}

		if (strstr(Source->GetObjectName(), "AhriSeduceMissile"))
		{
			EMissile = nullptr;
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
		if (strstr(Args.Name_, "AhriOrb"))
		{
			MissileEndPos = Args.EndPosition_;
		}
	}
};
