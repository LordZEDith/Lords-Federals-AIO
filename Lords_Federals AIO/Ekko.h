#pragma once
#include "PluginSDK.h"
#include "Common.h"
#include "BaseMenu.h"


class Ekko
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Ekko");
		KS = MainMenu->AddMenu("KS");
		Activator = MainMenu->AddMenu("Activator");
		Draw = MainMenu->AddMenu("Draw");
		WOpt = MainMenu->AddMenu("W Option");
		ROpt = MainMenu->AddMenu("R Option");
		Farm = MainMenu->AddMenu("Farm");
		AutoPotion = MainMenu->CheckBox("Auto Potion", true);

		useProto = Activator->CheckBox("Use Protobelt", true);
		useZhonyas = Activator->CheckBox("Use Zhonyas", true);
		ZhonyasHP = Activator->AddInteger("Zhonyas at %HP", 0, 100, 45);

		QKS = KS->CheckBox("Use Q", true);
		EKS = KS->CheckBox("Use E", true);
		IgniteKS = KS->CheckBox("Use Ignite", true);

		DrawQ = Draw->CheckBox("Draw Q", true);
		DrawW = Draw->CheckBox("Draw W", true);
		DrawE = Draw->CheckBox("Draw E", true);
		DrawR = Draw->CheckBox("Draw R", true);
		QHelp = Draw->CheckBox("Draw Q Help", true);
		onlyReady = Draw->CheckBox("Draw Only Ready Spells", true);

		autoW = WOpt->CheckBox("Auto W", true);
		WAOE = WOpt->AddInteger("Cast if X targets", 1, 5, 2);

		autoR = ROpt->CheckBox("Auto R", true);
		rCount = ROpt->AddInteger("Auto R if X enemies in range", 1, 5, 3);

		farmQ = Farm->CheckBox("Farm Q", true);
		farmW = Farm->CheckBox("Farm W", true);
		jungleQ = Farm->CheckBox("Jungle Q", true);
		jungleW = Farm->CheckBox("Jungle W", true);
	}

	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall);
		Q1 = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithYasuoWall);
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, kCollidesWithNothing);

		Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("summonerdot"), 600);
		HealthPot = GPluginSDK->CreateItemForId(2003, 0);
		CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
		RefillPot = GPluginSDK->CreateItemForId(2031, 0);
		Biscuit = GPluginSDK->CreateItemForId(2010, 0);
		Zhonyas = GPluginSDK->CreateItemForId(3157, 0);
		Protobelt = GPluginSDK->CreateItemForId(3152, 300);

		Q->SetOverrideRange(750);
		Q1->SetOverrideRange(1000);
		W->SetOverrideRange(1600);
		E->SetOverrideRange(325);
		R->SetOverrideRange(280);

		Q->SetOverrideDelay(0.25f);
		Q1->SetOverrideDelay(0.5f);
		W->SetOverrideDelay(2.5f);
		R->SetOverrideDelay(0.4f);

		Q->SetOverrideSpeed(1650);
		Q1->SetOverrideSpeed(1000);
		W->SetOverrideSpeed(9999);
		R->SetOverrideSpeed(9999);

	}	

	bool CanHarass()
	{
		if (!GEntityList->Player()->IsWindingUp() && !IsUnderTurret(GEntityList->Player(), false, true))
			return true;
		else
			return false;
	}

	double GetKsDamage(IUnit* t, ISpell2* QWER, bool includeIncomingDamage = true)
	{
		double totalDmg = GDamage->GetSpellDamage(GEntityList->Player(), t, kSlotQ);
		totalDmg -= t->HPRegenRate();

		if (totalDmg > t->GetHealth())
		{
			if (GEntityList->Player()->HasBuff("summonerexhaust"))
				totalDmg = totalDmg * 0.6f;
			if (t->HasBuff("ferocioushowl"))
				totalDmg = totalDmg * 0.7f;
			if (t->ChampionName() == "Blitzcrank" && !t->HasBuff("BlitzcrankManaBarrierCD") && !t->HasBuff("ManaBarrier"))
			{
				totalDmg -= t->GetMana() / 2;
			}
		}
		//ToDo: Add incoming damage here
		return totalDmg;
	}

	float GetEchoLudenDamage(IUnit* t)
	{
		float totalDamage = 0;

		if (GEntityList->Player()->GetBuffDataByName("itemmagicshankcharge"))
		{
			if (GEntityList->Player()->GetBuffCount("itemmagicshankcharge") == 100)
			{
				totalDamage += (float)GDamage->CalcMagicDamage(GEntityList->Player(), t, 100 + 0.1 * GEntityList->Player()->MagicDamage());
			}
		}
		return totalDamage;
	}

	void PotionManager()
	{
		if (GEntityList->Player()->GetLevel() == 1 && CountEnemiesInRange(1000) == 1 && GEntityList->Player()->GetHealth() >= GEntityList->Player()->GetMaxHealth() * 0.35) return;
		if (GEntityList->Player()->GetLevel() == 1 && CountEnemiesInRange(1000) == 2 && GEntityList->Player()->GetHealth() >= GEntityList->Player()->GetMaxHealth() * 0.50) return;

		if (AutoPotion->Enabled() && !GEntityList->Player()->IsRecalling() && !GEntityList->Player()->IsDead())
		{
			if (Biscuit->IsReady() && !GEntityList->Player()->GetBuffDataByName("ItemMiniRegenPotion") && !GEntityList->Player()->GetBuffDataByName("ItemCrystalFlask"))
			{
				if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 170 && GEntityList->Player()->GetMaxMana() > GEntityList->Player()->GetMana() + 10 && CountEnemiesInRange(1000) > 0
					&& GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.75)
				{
					Biscuit->CastOnPlayer();
				}
				else if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 170 && GEntityList->Player()->GetMaxMana() > GEntityList->Player()->GetMana() + 10 && CountEnemiesInRange(1000) == 0
					&& GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.6)
				{
					Biscuit->CastOnPlayer();
				}
			}
			else if (HealthPot->IsReady() && !GEntityList->Player()->GetBuffDataByName("RegenerationPotion") && !GEntityList->Player()->GetBuffDataByName("ItemCrystalFlask"))
			{
				if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 150 && CountEnemiesInRange(1000) > 0 &&
					GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.75)
				{
					HealthPot->CastOnPlayer();
				}
				else if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 150 && CountEnemiesInRange(1000) == 0 &&
					GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.6)
				{
					HealthPot->CastOnPlayer();
				}
			}
			else if (CorruptPot->IsReady() && !GEntityList->Player()->GetBuffDataByName("ItemDarkCrystalFlask") && !GEntityList->Player()->GetBuffDataByName("RegenerationPotion") && !GEntityList->Player()->GetBuffDataByName("ItemCrystalFlask") && !GEntityList->Player()->GetBuffDataByName("ItemMiniRegenPotion"))
			{
				if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 120 && GEntityList->Player()->GetMaxMana() > GEntityList->Player()->GetMana() + 60 && CountEnemiesInRange(1000) > 0 && (GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.7 || GEntityList->Player()->GetMana() < GEntityList->Player()->GetMaxMana() * 0.5))
				{
					CorruptPot->CastOnPlayer();
				}
				else if (GEntityList->Player()->GetMaxHealth() > GEntityList->Player()->GetHealth() + 120 && GEntityList->Player()->GetMaxMana() > GEntityList->Player()->GetMana() + 60 && CountEnemiesInRange(1000) == 0 && (GEntityList->Player()->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.7 || GEntityList->Player()->GetMana() < GEntityList->Player()->GetMaxMana() * 0.5))
				{
					CorruptPot->CastOnPlayer();
				}
			}
		}
	}

	void KillSteal()
	{
		bool useIgniteKS = IgniteKS->Enabled();
		bool useQKS = QKS->Enabled();
		bool useEKS = EKS->Enabled();

		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (CheckTarget(target))
			{

				if (useQKS && Q->IsReady() && target->IsVisible() && GEntityList->Player()->GetMana() >= QMANA && target->GetHealth() < GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) &&
					GetDistance(GEntityList->Player(), target) <= Q->Range() && target->IsValidTarget())
				{
					Q->CastOnTarget(target, kHitChanceHigh);
				}
				if (useEKS && E->IsReady() && GEntityList->Player()->GetMana() >= EMANA && target->IsVisible() && target->GetHealth() < GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) &&
					GetDistance(GEntityList->Player(), target) <= E->Range() + 450 && !target->IsDead() && target->IsValidTarget())
				{
					E->CastOnPosition(target->ServerPosition());
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, target);
				}
				if (useIgniteKS && Ignite->GetSpellSlot() != kSlotUnknown && target->IsVisible() && GDamage->GetSummonerSpellDamage(GEntityList->Player(), target, kSummonerSpellIgnite) > target->GetHealth()
					&& GetDistance(GEntityList->Player(), target) <= Ignite->GetSpellRange() && target->IsValidTarget())
				{
					Ignite->CastOnUnit(target);
				}
				if (useQKS && useEKS && Q->IsReady() && E->IsReady() && GEntityList->Player()->GetMana() >= QMANA + EMANA && target->IsVisible() && target->GetHealth() < (GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) + GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false)) &&
					GetDistance(GEntityList->Player(), target) <= E->Range() + 450 && !target->IsDead() && target->IsValidTarget())
				{
					E->CastOnPosition(target->ServerPosition());
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, target);					
				}
				if (useQKS && useIgniteKS && target->IsVisible() && Ignite->GetSpellSlot() != kSlotUnknown && Q->IsReady() && GEntityList->Player()->GetMana() >= QMANA && target->GetHealth() < (GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) + GDamage->GetSummonerSpellDamage(GEntityList->Player(), target, kSummonerSpellIgnite))
					&& GetDistance(GEntityList->Player(), target) < 600 && !target->IsDead() && target->IsTargetable())
				{
					Q->CastOnTarget(target, kHitChanceHigh);					
				}
				if (useEKS && useIgniteKS && target->IsVisible() && Ignite->GetSpellSlot() != kSlotUnknown && E->IsReady() && GEntityList->Player()->GetMana() >= EMANA && target->GetHealth() < (GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) + GDamage->GetSummonerSpellDamage(GEntityList->Player(), target, kSummonerSpellIgnite))
					&& GetDistance(GEntityList->Player(), target) < E->Range() + 450 && !target->IsDead() && target->IsTargetable())
				{
					E->CastOnPosition(target->ServerPosition());
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, target);					
				}
				if (useQKS && useEKS && useIgniteKS && target->IsVisible() && Ignite->GetSpellSlot() != kSlotUnknown && Q->IsReady() && E->IsReady() && GEntityList->Player()->GetMana() >= QMANA + EMANA && target->GetHealth() < (GHealthPrediction->GetKSDamage(target, kSlotQ, Q->GetDelay(), false) + GHealthPrediction->GetKSDamage(target, kSlotE, E->GetDelay(), false) + GDamage->GetSummonerSpellDamage(GEntityList->Player(), target, kSummonerSpellIgnite))
					&& GetDistance(GEntityList->Player(), target) && !target->IsDead() && !target->IsValidTarget())
				{
					E->CastOnPosition(target->ServerPosition());
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, target);					
				}
			}

		}
	}

	void SetMana()
	{
		if (GEntityList->Player()->HealthPercent() < 20)
		{
			QMANA = 0;
			WMANA = 0;
			EMANA = 0;
			RMANA = 0;
			return;
		}

		QMANA = Q->ManaCost();
		WMANA = W->ManaCost();
		EMANA = W->ManaCost();

		if (R->IsReady())
			RMANA = R->ManaCost();
		else
			RMANA = 0;
	}

	void Jungle()
	{
		if (GEntityList->Player()->GetMana() > QMANA + RMANA)
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), W->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				for (auto minion : Minion.ToVector())
				{
					auto mob = minion;

					if (W->IsReady() && jungleW->Enabled() && GetDistance(GEntityList->Player(), mob) <= W->Range())
					{
						W->CastOnPosition(mob->ServerPosition());						
					}

					if (Q->IsReady() && jungleQ->Enabled() && GetDistance(GEntityList->Player(), mob) <= Q->Range())
					{
						Q->CastOnPosition(mob->ServerPosition());						
					}
				}
			}
		}
	}

	void Items()
	{
		if (useProto->Enabled() && Protobelt->IsOwned() && Protobelt->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 300);

			if (!CheckTarget(t)) return;

			if (t != nullptr && GetDistance(GEntityList->Player(), t) <= 300)
				Protobelt->CastOnPosition(t->ServerPosition());
		}
		if (useZhonyas->Enabled() && Zhonyas->IsOwned() && Zhonyas->IsReady())
		{
			if (GEntityList->Player()->HealthPercent() <= ZhonyasHP->GetInteger())
				Zhonyas->CastOnPlayer();
		}
	}

	void Save()
	{
		if (GEntityList->Player()->HealthPercent() <= 30 && CountEnemiesInRange(Q->Range()) >= 1 && R->IsReady())
			R->CastOnPlayer();
	}

	void LogicQ()
	{
		if (Q->IsReady()) {
			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			auto t1 = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q1->Range());

			if (!CheckTarget(t)) return;
			if (!CheckTarget(t1)) return;

			if (t->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && GEntityList->Player()->GetMana() > RMANA + QMANA)
				{
					Q->CastOnTarget(t, kHitChanceHigh);
				}
				else if (GetKsDamage(t, Q) * 2 > t->GetHealth())
				{
					Q->CastOnTarget(t, kHitChanceHigh);
				}

				if (GEntityList->Player()->GetMana() > RMANA + QMANA + WMANA)
				{
					for (auto enemy : GEntityList->GetAllHeros(false, true))
					{
						if (enemy->IsValidTarget() && GetDistance(GEntityList->Player(), t) < Q->Range() && !CanMove(t))
						{
							Q->CastOnTarget(t, kHitChanceHigh);
						}
					}
				}
			}
			else if (t1 != nullptr && t1->IsValidTarget())
			{
				if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && GEntityList->Player()->GetMana() > RMANA + QMANA)
					Q1->CastOnTarget(t1, kHitChanceHigh);
				else if (GetKsDamage(t1, Q1) * 2 > t1->GetHealth())
					Q1->CastOnTarget(t, kHitChanceHigh);
				if (GEntityList->Player()->GetMana() > RMANA + QMANA + WMANA)
				{
					for (auto enemy : GEntityList->GetAllHeros(false, true))
					{
						if (enemy->IsValidTarget() && GetDistance(GEntityList->Player(), t1) < Q1->Range() && !CanMove(t1))
						{
							Q1->CastOnTarget(t1, kHitChanceHigh);
						}
					}
				}
			}
		}
	}

	void LaneClearQ()
	{
		if (Q->IsReady() && farmQ->Enabled())
		{
			int minions = 0;
			Vec3 pos = Vec3();
			Q->FindBestCastPosition(true, false, pos, minions);
			if (minions >= 3 && pos.x != 0 && pos.y != 0 && pos.z != 0)
				Q->CastOnPosition(pos);
		}
	}

	void HarassQ()
	{
		if (Q->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			auto t1 = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q1->Range());

			if (!CheckTarget(t)) return;
			if (!CheckTarget(t1)) return;

			if (t != nullptr && t->IsValidTarget() && GEntityList->Player()->GetMana() > RMANA + WMANA + QMANA + QMANA && CanHarass())
				Q->CastOnTarget(t, kHitChanceHigh);
			else if (t1 != nullptr && t1->IsValidTarget() && GEntityList->Player()->GetMana() > RMANA + WMANA + QMANA + QMANA && CanHarass())
				Q1->CastOnTarget(t1, kHitChanceHigh);
		}
	}

	void AutoW()
	{
		if (W->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());

			if (!CheckTarget(t)) return;

			if (t->IsValidTarget(GEntityList->Player(), W->Range()))
			{
				if (WAOE->Enabled())
				{
					int enemies = 0;
					Vec3 pos = Vec3();
					W->FindBestCastPosition(false, true, pos, enemies);
					if (enemies > 1 && pos.x != 0 && pos.y != 0 && pos.z != 0)
					{
						W->CastOnPosition(pos);
					}
				}
			}

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (!CheckTarget(enemy)) return;

				if (GEntityList->Player()->IsValidTarget(enemy, W->Range()) && !CanMove(enemy))
				{
					W->CastOnPosition(enemy->ServerPosition());
				}
			}
		}
	}

	void LogicW()
	{
		if (W->IsReady()) 
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());

			if (!CheckTarget(t)) return;

			if (t->IsValidTarget(GEntityList->Player(), W->Range())) 
			{
				Vec3 pos = Vec3();
				GPrediction->GetFutureUnitPosition(t, W->GetDelay(), true, pos);
				W->CastOnPosition(pos);
			}
		}
	}

	/*void LogicEBackup()
	{
	auto t = GTargetSelector->FindTarget(QuickestKill,SpellDamage,E->Range());
	if (t != nullptr && t->GetBuffCount("EkkoStacks") == 2 && CountEnemiesInRange(1000) <= 2)
	{
	E->CastOnPosition(t->ServerPosition());
	GGame->IssueOrder(GEntityList->Player(), kAutoAttack, t);
	}
	}*/

	void LogicE()
	{
		if (E->IsReady()) 
		{
			if (WMissile != nullptr)
			{
				if (CountEnemy(WMissile->GetPosition(), 200) > 0 && GetDistancePos(GEntityList->Player()->GetPosition(), WMissile->GetPosition()) < 100)
				{
					E->CastOnPosition(WMissile->GetPosition());
				}
			}

			auto t = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 800);

			if (!CheckTarget(t)) return;

			if (E->IsReady() && GEntityList->Player()->GetMana() > RMANA + EMANA && CountEnemy(GEntityList->Player()->GetPosition(), 260) > 0 && GetDistancePos(GEntityList->Player()->ServerPosition(), GGame->CursorPosition()) <= E->Range()
				&& CountEnemy(GEntityList->Player()->GetPosition(),500) < 3 && GetDistancePos(t->ServerPosition(), GGame->CursorPosition()) > GetDistancePos(t->ServerPosition(), GEntityList->Player()->ServerPosition()))
			{
				E->CastOnPosition(GGame->CursorPosition());

				if (GEntityList->Player()->IsValidTarget(t, 445))
				{
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, t);
				}
			}
			else if (GEntityList->Player()->GetHealth() > GEntityList->Player()->GetMaxHealth() * 0.4 && GEntityList->Player()->GetMana() > RMANA + EMANA
				&& !IsUnderTurret(GEntityList->Player(), false, true) && CountEnemiesInRange(700) < 3)
			{
				if (GEntityList->Player()->GetMana() > QMANA + EMANA + WMANA && GetDistancePos(t->ServerPosition(), GGame->CursorPosition()) + 300 < GetDistancePos(t->ServerPosition(), GEntityList->Player()->ServerPosition()))
				{
					E->CastOnPosition(GGame->CursorPosition());
					if (GEntityList->Player()->IsValidTarget(t, 445))
					{
						GGame->IssueOrder(GEntityList->Player(), kAutoAttack, t);
					}
				}
			}
			else if (GDamage->GetSpellDamage(GEntityList->Player(), t, kSlotE) + GDamage->GetSpellDamage(GEntityList->Player(), t, kSlotW) > t->GetHealth())
			{
				E->CastOnPosition(t->ServerPosition());

				if (GEntityList->Player()->IsValidTarget(t, 445))
				{
					GGame->IssueOrder(GEntityList->Player(), kAutoAttack, t);
				}
			}
			else
			{
				return;
			}
		}
	}

	void LogicR()
	{
		if (autoR->Enabled() && R->IsReady())
		{
			if (RMissile != nullptr && CountEnemy(RMissile->GetPosition(), 400) >= rCount->GetInteger())
			{
				R->CastOnPlayer();
			}
		}
	}

	void OnGameUpdate()
	{
		SetMana();
		PotionManager();
		Save();
		KillSteal();

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Items();
			LogicR();
			LogicQ();
			LogicW();
			LogicE();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			HarassQ(); //No Crash When Isolated
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			LaneClearQ();
			Jungle();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeNone && autoW->Enabled() && GEntityList->Player()->GetMana() > RMANA + WMANA + EMANA + QMANA)
		{
			//AutoW(); //Throws exception when isolated.
		}

		for (auto RMiss : GEntityList->GetAllUnits())
		{
			if (!strcmp(RMiss->GetObjectName(), "Ekko") && RMiss->IsVisible())
			{			
				RMissile = RMiss;
			}			
		}
	}

	void OnRender()
	{
		if (onlyReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), Q->Range());
			if (W->IsReady() && DrawW->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), W->Range());
			if (E->IsReady() && DrawE->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), E->Range());
			if (R->IsReady() && DrawR->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), Q->Range());
		}
		else
		{
			if (DrawQ->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), Q->Range());
			if (DrawW->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), W->Range());
			if (DrawE->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), E->Range());
			if (DrawR->Enabled())
				GRender->DrawOutlinedCircle(GEntityList->Player()->ServerPosition(), Vec4(255, 66, 134, 244), Q->Range());
		}

		/*if (RMissile != nullptr)
		{
			GRender->DrawOutlinedCircle(RMissile->ServerPosition(), Vec4(255, 66, 134, 244), 350);
		}*/
	}

	void OnCreateObject(IUnit* Source)
	{
		if (Source != nullptr)
		{			
			if (!strcmp(Source->GetObjectName(), "Ekko_Base_W_Indicator.troy"))
			{
				WMissile = Source;
				Wtime = GGame->Time();				
			}
			if (!strcmp(Source->GetObjectName(), "Ekko_Base_W_Cas.troy"))
			{
				WMissile2 = Source;
				Wtime2 = GGame->Time();				
			}
		}
	}

	void OnDestroyObject(IUnit* Source)
	{

		if (Source != nullptr)
		{			
			if (!strcmp(Source->GetObjectName(), "Ekko"))
			{
				RMissile = nullptr;
			}

			if (!strcmp(Source->GetObjectName(), "Ekko_Base_W_Indicator.troy"))
			{
				WMissile = nullptr;				
			}
			if (!strcmp(Source->GetObjectName(), "Ekko_Base_W_Cas.troy"))
			{
				WMissile2 = nullptr;
			}
		}
	}


};