#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"

static float _humQcd, _humWcd, _humEcd;
static float _spidQcd, _spidWcd, _spidEcd;
static float _humaQcd, _humaWcd, _humaEcd;
static float _spideQcd, _spideWcd, _spideEcd;

IMenuOption* Qspider;
IMenuOption* Wspider;
IMenuOption* Espider;
IMenuOption* JungleQspider;
IMenuOption* JungleWspider;
IMenuOption* JungleEspider;

class Elise
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Federal Olaf");
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->CheckBox("Human Combo Q", true);
			ComboW = ComboSettings->CheckBox("Human Combo W", true);
			ComboE = ComboSettings->CheckBox("Human Combo E", true);
			Qspider = ComboSettings->CheckBox("Spider Combo Q", true);
			Wspider = ComboSettings->CheckBox("Spider Combo W", true);
			Espider = ComboSettings->CheckBox("Spider Combo E", true);
			ComboR = ComboSettings->CheckBox("Auto Switch Form", true);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Human Q jungle", true);
			JungleW = JungleClearSettings->CheckBox("Human W jungle", true);
			JungleE = JungleClearSettings->CheckBox("Human E jungle", true);
			JungleQspider = JungleClearSettings->CheckBox("Spider Jungle Q", true);
			JungleWspider = JungleClearSettings->CheckBox("Spider Jungle W", true);
			JungleEspider = JungleClearSettings->CheckBox("Spider Jungle E", true);
			JungleR = JungleClearSettings->CheckBox("Auto Switch Form", true);
			JungleMana = JungleClearSettings->AddInteger("Minimum MP% to jungle", 1, 100, 20);
		}

		MiscSettings = MainMenu->AddMenu("Misc Settings");
		{
			Predic = MiscSettings->CheckBox("HitChance - Off: Medium | On: Hight", true);
			EGapCloser = MiscSettings->CheckBox("Human E GapCloser", false);
			QGapCloser = MiscSettings->CheckBox("Spider E GapCloser", false);
			EInterrupter = MiscSettings->CheckBox("Automatically E Interrupt Spell", true);						
			CheckShield = MiscSettings->CheckBox("No Charm (BlackShield, Banshee)", true);
			SemiManualKey = MiscSettings->AddKey("Fast Rappel", 71);
		}
		
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", false);	
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

		SkinsChange = MainMenu->AddMenu("Skins Changer");
		{
			MiscSkin = SkinsChange->AddInteger("Skins", 1, 5, 1);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
		Q->SetOverrideRange(625.f);
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
		W->SetSkillshot(0.25f, 100.f, 1000.f, 950.f);
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
		E->SetSkillshot(0.25f, 55.f, 1600.f, 1075.f);
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);

		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		Q2->SetOverrideRange(475.f);
		W2 = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		E2 = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E2->SetOverrideRange(750.f);
		
	}

	static void SkinChanger()
	{
		if (GEntityList->Player()->GetSkinId() != MiscSkin->GetInteger())
		{
			GEntityList->Player()->SetSkinId(MiscSkin->GetInteger());
		}
	}	
		
	static bool EliseHuman()
	{
		if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "EliseHumanQ"))
		{
			//GGame->PrintChat("Sou humano");
			return true;
		}

		return false;
	}

	static bool EliseSpider()
	{
		if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "EliseSpiderQCast"))
		{
			//GGame->PrintChat("Sou Aranha");
			return true;
		}

		return false;
	}

	static void EliseRappel()
	{
		if (IsKeyDown(SemiManualKey))
		{
			if (EliseHuman() && R->IsReady())
			{
				R->CastOnPlayer();
				E2->CastOnPlayer();
			}

			if (EliseSpider())
			{
				E2->CastOnPlayer();
			}
		}
	}
	
	static void Cooldowns()
	{
		_humaQcd = _humQcd - GGame->Time() > 0 ? _humQcd - GGame->Time() : 0;
		_humaWcd = _humWcd - GGame->Time() > 0 ? _humWcd - GGame->Time() : 0;
		_humaEcd = _humEcd - GGame->Time() > 0 ? _humEcd - GGame->Time() : 0;
		_spideQcd = _spidQcd - GGame->Time() > 0 ? _spidQcd - GGame->Time() : 0;
		_spideWcd = _spidWcd - GGame->Time() > 0 ? _spidWcd - GGame->Time() : 0;
		_spideEcd = _spidEcd - GGame->Time() > 0 ? _spidEcd - GGame->Time() : 0;
	}

	static void GetCooldown(CastedSpell spell)
	{
		if (EliseHuman())
		{
			if (spell.Name_ == "EliseHumanQ")
				_humQcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotQ);
			if (spell.Name_ == "EliseHumanW")
				_humWcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotW);
			if (spell.Name_ == "EliseHumanE")
				_humEcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotE);
		}
		if (EliseSpider())
		{
			if (spell.Name_ == "EliseSpiderQCast")
				_spidQcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotQ);
			if (spell.Name_ == "EliseSpiderW")
				_spidWcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotW);
			if (spell.Name_ == "EliseSpiderEInitial")
				_spidEcd = GEntityList->Player()->GetSpellRemainingCooldown(kSlotE);
		}
	}

	static void CastR()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		auto Target2 = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q2->Range());

		if (!CheckTarget(Target) || !R->IsReady()) return;

		if (EliseHuman())
		{
			if (!Q->IsReady() && !W->IsReady() && !E->IsReady())
			{
				if ((_spideQcd <= 0.f) && (_spideWcd <= 1.8f))
				{
					if ((Target->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), Target, kSlotQ)) &&
						(_humaQcd <= 1.5f) &&
						((_humaQcd <= 1.2f) || (_humaWcd <= 2)))
					{
						return;
					}
					else
					{
						R->CastOnPlayer();
					}
				}
			}
		}

		if (EliseSpider())
			if (!Q2->IsReady() && !W2->IsReady() && !GEntityList->Player()->HasBuff("EliseSpiderW"))
			{
				if ((_humaQcd <= 0.f) || ((_humaWcd <= 1.5f) && (_humaEcd <= 0.8f)))
				{
					if ((Target2->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), Target2, kSlotQ)) &&
						(_spideQcd <= 1.4f) &&
						((_spideQcd <= 1.0f) || (_spideWcd > 1.9f)))
					{
						return;
					}
					else
					{
						R->CastOnPlayer();
					}
				}
			}
	}

	static void CastSpiderAutoE()
	{
		if (EliseSpider() && E2->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, TrueDamage, E2->Range());
			if (!CheckTarget(target)) return;

			if ((!Q2->IsReady() || (Q2->Range() <= GetDistance(GEntityList->Player(), target))) && !W2->IsReady())
			{
				if (target->HasBuffOfType(BUFF_Stun))
				{
					E2->CastOnPlayer();
				}
			}
		}
	}

	static void CastSpiderE()
	{
		if (EliseSpider() && E2->IsReady())
		{
			auto Target = GTargetSelector->FindTarget(QuickestKill, TrueDamage, E2->Range());
			auto EQtarget = GTargetSelector->FindTarget(QuickestKill, TrueDamage, E2->Range() + Q->Range());

			if (Target != nullptr)
			{
				if (CanMove(Target) && (GetDistance(GEntityList->Player(), Target) < E2->Range() - 10))
				{
					E2->CastOnUnit(Target);
				}
				if (!CanMove(Target))
				{
					E2->CastOnUnit(Target);
				}
			}

			if (EQtarget != nullptr)
			{
				if (CanMove(EQtarget) && (GetDistance(GEntityList->Player(), EQtarget) < E2->Range() + Q2->Range() - 10))
				{
					for (auto minion : GEntityList->GetAllMinions(false, true, true))
					{
						if (minion != nullptr && minion->IsValidTarget(GEntityList->Player(), E2->Range() + Q->Range()))
						{
							if (GetDistance(GEntityList->Player(), minion) < E->Range())
							{
								E2->CastOnUnit(minion);
							}
						}
					}
				}
			}
		}
	}	

	static void Combo()
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());		

		if (CheckTarget(target))
		{
			auto qdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
			auto wdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW);

			if (EliseHuman())
			{
				if (GetDistance(GEntityList->Player(), target) < E->Range() && ComboE->Enabled() && E->IsReady())
				{
					E->CastOnTarget(target, kHitChanceHigh);;
				}

				if (GetDistance(GEntityList->Player(), target) <= W->Range() && ComboW->Enabled() && W->IsReady())
				{
					W->CastOnTarget(target, kHitChanceHigh);
				}

				if (GetDistance(GEntityList->Player(), target) <= Q->Range() && ComboQ->Enabled() && Q->IsReady())
				{
					Q->CastOnUnit(target);
				}				
				
				if (ComboR->Enabled())
				{
					CastR();
				}
			}

			if (EliseSpider())
			{
				if (GetDistance(GEntityList->Player(), target) <= Q2->Range() && Qspider->Enabled() && Q2->IsReady())
				{
					Q2->CastOnUnit(target);;
				}
				if (Espider->Enabled() && E2->IsReady())
				{
					//E2->CastOnUnit(target);
					CastSpiderE();
				}
				if (ComboR->Enabled())
				{
					CastR();
				}

				if ((_humaQcd <= 0.f && qdmg >= target->GetHealth() || _humaWcd <= 0.f && wdmg >= target->GetHealth()) && R->IsReady() && !Q2->IsReady() && ComboR->Enabled())
				{
					R->CastOnPlayer();
				}
			}
		}
	}

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{

			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{

				if (EliseHuman())
				{
					if (JungleR->Enabled() && R->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
						{
							if ((!Q->IsReady() || !JungleQ->Enabled()) && (!W->IsReady() || !JungleW->Enabled()))
							{
								if (((_spideQcd == 0) && (_spideWcd <= 1.8f)) || (_humaQcd >= 1.2f))
								{
									R->CastOnPlayer();
								}
							}
						}
					}

					if (JungleE->Enabled() && E->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
						{
							if (strstr(minion->GetObjectName(), "Dragon") || strstr(minion->GetObjectName(), "Baron") ||
								strstr(minion->GetObjectName(), "Crab") || strstr(minion->GetObjectName(), "RiftHerald"))
							{
								if (GEntityList->Player()->IsValidTarget(minion, 400))
								{
									E->CastOnUnit(minion);
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
									E->CastOnUnit(minion);
								}
							}
						}
					}

					if (JungleW->Enabled() && W->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, W->Range()))
						{
							W->CastOnUnit(minion);
						}
					}

					if (JungleQ->Enabled() && Q->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
						{
							Q->CastOnUnit(minion);
						}
					}
				}

				if (EliseSpider())
				{
					if (JungleR->Enabled() && R->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E->Range()))
						{
							if (!Q2->IsReady() && !W2->IsReady() && !GEntityList->Player()->HasBuff("EliseSpiderW"))
							{
								if ((_humaQcd <= 0.f) || ((_humaWcd <= 0.f) && (_humaEcd <= 0.f)))
								{									
										R->CastOnPlayer();									
								}
							}
						}
					}

					if (JungleEspider->Enabled() && E2->IsReady() && Q2->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, E2->Range() + Q2->Range()))
						{
							if (GetDistance(GEntityList->Player(), minion) < E2->Range() && GetDistance(GEntityList->Player(), minion) > Q2->Range())
							{
								if (strstr(minion->GetObjectName(), "Red") || strstr(minion->GetObjectName(), "Blue") ||
									strstr(minion->GetObjectName(), "SRU_Murkwolf2") || strstr(minion->GetObjectName(), "Razorbeak3") ||
									strstr(minion->GetObjectName(), "Razorbeak3") || strstr(minion->GetObjectName(), "SRU_Krug11") ||
									strstr(minion->GetObjectName(), "Gromp") ||
									strstr(minion->GetObjectName(), "SRU_Krug5") || strstr(minion->GetObjectName(), "Razorbeak9"))
								{
									E2->CastOnUnit(minion);
								}
							}
						}
					}

					if (JungleQspider->Enabled() && Q2->IsReady())
					{
						if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q2->Range()))
						{
							Q2->CastOnUnit(minion);
						}
					}
				}
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{
		if (Args.Caster_ == GEntityList->Player())
		{
			GetCooldown(Args);
		}
	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		if (source != GEntityList->Player() || target == nullptr)
			return;

		switch (GOrbwalking->GetOrbwalkingMode())
		{
		case kModeCombo:
			if (EliseSpider() && Wspider->Enabled() && W->IsReady())
			{
				W->CastOnPlayer();
			}
			break;
		case kModeLaneClear:
			if (EliseSpider() && JungleWspider->Enabled() && W2->IsReady() && FoundMinionsNeutral(600))
			{
				if (GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger())
				{
					W->CastOnPlayer();
				}
			}
			break;
		default:;
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{
		if (EliseHuman() && EGapCloser->Enabled() && E->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E->Range())
		{
			E->CastOnTarget(args.Sender, kHitChanceHigh);
		}

		if (!EliseHuman() && QGapCloser->Enabled() && E2->IsReady() && !args.IsTargeted && GetDistanceVectors(GEntityList->Player()->GetPosition(), args.EndPosition) < E2->Range())
		{
			E2->CastOnUnit(args.Sender);
		}
	}

	static void OnInterruptible(InterruptibleSpell const& Args)
	{
		if (EInterrupter->Enabled() && GetDistance(GEntityList->Player(), Args.Target) < E->Range())
		{
			if (EliseSpider() && E->IsReady() && R->IsReady())
			{
				R->CastOnPlayer();
				E->CastOnTarget(Args.Target, kHitChanceHigh);
			}

			if (EliseHuman() && E->IsReady())
			{
				E->CastOnTarget(Args.Target, kHitChanceHigh);
			}
		}
	}

	static void Drawings()
	{
		if (EliseHuman())
		{
			if (DrawReady->Enabled())
			{
				if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
				if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
				if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			}
			else
			{
				if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
				if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
				if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			}
		}
		else
		{
			if (DrawReady->Enabled())
			{
				if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q2->Range()); }
				if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E2->Range()); }
				if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W2->Range()); }
			}
			else
			{
				if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q2->Range()); }
				if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E2->Range()); }
				if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W2->Range()); }
			}
		}
				
	}
};
