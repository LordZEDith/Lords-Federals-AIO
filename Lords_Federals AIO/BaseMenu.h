#pragma once
#include "PluginSDK.h"
#include "Template.h"
#include "Geometry.h"
#include <list>
#include <map>


SArray<IUnit*> IvernBush;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;
ISpell2* Q2;
ISpell2* W2;
ISpell2* E2;
ISpell2* R2;
ISpell2* QE;

ISpell* Smite;
ISpell* Smites;
ISpell* Ignite;
ISpell* Flash;
ISpell* Wards;

IMenu* HarassMenu;
IMenu* ItemMenu;
IMenu* ClearMenu;
IMenu* DrawMenu;
IMenu* ComboMenu;
IMenu* JungleMenu;
IMenu* LaneClearMenu;
IMenu* KillStealMenu;
IMenu* Misc;
IMenu* QMenu;
IMenu* WMenu;
IMenu* EMenu;
IMenu* EMenuGap;
IMenu* RMenu;
IMenu* RMenu2;
IMenu* Miscs;
IMenu* Drawings;
IMenu* Drawingss;
IMenu* GankSettings;
IMenu* Jump2Settings;
IMenu* FarmMenu;
IMenu* FleeMode;
IMenu* WhiteList;
IMenu* WhiteListHarass;

IMenu* MainMenu;
IMenu* HarassSettings;
IMenu* ComboSettings;
IMenu* KillstealSettings;
IMenu* fedMiscSettings;
IMenu* InsecSettings;
IMenu* QSettings;
IMenu* WSettings;
IMenu* W2Settings;
IMenu* ESettings;
IMenu* RSettings;
IMenu* AxeSettings;
IMenu* DrawingSettings;
IMenu* LastHitSettings;
IMenu* LaneClearSettings;
IMenu* JungleClearSettings;
IMenu* SmiteSettings;
IMenu* TrinketSettings;
IMenu* SmiteJungle;
IMenu* SmiteChampion;
IMenu* SmiteDraw;
IMenu* BigMobs;
IMenu* SmallMobs;
IMenu* SkinsChange;
IMenu* KS;

IMenu* Draw;
IMenu* WOpt;
IMenu* ROpt;
IMenu* Farm;
IMenu* Activator;


// Toxic
IMenu* EmoteSpam;
IMenu* GameChat;
IMenu* GameEvents;
IMenu* GameStart;
IMenu* GameEnd;

IMenuOption* EmoteMode;
IMenuOption* EmoteOnKill;
IMenuOption* EmoteOnAssis;
IMenuOption* EmoteOnDeath;
IMenuOption* EmoteNearDead;

IMenuOption* cMode;
IMenuOption* Greeting;
IMenuOption* SayGreeting;
IMenuOption* MuteAll;
IMenuOption* CDelay;

IMenuOption* Ending;
IMenuOption* SayEnding;
IMenuOption* QuitGame;
IMenuOption* QuitDelay;

IMenuOption* AutoTrapFull;
IMenuOption* ManaFullAmmo;
IMenuOption* AutoInGrass;
IMenuOption* AutoInTowers;

int LastEmoteSpam = 0;
int MyKills = 0;
int MyAssits = 0;
int MyDeaths = 0;
int LastDeathNetworkId = 0;

bool onEndTriggerd;
bool onStartDone;
bool onStartTriggerd;

// F Toxic

IMenuOption* fedMiscSkin;
IMenuOption* fedMiscSkinON;

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
IMenuOption* axeSoften;
IMenuOption* axeMode;
IMenuOption* UseWToAxe;
IMenuOption* gotoPosition;

IMenuOption* ComboQ;
IMenuOption* ComboQA;
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
IMenuOption* LaneClearQ2;
IMenuOption* LastHitQ;
IMenuOption* CCedQ;
IMenuOption* RangeQ;
IMenuOption* RangeQlh;
IMenuOption* MinionsQ;
IMenuOption* JungleQ;
IMenuOption* CharmedQ;
IMenuOption* KSQ;
IMenuOption* ComboEW;
IMenuOption* Troll;
IMenuOption* EinWall;
IMenuOption* goPassiveC;
IMenuOption* goPassiveLC;
IMenuOption* goPassiveH;
IMenuOption* goPassiveJ;
IMenuOption* LaneClearQLast;
IMenuOption* HarassWithFarm;
IMenuOption* QHelp;
IMenuOption* onlyReady;
IMenuOption* QAfterAA;
IMenuOption* QAntiMelee;
IMenuOption* QCancelAnimation;
IMenuOption* AimMissile;
IMenuOption* FastQ;

