#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

class Lux
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Lux");

		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Use Q", true);
			ComboE = ComboSettings->CheckBox("Use E", true);
			ComboR = ComboSettings->CheckBox("Use R", true);
			ComboRKill = ComboSettings->CheckBox("Use R when killable", true);
			Raoe = ComboSettings->AddInteger("Use R AOE", 0, 5, 3);
		}

		WSettings = MainMenu->AddMenu("W Settings");
		{
			AutoW = WSettings->CheckBox("Auto W", true);
			HealthW = WSettings->AddInteger("W on Ally HP%", 0, 100, 30);
			WAllyrisk = WSettings->CheckBox("Only if Dmg > Ally Hp", true);
			for (auto enemy : GEntityList->GetAllHeros(true, false))
			{
				std::string szMenuName = "Shield Ally - " + std::string(enemy->ChampionName());
				MenuDontUlt[enemy->GetNetworkId()] = WSettings->CheckBox(szMenuName.c_str(), true);
			}
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->CheckBox("Use Q", true);
			HarassE = HarassSettings->CheckBox("Use E", true);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 40);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in laneclear", false);
			LaneClearE = LaneClearSettings->CheckBox("Use E in laneclear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions to E in laneclear", 1, 10, 4);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to laneclear", 1, 100, 40);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q to jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W to jungle", false);
			JungleE = JungleClearSettings->CheckBox("Use E to jungle", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
			AutoRjungle = JungleClearSettings->CheckBox("R Jungle Stealer", true);
			Rdragon = JungleClearSettings->CheckBox("Dragon", true);
			Rbaron = JungleClearSettings->CheckBox("Baron", true);
			Rred = JungleClearSettings->CheckBox("Red", true);
			Rblue = JungleClearSettings->CheckBox("Blue", true);
			Rally = JungleClearSettings->CheckBox("Ally Stealer", false);
		}

		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			QGapCloser = fedMiscSettings->CheckBox("Automatically Q GapCloser", true);
			killstealR = fedMiscSettings->CheckBox("Auto KS with R", false);
			CCedE = fedMiscSettings->CheckBox("Auto E on Enemy CC", false);
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
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25f, 80.f, 1200.f, 1175.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, kCollidesWithNothing);
		W->SetSkillshot(0.25f, 110.f, 1200.f, 1075.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		E->SetSkillshot(0.3f, 250.f, 1050.f, 1075.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, kCollidesWithYasuoWall);
		R->SetSkillshot(1.35f, 190.f, 2000.f, 3000.f);
	}
	
	static void KsJungle()
	{
		if (AutoRjungle->Enabled())
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
							auto timeTravel = R->GetDelay();
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
	}

	static void AutoRKS()
	{
		if (R->IsReady() && killstealR->Enabled())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (hero == nullptr || !hero->IsValidTarget() || GetDistance(GEntityList->Player(), hero) > R->Range() || hero->IsInvulnerable() || hero->IsDead())
				{
					return;
				}

				if (GHealthPrediction->GetKSDamage(hero, kSlotR, R->GetDelay(), false) > hero->GetHealth())
				{
					Vec3 position;
					auto Distance = GetDistance(GEntityList->Player(), hero);
					auto delay = R->GetDelay() + Distance / R->Speed();
					GPrediction->GetFutureUnitPosition(hero, delay, true, position);

					if (Distance < R->Range())
					{
						R->CastOnPosition(position);
					}
				}
			}
		}
	}

	static void AutoCCed()
	{
		if (CCedE->Enabled() && E->IsReady())
		{
			for (auto hero : GEntityList->GetAllHeros(false, true))
			{
				if (hero == nullptr || !hero->IsValidTarget() || GetDistance(GEntityList->Player(), hero) > E->Range() || hero->IsInvulnerable() || hero->IsDead())
				{
					return;
				}

				if (hero->HasBuffOfType(BUFF_Stun) || hero->HasBuffOfType(BUFF_Charm) || hero->HasBuffOfType(BUFF_Snare) || hero->HasBuffOfType(BUFF_Suppression) || hero->HasBuffOfType(BUFF_Fear))
				{
					Vec3 positioncc;
					auto delay = 0.25f + GetDistance(GEntityList->Player(), hero) / E->Speed();
					GPrediction->GetFutureUnitPosition(hero, delay, true, positioncc);

					if (E->CastOnPosition(positioncc))
					{
						return;
					}
				}
			}

		}

	}

	static bool ESkillToggle()
	{
		if (strstr(GEntityList->Player()->GetSpellName(kSlotE), "LuxLightstrikeToggle"))
		{
			return true;
		}

		return false;
	}

	static void CastR(IUnit* target)
	{
		if (!R->IsReady() || !target->IsValidTarget(GEntityList->Player(), R->Range())
			|| !ComboR->Enabled() || target->IsDead())
		{
			return;
		}

		if (Raoe->GetInteger() > 0)
		{
			auto minREnemies = Raoe->GetInteger();

			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy != nullptr && !enemy->IsDead())
				{
					if (enemy != nullptr &&  GEntityList->Player()->IsValidTarget(enemy, R->Range()))
					{
						R->CastOnTargetAoE(enemy, minREnemies, kHitChanceMedium);
					}
				}
			}
		}

		/*if (("Rooted"))
		{
		if (target.HasBuff("LuxLightBindingMis"))
		{
		if (HitChance.High)
		{
		R.Cast(target.Position);
		}
		}
		}*/

		if (GHealthPrediction->GetKSDamage(target, kSlotR, R->GetDelay(), false) > target->GetHealth() && ComboRKill->Enabled())
		{
			Vec3 position;
			auto Distance = GetDistance(GEntityList->Player(), target);
			auto delay = R->GetDelay() + Distance / R->Speed();
			GPrediction->GetFutureUnitPosition(target, delay, true, position);

			if (Distance < R->Range())
			{
				R->CastOnPosition(position);
			}
		}
	}

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

		if (target != nullptr && target->IsValidTarget(GEntityList->Player(), Q->Range()) && !target->IsInvulnerable() && !target->IsDead())
		{

			if (!ESkillToggle() && ComboE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				if (EMissile == nullptr)
				{
					/*Vec3 position;
					auto Distance = GetDistance(GEntityList->Player(), target);
					auto delay = E->GetDelay() + Distance / E->Speed();
					GPrediction->GetFutureUnitPosition(target, delay, true, position);

					if (Distance < E->Range())
					{
					E->CastOnTarget(target, kHitChanceHigh);
					}*/

					E->CastOnTarget(target, kHitChanceHigh);
				}
			}

			if (ComboQ->Enabled() & Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				/*Vec3 position;
				auto Distance = GetDistance(GEntityList->Player(), target);
				auto delay = Q->GetDelay() + Distance / Q->Speed();
				GPrediction->GetFutureUnitPosition(target, delay, true, position);

				if (Distance < Q->Range())
				{
				Q->CastOnTarget(target, kHitChanceHigh);
				}*/

				Q->CastOnTarget(target, kHitChanceHigh);
			}

			if (ESkillToggle() && EMissile != nullptr && CountEnemy(EMissile->GetPosition(), E->Radius()) >= 1)
			{
				E->CastOnPlayer();
				GGame->IssueOrder(GEntityList->Player(), kAttackUnit, target);
			}

			if (ComboR->Enabled())
			{
				CastR(target);
			}
		}
	}

	static void Harass()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());

		if (target != nullptr && target->IsValidTarget(GEntityList->Player(), Q->Range()) && !target->IsInvulnerable() && !target->IsDead())
		{

			if (!ESkillToggle() && HarassE->Enabled() && E->IsReady() && target->IsValidTarget(GEntityList->Player(), E->Range()))
			{
				if (EMissile == nullptr)
				{
					/*Vec3 position;
					auto Distance = GetDistance(GEntityList->Player(), target);
					auto delay = E->GetDelay() + Distance / E->Speed();
					GPrediction->GetFutureUnitPosition(target, delay, true, position);

					if (Distance < E->Range())
					{
					E->CastOnTarget(target, kHitChanceHigh);
					}*/

					E->CastOnTarget(target, kHitChanceHigh);
				}
			}

			if (HarassQ->Enabled() & Q->IsReady() && target->IsValidTarget(GEntityList->Player(), Q->Range()))
			{
				/*Vec3 position;
				auto Distance = GetDistance(GEntityList->Player(), target);
				auto delay = Q->GetDelay() + Distance / Q->Speed();
				GPrediction->GetFutureUnitPosition(target, delay, true, position);

				if (Distance < Q->Range())
				{
				Q->CastOnTarget(target, kHitChanceHigh);
				}*/

				Q->CastOnTarget(target, kHitChanceHigh);
			}

			if (ESkillToggle() && EMissile != nullptr && CountEnemy(EMissile->GetPosition(), E->Radius()) >= 1)
			{
				E->CastOnPlayer();
				GGame->IssueOrder(GEntityList->Player(), kAttackUnit, target);
			}
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{
				if (JungleQ->Enabled() && Q->IsReady() && !FoundMinions(Q->Range()) && FoundMinionsNeutral(Q->Range()))
				{

					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							if (GEntityList->Player()->IsValidTarget(minion, 400))
							{
								Q->CastOnUnit(minion);
							}
						}
						else
						{
							if (strstr(minion->GetObjectName(), "Red") || strstr(minion->GetObjectName(), "Blue") ||
								strstr(minion->GetObjectName(), "SRU_Murkwolf2") || strstr(minion->GetObjectName(), "Razorbeak3") ||
								strstr(minion->GetObjectName(), "Razorbeak3") || strstr(minion->GetObjectName(), "SRU_Krug11") ||
								strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "Gromp") ||
								strstr(minion->GetObjectName(), "SRU_Krug5") || strstr(minion->GetObjectName(), "Razorbeak9"))
							{
								Q->CastOnUnit(minion);								
							}
						}
					}
				}

				if (JungleE->Enabled() && E->IsReady() && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger() && !FoundMinions(E->Range()) && FoundMinionsNeutral(E->Range()))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
					{
						Vec3 posE;
						int hitE;

						if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
						{
							GPrediction->FindBestCastPosition(500, E->Radius(), false, true, false, posE, hitE);
						}
						else
						{
							GPrediction->FindBestCastPosition(E->Range(), E->Radius(), false, true, false, posE, hitE);
						}

						if (hitE > 1)
						{
							if (!ESkillToggle() && EMissile == nullptr)
							{
								E->CastOnPosition(posE);
							}
							else if (ESkillToggle() && EMissile != nullptr && CountMinionsNeutral(EMissile->GetPosition(), E->Radius()) >= 1)
							{
								E->CastOnPlayer();
								GGame->IssueOrder(GEntityList->Player(), kAttackUnit, minion);
							}
						}
						else
						{
							if (!ESkillToggle() && EMissile == nullptr)
							{
								E->CastOnUnit(minion);
							}
							else if (ESkillToggle() && EMissile != nullptr && CountMinionsNeutral(EMissile->GetPosition(), E->Radius()) >= 1)
							{
								E->CastOnPlayer();
								GGame->IssueOrder(GEntityList->Player(), kAttackUnit, minion);
							}
						}
					}
				}

				if (JungleW->Enabled() && W->IsReady() && !FoundMinions(W->Range()) && FoundMinionsNeutral(W->Range()))
				{
					W->CastOnPlayer();
				}
			}
		}
	}

	static void LaneClear()
	{
		if (GEntityList->Player()->ManaPercent() > LaneClearMana->GetInteger() && !FoundMinionsNeutral(E->Range() + 100) && FoundMinions(E->Range()))
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (LaneClearE->Enabled() && E->IsReady() && minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
				{
					Vec3 posQ;
					int hitQ;
					GPrediction->FindBestCastPosition(E->Range(), E->Radius(), false, true, false, posQ, hitQ);

					if (!ESkillToggle() && EMissile == nullptr && hitQ >= MinionsE->GetInteger() && E->CastOnPosition(posQ))
					{
						return;
					}

					if (ESkillToggle() && EMissile != nullptr && CountMinions(EMissile->GetPosition(), E->Radius()) >= 1)
					{
						E->CastOnPlayer();
						GGame->IssueOrder(GEntityList->Player(), kAttackUnit, minion);
					}
				}

				if (LaneClearQ->Enabled() && Q->IsReady() && minion != nullptr && !minion->IsDead() && !FoundMinionsNeutral(Q->Range() + 100) && minion->IsValidTarget(GEntityList->Player(), Q->Range()))
				{
					Q->CastOnUnit(minion);
				}
			}
		}
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), W->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), E->Range()); }
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (QGapCloser->Enabled() && Q->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < Q->Range())
		{
			Q->CastOnTarget(args.Sender, kHitChanceMedium);
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{

	}

	static void OnCreateObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Lux_Base_E_mis.troy"))
		{
			EMissile = Source;
		}
	}

	static void OnDeleteObject(IUnit* Source)
	{
		if (strstr(Source->GetObjectName(), "Lux_Base_E_tar_nova.troy"))
		{
			EMissile = nullptr;
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (AutoW->Enabled() && W->IsReady() && Args.Caster_->IsEnemy(GEntityList->Player()) && Args.Caster_ != nullptr && Args.Target_ != nullptr && !GEntityList->Player()->IsRecalling() && !GEntityList->Player()->IsDead())
		{
			if (Args.Caster_->IsHero() && Args.Target_->IsHero() && Args.Caster_->IsEnemy(Args.Target_) && GetDistance(Args.Target_, GEntityList->Player()) <= W->Range())
			{
				auto DamagePercent = (Args.Damage_ / GEntityList->Player()->GetMaxHealth()) * 100;

				if (Args.Target_->HealthPercent() < HealthW->GetInteger() && CountEnemy(GEntityList->Player()->GetPosition(), W->Range()) >= 1)
				{
					if (!MenuDontUlt[Args.Target_->GetNetworkId()]->Enabled()) { return; }

					if (WAllyrisk->Enabled())
					{
						if ((DamagePercent >= 1 || Args.Damage_ >= Args.Target_->GetHealth()))
						{
							W->CastOnPosition(Args.Target_->GetPosition());
						}
					}
					else
					{
						W->CastOnPosition(Args.Target_->GetPosition());
					}

				}
			}
		}
	}

};
