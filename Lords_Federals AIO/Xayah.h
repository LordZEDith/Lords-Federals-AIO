#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


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
			ComboE = ComboSettings->AddSelection("Use E Mode", 1, std::vector<std::string>({ "Disable", "Automatic", "Combo Key" }));
			PassiveStacks = ComboSettings->AddInteger("Min E Feather Stacks", 1, 10, 3);
			ComboR = ComboSettings->CheckBox("Use R", true);
		}
		
		fedMiscSettings = MainMenu->AddMenu("Miscs Settings");
		{
			Predic = fedMiscSettings->AddSelection("Q Prediction", 2, std::vector<std::string>({ "Medium", "High", "Very High" }));			
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
				auto cRect = Geometry::Rectangle(Feather->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), 95);

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
						auto cRectx = Geometry::Rectangle(Feather->GetPosition().To2D(), GEntityList->Player()->GetPosition().To2D(), 95);

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
		AutoE();
	}

	static void Combo()
	{
		auto Target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (!CheckTarget(Target)) return;

		if (ComboW->GetInteger() == 2 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
		{
			if (GetFeatherBuffCount() == 0)
			{
				W->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}
		}

		if (ComboQ->GetInteger() == 2 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
		{
			if (GetFeatherBuffCount() == 0)
			{
				Q->CastOnTarget(Target, PredicChange());
				LastSpellTick = GGame->TickCount();
			}
		}

		if (ComboE->GetInteger() == 2 && E->IsReady() && CountPossiblesFeathers(Target) >= PassiveStacks->GetInteger())
		{
			if (GetFeatherBuffCount() == 0 || CountPossiblesFeathers(Target) >= 3)
			{
				E->CastOnPlayer();
				LastSpellTick = GGame->TickCount();
			}
		}		
	}

	static void AutoE()
	{		
		if (ComboE->GetInteger() == 1 && E->IsReady())
		{
			for (auto Target : GEntityList->GetAllHeros(false, true))
			{
				if (CheckTarget(Target))
				{
					if (CountPossiblesFeathers(Target) >= PassiveStacks->GetInteger() && CountPossiblesFeathers(Target) >= 3)
					{
						E->CastOnPlayer();
					}
				}
			}
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

	static void OnAfterAttack(IUnit* Source, IUnit* Target)
	{
		if (!CheckTarget(Target)) return;

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (ComboW->GetInteger() == 1 && W->IsReady() && Target->IsValidTarget(GEntityList->Player(), GEntityList->Player()->GetRealAutoAttackRange(Target)) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (GetFeatherBuffCount() == 0)
				{
					W->CastOnPlayer();
					LastSpellTick = GGame->TickCount();
				}
			}

			if (ComboQ->GetInteger() == 1 && Q->IsReady() && Target->IsValidTarget(GEntityList->Player(), Q->Range()) && GGame->TickCount() - LastSpellTick > 300)
			{
				if (GetFeatherBuffCount() == 0)
				{
					Q->CastOnTarget(Target, PredicChange());
					LastSpellTick = GGame->TickCount();
				}
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