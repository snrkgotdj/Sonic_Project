#include "stdafx.h"
#include "Stone.h"
#include "ResManager.h"
#include "Animator.h"
#include "Effect_Stone.h"
#include "StageManager.h"
#include "Stage.h"
#include "Collider.h"

Stone::Stone()
{
}


Stone::~Stone()
{
}


void Stone::render(HDC _dc)
{
	Anim->render(_dc, pos);
}

void Stone::enterCollision(Collider * _other)
{
	
}

float Stone::getRandomNumber(float min, float max)
{
	//< 1단계. 시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	//< 2단계. 분포 설정 ( 정수 )
	uniform_real_distribution<float> range(min, max);

	//< 3단계. 값 추출
	return range(rnd);
}