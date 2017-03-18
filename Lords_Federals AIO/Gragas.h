#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Gragas
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Gragas");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R", true);			
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{			
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);
			LaneClearW = LaneClearSettings->CheckBox("W laneclear", true);			
			LaneClearE = LaneClearSettings->CheckBox("E laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 6, 3);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);			
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 0, 100, 40);
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.3, 110, 1000, 800);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.25, 0, 1000, FLT_MAX);		

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0, 200, 1200, 600);		

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, true, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 150, 1750, 1050);		
	}

	static bool GragasQone()
	{
		if (GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ) >= 1)
		{
			if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "GragasQToggle"))
			{				
				return false;
			}
		}		

		return true;
	}

	static void Automatic()
	{
	}

	static float getQdamage(IUnit* target)
	{
		double damage = 0;

		if (Q->IsReady())
		{
			if (BarrilQ == Vec3(0,0,0))
			{
				damage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
			}
			else
			{
				if (GGame->TickCount() - LastQTick > 2000)
				{
					damage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) * 1.5f;
				}
				else
				{
					damage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
				}
			}
		}
		
		return (float)damage;
	}	
	
	static void CastE(IUnit* target)
	{
		if (E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
		{
			if (GetDistance(GEntityList->Player(), target) < 200)
			{
				E->CastOnPosition(target->GetPosition());				
			}
			else
			{
				E->CastOnTarget(target, kHitChanceVeryHigh);
			}			
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

		if (!CheckTarget(target)) return;		

		if (ComboQ->Enabled() && Q->IsReady() && BarrilQ == Vec3(0,0,0) && GragasQone() && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnTarget(target, kHitChanceHigh);
			LastSpellTick = GGame->TickCount();
		}

		if (ComboQ->Enabled() && Q->IsReady() && !GragasQone() && CountEnemy(BarrilQ, 300) > 0 && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}		

		if (W->IsReady() && (!GragasQone() || !Q->IsReady()) && ComboW->Enabled() &&
			GetDistance(GEntityList->Player(),target) < 300 && GOrbwalking->CanMove(100) && GGame->TickCount() - LastSpellTick > 50)
		{
			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (E->IsReady() && W->IsReady() && (!GragasQone() || !Q->IsReady()) && ComboW->Enabled() &&
			GetDistance(GEntityList->Player(), target) < Q->Range() && GOrbwalking->CanMove(100) && GGame->TickCount() - LastSpellTick > 50)
		{
			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (ComboE->Enabled() && GGame->TickCount() - LastSpellTick > 50)
		{
			CastE(target);
			LastSpellTick = GGame->TickCount();
		}


		// R Todo
	}

	static void Harass()
	{
	}

	static void LastHit()
	{
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;
		if (FoundMinions(Q->Range()) || !FoundMinionsNeutral(Q->Range())) return;

		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion == nullptr || minion->IsDead()) return;

			if (JungleQ->Enabled() && Q->IsReady() && BarrilQ == Vec3(0, 0, 0) && GragasQone())
			{
				if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					Vec3 posQ;
					int hitQ;
					
					if (strstr(minion->GetObjectName(), "Crab"))
					{
						GPrediction->FindBestCastPosition(500, Q->Radius(), false, true, false, posQ, hitQ);
					}
					else
					{
						GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, posQ, hitQ);
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

			if (JungleQ->Enabled() && Q->IsReady() && BarrilQ != Vec3(0, 0, 0) && !GragasQone() && CountMinionsNeutral(BarrilQ, 300) > 0)
			{
				if (GGame->TickCount() - LastQTick > 2000 || GHealthPrediction->GetKSDamage(minion, kSlotQ, Q->GetDelay(), false) > minion->GetHealth())
				{
					Q->CastOnPlayer();
				}
			}

			if (JungleW->Enabled() && W->IsReady())
			{
				if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
				{
					W->CastOnPlayer();
				}
			}

			if (JungleE->Enabled() && E->IsReady())
			{
				if (GEntityList->Player()->IsValidTarget(minion, E->Range()))
				{
					Vec3 posE;
					int hitE;

					if (strstr(minion->GetObjectName(), "Crab"))
					{
						GPrediction->FindBestCastPosition(500, E->Radius(), false, true, false, posE, hitE);
					}
					else
					{
						GPrediction->FindBestCastPosition(E->Range() , E->Radius(), false, true, false, posE, hitE);
					}

					if (hitE > 1)
					{
						E->CastOnPosition(posE);
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
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			if (strstr(Args.Name_, "GragasQ"))
			{
				if (!justQ)
				{
					justQ = true;
					lastQpos = Args.EndPosition_;
					//BarrilQ = Args.EndPosition_;
					//LastQTick = GGame->TickCount();
				}
			}
		}		
	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Gragas_Base_Q_Ally.troy"))
		{
			BarrilQ = Source->GetPosition();
			LastQTick = GGame->TickCount();
			GGame->PrintChat("Barril Jogado");
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Gragas_Base_Q_Ally.troy"))
		{
			BarrilQ = Vec3(0,0,0);
			lastQpos = Vec3(0, 0, 0);
			LastQTick = 0;
		}
	}
};
