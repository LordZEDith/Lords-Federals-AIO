#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include "Common.h"


class Vayne
{
public:

	static void InitializeMenu()
	{
		MainMenu = GPluginSDK->AddMenu("Lords & Federals Vayne");

		ComboSettings = MainMenu->AddMenu("Vayne Coming Soon");
		{
			ComboE = ComboSettings->AddSelection("Modo", 0, std::vector<std::string>({ "Modo 1", "Mode 2" }));
		}

		DrawingSettings = MainMenu->AddMenu("Drawing Settings");
		{
			DrawReady = DrawingSettings->CheckBox("Draw Only Ready Spells", true);
			DrawQ = DrawingSettings->CheckBox("Draw Q", false);
			DrawW = DrawingSettings->CheckBox("Draw W", false);
			DrawE = DrawingSettings->CheckBox("Draw E", true);
			DrawR = DrawingSettings->CheckBox("Draw R", false);
			DrawComboDamage = DrawingSettings->CheckBox("Draw combo damage", true);
		}

		
	}

	static void LoadSpells()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(1.0, 150, 3200, 1625);

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1450, 725);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithNothing);
		E->SetSkillshot(0.25f, FLT_MAX, 1200.f, 710.f);

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.5, 250, 850, 2750);
	}

	static bool CondemnCheck(Vec3 Position, IUnit* target)
	{		
		auto distance = GetDistance(GEntityList->Player(), target);

		Vec3 prepos;
		Vec3 pPos = GEntityList->Player()->GetPosition();

		auto delay = E->GetDelay() + distance / E->Speed();
		GPrediction->GetFutureUnitPosition(target, delay, true, prepos);

		auto pushDistance = 470.f;

		if (GEntityList->Player()->ServerPosition() != Position)
		{
			pushDistance = 410.f;
		}

		auto radius = 250;
		auto start2 = target->ServerPosition();
		auto end2 = prepos.Extend(Position, -pushDistance);

		Vec2 start = start2.To2D();
		Vec2 end = end2.To2D();
		auto dir = (end - start).VectorNormalize();
		auto pDir = dir.Perpendicular();

		auto rightEndPos = end + pDir * radius;
		auto leftEndPos = end - pDir * radius;

		auto rEndPos = Vec3(rightEndPos.x, GEntityList->Player()->GetPosition().y, rightEndPos.y);
		auto lEndPos = Vec3(leftEndPos.x, GEntityList->Player()->GetPosition().y, leftEndPos.y);

		auto step = GetDistanceVectors(start2, rEndPos) / 10;

		for (auto i = 0; i < 10; i++)
		{
			auto pr = start2.Extend(rEndPos, step * i);
			auto pl = start2.Extend(lEndPos, step * i);
			if (GPrediction->IsPointWall(pr) && GPrediction->IsPointWall(pl))
			{
				return true;
			}
		}

		return false;
	}

	static bool CheckWallsVayne(IUnit* player, IUnit* enemy)
	{
		auto distance = GetDistance(player, enemy);

		for (auto i = 1; i < 6; i++)
		{
			Vec3 position;
			Vec3 pPos = GEntityList->Player()->GetPosition();
			auto delay = E->GetDelay() + distance / E->Speed();
			GPrediction->GetFutureUnitPosition(enemy, delay, true, position);

			Vec3 PositionTarget = pPos.Extend(position, distance + (90 * i));

			if (GNavMesh->IsPointWall(PositionTarget))
			{
				return true;
			}
		}
		return false;
	}

	static void Automatic()
	{
		
		for (auto target : GEntityList->GetAllHeros(false, true))
		{
			if (!CheckTarget(target)) return;
			
			if (ComboE->GetInteger() == 1)
			{
				if (CondemnCheck(GEntityList->Player()->ServerPosition(), target) && target->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					E->CastOnUnit(target);
				}
			}
			else
			{
				if (CheckWallsVayne(GEntityList->Player(), target) && target->IsValidTarget(GEntityList->Player(), E->Range()))
				{
					E->CastOnUnit(target);
				}

			}
		}
		
	}

	static void Combo()
	{
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

	static void Drawing()
	{
		if (DrawReady->Enabled())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
		else
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }
			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
			if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
		}
	}

	static void OnGapcloser(GapCloserSpell const& args)
	{

	}

	static void OnAfterAttack(IUnit* source, IUnit* target)
	{
		
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