IMenuOption* QMaxRange;
IMenuOption* QAlways;
IMenuOption* HarassQmin;
IMenuOption* EAlways;
IMenuOption* HarassEmin;

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
IMenuOption* farmW;
IMenuOption* slowW;
IMenuOption* AutoW;
IMenuOption* WAOE;
IMenuOption* ComboWRengar;
IMenuOption* ComboWAlly;
IMenuOption* ComboWSelf;

IMenuOption* ComboE;
IMenuOption* ComboERange;
IMenuOption* EKS;
IMenuOption* QKS;
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
IMenuOption* JungleEBig;
IMenuOption* WAllyrisk;
IMenuOption* ECountEnemy;
IMenuOption* ESafety;
IMenuOption* EBypass;
IMenuOption* EBypassTower;
IMenuOption* dJumpEnabled;
IMenuOption* JEDelay;
IMenuOption* JumpMode;
IMenuOption* SaveH;
IMenuOption* Noauto;
IMenuOption* jCursor;
IMenuOption* SecondJump;
IMenuOption* jCursor2;
IMenuOption* JumpDraw;
IMenuOption* EUnderTowerAttack;
IMenuOption* IgniteKS;
IMenuOption* EOrder;
IMenuOption* PushDistance;
IMenuOption* EPassive;

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
IMenuOption* FleeKey;
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
IMenuOption* rCount;
IMenuOption* RMode;
IMenuOption* RPush;
IMenuOption* REnemyRange;
IMenuOption* RAllysRange;

//Dash
IMenuOption* EnemyCheck;
IMenuOption* WallCheck;
IMenuOption* TurretCheck;
IMenuOption* AAcheck;
// Dash

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
IMenuOption* DrawQ2;
IMenuOption* DrawE2;
IMenuOption* DrawTime;
IMenuOption* DrawTimex;
IMenuOption* DrawTimey;
IMenuOption* DrawWard;
IMenuOption* DrawEsca;
IMenuOption* DrawEscaW;
IMenuOption* DrawSelect;
IMenuOption* DrawPosInsec;
IMenuOption* DrawNear;
IMenuOption* WMinions;
IMenuOption* DrawPetStatus;
IMenuOption* DrawECustom;
IMenuOption* DrawCaitSpots;

IMenuOption* HealthPercent;
IMenuOption* FarmMana;
IMenuOption* HealthQ;
IMenuOption* HealthW;
IMenuOption* HealthAutoW;
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
IMenuOption* SmiteLowHp;
IMenuOption* LowHPpct;

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
IMenuOption* RHP;

IMenuOption* UseItems;
IMenuOption* AutoSmites;
IMenuOption* AutoHarass;
IMenuOption* AntiDash;
IMenuOption* CheckShield;
IMenuOption* AntiMelee;
IMenuOption* AntiMeleeMode;
IMenuOption* AntiGrab;
IMenuOption* AutoShielded;
IMenuOption* minAutoShield;
IMenuOption* AutoPotion;
IMenuOption* TrinketBush;
IMenuOption* TrinketBushdelay;
IMenuOption* AntiRengar;
IMenuOption* AntiKhazix;
IMenuOption* AntiAlistar;
IMenuOption* AntiFlash;
IMenuOption* AntiKindred;
IMenuOption* AntiSpells;
IMenuOption* BuyBlueTrinket;
IMenuOption* StartTrinket;
IMenuOption* ChangeTrinket;
IMenuOption* FleeQ;
IMenuOption* FleeE;
IMenuOption* FleeR;

IMenuOption* useProto;
IMenuOption* useZhonyas;
IMenuOption* ZhonyasHP;
IMenuOption* zzRot;

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

IMenuOption* hQ;
IMenuOption* hW;
IMenuOption* hE;
IMenuOption* hMana;

IMenuOption* laneQ;
IMenuOption* laneW;
IMenuOption* laneE;
IMenuOption* clearMana;
IMenuOption* QMinions;

IMenuOption* DrawDisabled;

IMenuOption* Interrupt;
IMenuOption* antigap;

IMenuOption* Debug;

IInventoryItem* Tiamat;
IInventoryItem* Hydra;
IInventoryItem* Ravenous;
IInventoryItem* Ward1;
IInventoryItem* Ward2;
IInventoryItem* Ward3;
IInventoryItem* Ward4;
IInventoryItem* Ward5;
IInventoryItem* Ward6;
IInventoryItem* Ward7;
IInventoryItem* Ward8;
IInventoryItem* Ward9;
IInventoryItem* Ward10;
IInventoryItem* Ward11;
IInventoryItem* Ward12;
IInventoryItem* Ward13;
IInventoryItem* Ward14;
IInventoryItem* Ward15;
IInventoryItem* Ward16;
IInventoryItem* myWards;
IInventoryItem* zzRots;
IInventoryItem* TrinketY;
IInventoryItem* TrinketR;
IInventoryItem* TrinketROracle;
IInventoryItem* TrinketB;

