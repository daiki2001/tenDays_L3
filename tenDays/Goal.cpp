﻿#include "Goal.h"
#include <DxLib.h>

Goal::Goal(const Vec2& pos) :
	pos(pos),
	isGoal(false),
	graph(-1)
{
	Init();
}

Goal::Goal(const int& posX, const int& posY) :
	pos(static_cast<float>(posX), static_cast<float>(posY)),
	isGoal(false),
	graph(-1)
{
	Init();
}

void Goal::Init()
{
	if (graph == -1)
	{
		graph = LoadGraph("./Resources/goal/goal0912.png");
	}
}

void Goal::Update(const Vec2& playerPos)
{
	if (isGoal)
	{
		return;
	}

	static const int goalSize = 20;
	static const int playerSize = 10;
	Vec2 distance = playerPos - pos;

	isGoal = sqrtf((distance.x * distance.x) + (distance.y * distance.y)) < (goalSize + playerSize);
}

void Goal::Draw(const Vec2& offset)
{
	Vec2 drawPos = pos + offset;

	if (graph == -1)
	{
		DrawTriangle(drawPos.x - 10, drawPos.y - 10,
					 drawPos.x - 10, drawPos.y + 10,
					 drawPos.x + 20, drawPos.y + 0,
					 GetColor(0xFF, 0xFF, 0x00), true);
	}
	else
	{
		DrawGraph(drawPos.x - 32, drawPos.y - 32, graph, true);
	}
}

void Goal::SetGoalPos(int stageNum)
{
	if (stageNum == 1)
	{
		pos = { 1000.0f,360.0f };
	}
	else if (stageNum == 2)
	{
		pos = { 1000.0f,50.0f };
	}
	else if (stageNum == 3)
	{
		pos = { 1050.0f,120.0f };
	}
}
