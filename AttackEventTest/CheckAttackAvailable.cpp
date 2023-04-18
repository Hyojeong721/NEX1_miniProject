#include "pch.h"
#include "AttackEvent.h"

using namespace std;

TEST(CheckAttackAvailable, ouside) {

	AttackEvent attackEvnet;
	MissileInfo missileinfo;
	missileinfo._x = 0.0;
	missileinfo._y = 0.0;
	TargetInfo targetInfo;
	targetInfo._sx = -50000;
	targetInfo._sy = 100000;
	targetInfo._ex = 50000;
	targetInfo._ey = 100000;
	targetInfo.speed = 1;
	attackEvnet.SettingParameters(missileinfo, targetInfo);

	bool result = attackEvnet.CheckAttackAvailable();


	EXPECT_EQ(result, false);
	EXPECT_TRUE(true);
}

TEST(CheckAttackAvailable, inside) {

	AttackEvent attackEvnet;
	MissileInfo missileinfo;
	missileinfo._x = 0.0;
	missileinfo._y = 0.0;
	TargetInfo targetInfo;
	targetInfo._sx = -50000;
	targetInfo._sy =  40000;
	targetInfo._ex = 50000;
	targetInfo._ey = 40000;
	targetInfo.speed = 1;
	attackEvnet.SettingParameters(missileinfo, targetInfo);

	bool result = attackEvnet.CheckAttackAvailable();


	EXPECT_EQ(result, true);
	EXPECT_TRUE(true);
}