Vec2 HeroCoordsVec2;
Vec3 lastQpos;
Vec3 lastQpos2;
Vec3 MissileEndPos;
Vec3 extz;
Vec3 WardPos;
Vec3 TrinketPos;
Vec3 JumpPos;
Vec3 InsecST;
Vec3 InsecED;
Vec3 InsecPOS;
Vec3 TestPOS;
Vec3 BarrilQ;
Vec3 ClickPOS;
Vec3 JungleSpot;
Vec3 JumpPos1;
Vec3 JumpPos2;
Vec3 AimQ;
Vec3 EndPos;

IUnit* Teamate01;
IUnit* Teamate02;
IUnit* Teamate03;
IUnit* Teamate04;
IUnit* Teamate05;
IUnit* QMissile;
IUnit* EMissile;
IUnit* CheckQKillable;

struct XayahFeathers
{	
	IUnit* Source;
	IUnit* Target;	
};

//std::vector<IUnit*> axeList;
std::list<IUnit*> axeListTeste;
SArray<IUnit*> DravenAxes;
SArray<IUnit*> SkillMissiles;
SArray<IUnit*> SyndraOrbs;
SArray<IUnit*> SyndraOrbsIddle;

SArray<XayahFeathers> XayahReturn;
SArray<Vec3> Retorno;
std::map<int, IMenuOption*> MenuDontUlt;
std::map<int, IMenuOption*> ChampionUse;
std::map<int, IMenuOption*> ChampionUseW;
std::map<int, IMenuOption*> ChampionAntiMelee;
std::map<int, IMenuOption*> GapCloserList;
std::map<int, IMenuOption*> ChampionUseE;

bool FoundSmite = false;
bool FoundSmiteQ = false;
bool FoundFlash = false;
bool FoundIgnite = false;
int tempaxe = 0;
bool temp = false;
int cnumber = 0;
float DragonDmg = 0;
double DragonTime = 0;
int QLastCast = 0;
bool WSpellStatus;
int LastWTick;
int LastQTick;
int LastQ2Tick;
int LastRTick;
int LastETick;
int LastClick;
int LastWardTime;
int LastFlashTime;
int LastSpellTick;
int LastAATick;
int WObjectNetworkId = -1;
bool EhWard;
bool testflash;
bool Jumping;
bool EvolvedQ, EvolvedW, EvolvedE, EvolvedR;
bool justQ;
bool checkVisible;
bool putWard;
bool putTrinket;
bool wardjump;
bool ColoqueiWard;

short keystate;
short keystate2;
short keystate3;
bool smiteKeyWasDown = false;
bool harassKeyWasDown = false;
bool comboKeyWasDown = false;
bool KeyWasDown = false;

float RCastSpell = 0;
Vec3 Rposition;
const char* LastSpellName;
int LastSpellTime = 0;
int timeTrinket = 0;

enum HitChance; 

//Lee
bool castQAgain;
int PassiveStacksNum;
bool isDashingQ;
bool escActive;
bool escActivedraw;
int LastWard;
int LastCheckWard;
int LastPress;
bool goWard = false;
int mypredic;
bool WardCheck = true;
bool enemyscheck;
bool goUltimate = false;
bool goInsecUnder = false;
bool canAttack = false;
bool EQcastNow = false;
bool CheckAttack = false;

IMenuOption* PassiveStacks;
IMenuOption* jPassiveStacks;
IMenuOption* lPassiveStacks;
IMenuOption* StartComboKey;
IMenuOption* TrapKey;
IMenuOption* TrapDelayDistance;
IMenuOption* GankComboKey;
IMenuOption* InstaFlashKey;
IMenuOption* InsecKey;
IMenuOption* EscapeKey;
IMenuOption* EscapeMode;
IMenuOption* WardJumpKey;
IMenuOption* QSemiManualKey;
IMenuOption* WSemiManualKey;
IMenuOption* ESemiManualKey;
IMenuOption* RSemiManualKey;
IMenuOption* OrbwalkSemiKey;
IMenuOption* WardMax;
IMenuOption* JumpMinion;
IMenuOption* JumpAllys;
IMenuOption* kickKill;
IMenuOption* kickHit;
IMenuOption* kickBehind;
IMenuOption* SmiteQ1;
IMenuOption* clickInsec;
IMenuOption* ExtraDist;
IMenuOption* jumpMinion;
IMenuOption* jumpAliado;
IMenuOption* jumpWards;
IMenuOption* AutoStartKill;
IMenuOption* AutoStartWard;
IMenuOption* useFlash;
IMenuOption* InsecSelect;
IMenuOption* InsecOrbwalk;
IMenuOption* Flashdistance;
IMenuOption* UseWardgap;
IMenuOption* UseFlashgap;
IMenuOption* InsecTo;
IMenuOption* InsecUnder;
IMenuOption* Gankward;
IMenuOption* GankQ;
IMenuOption* GankR;
IMenuOption* ComboChange;
IMenuOption* ChangetoCombo;
IMenuOption* DrawGankCombo;

