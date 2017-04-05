#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class Vayne
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Vayne");

		QSettings = MainMenu->AddMenu("Tumble Settings");
		{
			AutoQ = QSettings->CheckBox("Auto Use Q", true);
			ComboQH = QSettings->AddSelection("Q Modes", 2, std::vector<std::string>({ "Q To Cursor", "Side Q", "Safe Q", "Beta Q", "Gosu" }));						
			ComboQA = QSettings->CheckBox("Auto Q when R active", true);			
			PassiveStacks = QSettings->AddInteger("Q at X stack", 1, 2, 2);
			QAfterAA = QSettings->CheckBox("Q only after AA", false);			
			EnemyCheck = QSettings->AddInteger("Block Q in x enemies", 1, 5, 3);
			WallCheck = QSettings->CheckBox("Block Q in wall", false);
			TurretCheck = QSettings->CheckBox("Block Q under turret", false);
			AAcheck = QSettings->CheckBox("Q only in AA range", false);
			QAntiMelee = QSettings->CheckBox("Auto Q Anti Melee", true);
			QCancelAnimation = QSettings->CheckBox("Q Cancel Animation", false);			
		}

		ESettings = MainMenu->AddMenu("Condemn Settings");
		{
			AutoE = ESettings->AddSelection("Condemn Mode", 0, std::vector<std::string>({ "Combo & Harass", "Automatic", "Off" }));
			ComboE = ESettings->AddSelection("Condemn Method", 2, std::vector<std::string>({ "Method 1", "Method 2", "Method 3" }));
			RangeE = ESettings->AddFloat("Condemn Max Range", 400, 760, 550);
			PushDistance = ESettings->AddInteger("Push Distance", 300, 470, 420);
			RWall = ESettings->AddSelection("Flash E Mode", 1, std::vector<std::string>({ "Automatic", "PressKey + LowHP", "Press Key", "OFF" }));
			HealthE = ESettings->AddInteger("Flash E Low HP% (1x1)", 1, 50, 15);
			SemiManualKey = ESettings->AddKey("Flash E Key", 71);
			KillstealE = ESettings->CheckBox("Smart E KS", false);
		}

		EMenu = ESettings->AddMenu("Condemn Extras");
		{
			EInterrupter = EMenu->CheckBox("Use Condemn Interrupter", true);
			AntiSpells = EMenu->CheckBox("Interrupt Danger Spells", true);			
			AntiRengar = EMenu->CheckBox("Interrupt Rengar Jump", true);
			AntiKhazix = EMenu->CheckBox("Interrupt Khazix R", true);
			AntiFlash = EMenu->CheckBox("Condemn on Enemy Flashes", true);
			AntiKindred = EMenu->CheckBox("Inside Kindred R", true);
		}

		EMenuGap = ESettings->AddMenu("Melee & Gapcloser");
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

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			jPassiveStacks = JungleClearSettings->AddInteger("Q at X stack", 1, 2, 2);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);			
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 40);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{			
			zzRot = fedMiscSettings->AddKey("[Beta] ZZrot Condemn", 0x49);
			EOrder = fedMiscSettings->CheckBox("Focus W stacks Target", true);
			TrinketBush = fedMiscSettings->AddSelection("Trinket Bush Mode", 2, std::vector<std::string>({ "Off", "Only After Condemn", "Last Target Enter" }));
			TrinketBushdelay = fedMiscSettings->AddInteger("Trinket Delay (ms)", 0, 600, 180);			
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", false);			
			DrawE = DrawingSettings->CheckBox("Draw E", true);			
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
		Ward2 = GPluginSDK->CreateItemForId(3363, 900);		
	}

	static double Wdmg(IUnit* target)
	{
		return target->GetMaxHealth() * (4.5 + GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) * 1.5) * 0.01;
	}

	static void EAntiMelee()
	{		
		if (EGapCloser->Enabled() && E->IsReady() && AntiMeleeMode->GetInteger() == 0)
		{
			for (auto target : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(target)) return;

				if (target->IsMelee() && GetDistance(GEntityList->Player(), target) < 300 && target->IsValidTarget(GEntityList->Player(), GOrbwalking->GetAutoAttackRange(GEntityList->Player())))
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
	
	static void RotE()
	{
		zzRots = GPluginSDK->CreateItemForId(3512, 400);
		zzRots->SetRange(400);
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 400);
		if (E->IsReady() && zzRots->IsTargetInRange(target) && zzRots->IsReady() && target != nullptr)
		{
			if (zzRots->CastOnPosition(target->ServerPosition()))
			{
				E2->CastOnUnit(target);
			}
		}
	}

	static void zzRotRun()
	{
		if (GetAsyncKeyState(zzRot->GetInteger()))
		{
			zzRots = GPluginSDK->CreateItemForId(3512, 400);
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 400);
			if (E->IsReady() && zzRots->IsTargetInRange(target) && zzRots->IsReady() && target != nullptr)
			{
				if (zzRots->CastOnPosition(target->ServerPosition()))
				{
					E2->CastOnUnit(target);
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
				GOrbwalking->SetOverrideTarget(enemy.MaxOrDefault<float>([](IUnit* i) {return i->GetBuffCount("VayneSilveredDebuff"); }));
			}

			else if (minions.Any() && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
			{
				//GOrbwalking->SetOverrideTarget(minions.MaxOrDefault<float>([](IUnit* i) {return i->GetBuffCount("VayneSilveredDebuff"); }));
			}

			else
			{
				GOrbwalking->SetOverrideTarget(nullptr);
			}
		}
	}

	static bool AARange(Vec3 point)
	{
		if (!AAcheck->Enabled())
		{
			return true;
		}
		else if (GOrbwalking->GetLastTarget() != nullptr && GOrbwalking->GetLastTarget()->IsHero())
		{
			return GetDistanceVectors(point, GOrbwalking->GetLastTarget()->GetPosition()) < GEntityList->Player()->AttackRange();
		}
		else
		{
			return CountEnemy(point, GEntityList->Player()->AttackRange()) > 0;
		}
	}

	static bool GPosition(Vec3 Pos)
	{
		if (WallCheck->Enabled())
		{
			float segment = Q->Range() + 50 / 5;

			for (int i = 1; i <= 5; i++)
			{
				auto pPos = GEntityList->Player()->GetPosition();

				if (GPrediction->IsPointWall(pPos.Extend(Pos, i * segment)))
				{
					return false;
				}
			}
		}

		if (TurretCheck->Enabled())
		{
			if (IsUnderTurretPos(Pos) && !IsUnderTurret(GEntityList->Player()))
			{
				return false;
			}
		}

		auto enemyCheck = EnemyCheck->GetInteger();
		auto enemyCount = CountEnemy(Pos, 600);

		if (enemyCheck > enemyCount)
		{
			return true;
		}

		auto enemyCountPlayer = CountEnemy(GEntityList->Player()->GetPosition(), 400);

		if (enemyCount <= enemyCountPlayer)
		{
			return true;
		}

		return false;
	}

	static Vec3 PosQ(bool asap = false, IUnit* target = nullptr)
	{
		int Mode = ComboQH->GetInteger();

		Vec3 bestpoint;
		auto pPos = GEntityList->Player()->GetPosition();
		auto cPos = GGame->CursorPosition();

		if (Mode == 0)
		{
			bestpoint = pPos.Extend(cPos, Q->Range());
		}
		else if (Mode == 1)
		{
			auto orbT = GOrbwalking->GetLastTarget();

			if (orbT != nullptr && orbT->IsHero())
			{
				Vec2 start = pPos.To2D();
				Vec2 end = orbT->GetPosition().To2D();

				auto dir = (end - start).VectorNormalize();
				auto pDir = dir.Perpendicular();

				auto rightEndPos = end + pDir * GetDistance(GEntityList->Player(), orbT);
				auto leftEndPos = end - pDir * GetDistance(GEntityList->Player(), orbT);

				auto rEndPos = Vec3(rightEndPos.x, GEntityList->Player()->GetPosition().y, rightEndPos.y);
				auto lEndPos = Vec3(leftEndPos.x, GEntityList->Player()->GetPosition().y, leftEndPos.y);

				if (GetDistanceVectors(cPos, rEndPos) < GetDistanceVectors(cPos, lEndPos))
				{
					bestpoint = pPos.Extend(rEndPos, Q->Range());
				}
				else
				{
					bestpoint = pPos.Extend(lEndPos, Q->Range());
				}
			}
		}
		else if (Mode == 2)
		{
			auto points = CirclePoints(15, Q->Range(), pPos);
			bestpoint = pPos.Extend(cPos, Q->Range());
			auto enemies = CountEnemy(bestpoint, 350);

			for (auto point : points)
			{
				auto count = CountEnemy(point, 350);

				if (!AARange(point))
					continue;
				if (IsUnderTurretPosAlly(point))
				{
					bestpoint = point;
					enemies = count - 1;
				}
				else if (count < enemies)
				{
					enemies = count;
					bestpoint = point;
				}
				else if (count == enemies && GetDistanceVectors(cPos, point) < GetDistanceVectors(cPos, bestpoint))
				{
					enemies = count;
					bestpoint = point;
				}
			}
		}
		else if (Mode == 3)
		{
			auto direction = GEntityList->Player()->Direction().To2D().Perpendicular();
			for (auto i = 0.f; i < 360.f; i += 45)
			{
				auto angleRads = DegreeToRadian(i);
				auto rotatedPosition = GEntityList->Player()->GetPosition().To2D() + (300.f * direction.Rotated(angleRads));

				if (target->IsValidTarget(GEntityList->Player(), 300.f) && GPosition(Get3DPoint(rotatedPosition)))
				{
					bestpoint = Get3DPoint(rotatedPosition);
				}
			}
		}
		else
		{			
			// lord Gosu
			auto after = GEntityList->Player()->GetPosition() + (GGame->CursorPosition() - GEntityList->Player()->GetPosition()).VectorNormalize() * 300;
			auto disafter = pow((after - target->GetPosition()).Length(), 2);

			if ((disafter < 630 * 630) && disafter > 150 * 150)
			{
				return GGame->CursorPosition();
			}
			if (pow((target->GetPosition() - GEntityList->Player()->GetPosition()).Length(), 2) > 630 * 630 && disafter < 630 * 630)
			{
				return GGame->CursorPosition();
			}
		}

		if (bestpoint == Vec3(0, 0, 0))
		{
			return Vec3(0, 0, 0);
		}

		auto GoodPos = GPosition(bestpoint);

		if (asap && GoodPos)
		{
			return bestpoint;
		}
		else if (GoodPos && AARange(bestpoint))
		{
			return bestpoint;
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
		if (target == nullptr || !target->IsValidTarget(GEntityList->Player(), RangeE->GetFloat())
			|| target->IsDead() || target->IsDashing()
			|| target->HasBuffOfType(BUFF_SpellShield)
			|| target->HasBuffOfType(BUFF_SpellImmunity)
			|| (!target->IsHero() && !target->IsJungleCreep()))
			return false;

		AdvPredictionOutput prediction_output;
		E->RunPrediction(target, false, kCollidesWithYasuoWall, &prediction_output);

		// VHR
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

					return true;
				}
			}
		}
		return false;
	}

	static bool IsCondemable2(IUnit* target, Vec3 from, int PushDistance, bool CondemnCurrent)
	{
		if (target == nullptr || !target->IsValidTarget(GEntityList->Player(), RangeE->GetFloat())
			|| target->IsDead() || target->IsDashing()
			|| target->HasBuffOfType(BUFF_SpellShield)
			|| target->HasBuffOfType(BUFF_SpellImmunity)
			|| (!target->IsHero() && !target->IsJungleCreep()))
			return false;

		AdvPredictionOutput prediction_output;
		E->RunPrediction(target, false, kCollidesWithYasuoWall, &prediction_output);

		// Shine
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

					return true;
				}
			}
		}
		return false;
	}

	static void Automatic()
	{
		FocusTargetW();
		UseUltimate();
		putWardAfterStun();

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
					if (E->IsReady() && Wdmg(Hero) + GDamage->GetSpellDamage(GEntityList->Player(), Hero, kSlotE) > Hero->GetHealth() + (Hero->HPRegenRate() * 2) + 10 && Hero->GetBuffCount("VayneSilveredDebuff") == 2)
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
				auto dashPos = PosQ();
				if (dashPos != Vec3(0, 0, 0))
				{
					Q->CastOnPosition(dashPos);
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

						if (GPosition(dash))
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
					}
				}
				else
				{
					if (IsCondemable2(target, GEntityList->Player()->GetPosition(), PushDistance->GetInteger(), false))
					{
						E->CastOnUnit(target);
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

	static void LastHit()
	{
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

		if (jMonster != nullptr)
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

	static void LaneClear()
	{

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

		//GRender->DrawOutlinedCircle(PosQ(), Vec4(255, 255, 255, 255), 30);
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

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (target->IsHero() && !target->IsDead())
		{			
			if (AutoQ->Enabled() && Q->IsReady() &&
				(target->GetBuffCount("VayneSilveredDebuff") == PassiveStacks->GetInteger() - 1
					|| GEntityList->Player()->HasBuff("VayneInquisition")
					|| GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) == 0))
			{
				auto dashPos = PosQ(true);
				if (dashPos != Vec3(0, 0, 0))
				{
					Q->CastOnPosition(dashPos);

					canAttack = true;
					BaseTarget = target;
				}
			}			
		}		

		if (target->IsJungleCreep())
		{
			if (Q->IsReady() && JungleQ->Enabled() && (target->GetBuffCount("VayneSilveredDebuff") == jPassiveStacks->GetInteger() - 1 || GEntityList->Player()->GetSpellBook()->GetLevel(kSlotW) == 0))
			{
				if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;

				auto pPos = GEntityList->Player()->GetPosition();
				auto dash = pPos.Extend(GGame->CursorPosition(), Q->Range());

				if (!GPosition(dash)) return;

				Q->CastOnPosition(dash);
				
				canAttack = true;
				BaseTarget = target;
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

		if (Args.Caster_->IsEnemy(GEntityList->Player()) && Args.Caster_->IsHero() && Args.Target_ == GEntityList->Player() && Args.Caster_->IsMelee() && Args.AutoAttack_)
		{
			if (!CheckTarget(Args.Caster_)) return;
			
			if (QAntiMelee->Enabled() && Q->IsReady())
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
		SArray<IUnit*> Rengar = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* Aliados) {return Aliados != nullptr &&
			!Aliados->IsDead() && GetDistance(GEntityList->Player(), Aliados) < E->Range() &&
			(strstr(Aliados->ChampionName(), "Rengar") || strstr(Aliados->ChampionName(), "Khazix")); });	

	}

	static void OnDeleteObject(IUnit* Source)
	{

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
