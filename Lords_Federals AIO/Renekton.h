#pragma once
#include "PluginSDK.h"
#include "Common.h"
#include "BaseMenu.h"
#include <cmath>
#include <algorithm>
using namespace std;


class Renekton
{
public:

	void  Menu()
	{
		MainMenu = GPluginSDK->AddMenu("Federals Renekton");		

		csettings = MainMenu->AddMenu("Combo Settings");
		{
			useq = csettings->CheckBox("Use Q", true);
			usew = csettings->CheckBox("Use W", true);
			usee = csettings->CheckBox("Use E", true);
			user = csettings->AddInteger("Use R under", 0, 100, 15);
			userindanger = csettings->AddInteger("Use R min X enemy", 1, 5, 2);
			furyMode = csettings->AddSelection("Fury Priority", 0, std::vector<std::string>({ "No priority", "Q", "W", "E" }));			
			useIgnite = csettings->CheckBox("Use Ignite", true);
			QCancelAnimation = csettings->CheckBox("Q Cancel Animation", false);

		}

		Hsettings = MainMenu->AddMenu("Harass Settings");
		{
			useqH = Hsettings->CheckBox("Use Q", true);
			usewH = Hsettings->CheckBox("Use W", true);
			useCH = Hsettings->AddSelection("Harass Mode", 0, std::vector<std::string>({ "E-furyQ-Eback if possible", "Basic" }));
			donteqwebtower = Hsettings->CheckBox("Dont Q Under Tower", true);
		}

		fedMiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			useHydra = fedMiscSettings->CheckBox("Use Titanic/Ravenous", true);
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", true);			
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}

