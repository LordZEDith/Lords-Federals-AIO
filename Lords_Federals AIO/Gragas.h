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
			AutoQ = ComboSettings->CheckBox("Destroy Barril", true);
			ComboW = ComboSettings->CheckBox("Use W", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R ToDO", true);			
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			autoQ = HarassSettings->CheckBox("Destroy Barril", true);
			HarassE = HarassSettings->CheckBox("Use E", false);
			AutoHarass = HarassSettings->CheckBox("Harass Toggle", false);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{			
			LaneClearQ = LaneClearSettings->CheckBox("Q laneclear", true);
			LaneClearQLast = LaneClearSettings->AddSelection("Destroy Barril", 1, std::vector<std::string>({ "Disable", "Instantly", "2 Seconds Or Kill" }));
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q in laneclear", 1, 6, 3);						
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
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawR = DrawingSettings->CheckBox("Draw R", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.3, 110, 1000, 800);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.25, 0, 1000, FLT_MAX);		

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithHeroes, kCollidesWithMinions));
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
		DestroyBarril();
		
		if (AutoHarass->Enabled())
		{
			Harass();
		}
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
		if (CheckTarget(target) && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
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
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, R->Range());		

		if (CheckTarget(target) && ComboQ->Enabled() && Q->IsReady() && BarrilQ == Vec3(0,0,0) && GragasQone() && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnTarget(target, kHitChanceHigh);
			LastSpellTick = GGame->TickCount();
		}			

		if (CheckTarget(target) && W->IsReady() && (!GragasQone() || !Q->IsReady()) && ComboW->Enabled() &&
			GetDistance(GEntityList->Player(),target) < 300 && GOrbwalking->CanMove(100) && GGame->TickCount() - LastSpellTick > 50)
		{
			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (CheckTarget(target) && E->IsReady() && W->IsReady() && (!GragasQone() || !Q->IsReady()) && ComboW->Enabled() &&
			GetDistance(GEntityList->Player(), target) < Q->Range() && GetDistance(GEntityList->Player(), target) > 300 && GOrbwalking->CanMove(100) && GGame->TickCount() - LastSpellTick > 50)
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
		if (GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) { return; }

		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());		

		if (CheckTarget(target) && HarassQ->Enabled() && Q->IsReady() && BarrilQ == Vec3(0, 0, 0) && GragasQone() && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnTarget(target, kHitChanceHigh);
			LastSpellTick = GGame->TickCount();
		}		

		if (HarassE->Enabled() && GGame->TickCount() - LastSpellTick > 50)
		{
			CastE(target);
			LastSpellTick = GGame->TickCount();
		}
	}

	static void JungleClear()
	{
		if (GEntityList->Player()->ManaPercent() < JungleMana->GetInteger()) return;
		if (FoundMinions(Q->Range()) || !FoundMinionsNeutral(Q->Range())) return;

		SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
			!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

		if (Minion.Any())
		{
			for (auto minion : Minion.ToVector())
			{
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
							GPrediction->FindBestCastPosition(E->Range(), E->Radius(), false, true, false, posE, hitE);
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
	}

	static void DestroyBarril()
	{
		if (LaneClearQ->Enabled() && LaneClearQLast->GetInteger() != 0 && Q->IsReady() && BarrilQ != Vec3(0, 0, 0) && !GragasQone())
		{
			if (LaneClearQLast->GetInteger() == 2)
			{
				for (auto minion : GEntityList->GetAllMinions(false, true, false))
				{
					if (GetDistanceVectors(BarrilQ, minion->GetPosition()) <= 300 &&
						getQdamage(minion) > minion->GetHealth())
					{
						Q->CastOnPlayer();						
					}
				}

				if (GGame->TickCount() - LastQTick > 2000 && CountMinions(BarrilQ, 300) >= 2)
				{
					Q->CastOnPlayer();
				}
			}

			if (LaneClearQLast->GetInteger() == 1 && CountMinions(BarrilQ, 300) >= 2)
			{
				Q->CastOnPlayer();
			}
		}

		if (JungleQ->Enabled() && Q->IsReady() && BarrilQ != Vec3(0, 0, 0) && !GragasQone() && CountMinionsNeutral(BarrilQ, 300) > 0)
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{
				if (!CheckTarget(minion)) return;

				if (GGame->TickCount() - LastQTick > 2000 || GetDistanceVectors(BarrilQ, minion->GetPosition()) <= 300 && getQdamage(minion) > minion->GetHealth())
				{
					Q->CastOnPlayer();
				}
			}
		}

		if (autoQ->Enabled() && HarassQ->Enabled() && Q->IsReady() && !GragasQone() && CountEnemy(BarrilQ, 300) > 0 && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (AutoQ->Enabled() && ComboQ->Enabled() && Q->IsReady() && !GragasQone() && CountEnemy(BarrilQ, 300) > 0 && GGame->TickCount() - LastSpellTick > 50)
		{
			Q->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}
	}

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() < LaneClearMana->GetInteger()) return;
		if (!FoundMinions(E->Range()) || FoundMinionsNeutral(E->Range())) return;

		if (LaneClearQ->Enabled() && Q->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), Q->Range()) >= MinionsQ->GetInteger())
		{
			Vec3 posQ;
			int hitQ;

			GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, true, posQ, hitQ);

			if (hitQ >= 3 && MinionsQ->GetInteger() >= 3)
			{
				if (BarrilQ == Vec3(0, 0, 0) && GragasQone())
				{
					Q->CastOnPosition(posQ);
				}				
			}
			else if (hitQ >= 1 && MinionsQ->GetInteger() < 3)
			{
				Q->CastOnPosition(posQ);
			}
			else
			{
				return;
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && CountMinions(GEntityList->Player()->GetPosition(), E->Range()) >= MinionsE->GetInteger())
		{
			Vec3 posE;
			int hitE;

			GPrediction->FindBestCastPosition(E->Range(), E->Radius(), false, true, true, posE, hitE);

			if (hitE >= 3 && MinionsE->GetInteger() >= 3)
			{
				E->CastOnPosition(posE);
			}
			else if (hitE >= 1 && MinionsE->GetInteger() < 3)
			{
				E->CastOnPosition(posE);
			}
			else
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
