#pragma once
#include "PluginSDK.h"
#include "BaseMenu.h"
#include <string>


inline double GetCorrectDamage(IUnit* target)
{
	auto BaseDamage = static_cast<float>(GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR));
	auto CalculatedDamage = BaseDamage;
	return GDamage->CalcPhysicalDamage(GEntityList->Player(), target, CalculatedDamage);
}

inline double GetRDamage(IUnit* target)
{
	if (target == nullptr || !target->IsHero() || !target->HasBuff("willrevive"))
		return 0;

	float BaseDamage = 0;
	 
	if (Q->IsReady() && Q->ManaCost() < GEntityList->Player()->GetMana())
	{
		BaseDamage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
	}

	if (W->IsReady() && W->ManaCost() < GEntityList->Player()->GetMana())
	{
		BaseDamage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW);
	}

	if (E->IsReady() && E->ManaCost() < GEntityList->Player()->GetMana())
	{
		BaseDamage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE);
	}

	if (R->IsReady() && R->ManaCost() < GEntityList->Player()->GetMana())
	{
		BaseDamage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR);
	}

	if (GEntityList->Player()->HasBuff("SummonerExhaust"))
		BaseDamage *= 0.6;

	if (GEntityList->Player()->HasBuff("urgotentropypassive"))
		BaseDamage *= 0.85;

	auto bondofstoneBuffCount = target->GetBuffCount("MasteryWardenOfTheDawn");
	if (bondofstoneBuffCount > 0)
		BaseDamage *= 1 - 0.06 * bondofstoneBuffCount;

	if (target->HasBuff("FerociousHowl"))
		BaseDamage *= 0.6 - std::vector<double>({ 0.1, 0.2, 0.3 }).at(target->GetSpellBook()->GetLevel(kSlotR) - 1);

	if (target->HasBuff("Tantrum"))
		BaseDamage *= std::vector<double>({ 2, 4, 6, 8, 10 }).at(target->GetSpellBook()->GetLevel(kSlotE) - 1);

	if (target->HasBuff("BraumShieldRaise"))
		BaseDamage *= std::vector<double>({ 0.3, 0.325, 0.35, 0.375, 0.4 }).at(target->GetSpellBook()->GetLevel(kSlotE) - 1);

	if (target->HasBuff("GragasWSelf"))
		BaseDamage *= std::vector<double>({ 0.1, 0.12, 0.14, 0.16, 0.18 }).at(target->GetSpellBook()->GetLevel(kSlotW) - 1);

	auto phantomdancerBuff = target->GetBuffDataByName("itemphantomdancerdebuff");
	if (phantomdancerBuff != nullptr && GBuffData->GetCaster(phantomdancerBuff) == target)
		BaseDamage *= 0.88;

	if (target->HasBuff("GalioIdolOfDurand"))
		BaseDamage *= 0.5;

	if (target->HasBuff("GarenW"))
		BaseDamage *= 0.7;

	if (target->HasBuff("KatarinaEReduction"))
		BaseDamage *= 0.85;

	/*if (target->ChampionName() == "Moredkaiser")
		BaseDamage *= target->ManaPercent;

	if (target->HasBuff("BlitzcrankManaBarrierCD") && target->HasBuff("ManaBarrier"))
		BaseDamage *= (target->ManaPercent/2);*/
	
	return (float)BaseDamage;
}

inline bool CheckTarget(IUnit* target)
{
	if (target != nullptr && !target->IsDead() && !target->IsInvulnerable() && target->IsVisible())
	{
		return true;
	}
	return false;
}

inline double GetQAttackDamage(IUnit* target)
{
	std::vector<double> AttackDamage = { 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80, 90, 110, 130, 150, 170, 190, 210 };

	return AttackDamage[GEntityList->Player()->GetLevel() - 1] + GEntityList->Player()->TotalMagicDamage() * 0.5 + GEntityList->Player()->TotalPhysicalDamage();
}

