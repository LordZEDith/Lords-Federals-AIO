#pragma once
#include "BaseMenu.h"
#include "Common.h";
#include "PluginSDK.h"
#include <string>

class AutoSmite
{	

public:	

	static void MenuSmite()
	{
		if (FoundSmite)
		{
			SmiteSettings = MainMenu->AddMenu("Smite Settings");
			{
				SmiteJungle = SmiteSettings->AddMenu("Smite Jungle");
				{
					BigMobs = SmiteJungle->AddMenu("Big Mobs");
					{
						SmiteBaron = BigMobs->CheckBox("Smite Baron", true);
						SmiteDragon = BigMobs->CheckBox("Smite Dragon", true);
						SmiteRed = BigMobs->CheckBox("Smite Red", true);
						SmiteBlue = BigMobs->CheckBox("Smite Blue", true);
						SmiteHerald = BigMobs->CheckBox("Smite Rift Herald", true);
					}

					SmallMobs = SmiteJungle->AddMenu("Small Mobs");
					{
						SmiteGromp = SmallMobs->CheckBox("Smite Gromp", false);
						SmiteWolves = SmallMobs->CheckBox("Smite Wolves", false);
						SmiteKrug = SmallMobs->CheckBox("Smite Krug", false);
						SmiteRazor = SmallMobs->CheckBox("Smite Chicken", false);
						SmiteCrab = SmallMobs->CheckBox("Smite Crab", false);
					}
				}

				SmiteChampion = SmiteSettings->AddMenu("Smite Champion");
				{
					SmiteCombo = SmiteChampion->CheckBox("Use Smite in Combo", true);
					SmiteComboHP = SmiteChampion->AddInteger("Minimum HP% to Smite Combo", 1, 100, 50);
					KillstealSmite = SmiteChampion->CheckBox("Use Smite to killsteal", true);
					SmiteAmmo = SmiteChampion->CheckBox("Save 1 smite charge", false);
				}

				SmiteDraw = SmiteSettings->AddMenu("Smite Drawings");
				{
					SmiteRange = SmiteDraw->CheckBox("Draw Smite Range", false);
					SmiteText = SmiteDraw->CheckBox("Draw Smite Text", true);
					SmiteDamage = SmiteDraw->CheckBox("Draw Smite Damage", true);
				}

				SmiteActive = SmiteSettings->CheckBox("Use Smite", true);
				SmiteLowHp = SmiteSettings->CheckBox("Use Smite you Low HP", true);
				LowHPpct = SmiteSettings->AddInteger("Low HP %", 1, 100, 10);
				SmiteKeyToggle = SmiteSettings->AddKey("Stop Smite Toggle", 17);
			}
		}
	}

	static void SpellsSmite()
	{
		if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerSmite"))
		{
			Smite = GPluginSDK->CreateSpell(kSummonerSlot1, 570);
			FoundSmite = true;
		}
		else if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerSmite"))
		{
			Smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
			FoundSmite = true;
		}
		else
		{
			FoundSmite = false;
		}

		if (FoundSmite)
		{
			GRender->NotificationEx(Color::Green().Get(), 2, true, true, ("Federal Smite: Smite Found!"));

		}
	}

	//thx Rembrandt to keytoogle
	static void KeyPressSmite()
	{
		if (FoundSmite)
		{
			keystate = GetAsyncKeyState(SmiteKeyToggle->GetInteger());

			if (keystate < 0)
			{
				if (smiteKeyWasDown == false)
				{					
					if (SmiteActive->GetInteger() == 0)
					{
						SmiteActive->UpdateInteger(1);
					}
					else
					{
						SmiteActive->UpdateInteger(0);
					}

					smiteKeyWasDown = true;
				}
			}
			else
			{
				smiteKeyWasDown = false;
			}
		}
	}	

