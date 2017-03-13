#pragma once
#include "BaseMenu.h"
#include "PluginSDK.h"
//ALL CREDS GO TO RYTAK FOR THIS SPELL LIB
 

class SpellLib
{
public:

	void Aatrox()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.6, 250, 2000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AatroxQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "AatroxW";

		W2 = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W2->SetSkillshot(0, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "aatroxw2";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, kCollidesWithYasuoWall);
		E->SetSkillshot(0.25, 35, 1250, 1075);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "AatroxE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AatroxR";
	}

	void Ahri()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 100, 2500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AhriOrbOfDeception";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, true, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0, 0, 900, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "AhriFoxFire";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 60, 1550, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "AhriSeduce";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		R->SetSkillshot(0, 600, 2200, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AhriTumble";
	}

	void Akali()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 600, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AkaliMota";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.5, 400, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "AkaliSmokeBomb";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, kCollidesWithNothing);
		E->SetSkillshot(0.25, 0, 1250, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "AkaliShadowSwipe";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 0, 2200, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AkaliShadowDance";
	}

	void Alistar()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 365, 20, 365);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Pulverize";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0, 650, 0, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "HeadButt";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0, 575, 0, 575);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TriumphantRoar";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 0, 828, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "FerociousHowl";
	}

	void Amumu()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithHeroes, kCollidesWithMinions, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 90, 2000, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BandageToss";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 300, 1000, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "AuraofDespair";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 350, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Tantrum";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 550, 1000, 0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "CurseoftheSadMummy";
	}

	void Anivia()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 110, 850, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "FlashFrost";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 100, 1600, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Crystalize";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 650, 1200, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Frostbite";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 400, 1600, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GlacialStorm";
	}

	void Annie()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 710, 1400, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Disintegrate";

		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 80, 1000, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Incinerate";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MoltenShield";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 250, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "InfernalGuardian";
	}

	void Ashe()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 0, 2500, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AsheQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0.2, 57.5, 2000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Volley";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 300, 1400, 25000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "AsheSpiritOfTheHawk";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetSkillshot(0.25, 130, 1600, FLT_MAX);
	}

	void AurelionSol()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithYasuoWall));
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
	}

	void Azir()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 2550, 875);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AzirQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 350, 2500, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "AzirW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 2000, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "AzirE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 60, 1000, 250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AzirR";
	}

	void Bard()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 60, 1600, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BardQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 100, 0, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BardW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithWalls));
		E->SetSkillshot(0.25, 2600, 0, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BardE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, true, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 350, 2100, 3400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "BardR";
	}

	void Blitzcrank()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 70, 1800, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RocketGrab";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 0, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Overdrive";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 0, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "PowerFist";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 600, 1000, 0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "StaticField";
	}

	void Brand()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 1600, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BrandQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.85, 240, 3200, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BrandW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BrandE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, true, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 600, 1000, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "BrandR";
	}

	void Braum()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 1700, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BraumQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BraumW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BraumE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.5, 115, 1400, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "BraumRWrapper";
	}

	void Caitlyn()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.625, 90, 2200, 1300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "CaitlynPiltoverPeacemaker";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.1, 100, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "CaitlynYordleTrap";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 90, 1600, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "CaitlynEntrapment";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetOverrideDelay(3.0);
		R->SetOverrideSpeed(1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "CaitlynAceintheHole";
	}

	void Camille()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, false, (kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithWalls));
		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
	}

	void Cassiopeia()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.75, 100, 1000, 850);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "CassiopeiaQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.75, 160, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "CassiopeiaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.125, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "CassiopeiaE";

		R = GPluginSDK->CreateSpell2(kSlotR, kConeCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 80, 3200, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "CassiepeiaR";
	}

	void ChoGath()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(1.2, 250, 3200, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Rupture";

		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 210, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "FeralScream";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VorpalSpikes";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 175);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Feast";
	}

	void Corki()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, true, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.3, 250, 1000, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "PhosphorusBomb";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.3, 200, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "CarpetBomb";
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "CarpetBombMega";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(0.3, 40, 1500, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GGun";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		R->SetSkillshot(0.175, 40, 2000, 1300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MissileBarrage";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MissileBarrage2")
		{
			R->SetOverrideRange(1500);
		}
	}

	void Darius()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.75, 425, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "DariusCleave";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.75, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "DariusNoxianTacticsONH";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 80, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "DariusAxeGrabCone";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 0, 1000, 460);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "DariusExecute";
	}

	void Diana()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 195, 1400, 895);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "DianaArc";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0, 315, 1400, 200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "DianaOrbs";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0, 450, 0, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "DianaVortex";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 250, 0, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "DianaTeleport";
	}

	void DrMundo()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 2000, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "InfectedCleaverMissileCast";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.3, 0, 20, 165);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BurningAgony";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.3, 0, 1000, 25);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Masochism";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "Sadism";
	}

	void Draven()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "DravenSpinning";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "DravenFury";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 130, 1400, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "DravenDoubleShot";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.4, 160, 2000, 20000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "DravenRCast";
	}

	void Ekko()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 1650, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "EkkoQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, true, (kCollidesWithNothing));
		W->SetSkillshot(3.75, 375, 1650, 1600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "EkkoW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 100, 2500, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EkkoE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 375, 1650, 1600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "EkkoR";
	}

	void Elise()
	{
		//Human Form
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "EliseHumanQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, (kCollidesWithNothing));
		W->SetSkillshot(3.0, 235, 1000, 975);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "EliseHumanW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 55, 1600, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EliseHumanE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 0, 1000, 125);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "EliseR";

		//Spider Form
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q2->SetSkillshot(0.25, 0, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "EliseSpiderQCast";

		W2 = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
		W2->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "EliseSpiderW";

		E2 = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E2->SetSkillshot(1.0, 400, 1000, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EliseSpiderE";
	}

	void Evelynn()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 450, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "EvelynnQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "EvelynnW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 225);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EvelynnE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 350, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "EvelynnR";
	}

	void Ezreal()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 60, 2000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "EzrealMysticShot";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 80, 1600, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "EzrealEssenceFlux";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(0.25, 275, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EzrealArcaneShift";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(1.5, 160, 2000, 5000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "EzrealTrueshotBarrage";
	}

	void Fiddlesticks()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 575);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Terrify";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 575);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Drain";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "FiddlesticksDarkWind";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 600, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "Crowstorm";
	}

	void Fiora()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 300, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "FioraQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.5, 70, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "FioraW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "FioraE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "FioraR";
	}

	void Fizz()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "FizzPiercingStrike";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "FizzSeastonePassive";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 330, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "FizzJump";

		E2 = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E2->SetSkillshot(0.25, 270, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "FizzJumpTwo";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, false, (kCollidesWithHeroes, kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 120, 1350, 1300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "FizzMarinerDoom";
	}

	void Galio()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 200, 1300, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GalioResoluteSmite";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GalioBulwark";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 120, 1200, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GalioRighteousGust";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 550, 1000, 0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GalioIdolOfDurand";
	}

	void Gangplank()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GangplankQWrapper";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GangplankW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(1.0, 400, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GangplankE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 600, 1000, 20000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GangplankR";
	}

	void Garen()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GarenQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GarenW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 300, 1000, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GarenE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GarenR";
	}

	void Gnar()
	{
		//Small Gnar
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 2500, 1125);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GnarQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GnarW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0, 150, 900, 470);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GnarE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 500, 1000, 0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GnarR";

		//Mega Gnar
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q2->SetSkillshot(0.5, 90, 2100, 1150);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GnarBigQ";

		W2 = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
		W2->SetSkillshot(0.6, 80, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GnarBigW";

		E2 = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E2->SetSkillshot(0.25, 200, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GnarBigE";
	}

	void Gragas()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 275, 1300, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GragasQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GragasW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0, 200, 1200, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GragasE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, true, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 375, 1800, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GragasR";
	}

	void Graves()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 3000, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GravesQLineSpell";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "GravesClusterShot")
		{
			Q->SetSkillshot(0.65, 100, 1000, 950);
		}

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 250, 1000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "GravesSmokeGrenade";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 100, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "GravesMove";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 100, 2100, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "GravesChargeShot";
	}

	void Hecarim()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 350, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "HecarimRapidSlash";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 525);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "HecarimW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "HecarimRamp";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 400, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "HecarimUlt";
	}

	void Heimerdinger()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 450, 1000, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "HeimerdingerQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 70, 1800, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "HeimerdingerW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 100, 1200, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "HeimerdingerE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "HeimerdingerR";
	}

	void Illaoi()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.75, 100, 3200, 850);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "IllaoiQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "IllaoiW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 50, 1900, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "IllaoiE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 450, 3200, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "IllaoiR";
	}

	void Irelia()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.15, 350, 2350, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "IreliaGatotsu";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "IreliaHitenStyle";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "IreliaEquilibriumStrike";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0, 120, 1600, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "IreliaTranscendentBlades";
	}

	void Ivern()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithHeroes, kCollidesWithHeroes, kCollidesWithMinions));
		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, (kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
	}

	void Janna()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0, 120, 900, 1700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "HowlingGale";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 2350, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SowTheWind";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "EyeOfTheStorm";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 725, 3200, 875);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ReapTheWhirlwind";
	}

	void JarvanIV()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 80, 2000, 845);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JarvanIVDragonStrike";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JarvanIVDragonStrike2")
		{
			Q->SetSkillshot(0.25, 120, 1800, 880);
		}

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 300, 3200, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JarvanIVGoldenAegis";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.5, 75, 3200, 860);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "JarvanIVDemacianStandard";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 325, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "JarvanIVCataclysm";
	}

	void Jax()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 2000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JaxLeapStrike";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JaxEmpowerTwo";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 187, 3200, 187);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "JaxCounterStrike";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, FLT_MAX, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "JaxRelentlessAssault";
	}

	void Jayce()
	{
		//Hammer Form
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, kCollidesWithNothing);
		Q->SetSkillshot(0.25, 550, 2800, 550);

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, kCollidesWithNothing);
		W->SetSkillshot(0.25, 285, 3200, 285);

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(0.25, 240, 3200, 240);

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);

		//Ranged Form
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q2->SetSkillshot(0.25, 70, 1450, 1470);

		W2 = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithYasuoWall);
		W2->SetSkillshot(0.25, 500, 3200, 500);

		E2 = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, kCollidesWithNothing);
		E2->SetSkillshot(0.25, 100, 1000, 650);

		R2 = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
	}

	void Jhin()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JhinQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		W->SetSkillshot(0.75, 40, 5000, 2550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JhinW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(1.0, 260, 1000, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "JhinE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetSkillshot(0.25, 80, 5000, 3500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "JhinRShot";
	}

	void Jinx()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 150);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JinxQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0.6, 60, 3300, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JinxW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		E->SetSkillshot(1.5, 50, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "JinxE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetSkillshot(0.6, 140, 1700, 20000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "JinxR";
	}

	void Kalista()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 40, 1700, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KalistaMysticShot";

		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 160, 1000, 5000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KalistaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.15, 0, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KalistaExpungeWrapper";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.45, 0, 1000, 1400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KalistaRx";
	}

	void Karma()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 60, 1700, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KarmaQ";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KarmaQMantra")
		{
			Q->SetSkillshot(0.25, 80, 1700, 950);
		}

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(2.0, 0, 1000, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KarmaSpiritBind";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KarmaWMantra")
		{
			W->SetSkillshot(2.0, 0, 1000, 675);
		}

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.4, 0, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KarmaSolKimShield";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KarmaSolKimShieldLocket")
		{
			E->SetSkillshot(0.4, 0, 1000, 800);
		}

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KarmaMantra";
	}

	void Karthus()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.625, 160, 1000, 875);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KarthusLayWasteA2";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 100, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KarthusWallOfPain";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 425, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KarthusDefile";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(3.0, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KarthusFallenOne";
	}

	void Kassadin()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "NullLance";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0, 0, 1000, 200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "NetherBlade";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.4, 350, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ForcePulse";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 270, 1000, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RiftWalk";
	}

	void Katarina()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 50, 1400, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KatarinaQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 375, 3200, 375);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KatarinaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 50, 1400, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KatarinaE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, true, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 550, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KatarinaR";
	}

	void Kayle()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 0, 1750, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JudicatorReckoning";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JudicatorDivineBlessing";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 525);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "JudicatorRighteousFury";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "JudicatorIntervention";
	}

	void Kennen()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.125, 50, 1700, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KennenShurikenHurlMissile1";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 750, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KennenBringTheLight";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KennenLightningRush";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 500, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KennenShurikenStorm";
	}

	void KhaZix()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 50, 1400, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KhazixQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		W->SetSkillshot(0.25, 73, 1700, 1025);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KhazixW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 300, 1500, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KhazixE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KhazixR";
	}

	void Kindred()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 500, 1400, 340);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KindredQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 800, 1400, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KindredW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KindredEWrapper";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KindredR";
	}

	void Kled()
	{
		//Mounted
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithHeroes, kCollidesWithMinions, kCollidesWithYasuoWall));
		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));

		//Dismounted
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kConeCast, true, false, (kCollidesWithYasuoWall));
	}

	void KogMaw()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 70, 1650, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "KogMawQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 50, 1400, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "KogMawBioArcaneBarrage";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 120, 1400, 1360);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "KogMawVoidOoze";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, false, (kCollidesWithNothing));
		R->SetSkillshot(1.2, 225, 1000, 1800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "KogMawLivingArtillery";
	}

	void LeBlanc()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LeblancChaosOrb";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0, 220, 1450, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LeblancSlide";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 70, 1750, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "LeblancSoulShackle";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));

		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LeblancChaosOrbM")
		{
			R->SetSkillshot(0.25, 0, 1000, 700);
		}
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LeblancSlideM")
		{
			R->SetSkillshot(0, 220, 1450, 600);
		}
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LeblancSoulShackleM")
		{
			R->SetSkillshot(0.25, 70, 1750, 950);
		}
	}

	void LeeSin()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 65, 1800, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BlindMonkQOne";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BlindMonkQTwo")
		{
			Q->SetSkillshot(0.25, 65, 1400, 1300);
		}

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BlindMonkWOne";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BlindMonkWTwo")
		{
			W->SetSkillshot(0.25, 50, 1400, FLT_MAX);
		}

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 125, 1400, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BlindMonkEOne";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BlindMonkETwo")
		{
			E->SetSkillshot(0.25, 0, 1000, 500);
		}

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithHeroes));
		R->SetSkillshot(0.25, 0, 1000, 375);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "BlindMonkRKick";
	}

	void Leona()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LeonaShieldOfDaybreak";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LeonaSolarBarrier";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 70, 2000, 905);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "LeonaZenithBlade";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 300, 1000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LeonaSolarFlare";
	}

	void Lissandra()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 75, 2200, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LissandraQ";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LissandraQShards")
		{
			Q->SetSkillshot(0.25, 90, 2200, 700);
		}

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 225, 1000, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LissandraW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 125, 850, 1025);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "LissandraE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LissandraR";
	}

	void Lucian()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, true, kCollidesWithNothing);
		Q->SetSkillshot(0.4, 50, 1600, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LucianQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, kCollidesWithYasuoWall);
		W->SetSkillshot(0.25, 80, 1600, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LucianW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, kCollidesWithNothing);
		E->SetSkillshot(0.25, 425, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LucianE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithYasuoWall);
		R->SetSkillshot(0.5, 110, 2800, 1400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LucianR";
	}

	void Lulu()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 1450, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LuluQ";
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LuluQPix";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LuluW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "LuluE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 150, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LuluR";
	}

	void Lux()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 70, 1200, 1300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "LuxLightBinding";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 150, 1000, 1075);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "LuxPrismaticWave";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 275, 1300, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "LuxLightStrikeLugel";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 190, 1000, 3500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "LuxMaliceCannon";
	}

	void Malphite()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SeismicShard";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 225);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Obduracy";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 200, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Landslide";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 270, 1500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "UFSlash";
	}

	void Malzahar()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(1.0, 85, 3200, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "MalzaharQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 250, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MalzaharW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MalzaharE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 3200, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MalzaharR";
	}

	void Maokai()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 100, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "MaokaiTrunkLine";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.45, 0, 1000, 525);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MaokaiUnstableGrowth";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 250, 1000, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MaokaiSapling2";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MaokaiDrain3";
	}

	void MasterYi()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "AlphaStrike";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Meditate";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "WujuStyle";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "Highlander";
	}

	void MissFortune()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 250, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "MissFortuneRicochetShot";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MissFortuneViciousStrikes";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.35, 200, 3200, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MissFortuneScattershot";

		R = GPluginSDK->CreateSpell2(kSlotR, kConeCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 0, 1000, 1400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MissFortuneBulletTime";
	}

	void Mordekaiser()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "MordekaiserMaceOfSpades";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 250, 1100, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MordekaiserCreepingDeathCast";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.35, 160, 3200, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MordekaiserSyphonOfDestruction";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 3200, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MordekaiserChildrenOfTheGrave";
	}

	void Morgana()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 80, 1200, 1075);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "DarkBindingMissile";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 275, FLT_MAX, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TormentedSoil";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BlackShield";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 1050, FLT_MAX, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SoulShackles";
	}

	void Nami()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(1.0, 150, 3200, 1625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "NamiQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1450, 725);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "NamiW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "NamiE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.5, 250, 850, 2750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "NamiR";
	}

	void Nasus()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 3200, 150);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "NasusQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 3200, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "NasusW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 400, 3200, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "NasusE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "NasusR";
	}

	void Nautilus()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 90, 2000, 1250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "NautilusAnchorDrag";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "NautilusPiercingGaze";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 450, 3200, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "NautilusSplashZone";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 60, 1000, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "NautilusGrandLine";
	}

	void Nidalee()
	{
		//Human Form
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 40, 1300, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "JavelinToss";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.0, 100, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Bushwhack";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "PrimalSurge";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AspectOfTheCougar";

		//Cougar Form
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q2->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Takedown";

		W2 = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, (kCollidesWithNothing));
		W2->SetSkillshot(0.25, 75, 1000, 375);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Pounce";

		E2 = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E2->SetSkillshot(0.25, 0, 1000, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Swipe";
	}

	void Nocturne()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 60, 1400, 1125);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "NocturneDuskbringer";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "NocturneShroudofDarkness";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 300, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "NocturneUnspeakableHorror";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 2500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "NocturneParanoia";
	}

	void Nunu()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 125);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Consume";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "BloodBoil";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "IceBlast";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 650, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "AbsoluteZero";
	}

	void Olaf()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 105, 1600, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "OlafAxeThrowCast";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "OlafFrenziedStrikes";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "OlafRecklessStrike";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "OlafRagnarok";
	}

	void Orianna()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0, 80, 1200, 825);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "OriannasQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 255, 3200, 255);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "OrianaDissonanceCommand-";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0, 85, 1850, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "OriannasE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.7, 410, 1000, 0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "OrianaDetonateCommand-";
	}

	void Pantheon()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 50, 1400, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "PantheonQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 50, 1400, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "PantheonW";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, true, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 600, 1400, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "PantheonE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(2.0, 700, 1000, 5500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "PantheonRJump";
	}

	void Poppy()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.5, 100, 1000, 430);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "PoppyQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 400, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "PoppyW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithWalls));
		E->SetSkillshot(0.25, 0, 1000, 375);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "PoppyE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.3, 100, 1600, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "PoppyRSpell";
	}

	void Quinn()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.3, 60, 1550, 1050);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "QuinnQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 2100, 1000, 2100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "QuinnW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "QuinnE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "QuinnR";
	}

	void Rammus()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithMinions, kCollidesWithHeroes));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "PowerBall";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "DefensiveBallCurl";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "PuncturingTaunt";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 300, 1000, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "Tremors2";
	}

	void RekSai()
	{
		//Unburrowed
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RekSaiQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RekSaiW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RekSaiE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RekSaiR";

		//Burrowed
		Q2 = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q2->SetSkillshot(0.5, 60, 1950, 1625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RekSaiQBurrowed";

		W2 = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W2->SetSkillshot(0.25, 200, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RekSaiWBurrowed";

		E2 = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E2->SetSkillshot(0.25, 0, 1000, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RekSaiEBurrowed";
	}

	void Renekton()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 225, 1000, 225);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RenektonCleave";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RenektonPreExecute";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 85, 1000, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RenektonSliceAndDice";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RenektonReignOfTheTyrant";
	}

	void Rengar()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RengarQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 500, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RengarW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 70, 1500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RengarE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RengarR";
	}

	void Riven()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 150, 1000, 260);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RivenTriCleave";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 125, 1000, 125);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RivenMartyr";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 80, 1000, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RivenFeint";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 125, 1600, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RivenFengShuiEngine";

		R2 = GPluginSDK->CreateSpell2(kSlotR, kConeCast, true, false, kCollidesWithYasuoWall);
		R2->SetSkillshot(0.25, 125, 1600, 1100);
		//std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "";
	}

	void Rumble()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kConeCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 600, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RumbleFlameThrower";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RumbleShield";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.25, 60, 2000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RumbleGrenade";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithNothing));
		R->SetSkillshot(0.4, 200, 1600, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "RumbleCarpetBomb";
	}

	void Ryze()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 50, 1700, 990);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "RyzeQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithNothing);
		W->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "RyzeW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithMinions, kCollidesWithHeroes, kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "RyzeE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, kCollidesWithNothing);
		R->SetOverrideRadius(450);
		R->SetOverrideDelay(2.5);
	}

	void Sejuani()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, true, (kCollidesWithHeroes, kCollidesWithMinions, kCollidesWithYasuoWall));
		Q->SetSkillshot(0, 70, 1600, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SejuaniArcticAssault";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SejuaniNorthernWinds";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SejuaniWintersClaw";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetSkillshot(0.25, 110, 1600, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SejuaniGlacialPrisonStart";
	}

	void Shaco()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Deceive";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(2.0, 300, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "JackInTheBox";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TwoShivPoison";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "HallucinateFull";
	}

	void Shen()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 250, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ShenQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 250, 3200, 250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ShenW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0, 60, 1600, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ShenE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ShenR";
	}

	void Shyvana()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ShyvanaDoubleAttack";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 160, 1000, 160);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ShyvanaImmolationAura";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 60, 1700, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ShyvanaFireball";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 150, 1500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ShyvanaTransformCast";
	}

	void Singed()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "PoisonTrail";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 175, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MegaAdhesive";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "Fling";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "InsanityPotion";
	}

	void Sion()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 100, 1000, 300);
		Q->SetCharged(300, 600, 2.0);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SionQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 400, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SionW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 80, 1800, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SionE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.5, 120, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SionR";
	}

	void Sivir()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 90, 1350, 1250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SivirQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SivirW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SivirE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SivirR";
	}

	void Skarner()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 350, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SkarnerVirulentSlash";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SkarnerExoskeleton";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 70, 1500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SkarnerFracture";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SkarnerImpale";
	}

	void Sona()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 800, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SonaQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 950, 1000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SonaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 350, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SonaE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 140, 2400, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SonaR";
	}

	void Soraka()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.5, 300, 1750, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SorakaQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SorakaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.5, 300, 1750, 925);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SorakaE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SorakaR";
	}

	void Swain()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(1.5, 900, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SwainDecrepify";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.875, 125, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "SwainShadowGrasp";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SwainTorment";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 700, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SwainMetamorphism";
	}

	void Syndra()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.6, 150, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "SyndraQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 210, 1450, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "syndrawcast";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0, 100, 2000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "syndrae5";
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "SyndraE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 0, 1000, 675);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "SyndraR";
	}

	void TahmKench()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 70, 2000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TahmKenchQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 250, 3200, 250);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TahmKenchW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TahmKenchE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 250, 3200, 4000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TahmKenchNewR";
	}

	void Taliyah()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 100, 3600, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TaliyahQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.6, 200, FLT_MAX, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TaliyahW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(4.0, 450, FLT_MAX, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TaliyahE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, (kCollidesWithWalls));
		R->SetSkillshot(1.0, 200, 1500, 3000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TaliyahR";
	}

	void Talon()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TalonNoxianDiplomacy";

		W = GPluginSDK->CreateSpell2(kSlotW, kConeCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 80, 2300, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TalonRake";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithWalls));
		E->SetSkillshot(0.25, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TalonCutthroat";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TalonShadowAssault";
	}

	void Taric()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 325, 3200, 325);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TaricQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, FLT_MAX, 3200, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TaricW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(1.0, 100, 3200, 750);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TaricE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(2.5, 400, 3200, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TaricR";
	}

	void Teemo()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 50, 1450, 580);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "BlindingDart";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MoveQuick";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ToxicShot";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, false, (kCollidesWithNothing));
		R->SetSkillshot(1.0, 200, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TeemoRCast";
	}

	void Thresh()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.5, 70, 1900, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ThreshQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.3, 80, 1000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ThreshW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.125, 110, 2000, 1075);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ThreshE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.75, 400, 1000, 450);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ThreshRPenta";
	}

	void Tristana()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TristanaQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.5, 270, 1500, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TristanaW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TristanaE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TristanaR";
	}

	void Trundle()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0, FLT_MAX, 3600, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TrundleTrollSmash";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 1000, FLT_MAX, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "Trundledesecrate";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.6, 225, FLT_MAX, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TrundleCircle";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.35, FLT_MAX, 1500, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TrundlePain";
	}

	void Tryndamere()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "Bloodlust";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MockingShout";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0, 90, 1300, 660);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "slashCast";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "UndyingRage";
	}

	void TwistedFate()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, kCollidesWithYasuoWall);
		Q->SetSkillshot(0.25, 40, 1000, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "WildCards";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, kCollidesWithYasuoWall);
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "PickACard";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "CardmasterStack";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, kCollidesWithNothing);
		R->SetSkillshot(2.0, 0, 1000, 5500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "Destiny";
	}

	void Twitch()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(4.5, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "TwitchHideInShadows";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 275, 1400, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "TwitchVenomCask";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "TwitchExpunge";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, false, (kCollidesWithYasuoWall));
		R->SetSkillshot(0.25, 0, 1000, 850);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TwitchFullAutomatic";
		if (std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "TwitchSprayandPrayAttack")
		{
			R->SetSkillshot(0.25, 60, 4000, 1100);
		}
	}

	void Udyr()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "UdyrTigerStance";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "UdyrTurtleStance";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "UdyrBearStance";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "UdyrPhoenixStance";
	}

	void Urgot()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.125, 60, 1600, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "UrgotHeatseekingLineMissile";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "UrgotTerrorCapacitorActive2";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 210, 1500, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "UrgotPlasmaGrenade";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "UrgotSwap2";
	}

	void Varus()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 50, 1850, 925);
		Q->SetCharged(925, 1600, 1.5);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VarusQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VarusW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 200, 1000, 925);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VarusE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, true, (kCollidesWithYasuoWall, kCollidesWithHeroes));
		R->SetSkillshot(0.25, 50, 1850, 1075);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VarusR";
	}

	void Vayne()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.15, 85, 1000, 300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VayneTumble";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VayneSilveredBolts";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.4, 100, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VayneCondemn";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VayneInquisition";
	}

	void Veigar()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 70, 2000, 950);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VeigarBalefulStrike";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(1.35, 225, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VeigarDarkMatter";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.5, 80, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VeigarEventHorizon";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1400, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VeigarPrimordialBurst";
	}

	void VelKoz()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 50, 1300, 1100);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VelkozQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 85, 1700, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VelkozW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 225, 1000, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VelkozE";

		R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 50, 1000, 1550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VelkozR";
	}

	void Vi()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 90, 1500, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ViQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ViW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 650, 1000, 175);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ViE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ViR";
	}

	void Viktor()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ViktorPowerTransfer";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(4.0, 300, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ViktorGravitonField";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 80, 780, 1500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ViktorDeathRay";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, true, true, (kCollidesWithNothing));
		R->SetSkillshot(250, 300, 1000, 525);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ViktorChaosStorm";
	}

	void Vladimir()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, true, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VladimirQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 150, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VladimirW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 600, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VladimirE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.375, 175, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VladimirR";
	}

	void Volibear()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "VolibearQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "VolibearW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 425, 1000, 425);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "VolibearE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 500, 1000, 500);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "VolibearR";
	}

	void Warwick()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "HungeringStrike";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "HuntersCall";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "BloodScent";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "InfiniteDuress";
	}

	void Wukong()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "MonkeyKingDoubleAttack";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 3200, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "MonkeyKingDecoy";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 650);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "MonkeyKingNimbus";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 450, 3200, 660);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "MonkeyKingSpinToWin";
	}

	void Xerath()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
		Q->SetSkillshot(0.6, 100, 1000, 1600);
		Q->SetCharged(750, 1550, 1.5);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "XerathArcanopulse2";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.7, 200, 1000, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "XerathArcaneBarrage2";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithMinions, kCollidesWithYasuoWall, kCollidesWithHeroes));
		E->SetSkillshot(0.2, 60, 1400, 1150);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "XerathMageSpear";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "XerathLocusOfPower2";

		R->SetOverrideDelay(0.7);
		R->SetOverrideRadius(120);
		R->SetOverrideSpeed(1000);
	}

	void XinZhao()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "XenZhaoComboTarget";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "XenZhaoBattleCry";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "XenZhaoSweep";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 187, 1000, 187);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "XenZhaoParry";
	}

	void Yasuo()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.4, 20, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "YasuoQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 300, 1000, 400);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "YasuoWMovingWall";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 475);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "YasuoDashWrapper";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "YasuoR";
	}

	void Yorick()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "YorickSpectral";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 100, 1000, 600);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "YorickDecayed";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, true, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "YorickRavenous";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "YorickReviveAlly";
	}

	void Zac()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, (kCollidesWithNothing));
		Q->SetSkillshot(0.5, 120, FLT_MAX, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ZacQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 350, 1000, 350);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ZacW";

		E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 300, 1000, 1200);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ZacE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 300, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ZacR";
	}

	void Zed()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.25, 50, 1700, 925);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ZedQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 210, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ZedW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 290, 1000, 290);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ZedE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 625);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ZedR";
	}

	void Ziggs()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		Q->SetSkillshot(0.25, 140, 1700, 850);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ZiggsQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, (kCollidesWithYasuoWall));
		W->SetSkillshot(0.25, 275, 1750, 1000);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ZiggsW";

		E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, false, (kCollidesWithYasuoWall, kCollidesWithHeroes, kCollidesWithMinions));
		E->SetSkillshot(0.5, 235, 1750, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ZiggsE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0, 500, 1000, 5300);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ZiggsR";
	}

	void Zilean()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, true, (kCollidesWithYasuoWall));
		Q->SetSkillshot(0.7, 140, FLT_MAX, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ZileanQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 0, 1000, FLT_MAX);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ZileanW";

		E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, (kCollidesWithNothing));
		E->SetSkillshot(0.25, 0, 1000, 550);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ZileanE";

		R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, (kCollidesWithNothing));
		R->SetSkillshot(0.25, 0, 1000, 900);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ZileanR";
	}

	void Zyra()
	{
		Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, (kCollidesWithNothing));
		Q->SetSkillshot(0.85, 140, FLT_MAX, 800);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ)) == "ZyraQ";

		W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, (kCollidesWithNothing));
		W->SetSkillshot(0.25, 250, 1000, 850);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotW)) == "ZyraW";

		E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, (kCollidesWithYasuoWall));
		E->SetSkillshot(0.25, 70, 1400, 1150);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotE)) == "ZyraE";

		R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, true, (kCollidesWithYasuoWall));
		R->SetSkillshot(2.0, 500, 1000, 700);
		std::string(GEntityList->Player()->GetSpellBook()->GetName(kSlotR)) == "ZyraR";
	}

};
