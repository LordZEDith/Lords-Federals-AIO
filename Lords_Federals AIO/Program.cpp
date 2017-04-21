#include "PluginSDK.h"
#include "TextHeader.h"
#include "Color.h"
#include "Champions.h"
#include "AutoSmite.h"
#include <unordered_map>
#include "SkinsChange.h"
#include "Toxic.h"
#include "Version Checker.h"
#include "Trinket.h"
#pragma region Events
PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* Target)
{

}
PLUGIN_EVENT(void) OnOrbwalkAttack(IUnit* Source, IUnit* Target)
{

}
#pragma endregion

PluginSetup("Lords & Federals AIO");

class IChampion
{
public:		
	virtual void OnGameUpdate() = 0;
	virtual void OnAfterAttack(IUnit* Source, IUnit* Target) = 0;
	virtual void OnBeforeAttack(IUnit* Target) = 0;
	virtual void OnGapCloser(GapCloserSpell const& Args) = 0;
	virtual void OnInterruptible(InterruptibleSpell const& Args) = 0;
	virtual void OnDash(UnitDash* Args) = 0;
	virtual void OnCreateObject(IUnit* Object) = 0;
	virtual void OnDeleteObject(IUnit* Object) = 0;
	virtual void OnLevelUp(IUnit* Source, int NewLevel) = 0;
	virtual void OnProcessSpell(CastedSpell const& Args) = 0;
	virtual void OnExitVisible(IUnit* Source) = 0;
	virtual void OnLoad() {};
	virtual void OnBuffAdd(IUnit* Source, void* BuffData) = 0;
	virtual void OnBuffRemove(IUnit* Source, void* BuffData) = 0;
	//virtual void OnUnLoad() = 0;
	virtual void OnRender() = 0;
	virtual void OnGameEnd() = 0;
};
class cTemplate : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().SuppLaneSeries();
		//Message().ChampionLoadMessage();
		Template().InitializeMenu();
		Template().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{

		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{

		}

		Template().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		//Skins().fedSkinChanger();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		//Template().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack( IUnit* Target) override
	{
		
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Template().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Template().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cVarus : public IChampion
{
public:
	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		VarusV2().InitializeMenu();
		VarusV2().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
		Trinket().SpellsTrinket();
		Trinket().MenuTrinket();
	}

	virtual void OnRender() override
	{
		VarusV2().Drawing();

	}

	virtual void OnGameUpdate() override
	{
		Trinket().AutoTrinket();

		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
	     }
		
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			{
				VarusV2().Combo();
			}
			if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
			{
				VarusV2().Harass();
			}
			if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
			{				
				VarusV2().LaneClear();
				VarusV2().JungleClear();
			}
			VarusV2().Automatic();				
			AutoSmite().AutomaticSmite();
			AutoSmite().KeyPressSmite();
			Toxic().SpamEmote();
			//Skins().fedSkinChanger();
		 
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		VarusV2().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}	
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}	

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Trinket().TrinketOnProcessSpell(Args);
		VarusV2().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{
		Trinket().TrinketOnExitVisible(Source);
	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cZiggs : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		//Message().ChampionLoadMessage();
		Ziggs().InitializeSpells();
		Ziggs().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Ziggs().Combo();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Ziggs().Harass();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Ziggs().CastEFarm();
		}	

	    Ziggs().LogicW();
		Ziggs().LogicE();		
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		//Skins().fedSkinChanger();
		Toxic().SpamEmote();
	}

	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		
	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cAshe : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		Ashe().InitializeSpells();
		Ashe().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
		Trinket().SpellsTrinket();
		Trinket().MenuTrinket();
	}

	virtual void OnRender() override
	{
		Ashe().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		Trinket().AutoTrinket();

		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{			
			
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			
		}
		Ashe().LogicR();
		Ashe().LogicW();
		Ashe().Automatic();		
		//Skins().fedSkinChanger();
		Ashe().KeyPressUltimate();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}

	void OnGapCloser(GapCloserSpell const& Args) override
	{
		
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Ashe().OnInterruptible(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Ashe().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Trinket().TrinketOnProcessSpell(Args);
		Ashe().OnProcessSpell(Args);		
	}

	void OnExitVisible(IUnit* Source) override
	{
		Trinket().TrinketOnExitVisible(Source);
	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cDraven : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		Draven().InitializeSpells();
		Draven().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Draven().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{			
			Draven().LogicW();
			Draven().AxeLogicCombo();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Draven().AxeLogicFarm();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Draven().AxeLogicFarm();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLastHit)
		{
			Draven().AxeLogicFarm();
		}
		
		Draven().LogicR();
		Draven().LogicE();
		Draven().KeyPressUltimate();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}

	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Draven().OnGapcloser(Args);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Draven().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Draven().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Draven().OnDeleteObject(Source);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{		

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cEzreal : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		Ezreal().InitializeSpells();
		Ezreal().InitializeMenu();
		//Skins().Menu();
		Toxic().MenuToxic();
		Trinket().SpellsTrinket();
		Trinket().MenuTrinket();
	}

	virtual void OnRender() override
	{
		Ezreal().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		Trinket().AutoTrinket();

		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Ezreal().Combo();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Ezreal().Harass();
			Ezreal().LastHit();
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Ezreal().LaneClear();
			Ezreal().JungleClear();
		}
		
		Ezreal().Automatic();		
		Ezreal().StackMuneItem();
		Ezreal().KsJungle();
		//Skins().fedSkinChanger();
		Toxic().SpamEmote();
	}

	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Ezreal().OnGapcloser(Args);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Trinket().TrinketOnProcessSpell(Args);
		Ezreal().OnProcessSpell(Args);		
	}

	void OnExitVisible(IUnit* Source) override
	{
		Trinket().TrinketOnExitVisible(Source);
	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cAhri : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		//Message().ChampionLoadMessage();
		Ahri().LoadSpells();
		Ahri().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Ahri().Drawing();		
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Ahri().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Ahri().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Ahri().LaneClear();
			Ahri().JungleClear();
		}
		
		Ahri().Automatic();		
		//Skins().fedSkinChanger();	
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}

	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Ahri().OnGapcloser(Args);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Ahri().OnInterruptible(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Ahri().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Ahri().OnDeleteObject(Source);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Ahri().OnProcessSpell(Args);
		
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		Ahri().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cLux : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		//Message().ChampionLoadMessage();
		Lux().InitializeMenu();
		Lux().LoadSpells();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Lux().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Lux().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Lux().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Lux().JungleClear();
			Lux().LaneClear();
		}

		//Skins().fedSkinChanger();
		Lux().AutoRKS();
		Lux().AutoCCed();
		Lux().KsJungle();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Lux().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Lux().OnCreateObject(Source);

	}

	void OnDeleteObject(IUnit* Source) override
	{
		Lux().OnDeleteObject(Source);
	}

	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{

	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Lux().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cOlaf : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Olaf().InitializeMenu();
		Olaf().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Olaf().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}	

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Olaf().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Olaf().Harass();
			Olaf().LastHit();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{			
			Olaf().LaneClear();
			Olaf().JungleClear();
		}

		Olaf().Automatic();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Olaf().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Olaf().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Olaf().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Olaf().OnDeleteObject(Source);
	}	

	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cDrMundo : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		DrMundo().InitializeMenu();
		DrMundo().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		DrMundo().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			DrMundo().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			DrMundo().Harass();
			DrMundo().LastHit();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			DrMundo().LaneClear();
			DrMundo().JungleClear();			
		}

		DrMundo().Automatic();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		DrMundo().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		DrMundo().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}

	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cMaokai : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Maokai().InitializeMenu();
		Maokai().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Maokai().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Maokai().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Maokai().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Maokai().LaneClear();
			Maokai().JungleClear();
		}		
		
		Maokai().AutoUlt();
		Maokai().AutoUnderTower();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Maokai().OnGapcloser(Args);		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}

	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Maokai().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cPoppy : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Poppy().InitializeMenu();
		Poppy().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Poppy().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Poppy().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Poppy().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Poppy().LaneClear();
			Poppy().JungleClear();
		}

		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Poppy().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Poppy().OnCreateObject(Source);

	}

	void OnDeleteObject(IUnit* Source) override
	{
		Poppy().OnDeleteObject(Source);
	}

	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Poppy().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
		Poppy().OnDash(Args);
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cNocturne : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Nocturne().InitializeMenu();
		Nocturne().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Nocturne().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Nocturne().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Nocturne().Harass();			
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Nocturne().LaneClear();
			Nocturne().JungleClear();
		}

		Nocturne().RangeUltimate();
		Nocturne().Automatic();
		//Skins().fedSkinChanger();
		Nocturne().KeyPressUltimate();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
	
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		
	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}	

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cHecarim : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Hecarim().InitializeMenu();
		Hecarim().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Hecarim().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Hecarim().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Hecarim().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Hecarim().LaneClear();
			Hecarim().JungleClear();
		}
		
		Hecarim().Automatic();
		//Skins().fedSkinChanger();		
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Hecarim().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Hecarim().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cElise : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Elise().InitializeMenu();
		Elise().LoadSpells();
		Elise().LoadTextures();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Elise().Drawings();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Elise().Combo();			
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			//Elise().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			//Elise().LaneClear();
			Elise().JungleClear();
		}
		
		//Skins().fedSkinChanger();
		Elise().EliseRappel();
		Elise().Cooldowns();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Elise().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Elise().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Elise().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Elise().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cRengar : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Rengar().Menu();
		Rengar().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Rengar().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Rengar().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Rengar().Farm();
		}


		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		if (ComboAA->Enabled() && !(ComboA->Enabled()))
		{
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			{
				Rengar().Combo();
			}
		}
	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cMalphite : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Malphite().Menu();
		Malphite().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Malphite().Drawingss();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Malphite().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Malphite().Farm();
		}
		Malphite().Auto();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Malphite().GapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cXerath : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		//Message().ChampionLoadMessage();
		Xerath().InitializeMenu();
		Xerath().InitializeSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Xerath().Drawings();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Xerath().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Xerath().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Xerath().JungleClear();
			Xerath().LaneClear();
		}

		Xerath().Ultimate();
		Xerath().Automatic();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		Xerath().RPing();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Xerath().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Xerath().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Xerath().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cSona : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().SuppLaneSeries();
		//Message().ChampionLoadMessage();

		Sona().Menu();
		Sona().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Sona().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Sona().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{

		}
		Sona().AutoW();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cDiana : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Diana().Menu();
		Diana().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Diana().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Diana().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Diana().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Diana().Farm();
		}
		if (R->IsReady())
		{
			Diana().ComboRKill1();
		}
		if (QEnemies1->Enabled())
		{
			Diana().AutoQ();
		}
		Diana().StealR();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		//Diana().GapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cWarwick : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Warwick().Menu();
		Warwick().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Warwick().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Warwick().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Warwick().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Warwick().JungleClear();
		}


		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cDarius : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Darius().Menu();
		Darius().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Darius().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Darius().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Darius().Farm();
		}
		Darius().Automatic();
		Darius().Automatic2();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		//Darius().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cKayle : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Kayle().Menu();
		Kayle().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Kayle().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Kayle().LogicQC();
			Kayle().LogicEC();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Kayle().LogicQH();
			Kayle().LogicEH();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			//Need to Add
		}
		Kayle().Combo();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cTristana : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		zTristana().InitializeMenu();
		zTristana().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		zTristana().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			zTristana().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			zTristana().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			zTristana().LaneClear();
			zTristana().JungleClear();
		}
		
		zTristana().RMiscs();
		zTristana().WAntiMelee();		
		zTristana().FocusTargetE();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		//Skins().fedSkinChanger();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		zTristana().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		zTristana().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		zTristana().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cCaitlyn : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		Caitlyn().InitializeMenu();
		Caitlyn().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Caitlyn().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Caitlyn().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Caitlyn().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Caitlyn().LaneClear();
			Caitlyn().JungleClear();
		}

		Caitlyn().Automatic();
		Caitlyn().AutoTrap();
		Caitlyn().DashToMouse();
		//Skins().fedSkinChanger();		
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Caitlyn().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Caitlyn().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Caitlyn().OnDeleteObject(Source);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
		Caitlyn().OnDash(Args);
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Caitlyn().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cTwistedFate : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		//Message().ChampionLoadMessage();
		Twisted().Menu();
		Twisted().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Twisted().Drawings();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{

		}


		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cLeeSin : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		LeeSin().InitializeMenu();
		LeeSin().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();

		//GUtility->CreateDebugConsole();
	}

	virtual void OnRender() override
	{
		LeeSin().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			LeeSin().ComboSelected();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			LeeSin().Harass();
			LeeSin().LastHit();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			LeeSin().JungleClear();
			LeeSin().LaneClear();
		}

		LeeSin().StarCombo();
		LeeSin().EscapeJungle();
		LeeSin().InsecRework();
		LeeSin().WardJumpMouse();
		LeeSin().Automatic();
		LeeSin().KickBehind();
		LeeSin().KeyPressComboMode();
		//Skins().fedSkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		LeeSin().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		LeeSin().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
		LeeSin().OnBuffAdd(Source, BuffData);
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		LeeSin().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cKhazix : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Khazix().InitializeMenu();
		Khazix().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();		
	}

	virtual void OnRender() override
	{
		Khazix().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Khazix().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Khazix().LastHit();
			Khazix().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Khazix().JungleClear();
			Khazix().LaneClear();
		}
		
		Khazix().Automatic();
		Khazix().AutoEscape();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Khazix().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
		
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cRumble : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Rumble().InitializeMenu();
		Rumble().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Rumble().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Rumble().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Rumble().LastHit();
			Rumble().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Rumble().JungleClear();
			Rumble().LaneClear();
		}

		Rumble().Automatic();		
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}		

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cGragas : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Gragas().InitializeMenu();
		Gragas().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Gragas().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Gragas().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{			
			Gragas().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Gragas().JungleClear();
			Gragas().LaneClear();
		}

		Gragas().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack( IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Gragas().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Gragas().OnDeleteObject(Source);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Gragas().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cEkko : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Ekko().Menu();
		Ekko().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Ekko().OnRender();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		Ekko().OnGameUpdate();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Ekko().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Ekko().OnDestroyObject(Source);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cRenekton : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Renekton().Menu();
		Renekton().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Renekton().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		Renekton().OnGameUpdate();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Renekton().OnGapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Renekton().OnOrbwalkAfterAttack(Source,Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{
		Renekton().OnOrbwalkBeforeAttack(Target);
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Renekton().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Renekton().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cChoGatn : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		ChoGath().Menu();
		ChoGath().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		AutoSmite().DrawingsSmite();
		ChoGath().OnRender();
	}

	virtual void OnGameUpdate() override
	{
		ChoGath().OnGameUpdate();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		//Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		ChoGath().OnGapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		ChoGath().OnOrbwalkAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{
		
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{
		ChoGath().OnLevelUp(Source,NewLevel);
	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		ChoGath().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cTrundle : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Trundle().Menu();
		Trundle().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		AutoSmite().DrawingsSmite();
		Trundle().OnRender();
	}

	virtual void OnGameUpdate() override
	{
		Trundle().OnGameUpdate();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Trundle().OnGapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Trundle().OnOrbwalkAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{
	
	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Trundle().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}
	
	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cJax : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Jax().Menu();
		Jax().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		AutoSmite().DrawingsSmite();
		Jax().OnRender();
	}

	virtual void OnGameUpdate() override
	{
		Jax().OnGameUpdate();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		//Jax().OnGapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Jax().OnOrbwalkAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		Jax().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
	    // Jax).OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Jax().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

class cGalio : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Galio().InitializeMenu();
		Galio().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Galio().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Galio().ComboSelected();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Galio().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Galio().JungleClear();
			Galio().LaneClear();
		}

		Galio().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Galio().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Galio().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}	

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cGnar : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().TopLaneSeries();
		Message().ChampionLoadMessage();
		Gnar().InitializeMenu();
		Gnar().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Gnar().Drawing();
		Gnar().Drawing2();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}
		Gnar().OnUpdate();
	    AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Gnar().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Gnar().OnInterruptible(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
	
	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cIvern : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Ivern().InitializeMenu();
		Ivern().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Ivern().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Ivern().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Ivern().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{			
			Ivern().LaneClear();
			Ivern().WUnderTower();
		}

		Ivern().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{

	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{		
		Ivern().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		Ivern().OnDeleteObject(Source);
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		
	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cKindred : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Kindred().InitializeMenu();
		Kindred().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Kindred().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Kindred().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Kindred().LaneClear();
			Kindred().JungleClear();
		}

		Kindred().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Kindred().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Kindred().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		Kindred().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cVayne : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Vayne().InitializeMenu();
		Vayne().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Vayne().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		Vayne().BuyTrinket();
		
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Vayne().LaneClear();
			Vayne().JungleClear();
		}

		Vayne().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		Vayne().zzRotRun();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Vayne().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Vayne().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{
		Vayne().OnBeforeAttack(Target);
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		//Vayne().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		Vayne().OnInterrupt(Args);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Vayne().OnProcessSpell(Args);		
	}

	void OnExitVisible(IUnit* Source) override
	{
		Vayne().OnExitVisible(Source);
	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
		//Vayne().OnBuffAdd(Source, BuffData);
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		//Vayne().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cPantheon : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().TopLaneSeries();
		//Message().ChampionLoadMessage();
		Pantheon().Menu();
		Pantheon().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Pantheon().OnRender();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		Pantheon().OnGameUpdate();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Pantheon().OnOrbwalkAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{
		
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{

	}

	void OnDeleteObject(IUnit* Source) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{

	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{

	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{

	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cSyndra : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		//Message().ChampionLoadMessage();
		Syndra().InitializeMenu();
		Syndra().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
	}

	virtual void OnRender() override
	{
		Syndra().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Syndra().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{

		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Syndra().LaneClear();
			Syndra().JungleClear();
		}

		Syndra().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();		
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Syndra().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Syndra().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{
		
	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		
	}

	void OnDeleteObject(IUnit* Source) override
	{
		
	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{
		
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Syndra().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{
		
	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
		//Syndra().OnBuffAdd(Source, BuffData);
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
		//Syndra().OnBuffRemove(Source, BuffData);
	}

	void OnGameEnd() override
	{
		//Toxic().OnGameEnd();
	}
};

class cXayah : public IChampion
{
public:
	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		//Message().ChampionLoadMessage();
		Xayah().InitializeMenu();
		Xayah().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
		//Skins().Menu();
		Toxic().MenuToxic();
		Trinket().SpellsTrinket();
		Trinket().MenuTrinket();
	}

	virtual void OnRender() override
	{
		Xayah().Drawing();

	}

	virtual void OnGameUpdate() override
	{
		Trinket().AutoTrinket();

		if (GEntityList->Player()->IsDead() || GEntityList->Player()->IsRecalling() || GGame->IsChatOpen() || GGame->IsScoreboardOpen() || GGame->IsShopOpen())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Xayah().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Xayah().Harass();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{
			Xayah().LaneClear();
			Xayah().JungleClear();
		}
		Xayah().Automatic();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
		Toxic().SpamEmote();
		//Skins().fedSkinChanger();

	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Xayah().OnAfterAttack(Source, Target);
	}
	void OnBeforeAttack(IUnit* Target) override
	{

	}
	void OnLevelUp(IUnit* Source, int NewLevel) override
	{

	}
	void OnInterruptible(InterruptibleSpell const& Args) override
	{

	}

	void OnCreateObject(IUnit* Source) override
	{
		//Xayah().OnCreateObject(Source);
	}

	void OnDeleteObject(IUnit* Source) override
	{
		//Xayah().OnDeleteObject(Source);
	}

	void OnDash(UnitDash* Args) override
	{
	}

	void OnProcessSpell(CastedSpell const& Args) override
	{
		Trinket().TrinketOnProcessSpell(Args);		
	}

	void OnExitVisible(IUnit* Source) override
	{
		Trinket().TrinketOnExitVisible(Source);
	}

	void OnBuffAdd(IUnit* Source, void* BuffData) override
	{
	}

	void OnBuffRemove(IUnit* Source, void* BuffData) override
	{
	}

	void OnGameEnd() override
	{
		Toxic().OnGameEnd();
	}
};

IChampion* pChampion = nullptr;

PLUGIN_EVENT(void) OnRender()
{
	pChampion->OnRender();
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	pChampion->OnGameUpdate();
}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& Args)
{
	pChampion->OnGapCloser(Args);
}

PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& Args)
{
	pChampion->OnInterruptible(Args);
}

PLUGIN_EVENT(void) OnAfterAttack(IUnit* Source, IUnit* Target)
{
	pChampion->OnAfterAttack(Source, Target);
}
PLUGIN_EVENT(void) OnBeforeAttack(IUnit* Target)
{
	pChampion->OnBeforeAttack(Target);
}

PLUGIN_EVENT(void) OnLevelUp(IUnit* Source, int NewLevel)
{
	pChampion->OnLevelUp(Source, NewLevel);
}

PLUGIN_EVENT(void) OnCreateObject(IUnit* Source)
{
	pChampion->OnCreateObject(Source);
}

PLUGIN_EVENT(void) OnDeleteObject(IUnit* Source)
{
	pChampion->OnDeleteObject(Source);
}

PLUGIN_EVENT(void) OnProcessSpell(CastedSpell const& Args)
{
	pChampion->OnProcessSpell(Args);
}

PLUGIN_EVENT(void) OnExitVisible(IUnit* Source)
{
	pChampion->OnExitVisible(Source);
}

PLUGIN_EVENT(void) OnDash(UnitDash* Source)
{
	pChampion->OnDash(Source);
}

PLUGIN_EVENT(void) OnBuffAdd(IUnit* Source, void* BuffData)
{
	pChampion->OnBuffAdd(Source, BuffData);
}

PLUGIN_EVENT(void) OnBuffRemove(IUnit* Source, void* BuffData)
{
	pChampion->OnBuffRemove(Source, BuffData);
}

PLUGIN_EVENT(void) OnGameEnd()
{
	pChampion->OnGameEnd();
}


void LoadChampion()
{
	std::string szChampion = GEntityList->Player()->ChampionName();
	szChampion = ToLower(szChampion);

	//ADC
	if (szChampion == "varus")
		pChampion = new cVarus;
	else if (szChampion == "ashe")
		pChampion = new cAshe;
	else if (szChampion == "draven")
		pChampion = new cDraven;
	else if (szChampion == "tristana")
		pChampion = new cTristana;
	else if (szChampion == "ezreal")
		pChampion = new cEzreal;
	else if (szChampion == "caitlyn")
		pChampion = new cCaitlyn;
	else if (szChampion == "vayne")
		pChampion = new cVayne;
	else if (szChampion == "xayah")
		pChampion = new cXayah;
	// Midlane
	else if (szChampion == "ahri")
		pChampion = new cAhri;
	else if (szChampion == "lux")
		pChampion = new cLux;
	else if (szChampion == "ziggs")
		pChampion = new cZiggs;
	else if (szChampion == "xerath")
		pChampion = new cXerath;
	else if (szChampion == "twistedFate")
		pChampion = new cTwistedFate;
	else if (szChampion == "syndra")
		pChampion = new cSyndra;
	// Jungle
	else if (szChampion == "olaf")
		pChampion = new cOlaf;
	else if (szChampion == "nocturne")
		pChampion = new cNocturne;
	else if (szChampion == "hecarim")
		pChampion = new cHecarim;
	else if (szChampion == "rengar")
		pChampion = new cRengar;
	else if (szChampion == "diana")
		pChampion = new cDiana;
	else if (szChampion == "warwick")
		pChampion = new cWarwick;
	else if (szChampion == "elise")
		pChampion = new cElise;
	else if (szChampion == "leesin")
		pChampion = new cLeeSin;
	else if (szChampion == "khazix")
		pChampion = new cKhazix;
	else if (szChampion == "gragas")
		pChampion = new cGragas;
	else if (szChampion == "galio")
		pChampion = new cGalio;
	else if (szChampion == "ivern")
		pChampion = new cIvern;
	else if (szChampion == "kindred")
		pChampion = new cKindred;
	// Toplane
	else if (szChampion == "drmundo")
		pChampion = new cDrMundo;
	else if (szChampion == "maokai")
		pChampion = new cMaokai;
	else if (szChampion == "poppy")
		pChampion = new cPoppy;
	else if (szChampion == "malphite")
		pChampion = new cMalphite;
	else if (szChampion == "kayle")
		pChampion = new cKayle;
	else if (szChampion == "darius")
		pChampion = new cDarius;
	else if (szChampion == "rumble")
		pChampion = new cRumble;
	else if (szChampion == "ekko")
		pChampion = new cEkko;
	else if (szChampion == "renekton")
		pChampion = new cRenekton;
	else if (szChampion == "chogath")
		pChampion = new cChoGatn;
	else if (szChampion == "trundle")
		pChampion = new cTrundle;
	else if (szChampion == "jax")
		pChampion = new cJax;
	else if (szChampion == "gnar")
		pChampion = new cGnar;
	else if (szChampion == "pantheon")
		pChampion = new cPantheon;
	// Support
	else if (szChampion == "sona")
		pChampion = new cSona;
	else if (szChampion == "blitzcrank")
		pChampion = new cTemplate;
	else
	{		
		GGame->PrintChat(szChampion.data());
		GGame->PrintChat("Champion Not Supported");
	}	
	
	if (pChampion != nullptr)
	{
		GEventManager->AddEventHandler(kEventOnRender, OnRender);
		GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
		GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
		GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);		
		GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
		GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
		GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
		GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
		GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
		GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpell);
		GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
		GEventManager->AddEventHandler(kEventOnDestroyObject, OnDeleteObject);
		GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);		
		GEventManager->AddEventHandler(kEventOnDash, OnDash);
		GEventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
	}
}

// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	//VersionCheck().RunVersionChecker();
	LoadChampion();
	pChampion->OnLoad();	
	GRender->NotificationEx(Color::LightBlue().Get(), 10, true, true, "Welcome to Lords & Federals AIO");	
	GRender->NotificationEx(Color::LightBlue().Get(), 10, true, true, "[News]: Galio, Pantheon, Gnar, Kindred and Ivern are now Supported");
	GRender->NotificationEx(Color::LightBlue().Get(), 3, true, false, "[Betas]: Ahri Updates, Draven Update, Vayne");
	GRender->NotificationEx(Color::LightBlue().Get(), 10, true, true, "[Donations]: If you like our plugins please leave a donation, link can be found in our signatures");

	//GUtility->CreateDebugConsole();	
}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	//pChampion->OnUnLoad();

	MainMenu->Remove();
	//GUtility->DestroyDebugConsole();
	
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);	
	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->RemoveEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpell);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDeleteObject);
	GEventManager->RemoveEventHandler(kEventOnExitVisible, OnExitVisible);	
	GEventManager->RemoveEventHandler(kEventOnDash, OnDash);
	GEventManager->RemoveEventHandler(kEventOnGameEnd, OnGameEnd);
}
