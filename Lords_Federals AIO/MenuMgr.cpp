#include "MenuMgr.h"


MenuMgr::MenuMgr()
	: m_MainMenu(nullptr)
{

}

MenuMgr::MenuMgr(IMenu *main)
	: m_MainMenu(main)
{

}


MenuMgr::~MenuMgr()
{

}

MenuMgr& MenuMgr::AddSubMenu(const std::string& title, const std::string& name)
{
	auto menu = m_MainMenu->AddMenu(title.c_str());
	m_SubMenus[name] = menu;
	return m_SubMenus[name];
}

IMenuOption *MenuMgr::AddCheckBox(const std::string& title, const std::string& name, bool value)
{
	auto opt = m_MainMenu->CheckBox(title.c_str(), value);
	m_MenuOpts[name] = opt;
	return opt;
}

IMenuOption *MenuMgr::AddInteger(const std::string& title, const std::string& name, int min, int max, int val)
{
	auto opt = m_MainMenu->AddInteger(title.c_str(), min, max, val);
	m_MenuOpts[name] = opt;
	return opt;
}

IMenuOption *MenuMgr::AddFloat(const std::string& title, const std::string& name, float min, float max, float val)
{
	auto opt = m_MainMenu->AddFloat(title.c_str(), min, max, val);
	m_MenuOpts[name] = opt;
	return opt;
}

IMenuOption *MenuMgr::AddColor(const std::string& title, const std::string& name, DWORD val)
{
	auto opt = m_MainMenu->AddColor(title.c_str(), val);
	m_MenuOpts[name] = opt;
	return opt;
}

IMenuOption *MenuMgr::AddColor(const std::string& title, const std::string& name, float R, float G, float B, float A)
{
	auto opt = m_MainMenu->AddColor(title.c_str(), R, G, B, A);
	m_MenuOpts[name] = opt;
	return opt;
}

IMenu *MenuMgr::GetMainMenu() const
{
	return m_MainMenu;
}

MenuMgr& MenuMgr::GetMenu(const std::string& name)
{
	return m_SubMenus[name];
}

IMenuOption *MenuMgr::GetOption(const std::string& name)
{
	return m_MenuOpts[name];
}

void MenuMgr::SetMenu(IMenu *menu)
{
	if (m_MainMenu)
	{
		throw std::exception("main menu already set");
	}
	m_MainMenu = menu;
}