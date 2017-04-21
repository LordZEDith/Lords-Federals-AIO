#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"
#include "HpBarIndicator.h"


class Xayah
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Xayah");		
		
		ComboSettings = MainMenu->AddMenu("Combo Settings");
		{
			ComboQ = ComboSettings->AddSelection("Use Q Mode", 2, std::vector<std::string>({ "Disable", "After AA", "Always" }));
			ComboW = ComboSettings->AddSelection("Use W Mode", 1, std::vector<std::string>({ "Disable", "After AA", "Always" }));
			ComboE = ComboSettings->CheckBox("Use E", false);
			ComboE2 = ComboSettings->CheckBox("Use E KS!", true);
			ComboEA = ComboSettings->AddInteger("E Damage Reduction", 0, 100, 0);
			PassiveStacks = ComboSettings->AddInteger("Min E Feather Stacks", 1, 10, 3);
			ComboR = ComboSettings->CheckBox("Use R", true);
		}

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->AddSelection("Use Q Mode", 2, std::vector<std::string>({ "Disable", "After AA", "Always" }));
			HarassW = HarassSettings->AddSelection("Use W Mode", 1, std::vector<std::string>({ "Disable", "After AA", "Always" }));
			HarassE = HarassSettings->CheckBox("Use E", false);
			hPassiveStacks = HarassSettings->AddInteger("Min E Feather Stacks", 1, 10, 3);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}
		
		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));
			cMode = fedMiscSettings->AddSelection("E Mode Active", 0, std::vector<std::string>({ "Automatic", "Combo/Harass Key" }));
			//ComboAA = fedMiscSettings->AddInteger("Cast Spell When x Feathers", 0, 3, 0);
		}
		
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", true);			
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawAxe = DrawingSettings->CheckBox("Draw Feathers", true);
			DrawNear = DrawingSettings->CheckBox("Draw Feathers Rect", true);
			DrawEA = DrawingSettings->CheckBox("Possible Feathers Return", true);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25f, 50.f, 1850.f, 1050.f);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetOverrideRange(1000);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));		

		R = GPluginSDK->CreateSpell2(kSlotR, kConeCast, true, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25f, 50.f, 1850.f, 1050.f);
	}

	static int PredicChange()
	{
		if (Predic->GetInteger() == 0)
		{
			return mypredic = kHitChanceMedium;
		}
		if (Predic->GetInteger() == 1)
		{
			return mypredic = kHitChanceHigh;
		}
		if (Predic->GetInteger() == 2)
		{
			return mypredic = kHitChanceVeryHigh;
		}

		return mypredic = kHitChanceLow;
	}

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }			
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }			
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}

		for (auto Feather : GEntityList->GetAllUnits())
		{
			if (Feather != nullptr && Feather->GetTeam() == GEntityList->Player()->GetTeam() && !Feather->IsDead() && std::string(Feather->GetObjectName()) == "Feather")
			{
				auto cRect = Geometry::Rectangle(Feather->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), 85);

				for (auto Target : GEntityList->GetAllHeros(false, true))
				{
					if (Target != nullptr)
					{
						if (cRect.IsInside(Target))
						{
							auto nf = false;
							for (auto f : XayahReturn.ToVector())
							{
								if (f.Source->GetNetworkId() == Feather->GetNetworkId() && f.Target == Target)
								{
									nf = true;
								}
							}

							if (!nf)
							{
								XayahFeathers FT;
								FT.Source = Feather;
								FT.Target = Target;
								XayahReturn.Add(FT);
							}
						}
						else
						{
							XayahReturn.RemoveAll([&](XayahFeathers i) {return i.Source->GetNetworkId() == Feather->GetNetworkId() && i.Target == Target; });
						}
					}
				}
			}
		}

		if (DrawAxe->Enabled())
		{
			Vec2 mypos;
			Vec2 fPos;
			GGame->Projection(GEntityList->Player()->GetPosition(), &mypos);

			for (auto Feather : GEntityList->GetAllUnits())
			{
				if (Feather != nullptr && Feather->GetTeam() == GEntityList->Player()->GetTeam() && !Feather->IsDead() && std::string(Feather->GetObjectName()) == "Feather")
				{
					GGame->Projection(Feather->GetPosition(), &fPos);
					GRender->DrawOutlinedCircle(Feather->GetPosition(), Vec4(255, 255, 0, 255), 60);

					//GRender->DrawLine(mypos, fPos, Vec4(255, 255, 0, 255));
					
					if (DrawNear->Enabled())
					{
						auto cRectx = Geometry::Rectangle(Feather->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), 85);

						if (XayahReturn.Count() > 0)
						{
							auto check = false;

							for (auto fx : XayahReturn.ToVector())
							{
								if (fx.Source == Feather)
								{
									check = true;
								}
							}

							if (check)
							{
								cRectx.Draw(Vec4(0, 255, 0, 255), 10);
							}
							else
							{
								cRectx.Draw(Vec4(255, 255, 100, 255), 10);
							}
						}
						else
						{
							cRectx.Draw(Vec4(255, 255, 100, 255), 10);
						}
					}
				}
			}			
		}

		if (DrawEA->Enabled())
		{
			for (auto Target : GEntityList->GetAllHeros(false, true))
			{
				GetTargetDraw = nullptr;

				if (Target != nullptr)
				{
					GetTargetDraw = Target;
					SArray<XayahFeathers> fed = XayahReturn.Where([](XayahFeathers m) {return m.Target == GetTargetDraw; });

					if (fed.Count() > 0)
					{
						Vec2 pos;
						GGame->Projection(Target->GetPosition(), &pos);

						static auto messageTimer = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
						messageTimer->SetLocationFlags(kFontLocationCenter);
						messageTimer->SetOutline(true);

						if (XayahReturn.Count() > 0)
						{
							messageTimer->SetColor(Vec4(0, 255, 0, 255));
							messageTimer->Render(pos.x, pos.y, "Feather Back: %i", fed.Count());
						}
					}
				}
			}
		}

		
		if (DrawComboDamage->Enabled())
		{
			for (auto t : GEntityList->GetAllHeros(false, true))
			{
				auto damage = GetEDamage(t);
				HpBarIndicator::drawDmg(t, damage, Vec4(0, 0, 255, 255));
			}
		}
	}	

	static int GetFeatherBuffCount()
	{
		if (GEntityList->Player()->HasBuff("XayahPassiveActive"))
		{
			return GEntityList->Player()->GetBuffCount("XayahPassiveActive");
		}
		else
		{
			return 0;
		}
	}

	static int CountPossiblesFeathers(IUnit* target)
	{
		GetTarget = nullptr;

		if (XayahReturn.Count() > 0)
		{
			GetTarget = target;
			SArray<XayahFeathers> fed = XayahReturn.Where([](XayahFeathers m) {return m.Target == GetTarget; });

			return fed.Count();
		}

		return 0;
	}

	static void DeleteFeathersCheck()
	{
		if (XayahReturn.Count() > 0)
		{
			for (auto f : XayahReturn.ToVector())
			{
				if (f.Source->IsDead() || !f.Source->IsVisible())
				{					
					XayahReturn.RemoveAll([&](XayahFeathers i) {return i.Source->GetNetworkId() == f.Source->GetNetworkId(); });
				}

				if (f.Target->IsDead() || !f.Target->IsVisible())
				{
					XayahReturn.RemoveAll([&](XayahFeathers i) {return i.Target == f.Target; });
				}
			}
		}
	}

	static void Automatic()
	{
		DeleteFeathersCheck();		
	}

	static float Damage(IUnit* target)
	{
		auto line = CountPossiblesFeathers(target);
		float EDamage[5] = { 50, 60, 70, 80, 90 };
		auto damage = EDamage[GEntityList->Player()->GetSpellLevel(kSlotE) - 1]* 1.05 + (GEntityList->Player()->BonusDamage()* 0.635) /*+ (GEntityList->Player()->CritDamageMultiplier()* 0.5)*/;
		
		if (line == 0)
		{
			return 0;
		}
		if(line == 1)
		{
		return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage);
		}
		if(line == 2)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9);
		}
		if(line == 3)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8);
		}
		if(line == 4)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7);
		}
		if (line == 5)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6);
		}
		if (line == 6)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5);
		}
		if (line == 7)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4);
		}
		if (line == 8)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3);
		}
		if (line == 9)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2);
		}
		if (line == 10)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2 + damage*0.1);
		}
		if (line >= 11)
		{
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2 + damage*0.1 + ((line - 10)*(damage*0.1)));
		}			
	}

	static float GetEDamage(IUnit* target)
	{
		auto damage = Damage(target);

		if (target->HasBuff("FerociousHowl"))
			damage *= 1.f - std::vector<float>{ .5f, .6f, .7f }[target->GetSpellLevel(kSlotR) - 1];

		if (target->HasBuff("meditate"))
			damage *= 1.f - std::vector<float>{ .5f, .55f, .6f, .65f, .7f }[target->GetSpellLevel(kSlotW) - 1];

		if (target->HasBuff("Tantrum"))
			damage -= std::vector<float>{ 2, 4, 6, 8, 10}[target->GetSpellLevel(kSlotE) - 1];

		if (GEntityList->Player()->HasBuff("summonerexhaust"))
			damage *= 0.6f;

		if (std::string(target->GetBaseSkinName()) == "SRU_Baron" && GEntityList->Player()->HasBuff("barontarget"))
			damage *= 0.5f;

		if (target->HasBuff("MoltenShield"))
			damage *= std::vector<float>{ 16.f, 22.f, 28.f, 34.f, 40.f }[target->GetSpellBook()->GetLevel(kSlotE) - 1];

		if (target->HasBuff("braumeshieldbuff"))
			damage *= 1.f - (0.275f + 0.025f * target->GetSpellLevel(kSlotE));

		if (target->HasBuff("BraumShieldRaise"))
			damage *= std::vector<float>{ .3f, .325f, .35f, .375f, .4f }[target->GetSpellBook()->GetLevel(kSlotE) - 1];

		if (target->HasBuff("GarenW"))
			damage *= 0.7f;

		if (target->HasBuff("MaokaiUlt"))
			damage *= 0.8f;

		if (target->HasBuff("GragasWSelf"))
			damage *= 1.f - (0.08f + 0.02f * target->GetSpellLevel(kSlotW));

		if (target->HasBuff("urgotswapdef"))
			damage *= 1.f - (0.2f + 0.1f * target->GetSpellLevel(kSlotR));

		if (GEntityList->Player()->HasBuff("urgotentropypassive"))
			damage *= 0.85;

		if (GEntityList->Player()->HasBuff("itemphantomdancerdebuff") && target->HasItemId(3046))
			damage *= 0.88f;

		if (target->HasBuff("Mastery6263"))
			damage *= 0.96f;

		if (target->HasBuff("MasteryWardenOfTheDawn"))
			damage *= 1.f - 0.06f * target->GetBuffCount("MasteryWardenOfTheDawn");

		damage -= ComboEA->GetInteger();

		return damage;
	}

	void XayahE()
	{
		if (ComboE2->Enabled() && E->IsReady())
		{
			for (auto tar : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(tar))
				{
					GUtility->LogConsole("Dano: %f", Damage(tar));
					if(GetEDamage(tar) >= tar->GetHealth())
					{
						E->CastOnPlayer();
					}
				}
			}
		}
	}


	static void Combo()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(Target)) return;

		if (ComboW->GetInteger() == 2 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
		{
			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (ComboQ->GetInteger() == 2 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
		{
			Q->CastOnTarget(Target, PredicChange());
			LastSpellTick = GGame->TickCount();
		}

		if (ComboE->Enabled() && cMode->GetInteger() == 1 && E->IsReady() && CountPossiblesFeathers(Target) >= PassiveStacks->GetInteger())
		{
			if ( GetFeatherBuffCount() == 0 || CountPossiblesFeathers(Target) >= PassiveStacks->GetInteger())
			{
				E->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}
		}		
	}

	static void AutoE()
	{		
		if (cMode->GetInteger() == 0 && E->IsReady())
		{
			for (auto eTarget : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(eTarget))
				{
					if (CountPossiblesFeathers(eTarget) >= PassiveStacks->GetInteger() && CountPossiblesFeathers(eTarget) >= 3)
					{
						E->CastOnPlayer();
					}
				}
			}
		}
	}

	static void Harass()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(Target) || GEntityList->Player()->ManaPercent() < HarassMana->GetInteger()) return;

		if (HarassQ->GetInteger() == 2 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
		{
			Q->CastOnTarget(Target, PredicChange());
			LastSpellTick = GGame->TickCount();
		}
		
		if (HarassW->GetInteger() == 2 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
		{
			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (HarassE->Enabled() && cMode->GetInteger() == 1 && E->IsReady() && CountPossiblesFeathers(Target) >= hPassiveStacks->GetInteger())
		{
			if (GetFeatherBuffCount() == 0 || CountPossiblesFeathers(Target) >= hPassiveStacks->GetInteger())
			{
				E->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}
		}
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

	static void OnAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (!CheckTarget(Target)) return;

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (ComboW->GetInteger() == 1 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
			{
				W->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}

			if (ComboQ->GetInteger() == 1 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
			{
				Q->CastOnTarget(Target, PredicChange());
				LastSpellTick = GGame->TickCount();
			}
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			if (HarassW->GetInteger() == 1 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
			{
				W->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}

			if (HarassQ->GetInteger() == 1 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
			{
				Q->CastOnTarget(Target, PredicChange());
				LastSpellTick = GGame->TickCount();
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& Args)
	{

	}

	static void OnCreateObject(IUnit* Source)
	{

	}

	static void OnDeleteObject(IUnit* Source)
	{
		
	}
};