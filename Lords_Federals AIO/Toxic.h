#pragma once
#include "BaseMenu.h"
#include "Common.h";
#include "PluginSDK.h"

class Toxic
{
public:

	static void MenuToxic()
	{		
		EmoteSpam = MainMenu->AddMenu("Mastery Emote Spam");
		{
			EmoteMode = EmoteSpam->AddSelection("Emote Mode", 0, std::vector<std::string>({ "Mastery", "Laugh", "Off" }));
			EmoteOnKill = EmoteSpam->CheckBox("After Kill", true);
			EmoteOnAssis = EmoteSpam->CheckBox("After Assist", false);
			EmoteOnDeath = EmoteSpam->CheckBox("After Death", false);
			EmoteNearDead = EmoteSpam->CheckBox("Near Dead Bodies", false);	
			Debug = EmoteSpam->CheckBox("Debug", false);
		}

		/*GameChat = GameEvents->AddMenu("Start & End");
		{			
			GameStart = GameChat->AddMenu("OnGame Start");
			{
				Greeting = GameStart->AddSelection("Greetings", 1, std::vector<std::string>({ "gl & hf", "good luck & have fun" }));
				SayGreeting = GameStart->CheckBox("Say Greeting", false);
				CDelay = GameStart->AddInteger("Delay", 0, 75, 20);
				MuteAll = GameStart->CheckBox("Mute All", false);
			}

			GameEnd = GameChat->AddMenu("OnGame End");
			{
				Ending = GameEnd->AddSelection("Goodbyes", 1, std::vector<std::string>({ "gg", "gg wp", "well played" }));
				SayEnding = GameEnd->CheckBox("Say Goodbye", false);
				QuitGame = GameEnd->CheckBox("Quit Game", false);
				QuitDelay = GameEnd->AddInteger("Quit Delay", 3, 20, 10);
			}

			cMode = GameChat->AddSelection("Enable Mode ->", 1, std::vector<std::string>({ "ENABLED", "DISABLED" }));
		}*/
	}

	static void OpenDebug()
	{
		eCounterStrike = false;

		if (Debug->Enabled() && !eCounterStrike)
		{
			GUtility->CreateDebugConsole();
			eCounterStrike = true;
		}
		else
		{
			//GUtility->DestroyDebugConsole();
		}
	}

	static void SendEmote()
	{
		if (GGame->TickCount() - LastEmoteSpam > Random(6000, 12000))
		{
			LastEmoteSpam = GGame->TickCount();
			auto mode = EmoteMode->GetInteger();

			if (mode == 2) return;

			GGame->Say(mode == 0 ? "/masterybadge" : "/l");				
		}
	}	

	static void SpamEmote()
	{
		OpenDebug();

		if (GGame->IsChatOpen()) return;

		if (EmoteNearDead->Enabled())
		{
			SArray<IUnit*> Enemys = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return GetDistance(GEntityList->Player(), i) < 300 && i->IsDead() && 
				i->IsVisible(); });

			if (Enemys.Any())
			{
				SendEmote();
			}
		}
		
		if (GEntityList->Player()->GetKills() > MyKills && EmoteOnKill->Enabled())
		{
			MyKills = GEntityList->Player()->GetKills();
			SendEmote();
		}
		if (GEntityList->Player()->GetAssists() > MyAssits && EmoteOnAssis->Enabled())
		{
			MyAssits = GEntityList->Player()->GetAssists();
			SendEmote();
		}
		if (GEntityList->Player()->GetDeaths() > MyDeaths && EmoteOnDeath->Enabled())
		{
			MyDeaths = GEntityList->Player()->GetDeaths();
			SendEmote();
		}

		/*if (!onStartDone)
		{
			if (GGame->Time() > CDelay->GetInteger() && GGame->Time() < 600)
			{
				if (SayGreeting->Enabled() && GEntityList->Player()->GetLevel() == 1)
				{
					if (Greeting->GetInteger() == 0)
					{
						GGame->Say("/all gl & hf");
					}
					else
					{
						GGame->Say("/all good luck & have fun");
					}
				}

				if (MuteAll->Enabled() && GEntityList->Player()->GetLevel() == 1)
				{
					GGame->Say("/mute all");					
				}

				onStartDone = true;
			}
		}*/

		//GUtility->LogConsole("GameTime: %f", GGame->Time());
	}

	static void OnGameEnd()
	{
		/*if (SayEnding->Enabled())
		{
			if (Ending->GetInteger() == 0)
			{
				GGame->Say("/all gg");
			}
			else if (Ending->GetInteger() == 1)
			{
				GGame->Say("/all gg wp");
			}
			else
			{
				GGame->Say("/all well played");
			}
		}

		if (QuitGame->Enabled())
		{
			auto delay = QuitDelay->GetInteger() * 1000;

			GPluginSDK->DelayFunctionCall(delay, []() { GGame->Quit(); });
		}*/
	}
};
