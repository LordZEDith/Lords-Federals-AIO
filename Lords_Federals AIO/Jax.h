#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Jax
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Jax");
		ComboMenu = MainMenu->AddMenu("Combo Settings");
		HarassMenu = MainMenu->AddMenu("Harass Settings");
		FarmMenu = MainMenu->AddMenu("LaneClear Settings");
		JungleClearSettings = MainMenu->AddMenu("Jungle Settings");
		Drawings = MainMenu->AddMenu("Drawings");
		fedMiscSettings = MainMenu->AddMenu("Flee Settings");

		ComboQ = ComboMenu->CheckBox("Use Q", true);
		ComboQH = ComboMenu->CheckBox("Dont Use Q when enemy is in AA Range", false);
		inUnderTower = ComboMenu->CheckBox("Dont Q Under Tower", false);
		ComboW = ComboMenu->AddSelection("Use W Mode", 1, std::vector<std::string>({ "Disabled", "Always", "After AA" }));
		ComboE = ComboMenu->CheckBox("Use E", true);
		ComboE2 = ComboMenu->CheckBox("Use E Before Q Jump", true);
		AutoStun = ComboMenu->CheckBox("Auto Stun (Second E)", true);
		ComboR = ComboMenu->CheckBox("Use R", true);
		AutoR = ComboMenu->AddFloat("Auto R when health <= HP%", 10, 100, 50);
		REnemies = ComboMenu->AddInteger("Or Enemy >=", 1, 5, 3);

		HarassQ = HarassMenu->CheckBox("Use Q", true);
		HarassW = HarassMenu->CheckBox("Use W", true);

		FarmQ = FarmMenu->CheckBox("Use Q", true);
		FarmW = FarmMenu->CheckBox("Use W", true);

		JungleQ = JungleClearSettings->CheckBox("Use Q", true);
		JungleW = JungleClearSettings->CheckBox("Use W", true);
		JungleE = JungleClearSettings->CheckBox("Use E", true);
		JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
		
		WardJumpKey = fedMiscSettings->AddKey("Q Jump", 90);
		jumpWards = fedMiscSettings->CheckBox("Use Wards", true);
		WardMax = fedMiscSettings->CheckBox("Ward Max Range", true);
		jumpMinion = fedMiscSettings->CheckBox("Jump in Minion", true);
		jumpAliado = fedMiscSettings->CheckBox("Jump in Allys", true);

		DrawQ = Drawings->CheckBox("Draw Q", true);
		DrawE = Drawings->CheckBox("Draw E", true);
		DrawWard = Drawings->CheckBox("Draw Ward Range", false);
	}
	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, kCollidesWithNothing);
		Ward = GPluginSDK->CreateSpell2(kSlotTrinket, kCircleCast, false, false, kCollidesWithWalls);

		Q->SetOverrideRange(700);
		W->SetOverrideRange(GEntityList->Player()->AttackRange());
		E->SetOverrideRange(187.5);
		Ward->SetOverrideRange(600);

		Ward1 = GPluginSDK->CreateItemForId(2045, 600);
		Ward2 = GPluginSDK->CreateItemForId(2049, 600);
		Ward3 = GPluginSDK->CreateItemForId(2050, 600);
		Ward4 = GPluginSDK->CreateItemForId(2301, 600);
		Ward5 = GPluginSDK->CreateItemForId(2302, 600);
		Ward6 = GPluginSDK->CreateItemForId(2303, 600);
		Ward7 = GPluginSDK->CreateItemForId(3340, 600);
		Ward8 = GPluginSDK->CreateItemForId(3361, 600);
		Ward9 = GPluginSDK->CreateItemForId(3362, 600);
		Ward10 = GPluginSDK->CreateItemForId(3711, 600);
		Ward11 = GPluginSDK->CreateItemForId(1408, 600);
		Ward12 = GPluginSDK->CreateItemForId(1409, 600);
		Ward13 = GPluginSDK->CreateItemForId(1410, 600);
		Ward14 = GPluginSDK->CreateItemForId(1411, 600);
		Ward15 = GPluginSDK->CreateItemForId(2043, 600);
		Ward16 = GPluginSDK->CreateItemForId(2055, 600);
	}

	static bool JaxEUsed()
	{
		if (GEntityList->Player()->HasBuff("JaxCounterStrike"))
		{
			return true;			
		}

		return false;
	}

	static void WardJump(Vec3 pos, bool maxRange = false)
	{
		auto minions = jumpMinion->Enabled();
		auto champions = jumpAliado->Enabled();

		auto basePos = GEntityList->Player()->GetPosition();
		auto newPos = pos - GEntityList->Player()->GetPosition();

		if (!maxRange && GetDistanceVectors(GEntityList->Player()->GetPosition(), pos) <= 590)
		{
			JumpPos = pos;
		}
		else if (maxRange || GetDistanceVectors(GEntityList->Player()->GetPosition(), pos) > 590)
		{
			JumpPos = basePos + newPos.VectorNormalize() * 590;
		}
		else
		{
			JumpPos = basePos + newPos.VectorNormalize() * GetDistanceVectors(GEntityList->Player()->GetPosition(), pos);
		}

		if (!Q->IsReady())
		{
			return;
		}

		EhWard = false;
		
		if (minions || champions)
		{
			if (champions)
			{
				for (auto ally : GEntityList->GetAllHeros(true, false))
				{
					if (ally != nullptr && GetDistance(GEntityList->Player(), ally) < Q->Range() && GetDistance(GEntityList->Player(), ally) > 200 &&
						GetDistanceVectors(JumpPos, ally->GetPosition()) < 200 &&
						ally != GEntityList->Player() && 500 < GGame->TickCount() - LastQTick && ally->IsVisible())
					{
						Q->CastOnUnit(ally);
						return;
					}
				}
			}

			if (minions)
			{
				for (auto ally : GEntityList->GetAllMinions(true, false, false))
				{
					if (ally != nullptr && GetDistance(GEntityList->Player(), ally) < Q->Range() && GetDistance(GEntityList->Player(), ally) > 200 &&
						GetDistanceVectors(JumpPos, ally->GetPosition()) < 200 &&
						ally != GEntityList->Player() && 500 < GGame->TickCount() - LastQTick && ally->IsVisible())
					{
						Q->CastOnUnit(ally);
						return;
					}
				}
			}
		}

		for (auto ward : GEntityList->GetAllUnits())
		{
			if (ward != nullptr && ward->IsWard() && !ward->IsEnemy(GEntityList->Player()) && ward->IsVisible() && GetDistance(GEntityList->Player(), ward) > 200 &&
				GetDistanceVectors(JumpPos, ward->GetPosition()) < 200 &&
				GetDistance(GEntityList->Player(), ward) < W->Range())
			{

				EhWard = true;

				if (500 >= GGame->TickCount() - LastQTick)
				{
					return;
				}

				Q->CastOnUnit(ward);

				return;
			}
		}		

		if (!EhWard && jumpWards->Enabled())
		{
			if (Q->IsReady() && LastWard < GGame->TickCount())
			{
				if (Ward1->IsReady() && Ward1->IsOwned())
				{
					Ward1->CastOnPosition(JumpPos);
				}
				else if (Ward2->IsReady() && Ward2->IsOwned())
				{
					Ward2->CastOnPosition(JumpPos);
				}
				else if (Ward3->IsReady() && Ward3->IsOwned())
				{
					Ward3->CastOnPosition(JumpPos);
				}
				else if (Ward4->IsReady() && Ward4->IsOwned())
				{
					Ward4->CastOnPosition(JumpPos);
				}
				else if (Ward5->IsReady() && Ward5->IsOwned())
				{
					Ward5->CastOnPosition(JumpPos);
				}
				else if (Ward6->IsReady() && Ward6->IsOwned())
				{
					Ward6->CastOnPosition(JumpPos);
				}
				else if (Ward7->IsReady() && Ward7->IsOwned())
				{
					Ward7->CastOnPosition(JumpPos);
				}
				else if (Ward8->IsReady() && Ward8->IsOwned())
				{
					Ward8->CastOnPosition(JumpPos);
				}
				else if (Ward9->IsReady() && Ward9->IsOwned())
				{
					Ward9->CastOnPosition(JumpPos);
				}
				else if (Ward10->IsReady() && Ward10->IsOwned())
				{
					Ward10->CastOnPosition(JumpPos);
				}
				else if (Ward11->IsReady() && Ward11->IsOwned())
				{
					Ward11->CastOnPosition(JumpPos);
				}
				else if (Ward12->IsReady() && Ward12->IsOwned())
				{
					Ward12->CastOnPosition(JumpPos);
				}
				else if (Ward13->IsReady() && Ward13->IsOwned())
				{
					Ward13->CastOnPosition(JumpPos);
				}
				else if (Ward14->IsReady() && Ward14->IsOwned())
				{
					Ward14->CastOnPosition(JumpPos);
				}
				else if (Ward15->IsReady() && Ward15->IsOwned())
				{
					Ward15->CastOnPosition(JumpPos);
				}
				else if (Ward16->IsReady() && Ward16->IsOwned())
				{
					Ward16->CastOnPosition(JumpPos);
				}

				WardPos = JumpPos;
				LastWard = GGame->TickCount() + 1500;
				goWard = true;				
			}
		}
	}

	static void WardJumpMouse()
	{
		if (IsKeyDown(WardJumpKey))
		{
			WardJump(GGame->CursorPosition(), WardMax->Enabled());
		}
	}

	void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;

		if (!JaxEUsed() && ComboE->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range()) && (ComboE2->Enabled() || !ComboE2->Enabled() && !Q->IsReady() && LastQTick - GGame->TickCount() < 1500))
		{
			if (inUnderTower->Enabled() && IsUnderTurret(target) && GetDistance(GEntityList->Player(), target) > E->Range()) return;

			E->CastOnPlayer();
		}

		if (ComboQ->Enabled() && (!ComboQH->Enabled() || ComboQH->Enabled() && GetDistance(GEntityList->Player(), target) > GEntityList->Player()->GetRealAutoAttackRange(target)))
		{
			if (inUnderTower->Enabled() && IsUnderTurret(target)) return;

			Q->CastOnUnit(target);
		}

		if (ComboW->GetInteger() == 1 && W->IsReady() && GetDistance(GEntityList->Player(), target) < GEntityList->Player()->GetRealAutoAttackRange(target))
		{
			W->CastOnPlayer();
		}

		if (AutoStun->Enabled() && JaxEUsed())
		{
			E->CastOnPlayer();
		}
		
		if (ComboR->Enabled())
		{
			if (GEntityList->Player()->HealthPercent() <= AutoR->GetFloat() || CountEnemy(GEntityList->Player()->GetPosition(), Q->Range()) >= REnemies->GetInteger())
			{
				R->CastOnPlayer();
			}			
		}
	}

	void Harass()
	{
		if (HarassW->Enabled())
		{
			W->CastOnPlayer();
		}
		if (HarassQ->Enabled())
		{
			Q->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()));
		}
	}

	void LaneClear()
	{
		if (FarmQ->Enabled() && Q->IsReady() && !FoundMinionsNeutral(Q->Range()))
		{
			Q->LastHitMinion();
		}

		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

		if (Minion.Any())
		{
			if (FoundMinions(Q->Range())) return;

			for (auto jMonster : Minion.ToVector())
			{
				if (JungleE->Enabled() && E->IsReady() && !JaxEUsed())
				{
					if (Q->IsReady() && GEntityList->Player()->IsValidTarget(jMonster, Q->Range()))
					{
						E->CastOnPlayer();
					}
					else
					{
						if (GEntityList->Player()->IsValidTarget(jMonster, E->Range()))
						{
							E->CastOnPlayer();
						}
					}
				}

				if (JungleE->Enabled() && E->IsReady() && JaxEUsed() && CountMinionsNeutral(GEntityList->Player()->GetPosition(), E->Range()) > 0)
				{
					E->CastOnPlayer();
				}

				if (JungleQ->Enabled() && Q->IsReady())
				{
					if (GEntityList->Player()->IsValidTarget(jMonster, Q->Range()))
					{
						Q->CastOnUnit(jMonster);
					}
				}
			}
		}		
	}

	void OnGameUpdate()
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Combo();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Harass();
		}
		else if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			LaneClear();
		}

		WardJumpMouse();		
	}

	void OnRender()
	{
		if (DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 255, 64), Q->Range());
		}

		if (DrawE->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 183, 255), E->Range());
		}

		if (DrawWard->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), 590); }
	}

     void OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (Source != GEntityList->Player() || Target == nullptr || Target->IsTurret())
			return;

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			if (ComboW->GetInteger() == 2 && W->IsReady())
			{
				W->CastOnPlayer();
			}
			break;
		case kModeMixed:
			if (HarassW->Enabled() && W->IsReady())
			{
				W->CastOnPlayer();
			}
			break;
		case kModeLaneClear:
			for (auto jMinion : GEntityList->GetAllMinions(false, true, true))
			{
				if (jMinion != nullptr && !jMinion->IsDead())
				{
					if (FarmW->Enabled() && W->IsReady() && !FoundMinionsNeutral(Q->Range()) && GetDistance(GEntityList->Player(), jMinion) <= W->Range())
					{
						W->CastOnPlayer();
					}

					if (JungleW->Enabled() && W->IsReady() && !FoundMinions(Q->Range()) && GetDistance(GEntityList->Player(), jMinion) <= W->Range())
					{
						W->CastOnPlayer();
					}
				}
			}
			break;
		default:;
		}
	}

	 void OnProcessSpell(CastedSpell const& Args)
	 {
		 if (Args.Caster_ == GEntityList->Player())
		 {
			 if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			 {
				 LastQTick = GGame->TickCount();				 
			 }			 
		 }		 
	 }

	 void OnCreateObject(IUnit* Source)
	 {
		 if (Q->IsReady() && (strstr(Source->GetObjectName(), "SightWard") || strstr(Source->GetObjectName(), "VisionWard")))
		 {
			 if (GetDistanceVectors(Source->GetPosition(), WardPos) < 100)
			 {
				 Q->CastOnUnit(Source);
			 }			 
		 }
	 }
};