#pragma once
#include "PluginSDK.h"
#include "MenuMgr.h"

class SPlugin
{
public:
	SPlugin(IMenu *);
	virtual ~SPlugin() = 0;
	virtual MenuMgr& GetMenuMgr();
protected:
	MenuMgr m_Menu;
};