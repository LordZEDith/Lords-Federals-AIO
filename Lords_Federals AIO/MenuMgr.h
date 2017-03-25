#pragma once
#include <map>
#include "PluginSDK.h"

class MenuMgr
{
public:
	MenuMgr();
	MenuMgr(IMenu *);
	~MenuMgr();
	MenuMgr& AddSubMenu(const std::string& title, const std::string& name);
	IMenuOption *AddCheckBox(const std::string& title, const std::string& name, bool value);
	IMenuOption *AddInteger(const std::string& title, const std::string& name, int min, int max, int val);
	IMenuOption *AddFloat(const std::string& title, const std::string& name, float min, float max, float val);
	IMenuOption *AddColor(const std::string& title, const std::string& name, DWORD val);
	IMenuOption *AddColor(const std::string& title, const std::string& name, float R, float G, float B, float A);
	IMenu *GetMainMenu() const;
	MenuMgr& GetMenu(const std::string& name);
	IMenuOption *GetOption(const std::string& name);
	void SetMenu(IMenu *menu);
private:
	IMenu *m_MainMenu;
	std::map<std::string, MenuMgr> m_SubMenus;
	std::map<std::string, IMenuOption *> m_MenuOpts;
};

