#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Nocturne
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Nocturne");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q in Combo", true);
			ComboE = ComboSettings->CheckBox("Use E in Combo", true);
			ComboR = ComboSettings->CheckBox("Use R in Combo", true);			
			ComboRKill = ComboSettings->CheckBox("If only can kill", false);
			inUnderTower = ComboSettings->CheckBox("Dont Ult Under Turrent", false);			
			SemiManualKey = ComboSettings->AddKey("Semi Manual R", 71);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q in Harass", true);
			HarassE = HarassSettings->CheckBox("Use E in Harass", false);
			ComboE2 = HarassSettings->CheckBox("Only E + Q", false);
			HarassMana = HarassSettings->AddInteger("Min Mana to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 10, 3);			
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 60);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleBig = JungleClearSettings->CheckBox("Use E only BigMobs", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 20);
		}		

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawE = DrawingSettings->CheckBox("Draw E", false);
			DrawR = DrawingSettings->CheckBox("Draw R", false);			
			Drawkill = DrawingSettings->CheckBox("Killable Enemy Notification", true);
		}		
	}

	static void LoadSpells()
	{		
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25f, 60.f, 1400.f, 1125.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetOverrideRange(425);
		E->SetOverrideDelay(0.25);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetOverrideRange(4000);
		R->SetOverrideDelay(0.75);
	}	

	static void RangeUltimate()
	{
		auto RRange = GEntityList->Player()->GetSpellLevel(kSlotR) * 750 + 1750;
		R->SetOverrideRange(RRange);
	}

	static void Automatic()
	{
	}

	static void ExecuteComboR()
	{
		if (!R->IsReady() || !ComboR->Enabled())
		{
			return;
		}

		auto TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 4000);

		if ((inUnderTower->Enabled() && IsUnderTurret(TargetR)) || TargetR == nullptr || TargetR->IsDead() || TargetR->IsInvulnerable() || GetDistance(GEntityList->Player(), TargetR) > 4000)
		{
			return;
		}
		
		auto StatusR = GEntityList->Player()->GetSpellBook()->GetToggleState(kSlotR);
		
		auto comboDmg2 = GetDamageTeste(TargetR, true, true, false, true, true) + GEntityList->Player()->TotalPhysicalDamage() + GEntityList->Player()->TotalMagicDamage() + GEntityList->Player()->BonusDamage() + GEntityList->Player()->PhysicalDamage();
		auto Combo3 = GDamage->GetAutoAttackDamage(GEntityList->Player(), TargetR, true) * 4;
		auto comboDmg = comboDmg2 + Combo3;		

		if (!ComboRKill->Enabled())
		{		
			
			if ((GetDistance(GEntityList->Player(), TargetR) < R->Range() && GetDistance(GEntityList->Player(), TargetR) > 900 &&
				CountAlly(TargetR->GetPosition(), 2000) >= CountEnemy(TargetR->GetPosition(), 2000)) ||
				(comboDmg > TargetR->GetHealth() && GEntityList->Player()->HealthPercent() < 50 && TargetR->HealthPercent() < 40 && CountAlly(TargetR->GetPosition(), 1000) == 1 &&
				CountEnemy(TargetR->GetPosition(), 1000) == 1))
			{					
				if (StatusR == 1)
				{
					R->CastOnPlayer();
				}
				else
				{
					R->CastOnUnit(TargetR);
				}
			}
		}

		else
		{
			if (GetDistance(GEntityList->Player(), TargetR) > Q->Range() && TargetR->GetHealth() < comboDmg && CountAlly(TargetR->GetPosition(), 600) < 2)
			{

				if (StatusR == 1)
				{
					R->CastOnPlayer();
				}
				else
				{
					R->CastOnUnit(TargetR);
				}
			}
		}
	}

	static void ExecuteCombo()
	{
		auto rTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

		if (rTarget == nullptr || rTarget->IsDead() || rTarget->IsInvulnerable() || !rTarget->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			return;
		}

		if (ComboQ->Enabled() && Q->IsReady() && rTarget->IsValidTarget(GEntityList->Player(), Q->Range()) /*&&
			!rTarget->HasBuff("NocturneParanoiaTarget")*/)
		{
			if (GetDistance(GEntityList->Player(), rTarget) > 550)
			{
				Q->CastOnTarget(rTarget, kHitChanceHigh);
			}
			else 
			{
				Q->CastOnTarget(rTarget, kHitChanceMedium);
			}
		}

		if (ComboQ->Enabled() && Q->IsReady() && rTarget->IsValidTarget(GEntityList->Player(), Q->Range()) &&
			rTarget->HasBuff("NocturneUnspeakableHorror"))
		{
			if (GetDistance(GEntityList->Player(), rTarget) > 550)
			{
				Q->CastOnTarget(rTarget, kHitChanceHigh);
			}
			else
			{
				Q->CastOnTarget(rTarget, kHitChanceMedium);
			}
		}

		if (ComboE->Enabled() && E->IsReady() && rTarget->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			E->CastOnUnit(rTarget);
		}
	}

	static void Combo()
	{
		ExecuteComboR();
		ExecuteCombo();
	}

	static void Harass()
	{
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }
		
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(target)) return;
		
		if (!ComboE2->Enabled())
		{

			if (Q->IsReady() && HarassQ->Enabled() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				Q->CastOnTarget(target, kHitChanceMedium);				
			}

			if (E->IsReady() && HarassE->Enabled() && target->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				E->CastOnUnit(target);				
			}
		}
		else
		{
			if (Q->IsReady() && E->IsReady() && E->ManaCost() + Q->ManaCost() < GEntityList->Player()->GetMana() && target->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				E->CastOnUnit(target);
				Q->CastOnTarget(target, kHitChanceMedium);				
			}
		}
	}	

	static void JungleClear()
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{		

			if (!CheckTarget(minion)) return;

			if (JungleQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
			{

				if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
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

			else if (JungleE->Enabled() && E->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(Q->Range() - 50))
			{
				if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
				{
					if (JungleBig->Enabled())
					{
						if (strstr(minion->GetObjectName(), "Dragon") ||
							strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Gromp") ||
							strstr(minion->GetObjectName(), "Crab") ||
							strstr(minion->GetObjectName(), "Razorbeak3") ||
							strstr(minion->GetObjectName(), "SRU_Krug11") ||
							strstr(minion->GetObjectName(), "SRU_Murkwolf2") ||
							strstr(minion->GetObjectName(), "Red") ||
							strstr(minion->GetObjectName(), "Blue") ||
							strstr(minion->GetObjectName(), "RiftHerald"))
						{
							E->CastOnUnit(minion);
						}
						else 
						{
							return;
						}
					}
					else
					{
						E->CastOnUnit(minion);
					}
				}
			}
		}
	}

	static void LaneClear()
	{
		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100) && CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
		{
			Vec3 pos;
			int count;
			Q->FindBestCastPosition(true, true, pos, count);

			if (count >= 3 && Q->CastOnPosition(pos))
			{
				return;
			}			
		}	

		if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100))
		{
			Vec3 pos;
			int count;
			Q->FindBestCastPosition(true, true, pos, count);

			if (count >= MinionsQ->GetInteger() && Q->CastOnPosition(pos))
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
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }		
		}	
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		
	}

	static void OnCreateObject(IUnit* Source)
	{
		
	}

	static void OnDeleteObject(IUnit* Source)
	{
		
	}

	static void KeyPressUltimate()
	{
		if (IsKeyDown(SemiManualKey))
		{

			if (!R->IsReady())
			{
				return;
			}
			auto TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());

			auto StatusR = GEntityList->Player()->GetSpellBook()->GetToggleState(kSlotR);

			if (TargetR == nullptr || TargetR->IsDead() || TargetR->IsInvulnerable() || !TargetR->IsValidTarget(GEntityList->Player(), R->Range()))
			{
				return;
			}

			if (inUnderTower->Enabled() && IsUnderTurret(TargetR))
			{
				return;
			}

			if (StatusR == 1)
			{
				R->CastOnPlayer();
			}
			else
			{
				R->CastOnUnit(TargetR);
			}
		}
	}
			
	
};