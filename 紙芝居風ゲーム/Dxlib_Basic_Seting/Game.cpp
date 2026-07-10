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

	//最初はステージ1から
	stage = 1;

	//ステージ1の準備を呼び出す
	StartStage();


}

void Game::StartStage()
{
	//お化けの数は"ステージ数 ＋ 2"
	ghostCount = stage + 2;

	//もし配列の限界を超えそうなら25で止める
	if (ghostCount > 15) ghostCount = 15;

	//画像の元サイズを調べる
	int imgW, imgH;
	GetGraphSize(normalImage, &imgW, &imgH);

	//10分の1にしたサイズを計算しておく
	int w10 = imgW / 10;
	int h10 = imgH / 10;

	//お化けの初期位置をランダムに
	for (int i = 0; i < ghostCount; i++)
	{
		//画面からはみ出さないように、端に余裕を持たせ、本来のサイズ分だけ引く
		ghostX[i] = GetRand(800 - w10);
		ghostY[i] = GetRand(600 - h10);
		ghostAlive[i] = true;//全員復活
	}


}

///=========================================
/// 更新 
///=========================================
/// WinMain から今のマウスの位置（mx, my）とクリックされたか（click）を引っ張ってくる
void Game::Update(float dt, int mx, int my, bool click)
{
	// 画像のサイズはここでも使うから取得する
	int imgW, imgH;
	GetGraphSize(normalImage, &imgW, &imgH);

	//ここでも10分の1のサイズを計算
	int w10 = imgW / 10;
	int h10 = imgH / 10;

	//クリックされた時の処理
	if (click)
	{
		for (int i = 0; i < ghostCount; i++)
		{
			if (ghostAlive[i] == false) continue;

			/*
			マウスのXが、お化けの左端より右にある かつ
			マウスのXが、お化けの右端より左にある かつ
			マウスのYが、お化けの上端より下にある かつ
			マウスのYが、お化けの下端より上にある 場合、お化け退治可能
			*/
			if (mx >= ghostX[i] && mx <= (ghostX[i] + w10) &&
				my >= ghostY[i] && my <= (ghostY[i] + h10))
			{
				//i番目のお化けを倒された状態に
				ghostAlive[i] = false;

				//１クリックにつき１匹なためここでチェックを切り上げ
				break;
			}
		}
	}

	//画面に生き残ってるお化けがいるか計算
	int aliveLeft = 0;
	for (int i = 0; i < ghostCount; i++)
	{
		if (ghostAlive[i] == true)
		{
			aliveLeft++; // 生きてるやつがいたらカウントアップ
		}
	}

	//生きてるお化けが 0 になったらステージクリア
	if (aliveLeft == 0)
	{
		stage++; // ステージ番号を1個進める

		if (stage <= 10)
		{
			StartStage(); // 次のステージの準備をする（お化けが増えて復活）
		}
		else
		{
			// 10ステージ全部クリアした後の処理（今はとりあえずステージ10でループさせるか、フリーズ防止）
			stage = 10;
			StartStage();
		}
	}
}

///=========================================
/// 描画
///=========================================
void Game::Draw()
{
	//背景を横800,縦600に引き延ばして左上ぴったりに描画
	DrawExtendGraph(0, 0, 800, 600, backGround, TRUE);

	// 画像のサイズを取得
	int imgW, imgH;
	GetGraphSize(normalImage, &imgW, &imgH);

	//ここでも10分の1のサイズを計算
	int w10 = imgW / 10;
	int h10 = imgH / 10;

	//生きてるお化けだけ表示
	for (int i = 0; i < ghostCount; i++)
	{
		//生きてるお化けだけ
		if (ghostAlive[i] == true)
		{
			//背景の上に重なるようにお化けを表示(ghostX,ghostYに入れたランダムなやつを持ってくる) 
			// TRUEにしておくとちゃんと透過してくれる
			DrawExtendGraph(ghostX[i], ghostY[i], ghostX[i] + w10, ghostY[i] + h10, normalImage, TRUE);
		}
	}

	//今何ステージ目かを画面の左上に文字で出す
	DrawFormatString(20, 20, GetColor(255, 255, 0), "STAGE: %d", stage);
}