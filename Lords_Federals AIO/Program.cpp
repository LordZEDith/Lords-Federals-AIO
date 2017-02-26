#include "PluginSDK.h"
#include "TextHeader.h"
#include "Color.h"
#include "Champions.h"
#include "AutoSmite.h"
#include "Toxic.h"
#include "Version Checker.h"


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
	virtual void OnGapCloser(GapCloserSpell const& Args) = 0;
	virtual void OnInterruptible(InterruptibleSpell const& Args) = 0;
	virtual void OnDash(UnitDash* Args) = 0;
	virtual void OnCreateObject(IUnit* Object) = 0;
	virtual void OnDeleteObject(IUnit* Object) = 0;
	virtual void OnLevelUp(IUnit* Source, int NewLevel) = 0;
	virtual void OnProcessSpell(CastedSpell const& Args) = 0;
	virtual void OnExitVisible(IUnit* Source) = 0;
	virtual void OnUnitDeath(IUnit* Source) = 0;	
	virtual void OnLoad() = 0;
	//virtual void OnUnLoad() = 0;
	virtual void OnRender() = 0;
};
class cTemplate : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();


		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{

		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}	
};

class cVarus : public IChampion
{
public:
	virtual void OnLoad() override
	{
		//Message().ADCLaneSeries();
		Message().ChampionLoadMessage();
		Varus().Menu();
		Varus().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Varus().Drawing();

	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
		{
			return;
	     }
		
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			{
				Varus().Combo();
			}
			if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
			{
				Varus().Harass();
			}
			if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
			{
				Varus().FarmHarass();
				Varus().LaneClear();
				Varus().JungleClear();
			}
			Varus().SemiRLogic();
			Varus().AutoHarass();
			Varus().KillSteal();		
			AutoSmite().AutomaticSmite();
			AutoSmite().KeyPressSmite();
		 
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnUnitDeath(IUnit* Source) override
	{

	}	
};

class cZiggs : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Ziggs().InitializeSpells();
		Ziggs().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{

		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{

		}
		
		//Ziggs().SkinChanger();
		Ziggs().LogicW();
		Ziggs().CheckKeyPresses();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cAshe : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Ashe().InitializeSpells();
		Ashe().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();

	}

	virtual void OnRender() override
	{
		Ashe().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Ashe().SkinChanger();
		Ashe().KeyPressUltimate();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cDraven : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Draven().InitializeSpells();
		Draven().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Draven().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		
		Draven().LogicR();
		Draven().LogicE();
		Draven().KeyPressUltimate();
		Draven().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cEzreal : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Ezreal().InitializeSpells();
		Ezreal().InitializeMenu();	
	}

	virtual void OnRender() override
	{
		Ezreal().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		}
		
