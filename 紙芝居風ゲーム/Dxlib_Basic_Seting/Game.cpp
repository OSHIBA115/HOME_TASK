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
	hitImage = LoadGraph("image/bomb.png");

	//音ファイルの読み込み
	bgm = LoadSoundMem("Sound/obake_bgm.mp3");
	hitSound = LoadSoundMem("Sound/Punching_Sound.mp3");
	clearSound = LoadSoundMem("Sound/omedetou.mp3");

	// 【追加】BGMをループ再生（ずーっと鳴らし続ける）する！
	// DX_PLAYTYPE_LOOP を指定すると、曲が終わっても自動で最初から再生してくれるで
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//最初はステージ1から
	stage = 1;

	//最初はまだクリアしてない
	isGameClear = false;

	//ステージ1の準備を呼び出す
	StartStage();


}

///=========================================
/// ステージ開始の準備
///=========================================
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

		//全員復活
		ghostState[i] = 1;

		// タイマーも 0 にリセット
		ghostTimer[i] = 0.0f;
	}


}

///=========================================
/// 更新 
///=========================================
/// WinMain から今のマウスの位置（mx, my）とクリックされたか（click）を引っ張ってくる
void Game::Update(float dt, int mx, int my, bool click)
{
	//すでに全クリア状態なら、これ以上お化けの計算はしない
	if (isGameClear == true)
	{
		return;
	}

	// 画像のサイズはここでも使うから取得する
	int imgW, imgH;
	GetGraphSize(normalImage, &imgW, &imgH);

	//ここでも10分の1のサイズを計算
	int w10 = imgW / 10;
	int h10 = imgH / 10;

	//やられ中のお化けのタイマーを進める処理
	for (int i = 0; i < ghostCount; i++)
	{
		if (ghostState[i] == 2) // やられ中の時だけ
		{
			ghostTimer[i] += dt; // dt（前フレームからの秒数）を足していく

			if (ghostTimer[i] >= 1.0f) // 1.0秒以上経過したら
			{
				ghostState[i] = 0; // 0:完全に消滅　に変更
			}
		}
	}

	//クリックされた時の処理
	if (click)
	{
		for (int i = 0; i < ghostCount; i++)
		{
			if (ghostState[i] != 1) continue;

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
				ghostState[i] = 2;

				//お化けに当たった瞬間ヒット音を鳴らす
				// DX_PLAYTYPE_BACK を指定すると、裏で一瞬だけ「ポンッ」と鳴らして終わる（効果音向き）
				PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);

				//１クリックにつき１匹なためここでチェックを切り上げ
				break;
			}
		}
	}

	//画面に生き残ってるお化けがいるか計算
	int aliveLeft = 0;
	for (int i = 0; i < ghostCount; i++)
	{
		if (ghostState[i] == 1 || ghostState[i] == 2)
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
			//全クリフラグ
			isGameClear = true;

			//全クリでBGMを止める
			StopSoundMem(bgm);

			//全クリ用効果音を鳴らす
			PlaySoundMem(clearSound, DX_PLAYTYPE_BACK);
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

	//全クリア状態なら、クリア画面を描画して終了
	if (isGameClear == true)
	{
		/*
		先に文字の後ろの黒い四角を描く
		座標 (左端100, 上端200) から (右端700, 下端400) までの四角形
		最後の引数を「TRUE」にすると、中身が塗りつぶされる
		*/
		DrawBox(100, 200, 700, 400, GetColor(0, 0, 0), TRUE);

		// 文字のサイズを60サイズに
		SetFontSize(60);

		// 画面の真ん中に表示　色は黄色
		DrawString(200, 250, "ALL STAGE CLEAR!", GetColor(255, 255, 0));

		// これ以降のお化けの描画はスルー（戻る）する
		return;
	}

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
		if (ghostState[i] == 1)
		{
			//背景の上に重なるようにお化けを表示(ghostX,ghostYに入れたランダムなやつを持ってくる) 
			// TRUEにしておくとちゃんと透過してくれる
			DrawExtendGraph(ghostX[i], ghostY[i], ghostX[i] + w10, ghostY[i] + h10, normalImage, TRUE);
		}
		else if (ghostState[i] == 2) //やられ中の時は hitImage を表示
		{
			DrawExtendGraph(ghostX[i], ghostY[i], ghostX[i] + w10, ghostY[i] + h10, hitImage, TRUE);
		}
	}

	//今何ステージ目かを画面の左上に文字で出す
	DrawFormatString(20, 20, GetColor(255, 255, 0), "STAGE: %d", stage);
}