inline double GetDamageTeste(IUnit* target, bool CalCulateAttackDamage = true,
	bool CalCulateQDamage = true, bool CalCulateWDamage = true,
	bool CalCulateEDamage = true, bool CalCulateRDamage = true)
{
	if (CheckTarget(target))
	{
		double Damage = 0;
		std::string ChampionName = GEntityList->Player()->ChampionName();
		std::string TargetName = target->ChampionName();		

		if(GEntityList->Player()->GetSpellSlot("SummonerDot") != kSlotUnknown)
		{
			Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("SummonerDot"), 600);
		}

		if (CalCulateAttackDamage)
		{
			Damage += GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false);
		}

		if (CalCulateQDamage)
		{			
			if (ChampionName == "Ahri")
			{
				Damage += Q->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) * 2 : 0;
			}
			else if (ChampionName == "Viktor")
			{
				Damage += GEntityList->Player()->HasBuff("ViktorPowerTransferReturn") ? GetQAttackDamage(target) : 0;
			}
			else if (ChampionName == "Vladimir")
			{
				Damage += Q->IsReady() ? GEntityList->Player()->HasBuff("vladimirqfrenzy") ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) * 2 : GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) : 0;
			}			
			else
			{
				Damage += Q->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) : 0;
			}
		}

		if (CalCulateWDamage)
		{
			Damage += W->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotW) : 0;
		}

		if (CalCulateEDamage)
		{
			Damage += E->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) : 0;
		}

		if (CalCulateRDamage)
		{
			if (ChampionName == "Ahri")
			{
				Damage += R->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) * 3 : 0;
			}
			else
			{
				Damage += R->IsReady() ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR) : 0;
			}
		}

		if (GEntityList->Player()->GetSpellSlot("SummonerDot") != kSlotUnknown  && Ignite->IsReady())
		{
			Damage += 50 + 20 * GEntityList->Player()->GetLevel() - (target->HPRegenRate() / 5 * 3);
		}

		if (TargetName == "Moredkaiser")
			Damage -= target->GetMana();

		// exhaust
		if (GEntityList->Player()->HasBuff("SummonerExhaust"))
			Damage = Damage * 0.6f;

		// blitzcrank passive
		if (target->HasBuff("BlitzcrankManaBarrierCD") && target->HasBuff("ManaBarrier"))
			Damage -= target->GetMana() / 2;

		// kindred r
		if (target->HasBuff("KindredRNoDeathBuff"))
			Damage = 0;

		// tryndamere r
		if (target->HasBuff("UndyingRage") && GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("UndyingRage")) - GGame->Time() > 0.3)
			Damage = 0;

		// kayle r
		if (target->HasBuff("JudicatorIntervention"))
			Damage = 0;

		// zilean r
		if (target->HasBuff("ChronoShift") && GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("ChronoShift")) - GGame->Time() > 0.3)
			Damage = 0;

		// fiora w
		if (target->HasBuff("FioraW"))
			Damage = 0;

		return Damage;
	}
	return 0;
}


inline bool ToggleSpeall(int Spellslote)
{
	if (GEntityList->Player()->GetSpellBook()->GetToggleState(Spellslote) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool InFountain(IUnit* Source)
{
	if (Source->GetPosition().x < 1276 && Source->GetPosition().z < 1344) { return true; }
	if (Source->GetPosition().x > 13540 && Source->GetPosition().z > 13470) { return true; }

	return false;
}

inline bool IsUnderTurret(IUnit* source)
{
	for (auto turret : GEntityList->GetAllTurrets(false, true))
	{
		if (source->IsValidTarget(turret, 900) && turret->GetHealth() >= 1)
			return true;
	}

	return false;
}

inline bool FoundEnemies(IUnit* source, float range)
{
	for (auto enemys : GEntityList->GetAllHeros(false, true))
	{
		if (source->IsValidTarget(enemys, range))
			return true;
	}

	return false;
}

inline int CountEnemy(Vec3 Location, int range)
{
	int Count = 0;

	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if ((Enemy->GetPosition() - Location).Length() < range && Enemy->IsValidTarget() && !Enemy->IsDead())
		{
			Count++;
		}
	}
	return (Count);
}

inline int CountAlly(Vec3 Location, int range)
{
	int Count = 0;

	for (auto Ally : GEntityList->GetAllHeros(true, false))
	{
		if ((Ally->GetPosition() - Location).Length() < range && Ally->IsValidTarget() && !Ally->IsDead() && Ally != GEntityList->Player())
		{
			Count++;
		}
	}
	return (Count);
}

inline int GetEnemiesInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GEntityList->Player()->IsValidTarget(enemy, range))
			enemies++;
	}
	return enemies;
}

