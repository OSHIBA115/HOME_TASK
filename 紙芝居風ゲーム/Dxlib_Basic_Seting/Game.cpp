#include "Game.h"
#include "DxLib.h"

///=========================================
/// 初期化 
///=========================================
Game::Game()
{
	//imageフォルダに入っている画像に番号をつけて保存
	backGround = LoadGraph("image/background.jpg");
	normalImage = LoadGraph("image/obake.png");
	hitImage = LoadGraph("image/mole_hit.png");

	//お化けの初期位置をランダムに
	//画面からはみ出さないように端に余裕を持たせる
	ghostX = GetRand(800 - 150);//０　から　６５０　の間でランダム
	ghostY = GetRand(600 - 150);//０　から　４５０　の間でランダム
}


///=========================================
/// 更新 
///=========================================
/// WinMain から今のマウスの位置（mx, my）とクリックされたか（click）を引っ張ってくる
void Game::Update(float dt, int mx, int my, bool click)
{
	//クリックされた時の処理
	if (click)
	{
	}
}
///=========================================
/// 描画
///=========================================
void Game::Draw()
{
	//背景を横800,縦600に引き延ばして左上ぴったりに描画
	DrawExtendGraph(0, 0, 800, 600, backGround, TRUE);
	//背景の上に重なるようにお化けを表示(ghostX,ghostYに入れたランダムなやつを持ってくる) 
	// TRUEにしておくとちゃんと透過してくれるらしい
	//表示されるときに反対を向いたり細くなったりするが面白いのでそのままにしてる
	DrawExtendGraph(ghostX, ghostX, ghostX + 150, ghostY + 150, normalImage, TRUE);
	//文字のファンとサイズを設定
	SetFontSize(30);

}