#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"




bool jumpKeyWasDown = false;
bool wAtivo;
float DragonDmg = 0;
double DragonTime = 0;

class Ziggs
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ziggs");

		FarmSettings = MainMenu->AddMenu("Farm Settings");
		{
			farmQout = FarmSettings->CheckBox("Last hit Q minion out range AA", true);
			farmQ = FarmSettings->CheckBox("Lane clear Q", true);
			farmE = FarmSettings->CheckBox("Lane clear E", true);
			useQlcMinions = FarmSettings->AddInteger("Minimum minions in laneclear", 1, 10, 4);
			minManaLC = FarmSettings->AddInteger("Min Mana Lane clear", 0, 100, 60);
			jungleQ = FarmSettings->CheckBox("Jungle clear Q", true);
			jungleW = FarmSettings->CheckBox("Jungle clear W", false);
			jungleE = FarmSettings->CheckBox("Jungle clear E", true);
			minManaJ = FarmSettings->AddInteger("Min Mana Jungle clear", 0, 100, 40);
		}

		QSettings = MainMenu->AddMenu("Q Settings");
		{
			autoQ = QSettings->CheckBox("Auto Q", true);
			harassQ = QSettings->CheckBox("Harass Q", true);
			minManaQHarass = QSettings->AddInteger("Min Mana Q Harass", 0, 100, 30);
		}

		WSettings = MainMenu->AddMenu("W Settings");
		{
			autoW = WSettings->CheckBox("Auto W", true);
			minManaWHarass = WSettings->AddInteger("Min Mana use W", 0, 100, 30);
			interupterW = WSettings->CheckBox("Interrupter W", true);
			turretW = WSettings->CheckBox("Auto Destroy Turrets", true);
			jumpW = WSettings->AddKey("Jump with W", 90);
		}

		ESettings = MainMenu->AddMenu("E Settings");
		{
			autoE = ESettings->CheckBox("Auto E on CC", true);
			comboE = ESettings->CheckBox("Auto E Combo", true);
			minManaE = ESettings->AddInteger("Min Mana use E", 0, 100, 30);
			gapcloserE = ESettings->CheckBox("Anti Gapcloser E", true);
			opsE = ESettings->CheckBox("OnProcessSpellCastE", true);
			telE = ESettings->CheckBox("Auto E Teleport", true);
		}

		RSettings = MainMenu->AddMenu("R Settings");
		{
			autoR = RSettings->CheckBox("Auto R", true);
			minHpRTarget = RSettings->AddInteger("Min Target HP %", 0, 100, 60);
			Rcc = RSettings->CheckBox("R on Target CC", true);
			Raoe = RSettings->AddInteger("R Aoe", 2, 5, 3);
			killstealR = RSettings->CheckBox("R on KS", true);
			minRangeKillR = RSettings->AddInteger("Min R KS Range", 1, 2000, 900);
			maxRangeKillR = RSettings->AddInteger("Max R KS Range", 2000, 5000, 3000);
			keyToR = RSettings->AddKey("Semi-manual cast R key", 71);
			AutoRjungle = RSettings->CheckBox("R Jungle Stealer", true);
			Rdragon = RSettings->CheckBox("Dragon", true);
			Rbaron = RSettings->CheckBox("Baron", true);
			Rred = RSettings->CheckBox("Red", true);
			Rblue = RSettings->CheckBox("Blue", true);
			Rally = RSettings->CheckBox("Ally Stealer", false);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			noti = DrawingSettings->CheckBox("Show notification", false);
		}

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 7, 1);
		}
	}

	static void InitializeSpells()
	{
		Q1 = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, kCollidesWithYasuoWall);
		Q1->SetSkillshot(0.25f, 140.f, 1700.f, 850.f);
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, kCollidesWithYasuoWall);
		Q2->SetSkillshot(0.4f, 50.f, 1650.f, 1115.f);
		Q3 = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, kCollidesWithYasuoWall);
		Q3->SetSkillshot(0.6f, 50.f, 1650.f, 1390.f);

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithYasuoWall);
		W->SetSkillshot(0.25f, 275.f, 1750.f, 1000.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(0.50f, 235.f, 1750.f, 900.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, kCollidesWithYasuoWall);
		R->SetSkillshot(0.25f, 500.f, 1000.f, 5300.f);	
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
	}


	static bool FoundEnemies(IUnit* source, float range)
	{
		for (auto enemys : GEntityList->GetAllHeros(false, true))
		{
			if (source->IsValidTarget(enemys, range))
				return true;
		}

		return false;
	}

	static int CountMinions(Vec3 Location, int range)
	{
		int Count = 0;

		for (auto Minions : GEntityList->GetAllMinions(false, true, false))
		{
			if ((Minions->GetPosition() - Location).Length() < range && Minions->IsValidTarget() && !Minions->IsDead())
			{
				Count++;
			}
		}
		return (Count);
	}

	static int CountEnemy(Vec3 Location, int range)
	{
		int Count = 0;

		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if ((Enemy->GetPosition() - Location).Length() < range && Enemy->IsValidTarget() && !Enemy->IsDead())
			{
				Count++;
			}
		}
		return (Count);
	}

	static int CountAlly(Vec3 Location, int range)
	{
		int Count = 0;

		for (auto Ally : GEntityList->GetAllHeros(true, false))
		{
			if ((Ally->GetPosition() - Location).Length() < range && Ally->IsValidTarget() && !Ally->IsDead() && Ally != GEntityList->Player())
			{
				Count++;
			}
		}
		return (Count);
	}

	static bool IsUnderTurret(IUnit* source)
	{
		for (auto turret : GEntityList->GetAllTurrets(false, true))
		{
			if (source->IsValidTarget(turret, 950.0f))
				return true;
		}

		return false;
	}

	static bool FoundMinionsNeutral(float range)
	{
		for (auto Minions : GEntityList->GetAllMinions(false, false, true))
		{
			if (GEntityList->Player()->IsValidTarget(Minions, range))
				return true;
		}

		return false;
	}

	static bool FoundMinions(float range)
	{
		for (auto Minions : GEntityList->GetAllMinions(false, true, false))
		{
			if (GEntityList->Player()->IsValidTarget(Minions, range))
				return true;
		}

		return false;
	}

	static void CheckKeyPresses()
	{
		keystate = GetAsyncKeyState(jumpW->GetInteger());

		if (keystate < 0)
		{
			if (jumpKeyWasDown == false)
			{
				jumpKeyWasDown = true;
			}
		}
		else
		{
			jumpKeyWasDown = false;
		}
	}

	static bool CanMove(IUnit* target)
	{
		if (target->MovementSpeed() < 50 || target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Fear) || target->HasBuffOfType(BUFF_Snare) || target->HasBuffOfType(BUFF_Knockup) || target->HasBuff("Recall") ||

			target->HasBuffOfType(BUFF_Knockback) || target->HasBuffOfType(BUFF_Charm) || target->HasBuffOfType(BUFF_Taunt) || target->HasBuffOfType(BUFF_Suppression))

		{
			return false;
		}
		else
		{
			return true;
		}
	}

	static float GetDistance(IUnit* source, IUnit* target)
	{
		auto x1 = source->GetPosition().x;
		auto x2 = target->GetPosition().x;
		auto y1 = source->GetPosition().y;
		auto y2 = target->GetPosition().y;
		auto z1 = source->GetPosition().z;
		auto z2 = target->GetPosition().z;
		return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
	}

	static float GetDistanceVectors(Vec3 from, Vec3 to)
	{
		float x1 = from.x;
		float x2 = to.x;
		float y1 = from.y;
		float y2 = to.y;
		float z1 = from.z;
		float z2 = to.z;
		return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
	}

	static Vec3 GetTrapPos(float range)
	{

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{

			if (enemy->IsValidTarget() && GetDistance(GEntityList->Player(), enemy) < range && (enemy->HasBuff("BardRStasis") || enemy->HasBuffOfType(BUFF_Invulnerability)))
			{
				return enemy->GetPosition();
			}


			for (auto object : GEntityList->GetAllUnits())
			{
				if (object->IsValidObject() && GetDistance(GEntityList->Player(), object) < range)
				{

					auto name = object->GetObjectName();

					if (strstr(object->GetObjectName(), "gatemarker_red.troy") || strstr(object->GetObjectName(), "global_ss_teleport_target_red.troy") ||
						strstr(object->GetObjectName(), "lifeaura") && GetDistance(enemy, object) < 200 || strstr(object->GetObjectName(), "r_indicator_red.troy"))
					{
						return object->GetPosition();
					}
				}

			}
		}

		return Vec3(0, 0, 0);
	}

	static bool IsMovingInSameDirection(IUnit* source, IUnit* target)
	{
		auto sourceLW = source->GetWaypointList().front();

		if (sourceLW == source->GetPosition() || !source->IsMoving())
		{
			return false;
		}

		auto targetLW = target->GetWaypointList().front();

		if (targetLW == target->GetPosition() || !target->IsMoving())
		{
			return false;
		}

		Vec2 pos1 = sourceLW.To2D() - source->GetPosition().To2D();
		Vec2 pos2 = targetLW.To2D() - target->GetPosition().To2D();

		auto getAngle = pos1.AngleBetween(pos2);

		if (getAngle < 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static bool ValidUlt(IUnit* target)
	{
		if (target->HasBuffOfType(BUFF_PhysicalImmunity) || target->HasBuffOfType(BUFF_SpellImmunity)

			|| target->IsInvulnerable() || target->HasBuffOfType(BUFF_Invulnerability) || target->HasBuff("kindredrnodeathbuff")

			|| target->HasBuffOfType(BUFF_SpellShield))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	static float GetUltTravelTime(IUnit* source, float speed, float delay, Vec3 targetpos)
	{
		float distance = GetDistanceVectors(source->GetPosition(), targetpos);
		float missilespeed = speed;

		return (distance / missilespeed + delay);
	}

	static void KsJungle()
	{
		for (auto mob : GEntityList->GetAllMinions(false, false, true))
		{
			if (mob->GetHealth() == mob->GetMaxHealth())
			{
				continue;
			}

			if (((strstr(mob->GetObjectName(), "Dragon") && Rdragon->Enabled())
				|| (strstr(mob->GetObjectName(), "Baron") && Rbaron->Enabled())
				|| (strstr(mob->GetObjectName(), "Red") && Rred->Enabled())
				|| (strstr(mob->GetObjectName(), "Blue") && Rblue->Enabled()))
				&& (CountAlly(mob->GetPosition(), 1000) == 0 || Rally->Enabled())
				&& GetDistanceVectors(GEntityList->Player()->GetPosition(), mob->GetPosition()) > 1000)
			{
				if (DragonDmg == 0)
					DragonDmg = mob->GetHealth();

				if (GGame->Time() - DragonTime > 3)
				{
					if (DragonDmg - mob->GetHealth() > 0)
					{
						DragonDmg = mob->GetHealth();
					}
					DragonTime = GGame->Time();
				}
				else
				{
					auto DmgSec = (DragonDmg - mob->GetHealth()) * (std::abs(DragonTime - GGame->Time()) / 3);

					if (DragonDmg - mob->GetHealth() > 0)
					{

						auto timeTravel = GetUltTravelTime(GEntityList->Player(), R->Speed(), R->GetDelay(), mob->GetPosition());
						auto timeR = (mob->GetHealth() - GDamage->GetSpellDamage(GEntityList->Player(), mob, kSlotR)) / (DmgSec / 3);

						if (timeTravel > timeR)
						{
							R->CastOnPosition(mob->GetPosition());
						}
					}
					else
					{
						DragonDmg = mob->GetHealth();
					}
				}
			}
		}
	}

	static void LogicW()
	{
		if (!autoW->Enabled() || !W->IsReady()) { return; }

		if (GEntityList->Player()->GetSpellBook()->GetToggleState(kSlotW) == 0)
		{
			if (jumpKeyWasDown)
			{
				Vec2 posToJumpV2 = GEntityList->Player()->GetPosition().To2D().Extend(GGame->CursorPosition().To2D(), -100);
				Vec3 posToJump;
				posToJump.x = posToJumpV2.x;
				posToJump.y = GEntityList->Player()->GetPosition().y;
				posToJump.z = posToJumpV2.y;

				W->CastOnPosition(posToJump);
			}		

			
				for (auto hero : GEntityList->GetAllHeros(false, true))
				{
					if (hero != nullptr && hero->IsValidTarget(GEntityList->Player(), W->Range()) && !hero->IsInvulnerable() && !hero->IsDead())
					{
						if (GetDistance(GEntityList->Player(), hero) < 350 && hero->IsMelee() && hero->IsFacing(GEntityList->Player()))
						{
							auto delay = W->GetDelay() + GetDistance(GEntityList->Player(), hero) / 1750;

							Vec3 FuturePos;
							GPrediction->GetFutureUnitPosition(hero, delay, true, FuturePos);

							Vec2 TargetPos = FuturePos.To2D().Extend(GEntityList->Player()->GetPosition().To2D(), 50);
							Vec3 sendHere;

							sendHere.x = TargetPos.x;
							sendHere.y = FuturePos.y;
							sendHere.z = TargetPos.y;

							W->CastOnPosition(sendHere);
						}

						auto predDelay = W->GetDelay() + GetDistance(GEntityList->Player(), hero) / 1750;
						Vec3 predPos;
						GPrediction->GetFutureUnitPosition(hero, predDelay, true, predPos);

						auto heroDistance = GetDistance(GEntityList->Player(), hero);
						auto futureDistance = GetDistanceVectors(GEntityList->Player()->GetPosition(), predPos);

						if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && GEntityList->Player()->ManaPercent() > minManaWHarass->GetInteger())
						{
							if (heroDistance < futureDistance && heroDistance > 500)
							{
								Vec2 TargetPos = predPos.To2D().Extend(GEntityList->Player()->GetPosition().To2D(), heroDistance + 250);
								Vec3 sendHere;

								sendHere.x = TargetPos.x;
								sendHere.y = predPos.y;
								sendHere.z = TargetPos.y;

								W->CastOnPosition(sendHere);
							}
							else if (heroDistance > futureDistance && heroDistance < 500)
							{
								Vec2 TargetPos = predPos.To2D().Extend(GEntityList->Player()->GetPosition().To2D(), heroDistance - 250);
								Vec3 sendHere;

								sendHere.x = TargetPos.x;
								sendHere.y = predPos.y;
								sendHere.z = TargetPos.y;

								W->CastOnPosition(sendHere);

							}
						}
				}
			}

			if (turretW->Enabled())
			{
				for (auto turret : GEntityList->GetAllTurrets(false, true))
				{
					if (turret != nullptr && GEntityList->Player()->IsValidTarget(turret, W->Range()) && turret->HealthPercent() < 22.5 + (GEntityList->Player()->GetSpellLevel(kSlotW) * 2.5))
					{
						W->CastOnUnit(turret);
					}
				}
			} 
		}
		else
		{
			W->CastOnPlayer();
		}
	}

	static void LogicE()
	{
		if (GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() && autoE->Enabled() && E->IsReady())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (hero != nullptr && hero->IsValidTarget(GEntityList->Player(), E->Range() + 100) && !hero->IsInvulnerable() && !hero->IsDead())
				{
					if (GetDistance(GEntityList->Player(), hero) < 400 && hero->IsMelee() && hero->IsFacing(GEntityList->Player()))
					{
						E->CastOnTarget(hero, kHitChanceHigh);
					}

					if (hero->IsValidTarget(GEntityList->Player(), E->Range() + 50) && !CanMove(hero))
					{
						E->CastOnTarget(hero, kHitChanceHigh);
						return;
					}

					if (telE->Enabled())
					{
						auto trapPos = GetTrapPos(E->Range());

						if (trapPos.x > 0 && trapPos.y > 0)
						{
							E->CastOnPosition(trapPos);
						}
					}

					if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && GEntityList->Player()->IsMoving() && comboE->Enabled() && GEntityList->Player()->ManaPercent() > minManaE->GetInteger())
					{
						auto eTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

						if (GetDistance(GEntityList->Player(), eTarget) < E->Range() && eTarget->IsValidTarget() && !eTarget->IsDead() && !eTarget->IsInvulnerable())
						{
							E->CastOnTargetAoE(eTarget, 2, kHitChanceHigh);

							if (eTarget->HasBuffOfType(BUFF_Slow))
							{
								E->CastOnTarget(eTarget, kHitChanceHigh);
							}

							if (IsMovingInSameDirection(GEntityList->Player(), eTarget))
							{
								E->CastOnTarget(eTarget, kHitChanceHigh);
							}
						}
					}
					else if (GEntityList->Player()->ManaPercent() > minManaLC->GetInteger() && farmE->Enabled())
					{
						Vec3 posE;
						int allMinions;
						GPrediction->FindBestCastPosition(E->Range() - 50, E->Radius(), false, true, false, posE, allMinions);

						if (allMinions >= useQlcMinions->GetInteger())
						{
							E->CastOnPosition(posE);
						}
					}
				}
			}
		}
	}

	static void LogicR()
	{

		if (autoR->Enabled() && R->IsReady())
		{
			auto minHpCombo = minHpRTarget->GetInteger();

			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (hero->IsValidTarget(GEntityList->Player(), R->Range()) && ValidUlt(hero))
				{
					auto damageDagameR = GHealthPrediction->GetKSDamage(hero, kSlotR, R->GetDelay(), false);

					if (damageDagameR > hero->GetHealth() && killstealR->Enabled() &&
						GetDistance(GEntityList->Player(), hero) > minRangeKillR->GetInteger() &&
						GetDistance(GEntityList->Player(), hero) < maxRangeKillR->GetInteger())
					{
						R->CastOnTarget(hero, kHitChanceHigh);
					}

					if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && hero->HealthPercent() < minHpCombo)
					{
						R->CastOnTargetAoE(hero, Raoe->GetInteger(), kHitChanceHigh);
					}

					if (Rcc->Enabled() && !CanMove(hero) && hero->HealthPercent() < minHpCombo)
					{
						R->CastOnTarget(hero, kHitChanceHigh);
					}
				}
			}
		}
	}

	std::vector<Vec3*> CirclePoints(float CircleLineSegmentN, float radius, Vec3 *position)
	{

		std::vector<Vec3*> points;

		for (auto i = 1; i <= CircleLineSegmentN; i++)
		{

			auto angle = i * 2 * 3.1415927 / CircleLineSegmentN;
			auto point = new Vec3(position->x + radius * static_cast<float>(std::cos(angle)), position->y + radius * static_cast<float>(std::sin(angle)), position->z);

			points.push_back(point);
		}
		return points;
	}

	static void CastQ(IUnit* target)
	{
		if (!Q1->IsReady() || target->IsDead() || target->IsInvulnerable()){ return; }

		Vec3 predictionQ1, predictionQ2, predictionQ3;
		Vec2 pos1, pos2, pos3;
		Vec3 pos13D, pos23D, pos33D;
		int hitsQ1, hitsQ2, hitsQ3;

		auto delayQ1 = Q1->GetDelay() + GetDistance(GEntityList->Player(), target) / Q1->Speed();
		auto delayQ2 = Q2->GetDelay() + GetDistance(GEntityList->Player(), target) / Q2->Speed();
		auto delayQ3 = Q3->GetDelay() + GetDistance(GEntityList->Player(), target) / Q3->Speed();

		Q1->FindBestCastPosition(false, true, predictionQ1, hitsQ1);
		Q2->FindBestCastPosition(false, true, predictionQ2, hitsQ2);
		Q3->FindBestCastPosition(false, true, predictionQ3, hitsQ3);

		//if (GPrediction->GetCollisionFlagsForPoint(target->GetPosition()) == kCollidesWithHeroes)
		//GPrediction->GetFutureUnitPosition(target, delayQ1, true, predictionQ1);

		if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ1) > Q1->Range())
		{
			pos2 = GEntityList->Player()->GetPosition().To2D().Extend(predictionQ1.To2D(), Q1->Range());
			pos23D.x = pos2.x;
			pos23D.y = predictionQ1.y;
			pos23D.z = pos2.y;

			if (CountMinions(pos23D, 280) > 0)
			{
				return;
			}

			if (GPrediction->IsPointWall(pos23D))
			{
				return;
			}

			if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ2) > Q2->Range())
			{
				pos3 = GEntityList->Player()->GetPosition().To2D().Extend(predictionQ1.To2D(), Q2->Range());
				pos33D.x = pos3.x;
				pos33D.y = predictionQ2.y;
				pos33D.z = pos3.y;

				if (CountMinions(pos33D, 280) > 0)
				{
					return;
				}

				if (GPrediction->IsPointWall(pos33D))
				{
					return;
				}
				if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ3) > Q3->Range())
				{
					return;
				}
				else if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ3) < Q3->Range() && hitsQ3 >= 1)
				{
					Q3->CastOnPosition(predictionQ3);
				}
			}
			else if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ2) < Q2->Range() && hitsQ2 >= 1)
			{
				Q2->CastOnPosition(predictionQ2);
			}
		}
		else if (GetDistanceVectors(GEntityList->Player()->GetPosition(), predictionQ1) < Q1->Range() && hitsQ1 >= 1)
		{
			Q1->CastOnPosition(predictionQ1);
		}
	}	

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (args.Sender->IsEnemy(GEntityList->Player()) && args.Sender->IsHero())
		{
			if (gapcloserE->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())
			{
				if (GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost())
				{
					E->CastOnPosition(args.EndPosition);
				}
			}
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (interupterW->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < W->Range())
		{
			if (GEntityList->Player()->GetSpellBook()->GetToggleState(kSlotW) == 0)
			{
				W->CastOnTarget(Args.Target, kHitChanceHigh);
			}
			else
			{
				W->CastOnPlayer();
			}
		}
	}	
};