	static void AutomaticSmite()
	{
		//GGame->PrintChat(std::to_string(GEntityList->Player()->GetSpellBook()->GetAmmo(kSummonerSlot1)).data());		

		if (FoundSmite && Smite->IsReady() && SmiteActive->Enabled())
		{
			if (KillstealSmite->Enabled())
			{
				for (auto hero : GEntityList->GetAllHeros(false, true))
				{
					auto damage = GDamage->GetSummonerSpellDamage(GEntityList->Player(), hero, kSummonerSpellSmite);

					if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerSmitePlayerGanker") ||
						strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerSmitePlayerGanker"))
					{
						if (GetDistance(GEntityList->Player(), hero) <= 570 && 20 + 8 * GEntityList->Player()->GetLevel() > hero->GetHealth())
						{
							if (!FoundNeutralEpic(1500))
							{
								if (SmiteAmmo->Enabled() && (GEntityList->Player()->GetSpellBook()->GetAmmo(kSummonerSlot1) == 1 || GEntityList->Player()->GetSpellBook()->GetAmmo(kSummonerSlot2) == 1))
								{
									return;
								}
								
								Smite->CastOnUnit(hero);
							}
						}
					}
				}
			}

			// Use Smite Red in Combo
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && SmiteCombo->Enabled())
			{
				for (auto hero : GEntityList->GetAllHeros(false, true))
				{
					if (!hero->IsInvulnerable() && !hero->IsDead())
					{
						if (strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1), "SummonerSmiteDuel") ||
							strstr(GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2), "SummonerSmiteDuel"))
						{
							if (GetDistance(GEntityList->Player(), hero) <= 570 && SmiteComboHP->GetInteger() >= hero->HealthPercent())
							{
								if (!FoundNeutralEpic(1500))
								{
									if (SmiteAmmo->Enabled() && (GEntityList->Player()->GetSpellBook()->GetAmmo(kSummonerSlot1) == 1 || GEntityList->Player()->GetSpellBook()->GetAmmo(kSummonerSlot2) == 1))
									{
										return;
									}

									Smite->CastOnUnit(hero);
								}
							}
						}
					}
				}
			}

			for (auto minion : GEntityList->GetAllMinions(false, false, true))
			{
				if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, 570))
				{
					auto damage = GDamage->GetSummonerSpellDamage(GEntityList->Player(), minion, kSummonerSpellSmite);
					auto damageCombo = GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotE);

					if (SmiteLowHp->Enabled() && GEntityList->Player()->HealthPercent() < LowHPpct->GetInteger())
					{
						Smite->CastOnUnit(minion);
					}

					if (SmiteDragon->Enabled() && strstr(minion->GetObjectName(), "Dragon") ||
						SmiteBaron->Enabled() && strstr(minion->GetObjectName(), "Baron") ||
						SmiteRed->Enabled() && strstr(minion->GetObjectName(), "Red") ||
						SmiteBlue->Enabled() && strstr(minion->GetObjectName(), "Blue") ||
						SmiteHerald->Enabled() && strstr(minion->GetObjectName(), "RiftHerald") ||
						SmiteGromp->Enabled() && strstr(minion->GetObjectName(), "Gromp") ||
						SmiteCrab->Enabled() && strstr(minion->GetObjectName(), "Crab") ||
						SmiteRazor->Enabled() && strstr(minion->GetObjectName(), "Razorbeak3") ||
						SmiteKrug->Enabled() && strstr(minion->GetObjectName(), "SRU_Krug") ||
						SmiteWolves->Enabled() && strstr(minion->GetObjectName(), "SRU_Murkwolf2"))
					{
						std::string NameChampion = GEntityList->Player()->ChampionName();
						
						
						if (NameChampion == "Olaf")
						{

							if (E->IsReady() && GEntityList->Player()->IsValidTarget(minion, E->Range()) && damage + damageCombo >= minion->GetHealth())
							{
								E->CastOnUnit(minion);
								Smite->CastOnUnit(minion);
							}
							else if (damage >= minion->GetHealth())
							{
								Smite->CastOnUnit(minion);
							}
						}
						else if (NameChampion == "Ivern")
						{
							for (auto Obj : GEntityList->GetAllUnits())
							{
								if (GetDistance(GEntityList->Player(), Obj) <= 600 && 
									(strstr(Obj->GetObjectName(), "Ivern_Base_P_ring_timer.troy") || strstr(Obj->GetObjectName(), "Ivern_Base_P_ring_timer_scuttler.troy")))
								{
									Smite->CastOnUnit(minion);
								}
							}

							if (damage >= minion->GetHealth())
							{
								Smite->CastOnUnit(minion);
							}
						}
						else
						{
							if (damage >= minion->GetHealth())
							{
								Smite->CastOnUnit(minion);
							}
						}
					}
				}
			}
		}
	}

	static void DrawingsSmite()
	{
		if (FoundSmite)
		{
			if (Smite->IsReady() && SmiteRange->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(66, 173, 255, 255), 570); }

			Vec2 textPos = Vec2();
			if (GEntityList->Player()->GetHPBarPosition(textPos))
			{
				auto altura = 240;
				auto comprimento = 10;
				if (FoundSmite && SmiteActive->Enabled() && Smite->IsReady() && SmiteText->Enabled())
				{
					static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
					message->SetColor(Vec4(0, 255, 0, 255));
					message->SetOutline(true);
					message->Render(textPos.x + 10 + comprimento, textPos.y + altura, "SMITE ACTIVE!");
				}
				else if (SmiteActive->Enabled() && SmiteText->Enabled())
				{
					static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
					message->SetColor(Vec4(255, 255, 0, 255));
					message->SetOutline(true);
					message->Render(textPos.x + comprimento, textPos.y + altura, "SMITE COOLDOWN!");
				}

				else if (!SmiteActive->Enabled() && SmiteText->Enabled())
				{
					static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
					message->SetColor(Vec4(255, 0, 0, 255));
					message->SetOutline(true);
					message->Render(textPos.x + comprimento, textPos.y + altura, "SMITE DISABLED!");
				}
			}

			if (SmiteDamage->Enabled() && FoundSmite)
			{
				for (auto minion : GEntityList->GetAllMinions(false, false, true))
				{
					if (minion != nullptr && !minion->IsDead() && GEntityList->Player()->IsValidTarget(minion, Q->Range()))
					{
						if (strstr(minion->GetObjectName(), "Dragon") ||
							strstr(minion->GetObjectName(), "Baron") ||
							strstr(minion->GetObjectName(), "Gromp") ||
							strstr(minion->GetObjectName(), "Crab") ||
							strstr(minion->GetObjectName(), "Razorbeak3") ||
							strstr(minion->GetObjectName(), "Razorbeak9") ||
							strstr(minion->GetObjectName(), "SRU_Krug11") ||
							strstr(minion->GetObjectName(), "SRU_Krug5") ||
							strstr(minion->GetObjectName(), "SRU_Murkwolf2") ||
							strstr(minion->GetObjectName(), "Red") ||
							strstr(minion->GetObjectName(), "Blue") ||
							strstr(minion->GetObjectName(), "RiftHerald"))
						{
							auto damage2 = GDamage->GetSummonerSpellDamage(GEntityList->Player(), minion, kSummonerSpellSmite);

							int calc = 100 - 100 * (minion->GetHealth() - damage2) / minion->GetMaxHealth();
							if (calc > 100) { calc = 100; }

							Vec2 barPos = Vec2();
							if (minion->GetHPBarPosition(barPos))

							{
								std::string str1 = "Progress to Smite ";
								std::string str2 = " Percent!";
								std::string calcx = std::to_string(calc);
								std::string text;

								text = str1 + calcx + str2;

								if (barPos.x <= 0 && barPos.y <= 0) { return; }

								auto altura = 220;
								auto comprimento = 20;

								if (calc == 100)
								{

									static auto message = GRender->CreateFontW("Comic Sans", 15.f, kFontWeightBold);
									message->SetColor(Vec4(0, 255, 0, 255));
									message->SetOutline(true);
									message->Render(barPos.x + comprimento, barPos.y + altura, "Progress in 100pct SMITE NOW!");
								}
								else
								{
									static auto message = GRender->CreateFontW("Comic Sans", 15.f, kFontWeightBold);
									message->SetColor(Vec4(255, 255, 0, 255));
									message->SetOutline(true);
									message->Render(barPos.x + comprimento, barPos.y + altura, text.c_str());

								}

								if (SmiteRed->Enabled() && strstr(minion->GetObjectName(), "Red") ||
									SmiteBlue->Enabled() && strstr(minion->GetObjectName(), "Blue") ||
									SmiteHerald->Enabled() && strstr(minion->GetObjectName(), "RiftHerald") /*
																											SmiteDragon->Enabled() && strstr(minion->GetObjectName(), "Dragon") ||
																											SmiteBaron->Enabled() && strstr(minion->GetObjectName(), "Baron") ||																		||
																											SmiteGromp->Enabled() && strstr(minion->GetObjectName(), "Gromp") ||
																											SmiteCrab->Enabled() && strstr(minion->GetObjectName(), "Crab") ||
																											SmiteRazor->Enabled() && strstr(minion->GetObjectName(), "Razorbeak3") ||
																											SmiteKrug->Enabled() && strstr(minion->GetObjectName(), "SRU_Krug") ||
																											SmiteWolves->Enabled() && strstr(minion->GetObjectName(), "SRU_Murkwolf2") */)
								{

									if (!Smite->IsReady()){ return; }

									float percentHealthAfterDamage = (max(0, minion->GetHealth() - GDamage->GetSummonerSpellDamage(GEntityList->Player(), minion, kSummonerSpellSmite))) / minion->GetMaxHealth();

									int xOffset = 10;
									int yOffset = 20;
									int Width = 140;
									int Height = 9;
									Vec4 Color = Vec4(105, 198, 5, 255);
									Vec4 FillColor = Vec4(255, 20, 147, 255);

									float yPos = barPos.y + yOffset;
									float xPosDamage = barPos.x + xOffset + Width * percentHealthAfterDamage;
									float xPosCurrentHp = barPos.x + xOffset + Width * minion->GetHealth() / minion->GetMaxHealth();
									float pos1 = barPos.x + 10 + (145 * percentHealthAfterDamage);

									float differenceInHP = xPosCurrentHp - xPosDamage;

									for (int i = 0; i < differenceInHP; i++)
									{
										GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), FillColor);

										if (minion->HealthPercent() < 40)
										{
											GRender->DrawLine(Vec2(pos1 + i + 1, yPos), Vec2(pos1 + i + 1, yPos + Height), FillColor);
											GRender->DrawLine(Vec2(pos1 + i + 2, yPos), Vec2(pos1 + i + 2, yPos + Height), FillColor);
										}
									}

									if (minion->HealthPercent() > 60)
									{
										//GRender->DrawLine(Vec2(xPosDamage + 1, yPos), Vec2(xPosDamage + 1, yPos + Height), FillColor);
										GRender->DrawLine(Vec2(xPosDamage + 2, yPos), Vec2(xPosDamage + 2, yPos + Height), FillColor);
										GRender->DrawLine(Vec2(xPosDamage + 3, yPos), Vec2(xPosDamage + 3, yPos + Height), FillColor);
										GRender->DrawLine(Vec2(xPosDamage + 1, yPos), Vec2(xPosDamage + 1, yPos + Height), Vec4(0, 0, 0, 255));
									}

									else if (minion->HealthPercent() < 43)
									{
										//GRender->DrawLine(Vec2(xPosDamage - 3, yPos), Vec2(xPosDamage - 3, yPos + Height), Color);
										GRender->DrawLine(Vec2(xPosDamage - 2, yPos), Vec2(xPosDamage - 2, yPos + Height), Color);
									}

									GRender->DrawLine(Vec2(xPosDamage, yPos), Vec2(xPosDamage, yPos + Height), Color);
									GRender->DrawLine(Vec2(xPosDamage - 1, yPos), Vec2(xPosDamage - 1, yPos + Height), Color);
								}
							}
						}
					}
				}

			}
		}
	}

};
