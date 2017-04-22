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
			ComboQ = ComboSettings->AddSelection("Use Q Mode", 2, std::vector<std::string>({ "Off", "AfterAttacks", "Always" }));
			ComboW = ComboSettings->AddSelection("Use W Mode", 1, std::vector<std::string>({ "Off", "AfterAttacks", "Always" }));
			ComboE = ComboSettings->CheckBox("Use E", false);
			ComboE2 = ComboSettings->CheckBox("Use E KS!", true);
			ComboEA = ComboSettings->AddInteger("E Damage Reduction", 0, 100, 0);
			PassiveStacks = ComboSettings->AddInteger("Min E Feather Stacks", 1, 10, 3);			
			SemiManualKey = ComboSettings->AddKey("Semi Manual Cast R key", 71);
			RMode = ComboSettings->AddSelection("R Semi Manual Mode", 1, std::vector<std::string>({ "Target Selector", "Nearest Cursor" }));
		}		

		HarassSettings = MainMenu->AddMenu("Harass Settings");
		{
			HarassQ = HarassSettings->AddSelection("Use Q Mode", 2, std::vector<std::string>({ "Off", "AfterAttacks", "Always" }));
			HarassW = HarassSettings->AddSelection("Use W Mode", 1, std::vector<std::string>({ "Off", "AfterAttacks", "Always" }));
			HarassE = HarassSettings->CheckBox("Use E", false);
			hPassiveStacks = HarassSettings->AddInteger("Min E Feather Stacks", 1, 10, 3);
			HarassMana = HarassSettings->AddInteger("Minimum MP% to Harass", 1, 100, 60);
		}

		LaneClearSettings = MainMenu->AddMenu("LaneClear Settings");
		{
			LaneClearQ = LaneClearSettings->CheckBox("Use Q in LaneClear", true);
			MinionsQ = LaneClearSettings->AddInteger("Minimum minions to Q", 1, 10, 4);
			LaneClearW = LaneClearSettings->CheckBox("Use W in LaneClear", true);
			MinionsW = LaneClearSettings->AddInteger("Minimum minions to W", 1, 10, 6);
			LaneClearE = LaneClearSettings->CheckBox("Use E in LaneClear", true);
			MinionsE = LaneClearSettings->AddInteger("Minimum minions Kiable with E", 1, 10, 4);
			LaneClearMana = LaneClearSettings->AddInteger("Minimum MP% to LaneClear", 1, 100, 60);
		}

		JungleClearSettings = MainMenu->AddMenu("JungleClear Settings");
		{
			JungleQ = JungleClearSettings->CheckBox("Use Q in Jungle", true);
			JungleW = JungleClearSettings->CheckBox("Use W in Jungle", true);
			JungleE = JungleClearSettings->CheckBox("Use E in Jungle", true);
			jPassiveStacks = JungleClearSettings->AddInteger("Min E Feather Stacks", 0, 12, 5);
			JungleMana = JungleClearSettings->AddInteger("Min Mana to Jungle", 1, 100, 30);
		}
		
		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction", 1, std::vector<std::string>({ "Medium", "High", "Very High" }));
			cMode = fedMiscSettings->AddSelection("E Mode Active", 1, std::vector<std::string>({ "Automatic", "Combo/Harass Key" }));
			SaveMana = fedMiscSettings->CheckBox("Save Mana to Cast E", true);
			AutoR = fedMiscSettings->CheckBox("Auto R Dodge Dangers Spells", true);
			//ComboAA = fedMiscSettings->AddInteger("Cast Spell When x Feathers", 0, 3, 0);
		}
		
		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", true);
			DrawW = DrawingSettings->CheckBox("Draw W", false);			
			DrawR = DrawingSettings->CheckBox("Draw R", false);			
			DrawNear = DrawingSettings->AddSelection("Draw Feathers", 1, std::vector<std::string>({ "Off", "Rectangle", "Line" }));
			DrawColor = DrawingSettings->AddColor("Draws Color", 138, 43, 226, 255);
			DrawEA = DrawingSettings->AddSelection("Possible Feathers Return", 1, std::vector<std::string>({ "Off", "Mode Small", "Mode Big" }));			
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25f, 60.f, 1800.f, 1050.f);		

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetOverrideRange(1000);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));		

		R = GPluginSDK->CreateSpell2(kSlotR, kConeCast, true, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25f, 80.f, 1800.f, 1050.f);
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
		Vec4 MyColor;
		DrawColor->GetColor(&MyColor);
		
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, Q->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, W->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, Q->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, W->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), MyColor, R->Range()); }
		}

		for (auto Feather : GEntityList->GetAllUnits())
		{
			if (Feather != nullptr && Feather->GetTeam() == GEntityList->Player()->GetTeam() && !Feather->IsDead() && std::string(Feather->GetObjectName()) == "Feather")
			{
				auto cRect = Geometry::Rectangle(Feather->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), 85);

				for (auto Target : GEntityList->GetAllUnitsOfTypes(std::vector<eGameObjectClassId>({ kAIHeroClient, kobj_AI_Minion, kNeutralMinionCamp })))
				{
					if (Target != nullptr && Target->GetTeam() != GEntityList->Player()->GetTeam())
					{
						if (cRect.IsInside(Target) && Target->IsVisible() && !Target->IsDead())
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

		if (DrawNear->GetInteger() > 0)
		{
			Vec2 mypos;
			Vec2 fPos;
			GGame->Projection(GEntityList->Player()->GetPosition(), &mypos);

			for (auto Feather : GEntityList->GetAllUnits())
			{
				if (Feather != nullptr && Feather->GetTeam() == GEntityList->Player()->GetTeam() && !Feather->IsDead() && std::string(Feather->GetObjectName()) == "Feather")
				{
					GGame->Projection(Feather->GetPosition(), &fPos);					

					//GRender->DrawLine(mypos, fPos, Vec4(255, 255, 0, 255));					

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
							if (DrawNear->GetInteger() == 1)
							{
								cRectx.Draw(MyColor, 10);
							}
							else
							{
								GRender->DrawLine(mypos, fPos, MyColor);
							}
							GRender->DrawOutlinedCircle(Feather->GetPosition(), MyColor, 60);
						}
						else
						{
							if (DrawNear->GetInteger() == 1)
							{
								cRectx.Draw(Vec4(128, 128, 128, 255), 10);
							}
							else
							{
								GRender->DrawLine(mypos, fPos, Vec4(128, 128, 128, 255));
							}							
							GRender->DrawOutlinedCircle(Feather->GetPosition(), Vec4(128, 128, 128, 255), 60);
						}
					}
					else
					{
						if (DrawNear->GetInteger() == 1)
						{
							cRectx.Draw(Vec4(128, 128, 128, 255), 10);
						}
						else
						{
							GRender->DrawLine(mypos, fPos, Vec4(128, 128, 128, 255));
						}
						GRender->DrawOutlinedCircle(Feather->GetPosition(), Vec4(128, 128, 128, 255), 60);
					}
				}
			}			
		}

		if (DrawEA->GetInteger() > 0)
		{
			for (auto Target : GEntityList->GetAllUnitsOfTypes(std::vector<eGameObjectClassId>({ kAIHeroClient, kobj_AI_Minion, kNeutralMinionCamp })))
			{
				GetTargetDraw = nullptr;

				if (Target != nullptr && Target->GetTeam() != GEntityList->Player()->GetTeam())
				{
					GetTargetDraw = Target;
					SArray<XayahFeathers> fed = XayahReturn.Where([](XayahFeathers m) {return m.Target == GetTargetDraw; });

					if (fed.Count() > 0)
					{
						Vec2 pos;

						if (GetTargetDraw->IsHero())
						{
							if (GetTargetDraw->GetHPBarPosition(pos) && DrawEA->GetInteger() == 1)
							{
								static auto messageTimer = GRender->CreateFontW("Comic Sans", 16.f, kFontWeightNormal);
								messageTimer->SetLocationFlags(kFontLocationCenterVertical);
								messageTimer->SetOutline(true);

								if (XayahReturn.Count() > 0)
								{
									messageTimer->SetColor(Vec4(255, 255, 0, 255));
									messageTimer->Render(pos.x + 10, pos.y, "Feather Back: %i", fed.Count());
								}
							}
							else if (DrawEA->GetInteger() == 2)
							{								
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
						else
						{
							Vec2 LifePos;
							if (GetTargetDraw->GetHPBarPosition(LifePos))
							{
								static auto messageTimer = GRender->CreateFontW("Comic Sans", 12.f, kFontWeightNormal);
								messageTimer->SetLocationFlags(kFontLocationCenterVertical);
								messageTimer->SetOutline(true);

								if (XayahReturn.Count() > 0)
								{
									messageTimer->SetColor(Vec4(211, 211, 211, 255));
									messageTimer->Render(LifePos.x, LifePos.y - 3, "Feather Back: %i", fed.Count());
								}

							}
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
		auto damage = EDamage[GEntityList->Player()->GetSpellLevel(kSlotE) - 1]* 1.05 + (GEntityList->Player()->BonusDamage()* 0.635);
		auto dcrit = (GEntityList->Player()->Crit() * 0.49);
		
		if (line == 0)
		{
			return 0;
		}
		if(line == 1)
		{
		return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, damage + (dcrit * damage));
		}
		if(line == 2)
		{
			auto dano = damage + damage*0.9;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if(line == 3)
		{
			auto dano = damage + damage*0.9 + damage*0.8;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if(line == 4)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 5)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 6)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 7)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 8)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 9)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line == 10)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2 + damage*0.1;
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
		}
		if (line >= 11)
		{
			auto dano = damage + damage*0.9 + damage*0.8 + damage*0.7 + damage*0.6 + damage*0.5 + damage*0.4 + damage*0.3 + damage*0.2 + damage*0.1 + ((line - 10)*(damage*0.1));
			auto danocalc = dano + (dano * dcrit);
			return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, danocalc);
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

	static void XayahE()
	{
		if (ComboE2->Enabled() && E->IsReady())
		{
			for (auto tar : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(tar))
				{
					GUtility->LogConsole("Dano: %f, Critico? %f, My Critic? %f", Damage(tar), tar->Crit(), GEntityList->Player()->Crit());
					if(GetEDamage(tar) >= tar->GetHealth() && !tar->IsDashing())
					{
						E->CastOnPlayer();
					}
				}
			}			
		}
	}

	static void KSJungle()
	{
		if (JungleE->Enabled() && E->IsReady())
		{
			for (auto jm : GEntityList->GetAllMinions(false, false, true))
			{
				if (CheckTarget(jm))
				{
					if (strstr(jm->GetObjectName(), "Dragon") ||
						strstr(jm->GetObjectName(), "Baron") ||
						strstr(jm->GetObjectName(), "Gromp") ||
						strstr(jm->GetObjectName(), "Crab") ||
						strstr(jm->GetObjectName(), "Razorbeak3") ||
						strstr(jm->GetObjectName(), "Razorbeak9") ||
						strstr(jm->GetObjectName(), "SRU_Krug11") ||
						strstr(jm->GetObjectName(), "SRU_Krug5") ||
						strstr(jm->GetObjectName(), "SRU_Murkwolf2") ||
						strstr(jm->GetObjectName(), "Red") ||
						strstr(jm->GetObjectName(), "Blue") ||
						strstr(jm->GetObjectName(), "RiftHerald"))
					{
						//GUtility->LogConsole("Dano Neutral: %f | DanoAA: %f", Damage(jm), GDamage->GetAutoAttackDamage(GEntityList->Player(), jm, false));
						
						if (Damage(jm) > jm->GetHealth() && GDamage->GetAutoAttackDamage(GEntityList->Player(), jm, false) < jm->GetHealth())
						{
							E->CastOnPlayer();
						}
					}
				}
			}
		}

		if (LaneClearE->Enabled() && E->IsReady() && CountMinionsKiable() >= MinionsE->GetInteger())
		{
			E->CastOnPlayer();
		}		
	}

	static int CountMinionsKiable()
	{
		if (XayahReturn.Count() > 0)
		{			
			SArray<XayahFeathers> minions = XayahReturn.Where([](XayahFeathers m) {return !m.Target->IsDead() && m.Target->IsVisible() && m.Target->IsCreep() && (Damage(m.Target) * 0.498) > m.Target->GetHealth() && GDamage->GetAutoAttackDamage(GEntityList->Player(), m.Target, false) < m.Target->GetHealth(); });

			return minions.Count();
		}

		return 0;
	}

	static void Combo()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(Target)) return;

		if (ComboW->GetInteger() == 2 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
		{
			if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + W->ManaCost()) return;

			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (ComboQ->GetInteger() == 2 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
		{
			if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;

			Q->CastOnTarget(Target, PredicChange());
			LastSpellTick = GGame->TickCount();
		}

		if (ComboE->Enabled() && cMode->GetInteger() == 1 && E->IsReady() && CountPossiblesFeathers(Target) >= PassiveStacks->GetInteger() && !Target->IsDashing())
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
			if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;

			Q->CastOnTarget(Target, PredicChange());
			LastSpellTick = GGame->TickCount();
		}
		
		if (HarassW->GetInteger() == 2 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
		{
			if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + W->ManaCost()) return;

			W->CastOnPlayer();
			LastSpellTick = GGame->TickCount();
		}

		if (HarassE->Enabled() && cMode->GetInteger() == 1 && E->IsReady() && CountPossiblesFeathers(Target) >= hPassiveStacks->GetInteger() && !Target->IsDashing())
		{
			if (GetFeatherBuffCount() == 0 || CountPossiblesFeathers(Target) >= hPassiveStacks->GetInteger())
			{
				E->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}
		}
	}	

	static void JungleClear()
	{
		if (JungleMana->GetInteger() < GEntityList->Player()->ManaPercent())
		{
			SArray<IUnit*> Minion = SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([](IUnit* m) {return m != nullptr &&
				!m->IsDead() && m->IsVisible() && m->IsValidTarget(GEntityList->Player(), Q->Range()) && m->IsJungleCreep() && !strstr(m->GetObjectName(), "WardCorpse"); });

			if (Minion.Any())
			{
				auto jMonster = Minion.MinOrDefault<float>([](IUnit* i) {return GetDistanceVectors(i->GetPosition(), GGame->CursorPosition()); });

				if (JungleQ->Enabled() && Q->IsReady() && !FoundMinions(Q->Range()) && FoundMinionsNeutral(Q->Range()))
				{
					auto pred = FindBestLineCastPositionNeutral(vector<Vec3>{ GEntityList->Player()->GetPosition() }, 600, Q->Range(), Q->Radius(), true, false);

					if (pred.HitCount > 1)
					{
						if (GetDistanceVectors(GEntityList->Player()->GetPosition(), pred.CastPosition) <= Q->Range())
						{
							if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;
							Q->CastOnPosition(pred.CastPosition);
						}
					}
					else
					{
						if (CheckTarget(jMonster) && jMonster->IsValidTarget(GEntityList->Player(), Q->Range()))
						{
							if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;
							Q->CastOnUnit(jMonster);
						}
					}
				}

				if (JungleE->Enabled() && E->IsReady() && jPassiveStacks->GetInteger() > 0 && CountPossiblesFeathers(jMonster) >= jPassiveStacks->GetInteger()
					&& jMonster->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(jMonster)))
				{
					E->CastOnPlayer();
				}
			}
		}
	}

	static void LaneClear()
	{
		auto pred = FindBestLineCastPosition(vector<Vec3>{ GEntityList->Player()->GetPosition() }, Q->Range(), Q->Range(), Q->Radius(), true, true);

		if (FoundMinions(Q->Range()) && !FoundMinionsNeutral(Q->Range()))
		{
			if (LaneClearQ->Enabled() && Q->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger() && pred.HitCount >= MinionsQ->GetInteger())
			{
				if (GetDistanceVectors(GEntityList->Player()->GetPosition(), pred.CastPosition) <= Q->Range())
				{
					Q->CastOnPosition(pred.CastPosition);
				}
			}

			if (LaneClearW->Enabled() && W->IsReady() && GEntityList->Player()->ManaPercent() >= LaneClearMana->GetInteger()
				&& CountMinions(GEntityList->Player()->GetPosition(), GEntityList->Player()->AttackRange()) >= MinionsW->GetInteger())
			{
				W->CastOnPlayer();
			}			
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (CheckTarget(Target) && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (Target->IsHero() && ComboW->GetInteger() == 1 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + W->ManaCost()) return;
				W->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}

			if (Target->IsHero() && ComboQ->GetInteger() == 1 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;
				Q->CastOnTarget(Target, PredicChange());
				LastSpellTick = GGame->TickCount();
			}
		}

		if (CheckTarget(Target) && GOrbwalking->GetOrbwalkingMode() == kModeMixed && GEntityList->Player()->ManaPercent() >= HarassMana->GetInteger())
		{
			if (Target->IsHero() && HarassW->GetInteger() == 1 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + W->ManaCost()) return;
				W->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}

			if (Target->IsHero() && HarassQ->GetInteger() == 1 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + Q->ManaCost()) return;
				Q->CastOnTarget(Target, PredicChange());
				LastSpellTick = GGame->TickCount();
			}
		}

		if (CheckTarget(Target) && Target->IsJungleCreep() && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear && GEntityList->Player()->ManaPercent() >= JungleMana->GetInteger())
		{
			if (JungleW->Enabled() && W->IsReady() && GetFeatherBuffCount() <= 2)
			{
				if (SaveMana->Enabled() && GEntityList->Player()->GetMana() <= E->ManaCost() + W->ManaCost()) return;
				W->CastOnPlayer();
			}
		}
	}

	static void OnProcessSpell(CastedSpell const& args)
	{
		if (AutoR->Enabled() && args.Caster_->IsHero() && args.Caster_->GetTeam() != GEntityList->Player()->GetTeam())
		{
			std::string SName = args.Name_;
			for (auto Spells : SpellsDangerList)
			{
				if (strstr(Spells.Name.data(), ToLower(SName).c_str()))
				{					
					Vec2 EndPosition;
					ProjectionInfo projection;

					if (Spells.Type == isSkillshotCircle)
					{

					}

					if (Spells.Type == isSkillshotLine)
					{
						if (GetDistanceVectors(args.Position_, args.EndPosition_) > R->Range())
						{
							EndPosition = args.Position_.To2D() + (args.EndPosition_.To2D() - args.Position_.To2D()).VectorNormalize() * (R->Range() * 2);
						}

						if (GetDistanceVectors(args.Position_, args.EndPosition_) < R->Range())
						{
							EndPosition = args.Position_.To2D() + (args.EndPosition_.To2D() - args.Position_.To2D()).VectorNormalize() * (R->Range() + 50);
						}

						ProjectOn(GEntityList->Player()->ServerPosition().To2D(), args.Position_.To2D(), args.EndPosition_.To2D(), projection);

						if (projection.IsOnSegment)
						{
							if (R->IsReady())
							{
								R->CastOnPosition(args.Caster_->GetPosition());
							}
						}
					}					

					if (Spells.Type == isTargeted)
					{
						if (args.Target_ != nullptr && args.Target_->GetNetworkId() == GEntityList->Player()->GetNetworkId())
						{
							if (R->IsReady())
							{
								R->CastOnPosition(args.Caster_->GetPosition());
							}
						}
					}

					if (Spells.Type == isSelfCast)
					{
						if (args.Target_ != nullptr && GetDistance(GEntityList->Player(), args.Target_) <= args.Radius_) {
							if (R->IsReady())
							{
								R->CastOnPosition(args.Caster_->GetPosition());
							}
						}
					}					
				}
			}
		}		
	}

	static void OnCreateObject(IUnit* Source)
	{

	}

	static void OnDeleteObject(IUnit* Source)
	{
		
	}

	static void SemiManualR()
	{
		if (IsKeyDown(SemiManualKey))
		{
			//GOrbwalking->Orbwalk(nullptr, GGame->CursorPosition());

			if (!R->IsReady())
			{
				return;
			}

			IUnit* TargetR = nullptr;

			if (RMode->GetInteger() == 0)
			{
				TargetR = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
			}
			else
			{
				SArray<IUnit*> rtarget = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([](IUnit* m) {return m != nullptr &&
					!m->IsDead() && m->IsVisible()
					&& m->IsValidTarget(GEntityList->Player(), R->Range()); }).OrderBy<float>([&](IUnit* x) {return GetDistanceVectors(x->GetPosition(), GGame->CursorPosition()); });

				if (rtarget.Any())
				{
					for (auto x : rtarget.ToVector())
					{
						if (GetDistance(GEntityList->Player(), x) <= R->Range() && GetDistanceVectors(GGame->CursorPosition(), x->GetPosition()) <= 500)
						{
							TargetR = x;
						}
					}
				}
			}

			if (CheckTarget(TargetR) && CheckShielded(TargetR) && TargetR->IsValidTarget(GEntityList->Player(), R->Range()))
			{
				R->CastOnTarget(TargetR, PredicChange());
			}
		}
	}
};