	void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 225, 1000, 325);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 255);		

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 85, 1000, 450);		

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 300);		

		if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerDot"))
		{
			Ignite = GPluginSDK->CreateSpell(kSummonerSlot1, 425);
			FoundIgnite = true;
		}
		else if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerDot"))
		{
			Ignite = GPluginSDK->CreateSpell(kSummonerSlot2, 425);
			FoundIgnite = true;
		}
		else
		{
			FoundIgnite = false;
		}

		titHydra = GPluginSDK->CreateItemForId(3748, 700);
		ravHydra = GPluginSDK->CreateItemForId(3074, 400);
		usetimat = GPluginSDK->CreateItemForId(3077, 400);
	}

	static bool InRange(IUnit* i)
	{
		return i != nullptr && GetDistance(GEntityList->Player(), i) < Q->Range() - 40;
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
		}		
	}

	float CalcComboDmg(IUnit* Target)
	{
		float dmg = 0;
		if (Q->IsReady())
			dmg += GDamage->CalcPhysicalDamage(GEntityList->Player(), Target, GDamage->GetSpellDamage(GEntityList->Player(), Target, kSlotQ));
		if (W->IsReady())
			dmg += GDamage->CalcPhysicalDamage(GEntityList->Player(), Target, GDamage->GetSpellDamage(GEntityList->Player(), Target, kSlotW));
		if (E->IsReady())
			dmg += GDamage->CalcPhysicalDamage(GEntityList->Player(), Target, GDamage->GetSpellDamage(GEntityList->Player(), Target, kSlotE));
		if (R->IsReady())
			dmg += GDamage->CalcPhysicalDamage(GEntityList->Player(), Target, GDamage->GetSpellDamage(GEntityList->Player(), Target, kSlotE)) * 15;
		return dmg;
	}

	static bool rene()
	{
		if (GEntityList->Player()->HasBuff("renektonsliceanddicedelay"))
		{
			return true;
		}

		return false;
	}

	static bool fury()
	{
		if (GEntityList->Player()->HasBuff("renektonrageready"))
		{			
			return true;
		}

		return false;
	}

	static bool renw()
	{
		if (GEntityList->Player()->HasBuff("renektonpreexecute"))
		{
			return true;
		}

		return false;
	}	

	bool canBeOpWithQ(Vec3 vector3)
	{
		if (fury())
		{
			return false;
		}
		if ((GEntityList->Player()->GetMana() > 45 && !fury()) ||
			(Q->IsReady() &&
				GEntityList->Player()->GetMana() + CountMinionsInRange(vector3, Q->Range()) * 2.5 +
			      CountEnemiesInRange(Q->Range()) * 10 > 50))
		{
			return true;
		}
		return false;
	}

	bool canBeOpWithW()
	{
		if (GEntityList->Player()->GetMana() + 20 > 50)
		{
			return true;
		}
		return false;
	}

	void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
		if (target == nullptr)
			return;
		switch (useCH->GetInteger())
		{
		case 1:
			if (Q->IsReady() && E->IsReady() && lastE == 0 && fury() && !rene())
			{
				if (donteqwebtower->Enabled() && PosUnderTurret(Extend(GEntityList->Player()->GetPosition(), target->GetPosition(), E->Range()), false, true))
				{
					return;
				}
				auto vecMinions = GEntityList->GetAllMinions(false, true, false);
				auto closeGapTarget = std::find_if(vecMinions.begin(), vecMinions.end(), InRange);

				if (closeGapTarget != vecMinions.end())
				{
					auto pUnit = (*closeGapTarget);
					lastEpos = GEntityList->Player()->GetPosition();
					E->CastOnPosition(pUnit->GetPosition());
					lastE = GGame->TickCount();
					return;
				}
				else
				{
					lastEpos = GEntityList->Player()->GetPosition();
					E->CastOnPosition(target->GetPosition());
					lastE = GGame->TickCount();
					return;
				}
			}
			return;
			break;

		case 0:
			if (Q->IsReady() && W->IsReady() && !rene() && GEntityList->Player()->IsValidTarget(target, E->Range()))
			{
				if (donteqwebtower->Enabled() && PosUnderTurret(Extend(GEntityList->Player()->GetPosition(), target->GetPosition(), E->Range()), false, true))
				{
					return;
				}
				if (E->CastOnTarget(target, kHitChanceHigh))
				{
					lastE = GGame->TickCount();
				}
			}
			if (rene() && E->IsReady() && GEntityList->Player()->IsValidTarget(target, E->Range()) && lastE != 0 && GGame->TickCount() - lastE > 3600)
			{
				E->CastOnTarget(target, kHitChanceHigh);
			}
			/*if (SC.GetDistance(GEntityList->Player(), target) < GOrbwalking->GetAutoAttackRange(target) && Q->IsReady() && E->IsReady())
			{
			GOrbwalking->ForceTarget?
			}*/
			return;
			break;

		default:
			break;
		}

		if (useqH->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(target, Q->Range()))
		{
			Q->CastOnPlayer();
		}
		if (useCH->GetInteger() == 0 && lastE != 0 && rene() && !Q->IsReady() && !renw())
		{
			if (lastEpos.x != 0 && lastEpos.y != 0 && lastEpos.z != 0)
			{
				E->CastOnPosition(lastEpos);
			}
		}
	}

	bool checkFuryMode(eSpellSlot spellSlot, IUnit* target)
	{
		if (GDamage->GetSpellDamage(GEntityList->Player(), target, spellSlot) > target->GetHealth())
		{
			return true;
		}
		if (canBeOpWithQ(GEntityList->Player()->GetPosition()) && spellSlot != kSlotQ)
		{
			return false;
		}
		if (!fury())
		{
			return true;
		}
		if (GEntityList->Player()->IsWindingUp())
		{
			return false;
		}
		switch (furyMode->GetInteger())
		{
		case 0:
			return true;
			break;
		case 1:
			if (spellSlot != kSlotQ && Q->IsReady())
			{
				return false;
			}
			break;
		case 2:
			if (spellSlot != kSlotW && (W->IsReady() || renw()) && target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(target)))
			{
				return false;
			}
			break;
		case 3:
			if (spellSlot != kSlotE && E->IsReady() && rene())
			{
				return false;
			}
			break;
		}
		return true;
	}	

	void ComboLogic()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range() * 2);
		if (!CheckTarget(target)) return;		

		float FuryQ = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) * 0.5;
		float FuryW = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW) * 0.5;
		float eDmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE);
		float combodamage = CalcComboDmg(target);
		
		if (CheckShielded(target) && useIgnite->Enabled() && FoundIgnite && Ignite->IsReady() && GDamage->GetSummonerSpellDamage(GEntityList->Player(), target, kSummonerSpellIgnite) > target->GetHealth())
		{
			Ignite->CastOnUnit(target);
		}

		if (GetDistancePos(GEntityList->Player()->GetPosition(), target->GetPosition()) > E->Range() && E->IsReady() && (W->IsReady() || Q->IsReady()) && lastE == 0 && usee->Enabled())
		{
			GetTarget = target;
			IUnit* minions = nullptr;
			SArray<IUnit*> Minions = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && GetDistance(GEntityList->Player(), m) <= E->Range() && GetDistance(m, GetTarget) < Q->Range() - 40; });

			if (Minions.Any())
			{
				minions = Minions.MaxOrDefault<int>([](IUnit* i) {return CountMinions(i->GetPosition(), Q->Range()); });			
				
				if (CheckTarget(minions))
				{
					if ((canBeOpWithQ(minions->GetPosition()) || fury()) && !rene())
					{
						if (E->IsReady() && GEntityList->Player()->IsValidTarget(minions, E->Range()))
						{
							E->CastOnPosition(minions->GetPosition());
						}
					}
				}
			}
		}

		if (useq->Enabled() && Q->IsReady() && GEntityList->Player()->IsValidTarget(target, Q->Range()) && !renw() && 
			!GEntityList->Player()->IsDashing() && checkFuryMode(kSlotQ, target) && GGame->TickCount() - LastSpellTick > 600 && 
			(!W->IsReady() || GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ) == 0 || GetDistance(target, GEntityList->Player()) > W->Range()))
		{
			Q->CastOnPlayer();
		}

		auto distance = GetDistance(GEntityList->Player(), target);		

		if (usee->Enabled() && E->IsReady() && !rene() && GEntityList->Player()->IsValidTarget(target, E->Range()) && GGame->TickCount() - LastSpellTick > 300
			&& (eDmg > target->GetHealth() || 
			(((W->IsReady() && canBeOpWithQ(target->GetPosition())) ||
			(distance > GetDistanceVectors(target->GetPosition(), Extend(GEntityList->Player()->GetPosition(), target->GetPosition(), E->Range())) - distance)))))
		{
			E->CastOnPosition(target->GetPosition());			
		}

		if (usee->Enabled() && E->IsReady() && rene() && GEntityList->Player()->IsValidTarget(target, E->Range()) && GGame->TickCount() - LastSpellTick > 500 &&
			(eDmg + GDamage->CalcPhysicalDamage(GEntityList->Player(), target, GEntityList->Player()->PhysicalDamage()) > target->GetHealth() ||
				GetDistance(target, GEntityList->Player()) > Q->Range()))
		{
			E->CastOnPosition(target->GetPosition());
		}

		if (GEntityList->Player()->HealthPercent() <= user->GetInteger() || CountEnemy(GEntityList->Player()->GetPosition(), R->Range()) >= userindanger->GetInteger())
		{
			R->CastOnPlayer();
		}
	}

	void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (Args.Source != nullptr && W->IsReady() && GEntityList->Player()->IsValidTarget(Args.Source, W->Range() + GEntityList->Player()->BoundingRadius()))
			W->CastOnUnit(Args.Source);
	}

    void OnGapCloser(GapCloserSpell const& Args)
	{

	}

	void OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (Target->IsHero() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && checkFuryMode(kSlotW, Target) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			float time = GGame->Time() - GEntityList->Player()->GetSpellRemainingCooldown(kSlotW);

			if (useHydra->Enabled() &&
				(GEntityList->Player()->GetSpellRemainingCooldown(kSlotW) - abs(time) < 1 || time < -6 || GEntityList->Player()->HealthPercent() < 50))
			{
				if (titHydra->IsOwned() && titHydra->IsReady())
				{
					titHydra->CastOnPlayer();
				}
				if (ravHydra->IsOwned() && ravHydra->IsReady())
				{
					ravHydra->CastOnPlayer();
				}
				if (usetimat->IsOwned() && usetimat->IsReady())
				{
					usetimat->CastOnPlayer();
				}
			}
		}
		if (Target != nullptr && W->IsReady() && Target->IsHero() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && usew->Enabled() && checkFuryMode(kSlotW, Target))
		{
			W->CastOnPlayer();						
		}		

		if (Target != nullptr && Target->IsHero() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && checkFuryMode(kSlotE, Target) && usee->Enabled() && E->IsReady() && 
			rene() && GEntityList->Player()->IsValidTarget(Target, E->Range()) && GGame->TickCount() - LastSpellTick > 500 && !W->IsReady() && !Q->IsReady())
		{
			E->CastOnPosition(Target->GetPosition());
		}

		if (Target != nullptr && Target->IsHero() && GOrbwalking->GetOrbwalkingMode() == kModeMixed && useCH->GetInteger() == 0)
		{
			if (Target != nullptr && W->IsReady())
			{
				W->CastOnPlayer();				
			}

			if (Target != nullptr && Q->IsReady())
			{
				Q->CastOnPlayer();				
			}

			if (Target != nullptr && E->IsReady() && GEntityList->Player()->IsValidTarget(Target, E->Range() - 100))
			{
				E->CastOnPosition(Target->GetPosition());				
			}
		}
	}

	void OnOrbwalkBeforeAttack(IUnit* Target)
	{
		if (Target != nullptr && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeCombo && Target->IsHero() && checkFuryMode(kSlotW, Target) && usew->Enabled())
		{
			if (GEntityList->Player()->GetMana() > 40 && !fury() || (Q->IsReady() && canBeOpWithQ(GEntityList->Player()->GetPosition())))
			{
				return;
			}

			W->CastOnPlayer();			
		}

		if (Target != nullptr && W->IsReady() && GOrbwalking->GetOrbwalkingMode() == kModeMixed && usewH->Enabled() && Target->IsHero() && useCH->GetInteger() != 0)
		{
			W->CastOnPlayer();
		}
	}

	void OnGameUpdate()
	{
		if (GEntityList->Player()->IsDead())
			return;

		if (GGame->TickCount() - lastE > 4100)
			lastE = 0;

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			ComboLogic();
			break;
		case kModeMixed:
			Harass();
			break;
		}
	}

	void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			//GUtility->LogConsole("Ataques: %s", Args.Name_);

			if (GSpellData->GetSlot(Args.Data_) == kSlotW)
			{				
				LastSpellTick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotE)
			{
				LastSpellTick = GGame->TickCount();
				lastE = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			{
				if (QCancelAnimation->Enabled())
				{
					GGame->Taunt(kLaugh);
				}

				LastSpellTick = GGame->TickCount();
			}

			if (GSpellData->GetSlot(Args.Data_) == kSlotR)
			{
				LastSpellTick = GGame->TickCount();
			}
		}	
	}	
};