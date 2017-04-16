#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include <cmath>

class Syndra
{
public:
	 
	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Syndra");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{			
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R", true);
			ComboE2 = ComboSettings->CheckBox("Use QE", true);
		}
		
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawAxe = DrawingSettings->CheckBox("Draw QE", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
		Q->SetSkillshot(0.5f, 125.f, 2000.f, 790.f);

		QE = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, true, kCollidesWithYasuoWall);
		QE->SetSkillshot(0.8f, 70.f, 2500.f, 1250.f);

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithNothing);
		W->SetSkillshot(0.6f, 100.f, 1000.f, 925.f);

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, true, kCollidesWithYasuoWall);
		E->SetSkillshot(0.25f, 45.f, 2500.f, 700.f);

		E2 = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, true, kCollidesWithYasuoWall);
		E2->SetSkillshot(0.3f, 70.f, 2000.f, 1200.f);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithYasuoWall);
		R->SetOverrideRange(675.f);
	}

	static void Drawing()
	{
		for (auto Orbs : GEntityList->GetAllUnits())
		{
			if (Orbs != nullptr && Orbs->GetTeam() == GEntityList->Player()->GetTeam() && !Orbs->IsDead() && std::string(Orbs->GetObjectName()) == "Seed")
			{
				GRender->DrawOutlinedCircle(Orbs->GetPosition(), Vec4(255, 255, 0, 255), 100);
			}
		}

		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
			if (Q->IsReady() && E->IsReady() && DrawAxe->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), QE->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), R->Range()); }
			if (DrawAxe->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), QE->Range()); }
		}
	}

	static void ComboQE(IUnit* target)
	{		
		auto pPos = GEntityList->Player()->GetPosition();
		auto castQpos = pPos.Extend(target->GetPosition(), Q->Range());
		auto delay = QE->GetDelay() + GetDistance(GEntityList->Player(), target) / QE->Speed();

		QE->SetOverrideDelay(delay);
		QE->SetRangeCheckFrom(castQpos);
		QE->SetFrom(castQpos);

		AdvPredictionOutput prediction;
		QE->RunPrediction(target, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall), &prediction);

		if (prediction.HitChance >= kHitChanceVeryHigh)
		{
			if (Q->CastOnPosition(castQpos))
			{
				QE->SetFrom(Vec3(0, 0, 0));
				EQcastNow = true;
			}
		}	
	}

	static void CastOrbsE(IUnit* target)
	{
		if (Q->IsReady())
		{
			//CastQE(target);
		}
		if (!EQcastNow)
		{
			SArray<IUnit*> sOrbs = SArray<IUnit*>(GEntityList->GetAllUnits()).Where([](IUnit* m) {return m != nullptr &&
				m->GetTeam() == GEntityList->Player()->GetTeam() && !m->IsDead() && std::string(m->GetObjectName()) == "Seed"; });

			for (auto ball : sOrbs.ToVector())
			{
				if (GetDistance(GEntityList->Player(), ball) < E->Range() + 100)
				{					
					auto bPos = ball->GetPosition();
					auto pPos = GEntityList->Player()->GetPosition();
					auto startPoint = bPos.Extend(pPos, 100);
					auto endPoint = pPos.Extend(bPos, GetDistance(ball, GEntityList->Player()) > 200 ? 1300 : 1000);

					E2->SetOverrideDelay(E2->GetDelay() + GetDistance(ball, GEntityList->Player()) / E2->Speed());

					E2->SetRangeCheckFrom(ball->GetPosition());
					E2->SetFrom(ball->GetPosition());
					AdvPredictionOutput prediction;
					E2->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction);

					if (prediction.HitChance >= kHitChanceHigh && Distance(prediction.TargetPosition.To2D(), startPoint.To2D(), endPoint.To2D(), false) < E2->Radius() + target->BoundingRadius())				
					{
						E->CastOnPosition(ball->GetPosition());
						LastWTick = GGame->TickCount();
						E2->SetFrom(Vec3(0, 0, 0));
					}
				}
			}			
		}
	}

	static void Automatic()
	{
		if (!E->IsReady())
		{
			EQcastNow = false;
		}		
	}

	static void UseQSpell(IUnit* target)
	{
		if (Q->IsReady())
		{
			Vec3 position;
			auto delay = Q->GetDelay() + GetDistance(GEntityList->Player(), target) - target->MovementSpeed() / Q->Speed();
			GPrediction->GetFutureUnitPosition(target, 0.3f, true, position);

			Q->CastOnTarget(target, kHitChanceVeryHigh);
		}
	}

	static void UseWGrab(IUnit* target, bool onlyMinin = false)
	{
		if (GGame->TickCount() - LastWTick < 500) { return; }
		
		IUnit* obj = nullptr;

		SArray<IUnit*> sOrbs = SArray<IUnit*>(GEntityList->GetAllUnits()).Where([](IUnit* m) {return m != nullptr &&
			m->GetTeam() == GEntityList->Player()->GetTeam() && !m->IsDead() && std::string(m->GetObjectName()) == "Seed" && GetDistance(m, GEntityList->Player()) <= 925; });

		if (sOrbs.Count() > 0 && !onlyMinin)
		{
			auto orbs = sOrbs.MinOrDefault<float>([](IUnit* i) {return GetDistance(i, GEntityList->Player()); });

			obj = orbs;			
		}

		if (obj == nullptr)
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, true, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), 925) && !strstr(m->GetObjectName(), "WardCorpse"); });

			obj = Minion.MaxOrDefault<float>([](IUnit* i) {return i->GetHealth(); });
		}

		if (obj != nullptr)
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, true))
			{
				if (minion != nullptr && !minion->IsDead() && minion->IsVisible() &&
					minion->IsValidTarget(GEntityList->Player(), 925) &&
					GetDistance(target, minion) < GetDistance(target, obj))
				{
					obj = minion;
				}
			}

			W->CastOnPosition(obj->GetPosition());
		}
	}

	static void UseWSpell(IUnit* target)
	{
		if (W->IsReady())
		{
			if (GEntityList->Player()->GetSpellBook()->GetToggleState(kSlotW) == 1)
			{
				if (target->IsValidTarget(GEntityList->Player(), W->Range() - 50))
				{
					UseWGrab(target);
				}
			}
			else
			{
				if (GGame->TickCount() - LastWTick < 500) return;
				
				if (target->IsValidTarget(GEntityList->Player(), W->Range() - 50))
				{					
					W->CastOnTarget(target, kHitChanceVeryHigh);					
				}
			}
		}
	}

	static float GetUltimateDamage(IUnit* target)
	{
		if (target == nullptr || !R->IsReady() || !target->IsValidTarget() || !CheckShielded(target))
		{
			return 0.f;
		}

		float baseR[3] = { 270.0, 405.0, 540.0 };
		float baseOrbsR[3] = { 90.0, 135.0, 180.0 };
		auto holdMagicDmg = GEntityList->Player()->TotalMagicDamage();
		auto checkBase = baseR[GEntityList->Player()->GetSpellLevel(3) - 1];
		auto checkSoldAdd = baseOrbsR[GEntityList->Player()->GetSpellLevel(3) - 1];
		auto QRealBase = checkBase;
		auto holdmyballslol = checkSoldAdd * GEntityList->Player()->GetSpellBook()->GetAmmo(kSlotR);
		auto QRealAdditional = holdmyballslol + (holdMagicDmg * 0.2);
		auto RRealDamage = QRealBase + QRealAdditional;
		auto damage = GDamage->CalcMagicDamage(GEntityList->Player(), target, RRealDamage);

		return damage;
	}

	static float TestDagame(IUnit* target)
	{
		auto damage = GHealthPrediction->GetKSDamage(target, kSlotR, 0.25f, false);
		damage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) * (GEntityList->Player()->GetSpellBook()->GetAmmo(kSlotR) - 3);

		return damage;
	}


	static void Combo()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
		auto qeTarget = GTargetSelector->FindTarget(QuickestKill, SpellDamage, QE->Range());		

		if (CheckTarget(Target) && Q->IsReady() && ComboQ->Enabled() && Target->IsValidTarget(GEntityList->Player(), Q->Range()))
		{
			UseQSpell(Target);
		}

		if (CheckTarget(qeTarget) && E->IsReady() && ComboE->Enabled())
		{
			CastOrbsE(qeTarget);
		}

		if (CheckTarget(Target) && ComboW->Enabled() && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), W->Range()))
		{
			UseWSpell(Target);
		}

		if (CheckTarget(Target) && R->IsReady() && ComboR->Enabled() && Target->IsValidTarget(GEntityList->Player(), R->Range()) && GetUltimateDamage(Target) > Target->GetHealth())
		{
			R->CastOnUnit(Target);
		}

		if (ComboE2->Enabled() && Target == nullptr && CheckTarget(qeTarget) && Q->IsReady() && E->IsReady() && GEntityList->Player()->IsValidTarget(qeTarget, QE->Range()))
		{
			ComboQE(qeTarget);
		}

		if (CheckTarget(Target))
		{
			GUtility->LogConsole("Dano1: %f - Dano2: %f", GetUltimateDamage(Target), TestDagame(Target));
		}
	}


	static void Harass()
	{
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
	}

	static void LaneClear()
	{
	}	

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (GSpellData->GetSlot(Args.Data_) == kSlotQ)
			{
				if (EQcastNow && E->IsReady())
				{
					auto delay = Q->GetDelay() - (E->GetDelay() + (GetDistanceVectors(GEntityList->Player()->GetPosition(), Args.EndPosition_) / E->Speed()));
					EndPos = Args.EndPosition_;
					GPluginSDK->DelayFunctionCall(delay, []()
					{
						E->CastOnPosition(EndPos);
					});					
				}
			}
			
			if (GSpellData->GetSlot(Args.Data_) == kSlotW)
			{
				LastWTick = GGame->TickCount();
			}			
		}
	}

	static void OnCreateObject(IUnit* Source)
	{
		
	}	

	static void OnDeleteObject(IUnit* Source)
	{
		
	}
};
