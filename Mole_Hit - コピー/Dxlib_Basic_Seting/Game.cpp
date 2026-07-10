#include "Game.h"
#include "DxLib.h"

///=========================================
/// 初期化 
///=========================================
Game::Game()
{
	//スコアの初期化
	score = 0;
	backGround = LoadGraph("image/background.png");
	normalImage = LoadGraph("image/mole.png");
	hitImage = LoadGraph("image/mole_hit.png");

	//モグラを最初から複数用意（今回は４体）
	moleManager.Init(4);
}


///=========================================
/// 更新 
///=========================================
void Game::Update(float dt, int mx, int my, bool click)
{
	moleManager.Update(dt);
	if (click)
	{
		if (moleManager.HandClick(mx, my))
		{
			//スコア加算
			score += 5;
		}
	}
}
///=========================================
/// 描画
///=========================================
void Game::Draw()
{
	//背景を描画
	DrawGraph(0, 0, backGround, TRUE);
	moleManager.Draw(normalImage, hitImage);
	SetFontSize(30);
	DrawFormatString(10, 10, GetColor(255, 255, 255), "Score:%d", score);

}