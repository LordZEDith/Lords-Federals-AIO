#pragma once
#include "PluginSDK.h"
#include "Color.h"
#include "BaseMenu.h"

class VersionCheck
{
public:

	inline bool VersionChecker()
	{
		std::string szData;
		if (GPluginSDK->ReadFileFromURL("leagueplus.000webhostapp.com/Lords_AIO.txt", szData))
		{
			auto n = szData.find("LocalVersion = ");

			if (n != szData.npos)
			{
				n += 15;
				szData = szData.substr(n, szData.size() - n);

			}

			auto k = szData.find(";");

			if (k != szData.npos)
				szData = szData.substr(0, k);

			auto dwGitVersion = atoi(szData.c_str());

			return (dwGitVersion <= 5);
		}

		return true;
	}

	inline void RunVersionChecker()
	{
		if (VersionChecker() == true)
		{
		/*	GGame->Projection(GEntityList->Player()->GetPosition(), &HeroCoordsVec2);
			auto champx = HeroCoordsVec2.x;
			auto champy = HeroCoordsVec2.y;
			static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
			message->SetColor(Vec4(255, 0, 0, 255));
			message->SetOutline(true);
			message->Render(champx - 55 * 5, champy - 200, "VersionChecker: You Have The Latest Version");*/
			GRender->NotificationEx(Vec4(25, 188, 33, 1), 20, false, true, "VersionChecker: You Have The Latest Version");
		}
		else
		{
			/*GGame->Projection(GEntityList->Player()->GetPosition(), &HeroCoordsVec2);
			auto champx = HeroCoordsVec2.x;
			auto champy = HeroCoordsVec2.y;
			static auto message = GRender->CreateFontW("Impact", 30.f, kFontWeightNormal);
			message->SetColor(Vec4(188, 33, 25, 1));
			message->SetOutline(true);
			message->Render(champx - 55 * 5, champy - 200, "VersionChecker: You Have An old Version");*/
			GRender->NotificationEx(Vec4(200, 18, 18, 1), 20, false, true, "VersionChecker: You Have An Older Version");
		}
	}
};