inline float GetDistance(IUnit* source, IUnit* target)
{
	auto x1 = source->GetPosition().x;
	auto x2 = target->GetPosition().x;
	auto y1 = source->GetPosition().y;
	auto y2 = target->GetPosition().y;
	auto z1 = source->GetPosition().z;
	auto z2 = target->GetPosition().z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
}


inline int GetMinionsInRange(Vec3 Position, float Range)
{
	auto mingons = GEntityList->GetAllMinions(false, true, false);
	auto mingonsInRange = 0;
	for (auto mingon : mingons)
	{
		//counts enemies checking if they are enemy heroes and are within radius parameter
		if (mingon != nullptr && mingon->IsValidTarget() && !mingon->IsDead())
		{
			auto mingonDistance = (mingon->GetPosition() - Position).Length();
			if (mingonDistance < Range)
			{
				mingonsInRange++;
			}
		}
	}
	return mingonsInRange;
}

inline bool FoundMinionsNeutral(float range)
 {
	 for (auto Minions : GEntityList->GetAllMinions(false, false, true))
	 {
		 if (GEntityList->Player()->IsValidTarget(Minions, range))
			 return true;
	 }

	 return false;
 }

inline bool FoundMinions(float range)
 {
	 for (auto Minions : GEntityList->GetAllMinions(false, true, false))
	 {
		 if (GEntityList->Player()->IsValidTarget(Minions, range))
			 return true;
	 }

	 return false;
 }

inline int CountMinions(Vec3 Location, int range)
 {
	 int Count = 0;

	 for (auto Minions : GEntityList->GetAllMinions(false, true, false))
	 {
		 if ((Minions->GetPosition() - Location).Length() < range && Minions->IsValidTarget() && !Minions->IsDead())
		 {
			 Count++;
		 }
	 }
	 return (Count);
 }

inline int CountMinionsAlly(Vec3 Location, int range)
{
	int Count = 0;

	for (auto Minions : GEntityList->GetAllMinions(true, false, false))
	{
		if ((Minions->GetPosition() - Location).Length() < range && Minions->IsValidTarget() && !Minions->IsDead())
		{
			Count++;
		}
	}
	return (Count);
}

inline int CountMinionsWithBuff(Vec3 Location, int range, const char* buff)
{
	int Count = 0;

	for (auto Minions : GEntityList->GetAllMinions(false, true, false))
	{
		if ((Minions->GetPosition() - Location).Length() < range && Minions->IsValidTarget() && !Minions->IsDead() && Minions->HasBuff(buff))
		{
			Count++;
		}
	}
	return (Count);
}

inline int CountMinionsNeutral(Vec3 Location, int range)
{
	int Count = 0;

	for (auto Minions : GEntityList->GetAllMinions(false, false, true))
	{
		if ((Minions->GetPosition() - Location).Length() < range && Minions->IsValidTarget() && !Minions->IsDead())
		{
			Count++;
		}
	}
	return (Count);
}



inline float GetDistanceVectors(Vec3 from, Vec3 to)
{
	float x1 = from.x;
	float x2 = to.x;
	float y1 = from.y;
	float y2 = to.y;
	float z1 = from.z;
	float z2 = to.z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
}

inline bool IsUnderTurretPos(Vec3 source)
{
	for (auto turret : GEntityList->GetAllTurrets(false, true))
	{
		if (GetDistanceVectors(turret->GetPosition(), source) < 900)
			return true;
	}

	return false;
}

inline bool IsUnderTurretPosAlly(Vec3 source)
{
	for (auto turret : GEntityList->GetAllTurrets(true, false))
	{
		if (GetDistanceVectors(turret->GetPosition(), source) < 800)
			return true;
	}

	return false;
}

static bool IsKeyDown(IMenuOption *menuOption)
{
	return GetAsyncKeyState(menuOption->GetInteger()) & 0x8000;
}

