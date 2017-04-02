#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Kindred
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Kindred");

		RSettings = MainMenu->AddMenu("R Settings");
		{
			ComboR = RSettings->CheckBox("Use R", true);
			RAllys = RSettings->AddInteger("Min Allys in Range R", 1, 5, 1);
			REnemies = RSettings->AddInteger("Max Enemies in Range R", 1, 5, 4);
			UltPercent = RSettings->AddInteger("Min HP% To R", 1, 100, 15);
			for (auto ally : GEntityList->GetAllHeros(true, false))
			{
				std::string szMenuName = "Use R on - " + std::string(ally->ChampionName());
				ChampionUse[ally->GetNetworkId()] = RSettings->CheckBox(szMenuName.c_str(), true);
			}
		}

		QSettings = MainMenu->AddMenu("Q Settings");
		{
			ComboQH = QSettings->AddSelection("Q Modes", 0, std::vector<std::string>({ "Q To Cursor", "Q Side", "Safe Q" }));
			EnemyCheck = QSettings->AddInteger("Block Q in x enemies", 1, 5, 3);
			WallCheck = QSettings->CheckBox("Block Q in wall", true);
			TurretCheck = QSettings->CheckBox("Block Q under turret", true);
			AAcheck = QSettings->CheckBox("Q only in AA range", true);
		}

		ESettings = MainMenu->AddMenu("E Settings");
		{
			EOrder = ESettings->CheckBox("Focus E Target", true);
			for (auto enemys : GEntityList->GetAllHeros(false, true))
			{
				std::string szMenuName = "Use E on - " + std::string(enemys->ChampionName());
				ChampionUseE[enemys->GetNetworkId()] = ESettings->CheckBox(szMenuName.c_str(), true);
			}
		}
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{					
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);			
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);
			LaneClearW = LaneClearSettings->CheckBox("W laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("LaneClear minimum minions", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleEBig = JungleClearSettings->CheckBox("W & E only Big Mobs", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 30);
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 500, 1400, 340);

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1400, 800);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 500);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 500);
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
			float segment = Q->Range() / 5;

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
			if (IsUnderTurretPos(Pos))
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

	static Vec3 PosQ(bool asap = false)
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

	static void Automatic()
	{	
		FocusTargetE();	
	}

	static void FocusTargetE()
	{
		if (EOrder->Enabled())
		{
			SArray<IUnit*> enemy = SArray<IUnit*>(GEntityList->GetAllHeros(false,true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) &&
				m->HasBuff("KindredERefresher"); });

			SArray<IUnit*> minions = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), GEntityList->Player()->AttackRange()) &&
				m->HasBuff("KindredERefresher"); });

			if (enemy.Any())
			{
				GOrbwalking->SetOverrideTarget(enemy.FirstOrDefault());
			}

			if (minions.Any())
			{
				GOrbwalking->SetOverrideTarget(minions.FirstOrDefault());
			}
		}
	}

	static void Combo()
	{
		if (Q->IsReady() && GEntityList->Player()->GetMana() > R->ManaCost() + Q->ManaCost() && ComboQ->Enabled())
		{
			if (GOrbwalking->GetLastTarget() != nullptr) return;

			auto qPos = PosQ();

			if (qPos != Vec3(0, 0, 0) && CountEnemy(qPos, 550) > 0)
			{
				Q->CastOnPosition(qPos);
			}
		}

		auto wTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());

		if (!CheckTarget(wTarget)) return;

		if (W->IsReady() && GEntityList->Player()->GetMana() > R->ManaCost() + W->ManaCost() && ComboW->Enabled())
		{
			if (wTarget->IsValidTarget(GEntityList->Player(), 650) && !Q->IsReady())
			{
				W->CastOnPlayer();
			}
		}

		if (E->Range() && GEntityList->Player()->GetMana() > R->ManaCost() + E->ManaCost() && ComboE->Enabled())
		{
			if (wTarget->IsValidTarget(GEntityList->Player(), E->Range()) && ChampionUseE[wTarget->GetNetworkId()]->Enabled())
			{
				E->CastOnUnit(wTarget);
			}
		}
	}	

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;		

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), E->Range()); });

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
					if (JungleEBig->Enabled())
					{
						if (strstr(jMonster->GetObjectName(), "Dragon") ||
							strstr(jMonster->GetObjectName(), "Baron") ||
							strstr(jMonster->GetObjectName(), "Red") ||
							strstr(jMonster->GetObjectName(), "Blue") ||
							strstr(jMonster->GetObjectName(), "RiftHerald") ||
							strstr(jMonster->GetObjectName(), "Gromp") ||
							strstr(jMonster->GetObjectName(), "Crab") ||
							strstr(jMonster->GetObjectName(), "Razorbeak3") ||
							strstr(jMonster->GetObjectName(), "SRU_Krug") ||
							strstr(jMonster->GetObjectName(), "SRU_Murkwolf2"))
						{
							E->CastOnUnit(jMonster);
						}
					}
					else
					{
						E->CastOnUnit(jMonster);
					}
				}
			}

			if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(jMonster, 600))
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}

			if (JungleW->Enabled() && W->IsReady() && GEntityList->Player()->IsValidTarget(jMonster, W->Range()))
			{
				if (JungleEBig->Enabled())
				{
					if (strstr(jMonster->GetObjectName(), "Dragon") ||
						strstr(jMonster->GetObjectName(), "Baron") ||
						strstr(jMonster->GetObjectName(), "Red") ||
						strstr(jMonster->GetObjectName(), "Blue") ||
						strstr(jMonster->GetObjectName(), "RiftHerald") ||
						strstr(jMonster->GetObjectName(), "Gromp") ||
						strstr(jMonster->GetObjectName(), "Crab") ||
						strstr(jMonster->GetObjectName(), "Razorbeak3") ||
						strstr(jMonster->GetObjectName(), "SRU_Krug") ||
						strstr(jMonster->GetObjectName(), "SRU_Murkwolf2"))
					{
						W->CastOnPlayer();
					}
				}
				else
				{
					W->CastOnPlayer();
				}				
			}
		}
	}

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;

		if (Q->IsReady() && LaneClearQ->Enabled())
		{
			if (CountMinions(GEntityList->Player()->GetPosition(), 450) >= MinionsQ->GetInteger())
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}

		if (W->IsReady() && LaneClearW->Enabled())
		{
			if (CountMinions(GEntityList->Player()->GetPosition(), 600) >= MinionsQ->GetInteger())
			{
				W->CastOnPlayer();
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
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{		
		if (!target->IsHero() || !Q->IsReady()) return;

		if (ComboQ->Enabled() && GEntityList->Player()->GetMana() > R->ManaCost() + Q->ManaCost())
		{			
			if (target->IsValidTarget())
			{			
				if (PosQ() != Vec3(0, 0, 0) && CountEnemy(PosQ(), 600) > 0)
				{
					Q->CastOnPosition(PosQ());
				}
			}
		}		
	}	

	static void OnBuffRemove(IUnit* Source, void* BuffData)
	{
		if (strstr(GBuffData->GetBuffName(BuffData), "KindredERefresher"))
		{
			GOrbwalking->SetOverrideTarget(nullptr);
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (GEntityList->Player()->IsDead() || !ComboR->Enabled() || !R->IsReady()) return;
		if (!Args.Caster_->IsHero()) return;
		
		auto enemy = Args.Caster_;
		auto ally = Args.Target_;		

		if (enemy == nullptr || !enemy->IsValidTarget() || !enemy->IsEnemy(GEntityList->Player()) || ally == nullptr || !ally->IsValidTarget() || ally->IsEnemy(GEntityList->Player()))
		{
			return;
		}

		if (ChampionUse[ally->GetNetworkId()]->Enabled() && GetDistance(GEntityList->Player(), ally) <= R->Range())
		{
			auto predictedHealth = ally->GetHealth() - Args.Damage_;
			auto hpp = predictedHealth / ally->GetMaxHealth() * 100;
			
			if (predictedHealth < 0 || hpp < UltPercent->GetInteger())
			{				
				if (CountAlly(ally->GetPosition(), 500)+1 >= RAllys->GetInteger() &&
					CountEnemy(ally->GetPosition(), 500) <= REnemies->GetInteger())
				{					
					R->CastOnPlayer();
				}
			}						
		}		
	}
};
