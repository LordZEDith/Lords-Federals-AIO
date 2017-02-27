#pragma once
#include "PluginSDK.h"
#include <list>
#include <map>

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;
ISpell2* Q2;
ISpell2* W2;
ISpell2* E2;

ISpell* Smite;
ISpell* Ignite;


IMenu* HarassMenu;
IMenu* ComboMenu;
IMenu* JungleMenu;
IMenu* LaneClearMenu;
IMenu* KillStealMenu;
IMenu* Misc;
IMenu* QMenu;
IMenu* WMenu;
IMenu* EMenu;
IMenu* RMenu;
IMenu* Miscs;
IMenu* Drawings;
IMenu* Drawingss;



IMenu* MainMenu;
IMenu* HarassSettings;
IMenu* ComboSettings;
IMenu* KillstealSettings;
IMenu* MiscSettings;
IMenu* QSettings;
IMenu* WSettings;
IMenu* ESettings;
IMenu* RSettings;
IMenu* AxeSettings;
IMenu* DrawingSettings;
IMenu* LastHitSettings;
IMenu* LaneClearSettings;
IMenu* JungleClearSettings;
IMenu* SmiteSettings;
IMenu* SmiteJungle;
IMenu* SmiteChampion;
IMenu* SmiteDraw;
IMenu* BigMobs;
IMenu* SmallMobs;
IMenu* SkinsChange;

IMenuOption* MiscSkin;

IMenu* DmgInd;
IMenu* Keystones;
IMenu* AutoLevelers;
IMenu* InfoText;

IMenuOption* gotoAxeC;
IMenuOption* gotoAxeH;
IMenuOption* gotoAxelc;
IMenuOption* gotoAxeJ;
IMenuOption* gotoAxeRange;
IMenuOption* DrawAxe;
IMenuOption* DrawAxerange;
IMenuOption* gotoAxeMaxDist;
IMenuOption* MaxAxes;
IMenuOption* axeKill;
IMenuOption* axeTower;
IMenuOption* axeTower2;
IMenuOption* axeEnemy;
IMenuOption* axePro;

IMenuOption* ComboQ;
IMenuOption* AutoQ;
IMenuOption* FarmQ;
IMenuOption* HarassQ;
IMenuOption* HarassManaQ;
IMenuOption* ComboQH;
IMenuOption* QEnemies;
IMenuOption* QEnemies1;
IMenuOption* QGapCloser;
IMenuOption* QInterrupter;
IMenuOption* LaneClearQ;
IMenuOption* LastHitQ;
IMenuOption* CCedQ;
IMenuOption* RangeQ;
IMenuOption* RangeQlh;
IMenuOption* MinionsQ;
IMenuOption* JungleQ;
IMenuOption* CharmedQ;
IMenuOption* ComboEW;
IMenuOption* Troll;
IMenuOption* EinWall;
IMenuOption* goPassiveC;
IMenuOption* goPassiveLC;
IMenuOption* goPassiveH;
IMenuOption* goPassiveJ;
IMenuOption* LaneClearQLast;
IMenuOption* HarassWithFarm;

IMenuOption* ComboW;
IMenuOption* HarassW;
IMenuOption* FarmW;
IMenuOption* HarassManaW;
IMenuOption* LaneClearW;
IMenuOption* WGapCloser;
IMenuOption* WInterrupter;
IMenuOption* CCedW;
IMenuOption* RangeW;
IMenuOption* MinionsW;
IMenuOption* JungleW;
IMenuOption* slowW;
IMenuOption* AutoW;

IMenuOption* ComboE;
IMenuOption* ComboE2;
IMenuOption* ComboEA;
IMenuOption* HarassE;
IMenuOption* HarassManaE;
IMenuOption* FarmE;
IMenuOption* FarmEHit;
IMenuOption* AutoE;
IMenuOption* LaneClearE;
IMenuOption* LastHitE;
IMenuOption* LaneClearELast;
IMenuOption* EGapCloser;
IMenuOption* EInterrupter;
IMenuOption* CCedE;
IMenuOption* RangeE;
IMenuOption* MinionsE;
IMenuOption* JungleE;
IMenuOption* WAllyrisk;

IMenuOption* ComboR;
IMenuOption* ComboRKill;
IMenuOption* ComboREnemies;
IMenuOption* REnemies;
IMenuOption* AutoUlt;
IMenuOption* UltEnemies;
IMenuOption* UltPercent;
IMenuOption* UltPercent2;
IMenuOption* LaneClearR;
IMenuOption* CCedR;
IMenuOption* Raoe;
IMenuOption* RangeR;
IMenuOption* MinionsR;
IMenuOption* JungleR;
IMenuOption* RinRisk;
IMenuOption* SemiManualKey;
IMenuOption* inUnderTower;
IMenuOption* RWall;
IMenuOption* RMax;
IMenuOption* HarassEQ;
IMenuOption* RGapCloser;
IMenuOption* RInterrupter;
IMenuOption* Rsolo;
IMenuOption* RAllys;
IMenuOption* Rdelay;
IMenuOption* RBlock;

IMenuOption* Killsteal;
IMenuOption* KillstealQ;
IMenuOption* KillstealE;
IMenuOption* KillstealW;
IMenuOption* KillstealR;
IMenuOption* KillstealSmite;
IMenuOption* KillstealRange;

IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawEA;
IMenuOption* DrawR;
IMenuOption* DrawR2;
IMenuOption* DrawComboDamage;
IMenuOption* Drawkill;
IMenuOption* DrawTemp;

