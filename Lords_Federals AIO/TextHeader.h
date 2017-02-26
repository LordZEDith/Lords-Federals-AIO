#pragma once
#include "PluginSDK.h"
#include "Color.h"

class Message
{
public:

	void MidLaneSeries()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("Midlane Series Loaded"));
	}

	void TopLaneSeries()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("TopLane Series Loaded"));
	}

	void JungleLaneSeries()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("Jungle Series Loaded"));
	}

	void SuppLaneSeries()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("Support Series Loaded"));
	}

	void ADCLaneSeries()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("ADC Series Loaded"));
	}

	void AutoLevels()
	{
		GRender->NotificationEx(Color::LightRed().Get(), 2, true, true, ("Auto Leveler Loaded"));
	}

	void ChampionLoadMessage()
	{
		std::string urChampion = GEntityList->Player()->ChampionName();
		auto Messagem = " detected...Loading script";
		urChampion += Messagem;				
		
		GGame->PrintChat(urChampion.c_str());
	}
};