inline bool ValidUlt(IUnit* target)
{
	if (target->HasBuffOfType(BUFF_PhysicalImmunity) || target->HasBuffOfType(BUFF_SpellImmunity)

		|| target->IsInvulnerable() || target->HasBuffOfType(BUFF_Invulnerability) || target->HasBuff("kindredrnodeathbuff")

		|| target->HasBuffOfType(BUFF_SpellShield))
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline Vec3 GetTrapPos(float range)
{

	for (auto trap : GEntityList->GetAllHeros(false, true))
	{

		if (trap->IsValidTarget() && GetDistance(GEntityList->Player(), trap) < range && (trap->HasBuff("BardRStasis") || trap->HasBuffOfType(BUFF_Invulnerability)))
		{
			return trap->GetPosition();
		}


		for (auto object : GEntityList->GetAllUnits())
		{
			if (object->IsValidObject() && GetDistance(GEntityList->Player(), object) < range)
			{

				auto name = object->GetObjectName();

				if (strstr(object->GetObjectName(), "Pantheon_Base_R_indicator_red.troy") || strstr(object->GetObjectName(), "gatemarker_red.troy") || 
					strstr(object->GetObjectName(), "global_ss_teleport_target_red.troy") ||
					strstr(object->GetObjectName(), "lifeaura") && GetDistance(trap, object) < 200 || strstr(object->GetObjectName(), "r_indicator_red.troy"))
				{
					return object->GetPosition();
				}
			}

		}
	}

	return Vec3(0, 0, 0);
}

inline bool CanMove(IUnit* target)
{
	if (target->MovementSpeed() < 50 || target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Fear) || target->HasBuffOfType(BUFF_Snare) || target->HasBuffOfType(BUFF_Knockup) || target->HasBuff("Recall") ||

		target->HasBuffOfType(BUFF_Knockback) || target->HasBuffOfType(BUFF_Charm) || target->HasBuffOfType(BUFF_Taunt) || target->HasBuffOfType(BUFF_Suppression))

	{
		return false;
	}
	else
	{
		return true;
	}

}

inline bool CheckWalls(IUnit* player, IUnit* enemy)
{
	auto distance = GetDistance(player, enemy);

	for (auto i = 1; i < 6; i++)
	{		
		Vec3 position;
		Vec3 pPos = GEntityList->Player()->GetPosition();
		auto delay = E->GetDelay() + distance / E->Speed();
		GPrediction->GetFutureUnitPosition(enemy, delay, true, position);

		Vec3 PositionTarget = pPos.Extend(position, distance + 60 * i);

		if (GNavMesh->IsPointWall(PositionTarget))
		{
			return true;
		}
	}
	return false;
}

static bool CheckWallsVectores(Vec3 from, Vec3 to)
{
	auto steps = 6.f;
	auto stepLength = GetDistanceVectors(from, to) / steps;

	for (auto i = 1; i < steps + 1; i++)
	{
		auto PositionTarget = from.Extend(to, stepLength * i);
		
		if (GNavMesh->IsPointWall(PositionTarget))
		{
			return true;
		}
	}

	return false;
}

static bool CheckShielded(IUnit* target)
{
	if (!target->HasBuff("BlackShield") && !target->HasBuff("bansheesveil") && !target->HasBuff("itemmagekillerveil") && !target->HasBuffOfType(BUFF_SpellShield) &&
		!target->HasBuffOfType(BUFF_SpellImmunity) && !target->HasBuff("OlafRagnarok") && !target->HasBuff("SionR"))
	{
		return true;
	}

	return false;
}

static Vec3 Get3DPoint(Vec2 const& Position)
{
	return Vec3(Position.x, GNavMesh->GetHeightForPoint(Position), Position.y);
}

static void DrawLine(Vec2 const Start, Vec2 const End, Vec4 const Color)
{
	Vec3 vecStart3D = Get3DPoint(Start);
	Vec3 vecEnd3D = Get3DPoint(End);

	Vec3 vecOut1;
	GGame->Projection(vecStart3D, &vecOut1);

	Vec3 vecOut2;
	GGame->Projection(vecEnd3D, &vecOut2);

	if (vecOut1.z < 1.f && vecOut2.z < 1.f)
		GRender->DrawLine(Vec2(vecOut1.x, vecOut1.y), Vec2(vecOut2.x, vecOut2.y), Color);
}