IMenuOption* HealthPercent;
IMenuOption* HealthQ;
IMenuOption* HealthW;
IMenuOption* HealthE;
IMenuOption* HealthR;
IMenuOption* HarassMana;
IMenuOption* LastHitMana;
IMenuOption* LaneClearMana;
IMenuOption* JungleMana;
IMenuOption* JungleHealth;
IMenuOption* JungleSmall;
IMenuOption* JungleBig;
IMenuOption* SaveMana;
IMenuOption* HealthHarass;
IMenuOption* HealthLaneClear;
IMenuOption* HealthLaneClearW;
IMenuOption* HealthLastHit;
IMenuOption* JungleHealthW;

IMenuOption* SmiteActive;
IMenuOption* SmiteBaron;
IMenuOption* SmiteDragon;
IMenuOption* SmiteRed;
IMenuOption* SmiteBlue;
IMenuOption* SmiteHerald;
IMenuOption* SmiteGromp;
IMenuOption* SmiteWolves;
IMenuOption* SmiteKrug;
IMenuOption* SmiteRazor;
IMenuOption* SmiteCrab;
IMenuOption* SmiteCombo;
IMenuOption* SmiteComboHP;
IMenuOption* SmiteRange;
IMenuOption* SmiteText;
IMenuOption* SmiteDamage;
IMenuOption* SmiteKeyToggle;
IMenuOption* SmiteAmmo;

IMenuOption* FastCombo;
IMenuOption* ComboA;
IMenuOption* ComboAA;
IMenuOption* Predic;
IMenuOption* StackMune;

IMenuOption* rStun;
IMenuOption* rBlind;
IMenuOption* rCharm;
IMenuOption* rFear;
IMenuOption* rKnockback;
IMenuOption* rKnockup;
IMenuOption* rTaunt;
IMenuOption* rSlow;
IMenuOption* rSilence;
IMenuOption* rDisarm;
IMenuOption* rSnare;
IMenuOption* useRTF;

IMenuOption* UseItems;
IMenuOption* AutoSmites;
IMenuOption* AutoHarass;
IMenuOption* AntiDash;
IMenuOption* CheckShield;
IMenuOption* AntiMelee;
IMenuOption* AntiGrab;

IMenuOption* QD;
IMenuOption* WD;
IMenuOption* ED;
IMenuOption* RD;
IMenuOption* IG;
IMenuOption* Thunderlords;
IMenuOption* Fervor;
IMenuOption* ColorR;
IMenuOption* ColorG;
IMenuOption* ColorB;
IMenuOption* AA;

IMenuOption* AutoLevelerCheck;
IMenuOption* AutoLevelerStart;
IMenuOption* AutoLevel1;
IMenuOption* AutoLevel2;
IMenuOption* AutoLevel3;
IMenuOption* AutoLevel4;

IMenuOption* Teamate1;
IMenuOption* Teamate2;
IMenuOption* Teamate3;
IMenuOption* Teamate4;
IMenuOption* Teamate5;

IMenuOption* PickYellows;
IMenuOption* PickRedss;
IMenuOption* PickBluess;

IMenuOption* Debug;

IInventoryItem* Tiamat;
IInventoryItem* Hydra;
IInventoryItem* Ravenous;

Vec2 HeroCoordsVec2;
Vec3 lastQpos;
Vec3 lastQpos2;
Vec3 MissileEndPos;
Vec3 extz;

IUnit* Teamate01;
IUnit* Teamate02;
IUnit* Teamate03;
IUnit* Teamate04;
IUnit* Teamate05;
IUnit* QMissile;
IUnit* EMissile;

//std::vector<IUnit*> axeList;
std::list<IUnit*> axeListTeste;
std::map<int, IMenuOption*> MenuDontUlt;

bool FoundSmite = false;
int tempaxe = 0;
bool temp = false;
int cnumber = 0;
float DragonDmg = 0;
double DragonTime = 0;
int QLastCast = 0;

short keystate;
bool smiteKeyWasDown = false;
bool KeyWasDown = false;

float RCastSpell = 0;
Vec3 Rposition;
const char* LastSpellName;
int LastSpellTime = 0;

enum HitChance; 

//ZIGGS MENU
IMenu* FarmSettings;
IMenuOption* farmQout;
IMenuOption* farmQ;
IMenuOption* farmE;
IMenuOption* jungleQ;
IMenuOption* jungleE;
IMenuOption* jungleW;
IMenuOption* minManaLC;
IMenuOption* minManaJ;
IMenuOption* useQlcMinions;


IMenuOption* autoQ;
IMenuOption* harassQ;
IMenuOption* minManaQHarass;


IMenuOption* autoW;
IMenuOption* minManaWHarass;
IMenuOption* interupterW;
IMenuOption* turretW;
IMenuOption* jumpW;


IMenuOption* autoE;
IMenuOption* comboE;
IMenuOption* gapcloserE;
IMenuOption* opsE;
IMenuOption* telE;
IMenuOption* minManaE;


IMenuOption* autoR;
IMenuOption* minHpRTarget;
IMenuOption* Rcc;

IMenuOption* keyToR;
IMenuOption* killstealR;
IMenuOption* minRangeKillR;
IMenuOption* maxRangeKillR;
IMenuOption* AutoRjungle;
IMenuOption* Rdragon;
IMenuOption* Rbaron;
IMenuOption* Rred;
IMenuOption* Rblue;
IMenuOption* Rally;


IMenuOption* noti;



ISpell2* Q1;
ISpell2* Q3;

Vec3 prediction(0, 0, 0);
Vec3 sendQHere(0, 0, 0);


 

 