IMenuOption* ClickKeyPos;
IMenuOption* ClickExpire;

IMenuOption* KickAndFlash;
std::string InsecText = "";
std::string InsecTextQ2 = "";
std::string InsecType = "";
std::string LastSpell = "";

int InsecTime;
int CheckTime;

IUnit* otherT = nullptr;
IUnit* otherTM = nullptr;
IUnit* AliadoPos = nullptr;
IUnit* AllySoloPos = nullptr;
IUnit* TorrePos = nullptr;
IUnit* ComboTarget = nullptr;
IUnit* SmiteQu = nullptr;
IUnit* GetTarget = nullptr;
IUnit* GetTargetDraw = nullptr;
IUnit* TargetUnder = nullptr;
IUnit* jMonster = nullptr;
IUnit* BaseTarget = nullptr;
IUnit* WardObj = nullptr;

// Elise
float _humQcd, _humWcd, _humEcd;
float _spidQcd, _spidWcd, _spidEcd;
float _humaQcd, _humaWcd, _humaEcd;
float _spideQcd, _spideWcd, _spideEcd;
float _Rcd, _ultcd;

IMenuOption* Qspider;
IMenuOption* Wspider;
IMenuOption* Espider;
IMenuOption* JungleQspider;
IMenuOption* JungleWspider;
IMenuOption* JungleEspider;

ITexture* tHumanQ;
ITexture* tHumanW;
ITexture* tHumanE;
ITexture* tSpiderQ;
ITexture* tSpiderW;
ITexture* tSpiderE;
ITexture* tUltimate;

ITexture* cdtHumanQ;
ITexture* cdtHumanW;
ITexture* cdtHumanE;
ITexture* cdtSpiderQ;
ITexture* cdtSpiderW;
ITexture* cdtSpiderE;
ITexture* cdtUltimate;

Vec2 Resolution;

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
IMenuOption* AutoStun;
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
IMenuOption* AutoR;
IMenuOption* AutoRHealth;
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

IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* Zhonyas;
IInventoryItem* Protobelt;
IInventoryItem* GhostBlade;
IInventoryItem* BORK;
IInventoryItem* BilgewaterCut;
IInventoryItem* titHydra;
IInventoryItem* ravHydra;
IInventoryItem* usetimat;

IMenuOption* GBlade;
IMenuOption* BOTRK;
IMenuOption* BilgeCut;
IMenuOption* useIgnite;
IMenuOption* tHydra;
IMenuOption* rHydra;
IMenuOption* tiamat;

IMenuOption* PingLoc;
IMenuOption* RPingR;
IMenuOption* PingR;

ISpell2* Q1;
ISpell2* Q3;

Vec3 prediction(0, 0, 0);
Vec3 sendQHere(0, 0, 0);

float Wtime = 0, Wtime2 = 0;
float QMANA, WMANA, EMANA, RMANA;

static float qCasted, wCasted, eCasted;

IUnit* RMissile;
IUnit* WMissile;
IUnit* WMissile2;



//static int  qMana = 70 + (GEntityList->Player()->GetSpellLevel(kSlotQ) * 10);
//static int  wMana = 60 + (GEntityList->Player()->GetSpellLevel(kSlotW) * 10);
//static int  eMana = 55 + (GEntityList->Player()->GetSpellLevel(kSlotE) * 5);


IMenu*dsettings, *csettings, *Hsettings, *Lcsettings, *Msettings;

//dsettings
IMenuOption* drawqq, *drawee, *drawrr, *drawcombo, *rDamage;
//csettings
IMenuOption* useq, *usew, *usee, *user, *userindanger, *furyMode;
//Hsettings
IMenuOption* useqH, *usewH, *useCH, *donteqwebtower;
//Misc Setting
IMenuOption* useHydra;


ISpell2* Ignites;

static float lastE;
static Vec3 lastEpos;
static bool wChancel = false;

bool BlockE = false;
ISpell2* Ward;

bool eCounterStrike = false;
 

 