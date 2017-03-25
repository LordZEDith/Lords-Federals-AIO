#include "SPlugin.h"


SPlugin::SPlugin(IMenu *main_menu)
	: m_Menu(main_menu)
{

}

MenuMgr& SPlugin::GetMenuMgr()
{
	return m_Menu;
}

SPlugin::~SPlugin()
{

}