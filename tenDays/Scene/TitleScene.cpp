﻿#include "TitleScene.h"
#include <DxLib.h>
#include "General.h"
#include "./Input/KeyInput.h"
#include "./Input/Controller.h"
#include "Collision.h"

namespace
{
int backAnimation = 0;
}

TitleScene::TitleScene(SceneChanger* sceneChanger) :
	BaseScene(sceneChanger),
	back{},
	cloud(-1),
	player{},
	cloudPos{}
{
	Load();
	Init();
}

TitleScene::~TitleScene()
{
	Release();
}

void TitleScene::Init()
{
	player.Init();
}

void TitleScene::Update()
{
	if ((General::Frame::GetFrame() % 5) == 0)
	{
		++backAnimation %= 8;
	}

	cloudPos.x += 1.0f;
	if (cloudPos.x >= 1280.0f)
	{
		cloudPos.x -= 1280.0f;
	}

	player.Update();
	player.EffectUpdate();

	static const Vec2 groundPos = Vec2(General::WIN_WIDTH / 2, General::WIN_HEIGHT - 70);
	static const Vec2 groundSize = Vec2(General::WIN_WIDTH, 70);

	if (Collision::BoxCollision(player.GetPos(), groundPos, Vec2(player.GetSize(), player.GetSize()), groundSize))
	{
		if (player.GetPos().y + player.GetSize() > groundPos.y - groundSize.y && player.GetOldPos().y < player.GetPos().y &&
			player.GetOldPos().x + player.GetSize() > groundPos.x - groundSize.x && player.GetOldPos().x - player.GetSize() < groundPos.x + groundSize.x)
		{
			Vec2 pos = player.GetPos();
			pos.y = groundPos.y - groundSize.y - player.GetSize();
			player.SetPosition(pos);
			player.ChangeBoundFlag();
		}
	}

	// 画面外判定
	bool isIn = Collision::BoxCollision(player.GetPos(),
										Vec2(General::WIN_WIDTH / 2.0f, General::WIN_HEIGHT / 2.0f),
										Vec2(player.GetSize(), player.GetSize()),
										Vec2(General::WIN_WIDTH / 2.0f - 20.0f, General::WIN_HEIGHT / 2.0f));
	if (isIn == false)
	{
		player.ChangeFlag();
	}

	if (Controller::Decision_A() || KeyInput::IsKeyTrigger(KEY_INPUT_SPACE))
	{
		isSceneDest = true;
		nextScene = SceneChanger::Scene::Game;
		changeAnimation.Start();
	}

	if (isSceneDest && changeAnimation.GetChange())
	{
		sceneChanger->SceneChange(nextScene, true);
	}
}

void TitleScene::Draw()
{
	// 背景
	DrawGraph(0, 0, back[backAnimation], false);
	DrawGraph(static_cast<int>(cloudPos.x), static_cast<int>(cloudPos.y), cloud, true);
	DrawGraph(static_cast<int>(cloudPos.x) - 1280, static_cast<int>(cloudPos.y), cloud, true);

	// オブジェクト
	player.Draw();
}

void TitleScene::Load()
{
	if (background == -1)
	{
		background = LoadDivGraph("./Resources/Title.png", 8, 8, 1, 1280, 720, back);
	}
	if (cloud == -1)
	{
		cloud = LoadGraph("./Resources/forestback/cloud.png");
	}
}

void TitleScene::Release()
{
	for (size_t i = 0; i < 8; i++)
	{
		DeleteGraph(back[i]);
	}
}