static int GetWardSlot()
{
	static IInventoryItem* pWardItems[] = { nullptr };

	if (pWardItems[0] == nullptr)
	{
		int wardIds[] =
		{
			2045, 2049, 2050, 2301, 2302, 2303, 3340, 3361, 3362, 3711, 1408, 1409, 1410, 1411, 2043, 2055
		};

		for (auto i = 0; i < 16; i++)
		{
			pWardItems[i] = GPluginSDK->CreateItemForId(i, 590);
			//GGame->PrintChat(std::to_string(wardIds[i]).data());
		}
	}

	for (auto i : pWardItems)
	{
		if (i->IsOwned() && i->IsReady())
		{		
			//GGame->PrintChat(std::to_string(i->ItemId()).data());
			return i->ItemSpellSlot();
		}
	}

	return kSlotUnknown;
}

std::vector<Vec3> JunglePos =
{
	Vec3(6271.479f, 56.47668f, 12181.25f),
	Vec3(6971.269f, 55.2f, 10839.12f),
	Vec3(8006.336f, 52.31763f, 9517.511f),
	Vec3(10995.34f, 61.61731f, 8408.401f),
	Vec3(10895.08f, 51.72278f, 7045.215f),
	Vec3(12665.45f, 51.70544f, 6466.962f),
	Vec3(4966.042f, 71.24048f, 10475.51f),
	Vec3(39000.529f, 51.84973f, 7901.832f),
	Vec3(2106.111f, 51.77686f, 8388.643f),
	Vec3(3753.737f, 52.46301f, 6454.71f),
	Vec3(6776.247f, 55.27625f, 5542.872f),
	Vec3(7811.688f, 53.79456f, 4152.602f),
	Vec3(8528.921f, 50.92188f, 2822.875f),
	Vec3(9850.102f, 71.24072f, 4432.272f),
	Vec3(3926.0f, 51.74162f, 7918.0f)
};

template<class T>
vector<T> Add(vector<T> vec, T i)
{
	vector<T> newvec;
	newvec = vec;
	newvec.push_back(i);
	return newvec;
}
template<class T>
vector<T> AddRange(vector<T> vec, vector<T> vecToAdd)
{
	vector<T> newvec;
	newvec = vec;
	newvec.insert(newvec.end(), vecToAdd.begin(), vecToAdd.end());
	return newvec;
}
template<class T>
vector<T> RemoveAll(vector<T> vec, function<bool(T)> removefunc)
{
	vector<T> newvec;
	for each (T i in vec)
	{
		if (!removefunc(i))
			newvec.push_back(i);
	}
	return newvec;
}
template<class T>
vector<T> Where(vector<T> vec, function<bool(T)> wherefunc)
{
	vector<T> newvec;
	for each (T i in vec)
	{
		if (wherefunc(i))
			newvec.push_back(i);
	}
	return newvec;
}
template<class T>
bool Any(vector<T> vec, function<bool(T)> anyfunc)
{
	vector<T> newvec;
	newvec = vec;
	newvec = Where(newvec, anyfunc);
	return !newvec.empty();
}
template<class T>
bool Any(vector<T> vec)
{
	vector<T> newvec;
	newvec = vec;
	return !newvec.empty();
}
template<class T, class T2>
vector<T2> Select(vector<T> vec, function<T2(T)> selectfunc)
{
	vector<T> newvec;
	newvec = vec;
	vector<T2> returnvec;
	for each (T i in newvec)
	{
		returnvec.push_back(selectfunc(i));
	}
	return returnvec;
}
template<class T>
T FirstOrDefault(vector<T> vec, function<bool(T)> fst_function)
{
	vector<T> newvec;
	newvec = vec;

	newvec = Where(newvec, fst_function);
	if (newvec.empty())
		return T();
	return newvec.front();
}
template<class T>
T LastOrDefault(vector<T> vec, function<bool(T)> lst_function)
{
	vector<T> newvec;
	newvec = vec;

	newvec = Where(newvec, lst_function);
	if (newvec.empty())
		return T();
	return newvec.back();
}
template<class T, class T2>
T MinOrDefault(vector<T> vec, function<T2(T)> min_function)
{
	vector<T> newvec;
	newvec = vec;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.begin();
	for each (T i in newvec)
	{
		if (min_function(i) < min_function(returnelem))
			returnelem = i;
	}
	return returnelem;
}
template<class T, class T2>
T MaxOrDefault(vector<T> vec, function<T2(T)> max_function)
{
	vector<T> newvec;
	newvec = vec;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.begin();
	for each (T i in newvec)
	{
		if (max_function(i) < max_function(returnelem))
			returnelem = i;
	}
	return returnelem;
}