		Ezreal().Automatic();
		Ezreal().EAntiMelee();
		Ezreal().StackMuneItem();
		Ezreal().KsJungle();
		Ezreal().SkinChanger();		
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
		Ezreal().OnAfterAttack(Source, Target);
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
		Ezreal().OnProcessSpell(Args);
	}

	void OnExitVisible(IUnit* Source) override
	{

	}

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cAhri : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Ahri().LoadSpells();
		Ahri().InitializeMenu();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Ahri().Drawing();		
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Ahri().SkinChanger();	
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cLux : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Lux().InitializeMenu();
		Lux().LoadSpells();
	}

	virtual void OnRender() override
	{
		Lux().Drawing();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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

		Lux().SkinChanger();
		Lux().AutoRKS();
		Lux().AutoCCed();
		Lux().KsJungle();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Lux().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cOlaf : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Olaf().InitializeMenu();
		Olaf().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();		
	}

	virtual void OnRender() override
	{
		Olaf().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Olaf().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Olaf().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Olaf().OnAfterAttack(Source, Target);
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cDrMundo : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		DrMundo().InitializeMenu();
		DrMundo().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		DrMundo().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
			DrMundo().AutoStopW();
		}

		DrMundo().Automatic();
		DrMundo().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		DrMundo().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		DrMundo().OnAfterAttack(Source, Target);
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cMaokai : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Maokai().InitializeMenu();
		Maokai().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Maokai().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Maokai().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Maokai().OnGapcloser(Args);		
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cPoppy : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Poppy().InitializeMenu();
		Poppy().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Poppy().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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

		Poppy().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Poppy().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cNocturne : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Nocturne().InitializeMenu();
		Nocturne().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Nocturne().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Nocturne().SkinChanger();
		Nocturne().KeyPressUltimate();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
	
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cHecarim : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Hecarim().InitializeMenu();
		Hecarim().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Hecarim().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Hecarim().SkinChanger();		
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Hecarim().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cRengar : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Rengar().Menu();
		Rengar().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Rengar().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cMalphite : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().TopLaneSeries();
		Message().ChampionLoadMessage();
		Malphite().Menu();
		Malphite().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Malphite().Drawingss();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Malphite().GapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cXerath : public IChampion
{
public:

	virtual void OnLoad() override
	{
		//Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Xerath().InitializeMenu();
		Xerath().InitializeSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Xerath().Drawings();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		Xerath().SkinChanger();
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		Xerath().OnGapcloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cSona : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().SuppLaneSeries();
		Message().ChampionLoadMessage();

		Sona().Menu();
		Sona().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Sona().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cDiana : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Diana().Menu();
		Diana().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Diana().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{
		//Diana().GapCloser(Args);
	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cWarwick : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().JungleLaneSeries();
		Message().ChampionLoadMessage();
		Warwick().Menu();
		Warwick().LoadSpells();

		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Warwick().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cDarius : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().TopLaneSeries();
		Message().ChampionLoadMessage();
		Darius().Menu();
		Darius().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Darius().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cKayle : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().TopLaneSeries();
		Message().ChampionLoadMessage();
		Kayle().Menu();
		Kayle().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Kayle().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cTristana : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().ADCLaneSeries();
		Message().ChampionLoadMessage();
		Tristana().Menu();
		Tristana().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Tristana().Drawing();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
		{
			return;
		}

		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			Tristana().Combo();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			Tristana().HarassE2();
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		{

		}
		Tristana().SelfR();
		Tristana().Automatic();
		Tristana().Automatic2();

		AutoSmite().AutomaticSmite();
		AutoSmite().KeyPressSmite();
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
	{
		Tristana().AfterAttack();
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

	void OnUnitDeath(IUnit* Source) override
	{

	}
};

class cTwistedFate : public IChampion
{
public:

	virtual void OnLoad() override
	{
		Message().MidLaneSeries();
		Message().ChampionLoadMessage();
		Twisted().Menu();
		Twisted().LoadSpells();
		AutoSmite().SpellsSmite();
		AutoSmite().MenuSmite();
	}

	virtual void OnRender() override
	{
		Twisted().Drawings();
		AutoSmite().DrawingsSmite();
	}

	virtual void OnGameUpdate() override
	{
		if (GEntityList->Player()->IsDead() && GEntityList->Player()->IsRecalling())
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
	}
	void OnGapCloser(GapCloserSpell const& Args) override
	{

	}
	void OnAfterAttack(IUnit* Source, IUnit* Target) override
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

	void OnUnitDeath(IUnit* Source) override
	{

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

PLUGIN_EVENT(void) OnUnitDeath(IUnit* Source)
{
	pChampion->OnUnitDeath(Source);
}

PLUGIN_EVENT(void) OnDash(UnitDash* Source)
{
	pChampion->OnDash(Source);
}

void LoadChampion()
{
	std::string szChampion = GEntityList->Player()->ChampionName();

	//ADC
	if (szChampion == "Varus")
		pChampion = new cVarus;
	else if (szChampion == "Ashe")
		pChampion = new cAshe;
	else if (szChampion == "Draven")
		pChampion = new cDraven;
	else if (szChampion == "Tristana")
		pChampion = new cTristana;
	else if (szChampion == "Ezreal")
		pChampion = new cEzreal;
	// Midlane
	else if (szChampion == "Ahri")
		pChampion = new cAhri;
	else if (szChampion == "Lux")
		pChampion = new cLux;
	else if (szChampion == "Ziggs")
		pChampion = new cZiggs;
	else if (szChampion == "Xerath")
		pChampion = new cXerath;
	else if (szChampion == "TwistedFate")
		pChampion = new cTwistedFate;
	// Jungle
	else if (szChampion == "Olaf")
		pChampion = new cOlaf;
	else if (szChampion == "Nocturne")
		pChampion = new cNocturne;
	else if (szChampion == "Hecarim")
		pChampion = new cHecarim;
	else if (szChampion == "Rengar")
		pChampion = new cRengar;
	else if (szChampion == "Diana")
		pChampion = new cDiana;
	else if (szChampion == "Warwick")
		pChampion = new cWarwick;
	// Toplane
	else if (szChampion == "DrMundo")
		pChampion = new cDrMundo;
	else if (szChampion == "Maokai")
		pChampion = new cMaokai;
	else if (szChampion == "Poppy")
		pChampion = new cPoppy;
	else if (szChampion == "Malphite")
		pChampion = new cMalphite;
	else if (szChampion == "Kayle")
		pChampion = new cKayle;
	else if (szChampion == "Darius")
		pChampion = new cDarius;
	//else if (szChampion == "Shen")
		//pChampion = new cShen;
	// Support
	else if (szChampion == "Sona")
		pChampion = new cSona;
	else
	{
		GGame->PrintChat("Champion Not Supported");
	}	
	
	if (pChampion != nullptr)
	{
		GEventManager->AddEventHandler(kEventOnRender, OnRender);
		GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
		GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
		GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);		
		GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
		GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
		//GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
		//GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
		GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpell);
		GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
		GEventManager->AddEventHandler(kEventOnDestroyObject, OnDeleteObject);
		GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);
		GEventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
		GEventManager->AddEventHandler(kEventOnDash, OnDash);
	}
}

// Called when plugin is first loaded
PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	VersionCheck().RunVersionChecker();
	LoadChampion();
	pChampion->OnLoad();	
	GRender->NotificationEx(Color::LightBlue().Get(), 2, true, true, "Welcome to Lords & Federals AIO");
	GRender->NotificationEx(Color::LightBlue().Get(), 3, true, true, "News: Me and Federal decided to merge to bring you the best Scripts");
	
}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	//pChampion->OnUnLoad();

	MainMenu->Remove();
	
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);	
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);
	//GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	//GEventManager->RemoveEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpell);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDeleteObject);
	GEventManager->RemoveEventHandler(kEventOnExitVisible, OnExitVisible);
	GEventManager->RemoveEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->RemoveEventHandler(kEventOnDash, OnDash);
}
