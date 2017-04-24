#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include  "Polygons.h"

class Vayne
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Vayne");

		QSettings = MainMenu->AddMenu("Tumble Settings");
		{
			AutoQ = QSettings->CheckBox("Auto Use Q", true);
			ComboQH = QSettings->AddSelection("Q Modes", 1, std::vector<std::string>({ "Q To Cursor", "Q Logic" }));						
			ComboQA = QSettings->CheckBox("Auto Q when R active", true);			
			PassiveStacks = QSettings->AddInteger("Q at X stack", 1, 2, 2);
			QAfterAA = QSettings->CheckBox("Q only after AA", false);			
			EnemyCheck = QSettings->AddInteger("Block Q in x enemies", 1, 5, 3);
			WallCheck = QSettings->CheckBox("Block Q in wall", false);
			TurretCheck = QSettings->CheckBox("Block Q under turret", false);
			AAcheck = QSettings->CheckBox("Q only in AA range", false);
			QAntiMelee = QSettings->AddSelection("Auto Q Anti Melee", 2, std::vector<std::string>({ "Off", "After Hit Me", "Near Me" }));
			QCancelAnimation = QSettings->CheckBox("Q Cancel Animation", false);			
		}

		ESettings = MainMenu->AddMenu("Condemn Settings");
		{
			AutoE = ESettings->AddSelection("Condemn Mode", 0, std::vector<std::string>({ "Combo & Harass", "Automatic", "Off" }));
			ComboE = ESettings->AddSelection("Condemn Method", 2, std::vector<std::string>({ "Mode 1", "Mode 2", "Mode 3" }));
			RangeE = ESettings->AddFloat("Condemn Max Range", 400, 760, 550);
			PushDistance = ESettings->AddInteger("Push Distance", 300, 470, 420);
			RWall = ESettings->AddSelection("Flash E Mode", 1, std::vector<std::string>({ "Automatic", "PressKey + LowHP", "Press Key", "OFF" }));
			HealthE = ESettings->AddInteger("Flash E Low HP% (1x1)", 1, 50, 15);
			SemiManualKey = ESettings->AddKey("Flash E Key", 71);
			KillstealE = ESettings->CheckBox("Smart E KS", false);
		}

		EMenu = ESettings->AddMenu("::Condemn Interrupters");
		{
			EInterrupter = EMenu->CheckBox("Use Condemn Interrupter", true);
			AntiSpells = EMenu->CheckBox("Interrupt Danger Spells", true);			
			AntiRengar = EMenu->CheckBox("Interrupt Rengar", true);			
			AntiFlash = EMenu->CheckBox("Condemn on Enemy Flashes", true);
			AntiKindred = EMenu->CheckBox("Inside Kindred R", true);
		}

		EMenuGap = ESettings->AddMenu("::Melee & Gapcloser");
		{
			EGapCloser = EMenuGap->CheckBox("E GapCloser | Anti Meele", false);
			AntiMeleeMode = EMenuGap->AddSelection("Anti Meele Mode", 0, std::vector<std::string>({ "After Hit Me", "Near Me" }));
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Anti Gapcloser - " + std::string(enemy->ChampionName());
				GapCloserList[enemy->GetNetworkId()] = EMenuGap->CheckBox(szMenuName.c_str(), true);
			}

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsMelee())
				{
					std::string szMenuName = "Anti Melee - " + std::string(enemy->ChampionName());
					ChampionAntiMelee[enemy->GetNetworkId()] = EMenuGap->CheckBox(szMenuName.c_str(), true);
				}
			}
		}

		RSettings = MainMenu->AddMenu("Ultimate Settings");
		{
			AutoR = RSettings->CheckBox("Use Ultimate", true);
			REnemies = RSettings->AddInteger("Min Enemys in Range", 1, 5, 3);
			RBlock = RSettings->CheckBox("Dont AA while Stealthed", true);
			RMode = RSettings->AddSelection("Stealh Mode", 0, std::vector<std::string>({ "Time Duration", "Enemys Range", "Both" }));
			UltEnemies = RSettings->AddInteger("Min Enemys for Stealh", 1, 5, 3);
			UltPercent = RSettings->AddInteger("Min Health %", 1, 100, 40);
			Rdelay = RSettings->AddInteger("Stealh Duration", 0, 1000, 500);
		}

		JungleClearSettings = MainMenu->AddMenu("Farm Settings");
		{
			LaneClearQ = JungleClearSettings->CheckBox("Use Q in LaneClear", false);
			LaneClearMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 60);
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			jPassiveStacks = JungleClearSettings->AddInteger("Q at X stack", 1, 2, 2);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);			
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 30);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{			
			zzRot = fedMiscSettings->AddKey("Super Beta ZZrot Condemn", 0x49);
			EOrder = fedMiscSettings->CheckBox("Focus W stacks Target", true);
			TrinketBush = fedMiscSettings->AddSelection("Trinket Bush Mode", 2, std::vector<std::string>({ "Off", "Only After Condemn", "Last Target Enter" }));
			TrinketBushdelay = fedMiscSettings->AddInteger("Trinket Delay (ms)", 0, 600, 180);
			BuyBlueTrinket = fedMiscSettings->CheckBox("Buy Blue Trinket", false);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", false);			
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawAxe = DrawingSettings->CheckBox("Draw Condemn Rectangles", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
		Q->SetOverrideRange(300.f);		

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithNothing);
		E->SetSkillshot(0.25f, 0.f, 1600.f, 760.f);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);

		if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerFlash"))
		{
			Flash = GPluginSDK->CreateSpell(kSummonerSlot1, 425);
			FoundFlash = true;
		}
		else if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerFlash"))
		{
			Flash = GPluginSDK->CreateSpell(kSummonerSlot2, 425);
			FoundFlash = true;
		}
		else
		{
			FoundFlash = false;
		}

		Ward1 = GPluginSDK->CreateItemForId(3340, 600);
		Ward2 = GPluginSDK->CreateItemForId(3363, 4000);
		zzRots = GPluginSDK->CreateItemForId(3512, 400);
	}

	static int PassiveWCount(IUnit* target)
	{
		return target->GetBuffCount("VayneSilveredDebuff");
	}

	static double Wdmg(IUnit* target)
	{
		return target->GetMaxHealth() * (4.5 + GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) * 1.5) * 0.01;		
	}

	static void BuyTrinket()
	{
		if (BuyBlueTrinket->Enabled() && GEntityList->Player()->GetLevel() >= 9 && Ward1->IsOwned() &&
			(GEntityList->Player()->IsDead() || GUtility->IsPositionInFountain(GEntityList->Player()->GetPosition(), true, false)))
		{
			GPluginSDK->DelayFunctionCall(Random(500, 1000), []() { GGame->BuyItem(3363);});			
		}
	}

	static bool CheckPosition(Vec3 Pos)
	{
		if (TurretCheck->Enabled() && IsUnderTurretPos(Pos) && !IsUnderTurret(GEntityList->Player()))
		{
			return false;
		}

		if (EnemyCheck->GetInteger() > CountEnemy(Pos, 600))
		{
			return true;
		}

		if (CountEnemy(Pos, 600) <= CountEnemy(GEntityList->Player()->GetPosition(), 450))
		{
			return true;
		}

		if (WallCheck->Enabled())
		{
			float check = Q->Range() + 50 / 5;

			for (int i = 1; i <= 5; i++)
			{
				auto pPos = GEntityList->Player()->GetPosition();

				if (GPrediction->IsPointWall(pPos.Extend(Pos, i * check)))
				{
					return false;
				}
			}
		}

		return false;
	}

	static void DrawCondemn()
	{
		if (E->IsReady() && DrawAxe->Enabled())
		{
			auto Hero = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() + 130);

			if (Hero != nullptr && Hero->IsVisible())
			{
				auto targetPosition = Hero->GetPosition();
				auto finalPosition = targetPosition.Extend(GEntityList->Player()->GetPosition(), -PushDistance->GetInteger());
				auto finalPosition_ex = targetPosition.Extend(GEntityList->Player()->GetPosition(), -PushDistance->GetInteger() + Hero->BoundingRadius());

				auto condemnRectangle = Geometry::Rectangle(targetPosition.To2D(), finalPosition.To2D(), Hero->BoundingRadius());
				auto condemnRectangle_ex = Geometry::Rectangle(targetPosition.To2D(), finalPosition_ex.To2D(), Hero->BoundingRadius());

				auto distance = GetDistance(GEntityList->Player(), Hero);
				auto check = PushDistance->GetInteger() / 40;

				for (auto i = 1; i < 40; i++)
				{
					Vec3 position;
					Vec3 pPos = GEntityList->Player()->GetPosition();

					GPrediction->GetFutureUnitPosition(Hero, 0.2f, true, position);

					Vec3 PositionTarget = pPos.Extend(position, distance + (check * i));

					if (GNavMesh->IsPointWall(PositionTarget))
					{
						//condemnRectangle.Draw(Vec4(0, 255, 0, 255), 3);
						condemnRectangle_ex.Draw(Vec4(0, 255, 0, 255), 3);
					}
					else
					{
						//condemnRectangle.Draw(Vec4(255, 0, 0, 255), 3);
						condemnRectangle_ex.Draw(Vec4(255, 255, 255, 255), 3);
					}
				}
			}
		}
	}

	static void EAntiMelee()
	{		
		if (EGapCloser->Enabled() && E->IsReady() && AntiMeleeMode->GetInteger() == 0)
		{
			for (auto target : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(target)) return;

				if (target->IsMelee() && GetDistance(GEntityList->Player(), target) < 300 && target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(target)))
				{
					auto pPos = GEntityList->Player()->ServerPosition();
					auto distance = GetDistance(GEntityList->Player(), target);
					Vec3 PositionTarget = pPos.Extend(target->ServerPosition(), distance + 470);

					if (CountAlly(PositionTarget, 1000) > CountEnemy(PositionTarget, 1000) || CountAlly(PositionTarget, 1000) == 0)
					{
						if (ChampionAntiMelee[target->GetNetworkId()]->Enabled() && (target->HealthPercent() > 30 || target->HealthPercent() < 50 && target->HealthPercent() > GEntityList->Player()->HealthPercent()))
						{
							E->CastOnUnit(target);
						}
					}
				}
			}
		}		
	}

	static void CheckKindredR()
	{
		SArray<IUnit*> enemy = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) &&
			m->HasBuff("KindredRNoDeathBuff") && m->HealthPercent() <= 10; });

		for (auto tenemy : enemy.ToVector())
		{

			if (AntiKindred->Enabled() && E->IsReady() && CheckTarget(tenemy))
			{
				E->CastOnUnit(tenemy);
			}
		}
	}

	static void zzRotRun()
	{
		if (GetAsyncKeyState(zzRot->GetInteger()))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 400);

			if (CheckTarget(target))
			{
				if (E->IsReady() && target->IsValidTarget(GEntityList->Player(), 400) && zzRots->IsReady() && zzRots->IsOwned())
				{
					if (zzRots->CastOnPosition(target->ServerPosition()))
					{
						E->CastOnUnit(target);
					}
				}
			}
		}
	}

	static void FocusTargetW()
	{
		if (EOrder->Enabled())
		{
			SArray<IUnit*> enemy = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) &&
				m->HasBuff("VayneSilveredDebuff"); });

			SArray<IUnit*> minions = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) &&
				m->HasBuff("VayneSilveredDebuff"); });

			if (enemy.Any())
			{
				auto fTarget = enemy.MaxOrDefault<int>([](IUnit* i) {return i->GetBuffCount("VayneSilveredDebuff"); });

				if (CheckTarget(fTarget))
				{
					GOrbwalking->SetOverrideTarget(fTarget);
				}
			}

			else if (minions.Any() && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
			{
				//GOrbwalking->SetOverrideTarget(minions.MaxOrDefault<int>([](IUnit* i) {return i->GetBuffCount("VayneSilveredDebuff"); }));
			}

			else
			{
				GOrbwalking->SetOverrideTarget(nullptr);
			}
		}
	}

	static bool CheckAARange(Vec3 point)
	{
		if (!AAcheck->Enabled())
		{
			return true;
		}
		else if (GOrbwalking->GetLastTarget() != nullptr && GOrbwalking->GetLastTarget()->IsHero())
		{
			return GetDistanceVectors(point, GOrbwalking->GetLastTarget()->GetPosition()) < GEntityList->Player()->GetRealAutoAttackRange(GOrbwalking->GetLastTarget());
		}
		else
		{
			return CountEnemy(point, GEntityList->Player()->AttackRange()) > 0;
		}
	}	

	static Vec3 QDashPosition(IUnit* target = nullptr)
	{
		Vec3 dashPosition;
		auto pPos = GEntityList->Player()->GetPosition();
		auto cPos = GGame->CursorPosition();

		if (ComboQH->GetInteger() == 0)
		{
			dashPosition = pPos.Extend(cPos, Q->Range());

			if (CheckPosition(dashPosition))
			{
				return dashPosition;
			}
		}		
		else
		{	// Credits: Gosu
			auto after = GEntityList->Player()->GetPosition() + (GGame->CursorPosition() - GEntityList->Player()->GetPosition()).VectorNormalize() * Q->Range();			

			if (GetDistanceVectors(target->GetPosition(), after)  < 630 && GetDistanceVectors(target->GetPosition(), after) > 150)
			{
				return cPos;
			}
			if (GetDistanceVectors(target->GetPosition(), GEntityList->Player()->GetPosition()) > 630 && GetDistanceVectors(target->GetPosition(), after) < 630)
			{
				return cPos;
			}			
		}		

		return Vec3(0, 0, 0);
	}

	static void FlashCondemn()
	{
		if (E->IsReady() && FoundFlash && Flash->IsReady())
		{
			auto target = GTargetSelector->GetFocusedTarget() != nullptr
				? GTargetSelector->GetFocusedTarget()
				: GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RangeE->GetFloat() + 425.f);

			if (!IsCondemable2(target, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
			{
				auto pPos = GEntityList->Player()->ServerPosition();
				auto fPos = pPos.Extend(GGame->CursorPosition(), 425);

				Rposition = fPos;

				if (target != nullptr && Rposition != Vec3(0,0,0) && target->IsValidTarget() && !target->IsDead() && !target->IsInvulnerable())
				{
					if (IsCondemable2(target, fPos, PushDistance->GetInteger(), false))
					{
						E->CastOnUnit(target);
						Flash->CastOnPosition(fPos);
					}
				}
			}
		}
	}

	// federal
	static bool CheckWallsVayne(IUnit* player, IUnit* enemy, float Push)
	{
		auto distance = GetDistance(player, enemy);
		auto check = Push / 40;

		for (auto i = 1; i < 40; i++)
		{
			Vec3 position;
			Vec3 pPos = GEntityList->Player()->GetPosition();

			GPrediction->GetFutureUnitPosition(enemy, 0.2f, true, position);

			Vec3 PositionTarget = pPos.Extend(position, distance + (check * i));

			if (GNavMesh->IsPointWall(PositionTarget))
			{
				if (enemy->GetHealth() + 10 <= GDamage->GetAutoAttackDamage(GEntityList->Player(), enemy, true) * 2)
				{
					return false;
				}
				
				WardPos = PositionTarget;
				return true;
			}
		}
		return false;
	}

	static bool IsCondemable1(IUnit* target, Vec3 from, int PushDistance, bool CondemnCurrent)
	{
		if (!CheckTarget(target) || !target->IsValidTarget(GEntityList->Player(), RangeE->GetFloat()) || target->IsDashing() || !CheckShielded(target)
			|| (!target->IsHero() && !target->IsJungleCreep()))
		{
			return false;
		}

		AdvPredictionOutput prediction_output;
		E->RunPrediction(target, false, kCollidesWithYasuoWall, &prediction_output);

		// Credits: VHR
		if (prediction_output.HitChance >= kHitChanceHigh)
		{
			auto checks = static_cast<float>(ceil(PushDistance / 30));
			for (auto i = 0; i < 30; ++i)
			{
				auto normalizedVector = (prediction_output.TargetPosition - from).VectorNormalize();
				auto extendedPosition = prediction_output.TargetPosition + normalizedVector * (checks * i);
				if (GNavMesh->IsPointWall(extendedPosition) && !target->IsDashing())
				{
					if (CondemnCurrent && GOrbwalking->GetLastTarget() != nullptr && GOrbwalking->GetLastTarget()->GetNetworkId() != target->GetNetworkId())
						return false;

					if (target->GetHealth() + 10 <= GDamage->GetAutoAttackDamage(GEntityList->Player(), target, true) * 2)
						return false;

					WardPos = extendedPosition;
					return true;
				}
			}
		}
		return false;
	}

	static bool IsCondemable2(IUnit* target, Vec3 from, int PushDistance, bool CondemnCurrent)
	{
		if (!CheckTarget(target) || !target->IsValidTarget(GEntityList->Player(), RangeE->GetFloat()) || target->IsDashing() || !CheckShielded(target)
			|| (!target->IsHero() && !target->IsJungleCreep()))
		{
			return false;
		}

		AdvPredictionOutput prediction_output;
		E->RunPrediction(target, false, kCollidesWithYasuoWall, &prediction_output);

		// Credits: Shine
		if (prediction_output.HitChance >= kHitChanceHigh)
		{
			auto pushDirection = (prediction_output.TargetPosition - from).VectorNormalize();
			auto checkDistance = PushDistance / 40;
			for (auto i = 0; i < 40; ++i)
			{
				auto finalPosition = prediction_output.TargetPosition + (pushDirection * checkDistance * i);
				if (GNavMesh->IsPointWall(finalPosition))
				{
					if (CondemnCurrent && GOrbwalking->GetLastTarget() != nullptr && GOrbwalking->GetLastTarget()->GetNetworkId() != target->GetNetworkId())
						return false;

					if (target->GetHealth() + 10 <= GDamage->GetAutoAttackDamage(GEntityList->Player(), target, true) * 2)
						return false;

					WardPos = finalPosition;
					return true;
				}
			}
		}
		return false;
	}

	static float GetEDamage(IUnit* target)
	{
		float baseE[5] = { 45, 80, 115, 150, 185 };
		auto checkBase = baseE[GEntityList->Player()->GetSpellLevel(kSlotE) - 1];

		return (0.52 * checkBase) + GDamage->CalcPhysicalDamage(GEntityList->Player(), target, 0.5 * GEntityList->Player()->BonusDamage());
	}

	static void Automatic()
	{
		FocusTargetW();
		UseUltimate();
		putWardAfterStun();
		CheckKindredR();		

		if (IsKeyDown(SemiManualKey) || IsKeyDown(zzRot))
		{
			GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());
		}

		if (CheckTime < GGame->TickCount())
		{
			checkVisible = false;
			putWard = false;			
		}
		
		// AutoAttack after Q
		if (canAttack && GEntityList->Player()->HasBuff("vaynetumblebonus") && GetDistance(GEntityList->Player(), BaseTarget) <= GEntityList->Player()->AttackRange())
		{
			GGame->IssueOrder(GEntityList->Player(), kAutoAttack, BaseTarget);
			canAttack = false;
			BaseTarget = nullptr;
		}

		// SmartKS E
		if (KillstealE->Enabled())
		{
			for (auto Hero : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(Hero) && CheckShielded(Hero))
				{
					if (E->IsReady() && GDamage->GetSpellDamage(GEntityList->Player(), Hero, kSlotW) + GetEDamage(Hero) > Hero->GetHealth() + (Hero->HPRegenRate() / 2.f) && PassiveWCount(Hero) == 2)
					{
						E->CastOnUnit(Hero);						
					}
				}
			}
		}
		
		// Flash E
		if (RWall->GetInteger() != 3)
		{
			if (RWall->GetInteger() == 0)
			{
				FlashCondemn();
			}
			else if (RWall->GetInteger() == 1)
			{
				if (IsKeyDown(SemiManualKey) || GEntityList->Player()->HealthPercent() <= HealthE->GetInteger() && CountEnemy(GEntityList->Player()->GetPosition(), 700) == 1)
				{
					FlashCondemn();
				}
			}
			else
			{
				if (IsKeyDown(SemiManualKey))
				{
					FlashCondemn();
				}
			}
		}		
		
		if (Q->IsReady())
		{
			if (ComboQA->Enabled() &&
				GOrbwalking->GetOrbwalkingMode() != kModeNone &&
				GEntityList->Player()->HasBuff("VayneInquisition") && CountEnemy(GEntityList->Player()->GetPosition(), 1500) > 0 && 
				CountEnemy(GEntityList->Player()->GetPosition(), 670) != 1)
			{
				auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1500);

				if (CheckTarget(qtarget))
				{
					auto dashPos = QDashPosition(qtarget);
					auto pPos = GEntityList->Player()->GetPosition();

					if (dashPos != Vec3(0, 0, 0))
					{
						if (QAntiMelee->GetInteger() == 2 && GetDistance(GEntityList->Player(), qtarget) <= qtarget->GetRealAutoAttackRange(GEntityList->Player())
							&& qtarget->IsMelee() && qtarget->IsFacing(GEntityList->Player()))
						{
							Q->CastOnPosition(pPos.Extend(qtarget->GetPosition(), -Q->Range()));
							return;
						}

						Q->CastOnPosition(dashPos);						
					}
				}
			}

			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && AutoQ->Enabled() && 
				(!QAfterAA->Enabled() || GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) == 0))
			{
				auto qtarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GEntityList->Player()->AttackRange() + 250);

				if (CheckTarget(qtarget))
				{
					if (GetDistance(GEntityList->Player(), qtarget) > GEntityList->Player()->AttackRange() &&
						GetDistanceVectors(qtarget->GetPosition(), GGame->CursorPosition()) < GetDistance(GEntityList->Player(), qtarget) && !qtarget->IsFacing(GEntityList->Player()))
					{
						auto pPos = GEntityList->Player()->GetPosition();
						auto dash = pPos.Extend(qtarget->GetPosition(), Q->Range());

						if (CheckPosition(dash))
						{
							Q->CastOnPosition(dash);
						}
					}
				}
			}
		}

		if (AutoE->GetInteger() != 2 && (AutoE->GetInteger() == 0 && 
			(GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeMixed) || 
			AutoE->GetInteger() == 1))
		{
			auto target = GTargetSelector->GetFocusedTarget() != nullptr
				? GTargetSelector->GetFocusedTarget()
				: GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RangeE->GetFloat());

			if (CheckTarget(target) && target->IsValidTarget(GEntityList->Player(), RangeE->GetFloat()))
			{

				if (ComboE->GetInteger() == 0)
				{
					if (CheckWallsVayne(GEntityList->Player(), target, PushDistance->GetInteger()))
					{
						E->CastOnUnit(target);
						EMissile = target;
					}
				}
				else if (ComboE->GetInteger() == 1)
				{
					if (IsCondemable1(target, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
					{
						E->CastOnUnit(target);
						EMissile = target;
					}
				}
				else
				{
					if (IsCondemable2(target, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
					{
						E->CastOnUnit(target);
						EMissile = target;
					}
				}
			}
		}
	}	

	static void UseUltimate()
	{
		if (R->IsReady() && AutoR->Enabled())
		{
			if (CountEnemy(GEntityList->Player()->GetPosition(), 700) > 3)
			{
				R->CastOnPlayer();
			}
			else if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && CountEnemy(GEntityList->Player()->GetPosition(), 700) >= REnemies->GetInteger())
			{
				R->CastOnPlayer();
			}
			else if (GEntityList->Player()->HealthPercent() < 25 && CountEnemy(GEntityList->Player()->GetPosition(), 400) > 0)
			{
				R->CastOnPlayer();
			}
		}
	}	

	static void LaneClear()
	{
		if (Q->IsReady() && LaneClearQ->Enabled() && !FoundMinionsNeutral(E->Range()) && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger())
			{
				for (auto t : GEntityList->GetAllMinions(false, true, false))
				{
					if (CheckTarget(t) && GetDistance(GEntityList->Player(), t) < GEntityList->Player()->GetRealAutoAttackRange(t))
					{
						auto dmg1 = GDamage->GetSpellDamage(GEntityList->Player(), t, kSlotQ);
						auto dmg2 = GDamage->GetAutoAttackDamage(GEntityList->Player(), t, true);

						auto dmg3 = Wdmg(t);

						if (dmg3 > 200)
						{
							dmg3 = 200;
						}						

						if (PassiveWCount(t) != 2)
						{
							dmg3 = 0;
						}

						auto pPos = GEntityList->Player()->GetPosition();
						auto dashPosition = pPos.Extend(GGame->CursorPosition(), Q->Range());						

						if (dmg3 + dmg2 + dmg1 > t->GetHealth() || dmg1 + dmg2 > t->GetHealth())
						{
							if (t->GetHealth() > dmg1 && CheckPosition(dashPosition))
							{																
								GOrbwalking->SetOverrideTarget(t);
								Q->CastOnPosition(dashPosition);								
							}
						}
					}
				}
			}
		}		
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()) && !strstr(m->GetObjectName(), "WardCorpse") && m->IsJungleCreep(); });

		if (Minion.Any())
		{
			jMonster = Minion.MaxOrDefault<float>([](IUnit* i) {return i->GetMaxHealth(); });
		}

		if (CheckTarget(jMonster))
		{
			if (JungleE->Enabled() && E->IsReady())
			{
				if (GEntityList->Player()->IsValidTarget(jMonster, E->Range()))
				{
					if (strstr(jMonster->GetObjectName(), "Red") ||
						strstr(jMonster->GetObjectName(), "Blue") ||
						strstr(jMonster->GetObjectName(), "Gromp") ||
						strstr(jMonster->GetObjectName(), "Crab") ||
						strstr(jMonster->GetObjectName(), "Razorbeak3") ||
						strstr(jMonster->GetObjectName(), "SRU_Krug") ||
						strstr(jMonster->GetObjectName(), "SRU_Murkwolf2"))
					{						
						if (ComboE->GetInteger() == 0)
						{
							if (CheckWallsVayne(GEntityList->Player(), jMonster, PushDistance->GetInteger()))
							{
								E->CastOnUnit(jMonster);
							}
						}
						else if (ComboE->GetInteger() == 1)
						{
							if (IsCondemable1(jMonster, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
							{
								E->CastOnUnit(jMonster);
							}
						}
						else
						{
							if (IsCondemable2(jMonster, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
							{
								E->CastOnUnit(jMonster);
							}
						}
					}
				}
			}				
		}
	}	

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RangeE->GetFloat()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RangeE->GetFloat()); }
		}

		DrawCondemn();			
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (!CheckTarget(args.Source)) return;

		if (EGapCloser->Enabled() && E->IsReady() && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.Source->GetPosition()) <= E->Range())
		{
			if (GapCloserList[args.Source->GetNetworkId()]->Enabled())
			{
				E->CastOnUnit(args.Source);
			}
		}		
	}

	static void OnInterrupt(InterruptibleSpell const& args)
	{
		if (!CheckTarget(args.Source)) return;

		if (args.Source->IsEnemy(GEntityList->Player()) && EInterrupter->Enabled() && AntiSpells->Enabled() && E->IsReady() && args.DangerLevel >= kMediumDanger &&
			args.Source->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			E->CastOnUnit(args.Source);
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source->GetNetworkId() == GEntityList->Player()->GetNetworkId())
		{
			if (target->IsHero() && !target->IsDead())
			{
				if (AutoQ->Enabled() && Q->IsReady() &&
					(PassiveWCount(target) == PassiveStacks->GetInteger() - 1
						|| GEntityList->Player()->HasBuff("VayneInquisition")
						|| GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) == 0))
				{
					auto dashPos = QDashPosition(target);
					auto pPos = GEntityList->Player()->GetPosition();

					if (dashPos != Vec3(0, 0, 0))
					{					
						if (QAntiMelee->GetInteger() == 2 && GetDistance(GEntityList->Player(), target) <= target->GetRealAutoAttackRange(GEntityList->Player())
							&& target->IsMelee() && target->IsFacing(GEntityList->Player()))
						{							
							Q->CastOnPosition(pPos.Extend(target->GetPosition(), -Q->Range()));
							return;
						}

						Q->CastOnPosition(dashPos);

						canAttack = true;
						BaseTarget = target;
					}
				}
			}

			if (target->IsJungleCreep())
			{
				if (Q->IsReady() && JungleQ->Enabled() && (PassiveWCount(target) == jPassiveStacks->GetInteger() - 1 || GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) == 0))
				{
					if (GEntityList->Player()->ManaPercent() > JungleMana->GetInteger())
					{

						auto pPos = GEntityList->Player()->GetPosition();
						auto dash = pPos.Extend(GGame->CursorPosition(), Q->Range());

						if (CheckPosition(dash))
						{
							Q->CastOnPosition(dash);

							canAttack = true;
							BaseTarget = target;
						}
					}
				}
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			{
				if (QCancelAnimation->Enabled())
				{
					GGame->Taunt(kLaugh);
				}
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotE)
			{
				if (TrinketBush->GetInteger() == 1 && !checkVisible && GNavMesh->IsPointGrass(WardPos))
				{
					checkVisible = true;
					CheckTime = GGame->TickCount() + 3000;
				}
			}
		}

		if (strstr(Args.Name_, "TrinketTotemLvl1"))
		{
			if (CheckTime > GGame->TickCount())
			{
				checkVisible = false;
				putWard = false;
			}			
		}

		if (strstr(Args.Name_, "TrinketOrbLvl3"))
		{
			if (CheckTime > GGame->TickCount())
			{
				checkVisible = false;
				putWard = false;
			}
		}

		if (E->IsReady() && AntiFlash->Enabled() && Args.Caster_->IsEnemy(GEntityList->Player()) && strstr(Args.Name_, "SummonerFlash") && CheckTarget(Args.Caster_) && 
			GetDistanceVectors(Args.EndPosition_, GEntityList->Player()->GetPosition()) < 400)
		{
			E->CastOnUnit(Args.Caster_);
		}

		if (Args.Caster_->IsEnemy(GEntityList->Player()) && Args.Caster_->IsHero() && Args.Target_ == GEntityList->Player() && Args.Caster_->IsMelee() && Args.AutoAttack_)
		{
			if (!CheckTarget(Args.Caster_)) return;
			
			if (QAntiMelee->GetInteger() == 1 && Q->IsReady())
			{
				auto pPos = GEntityList->Player()->GetPosition();
				Q->CastOnPosition(pPos.Extend(Args.Caster_->GetPosition(), -Q->Range()));
			}

			if (EGapCloser->Enabled() && E->IsReady() && AntiMeleeMode->GetInteger() == 1)
			{
				auto pPos = GEntityList->Player()->ServerPosition();
				auto distance = GetDistance(GEntityList->Player(), Args.Caster_);
				Vec3 PositionTarget = pPos.Extend(Args.Caster_->ServerPosition(), distance + 470);

				if (CountAlly(PositionTarget, 1000) > CountEnemy(PositionTarget, 1000) || CountAlly(PositionTarget, 1000) == 0)
				{
					if (ChampionAntiMelee[Args.Caster_->GetNetworkId()]->Enabled() && (Args.Caster_->HealthPercent() > 30 || Args.Caster_->HealthPercent() < 50 && Args.Caster_->HealthPercent() > GEntityList->Player()->HealthPercent()))
					{
						E->CastOnUnit(Args.Caster_);
					}
				}
			}
		}
	}

	static void OnExitVisible(IUnit* Source)
	{
		if (TrinketBush->GetInteger() == 1 && checkVisible && EMissile != nullptr && EMissile == Source)
		{
			putWard = true;
			checkVisible = false;
			CheckTime = GGame->TickCount() + 2000;
			timeTrinket = GGame->TickCount() + TrinketBushdelay->GetInteger();
		}
		else if (TrinketBush->GetInteger() == 2)
		{
			if (Source->IsHero() && GOrbwalking->GetLastTarget() == Source && GetDistance(GEntityList->Player(), Source) < 700)
			{
				WardPos = Source->GetPosition();
				putWard = true;				
				CheckTime = GGame->TickCount() + 2000;
				timeTrinket = GGame->TickCount() + TrinketBushdelay->GetInteger();
			}
		}
	}

	static void putWardAfterStun()
	{
		if (TrinketBush->GetInteger() != 0 && putWard && checkWardsTemp() &&
			timeTrinket < GGame->TickCount())
		{
			auto pPos = GEntityList->Player()->GetPosition();
			auto distance = GetDistanceVectors(pPos, WardPos);
			auto check = 200 / 20;

			if (TrinketBush->GetInteger() == 1)
			{
				for (auto i = 1; i < 20; i++)
				{
					JumpPos = pPos.Extend(WardPos, (distance - 200) + (check * i));

					if (GNavMesh->IsPointGrass(JumpPos))
					{
						if (Ward1->IsReady() && Ward1->IsOwned())
						{
							Ward1->CastOnPosition(JumpPos);
						}
						else if (Ward2->IsReady() && Ward2->IsOwned())
						{
							Ward2->CastOnPosition(JumpPos);
						}
					}
				}
			}
			else
			{
				for (auto i = 1; i < 20; i++)
				{
					JumpPos = pPos.Extend(WardPos, (distance + 150) + (check * i));

					if (GNavMesh->IsPointGrass(JumpPos))
					{
						if (Ward1->IsReady() && Ward1->IsOwned())
						{
							Ward1->CastOnPosition(JumpPos);
						}
						else if (Ward2->IsReady() && Ward2->IsOwned())
						{
							Ward2->CastOnPosition(JumpPos);
						}
					}
				}
			}
		}
	}

	static bool checkWardsTemp()
	{
		if (Ward1->IsReady() && Ward1->IsOwned())
		{
			return true;
		}

		if (Ward2->IsReady() && Ward2->IsOwned())
		{
			return true;
		}		

		return false;
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (CheckTarget(Source))
		{
			if (AntiRengar->Enabled() && strstr(Source->GetObjectName(), "Rengar_LeapSound.troy") &&
				Source->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), Source) < E->Range() && E->IsReady())
			{
				E->CastOnUnit(Source);
			}

			if (AntiKhazix->Enabled() && strstr(Source->GetObjectName(), "Khazix_Base_E_Tar.troy") &&
				Source->IsEnemy(GEntityList->Player()) && GetDistance(GEntityList->Player(), Source) <= 300 && E->IsReady())
			{
				E->CastOnUnit(Source);
			}			
		}		
	}	

	static void OnBuffRemove(IUnit* Source, void* BuffData)
	{
		if (GetDistance(GEntityList->Player(), Source) < 500)
		{
			GGame->PrintChat(GBuffData->GetBuffName(BuffData));
		}
	}

	static void OnBeforeAttack(IUnit* target)
	{
		if (target != nullptr && target->IsHero() && RBlock->Enabled() && !IsUnderTurret(GEntityList->Player()) && CountEnemy(GEntityList->Player()->GetPosition(), 800) >= 1 &&
			GEntityList->Player()->HasBuff("VayneInquistion"))
		{
			auto duration = Rdelay->GetInteger();
			auto buff = GEntityList->Player()->GetBuffDataByName("vaynetumblefade");
			auto pHP = GEntityList->Player()->HealthPercent();
			
			if (RMode->GetInteger() == 0 && pHP <= UltPercent->GetInteger())
			{
				if (GBuffData->GetEndTime(buff) - GGame->Time() > GBuffData->GetEndTime(buff) - GBuffData->GetStartTime(buff) - duration / 1000)
				{					
					GOrbwalking->DisableNextAttack();
				}
			}

			else if (RMode->GetInteger() == 1 && pHP <= UltPercent->GetInteger())
			{
				if (CountEnemy(GEntityList->Player()->GetPosition(), 1100) >= UltEnemies->GetInteger())
				{
					GOrbwalking->DisableNextAttack();
				}
			}

			else
			{
				if (GBuffData->GetEndTime(buff) - GGame->Time() > GBuffData->GetEndTime(buff) - GBuffData->GetStartTime(buff) - duration / 1000 &&
					CountEnemy(GEntityList->Player()->GetPosition(), 1100) >= UltEnemies->GetInteger() &&
					pHP <= UltPercent->GetInteger())
				{
					GOrbwalking->DisableNextAttack();
				}
			}
		}
	}
};
