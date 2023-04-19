#include "pch.h"
#include "AttackEvent.h"

using namespace std;

TEST(SettingParameters, missile) {

	AttackEvent attackEvnet;

	MissileInfo missileinfo;
	missileinfo._x = 0.0;
	missileinfo._y = 0.0;

	TargetInfo targetInfo;
	targetInfo._sx = -50000;
	targetInfo._sy = 100000;
	targetInfo._ex =  50000;
	targetInfo._ey = 100000;
	targetInfo.speed = 1;

	attackEvnet.SettingParameters(missileinfo, targetInfo);

  EXPECT_EQ(attackEvnet.mis_x_0, missileinfo._x);
  EXPECT_TRUE(true);
  EXPECT_EQ(attackEvnet.mis_y_0, missileinfo._y);
  EXPECT_TRUE(true);
}

TEST(SettingParameters, target) {

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

	EXPECT_EQ(attackEvnet.tar_x_0, targetInfo._sx);
	EXPECT_TRUE(true);
	EXPECT_EQ(attackEvnet.tar_y_0, targetInfo._sy);
	EXPECT_TRUE(true);

	EXPECT_EQ(attackEvnet.tar_x_f, targetInfo._ex);
	EXPECT_TRUE(true);
	EXPECT_EQ(attackEvnet.tar_y_f, targetInfo._ey);
	EXPECT_TRUE(true);

	EXPECT_EQ(attackEvnet.tar_vel, targetInfo.speed*340);
	EXPECT_TRUE(true);
}