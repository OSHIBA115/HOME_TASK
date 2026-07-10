#include"DxLib.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//画面をウィンドウモードに
	ChangeWindowMode(TRUE);
	//画面の大きさを横800ピクセル、縦600ピクセル,色の細かさを32ピクセルに
	SetGraphMode(800, 600, 32);
	//一回見えない裏のキャンバスに絵を描いて、完成したら一瞬で表に切り替える（チカチカ防止）
	SetDrawScreen(DX_SCREEN_BACK);
	//DxLib_Initを使う準備。準備に失敗したら-1を返してすぐに処理を終了
	if (DxLib_Init() == -1) return -1;

	//インスタンス
	Game game;

	//GetNowCount()＝パソコンが起動してから何ミリ秒（1秒の1000分の1）経ったかを測る時計
	int prevTime = GetNowCount();
	//1フレーム前のマウスの状態を覚えとくための変数
	int prevMouse = 0;
	//バツボタンが押されるか、Escキーが押されるまで、1秒間に60回この中身を繰り返す
	while (ProcessMessage() == 0 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//前回のループから今回までに何秒かかったか（デルタタイム＝dt）
		int nowTimer = GetNowCount();
		float dt = (nowTimer - prevTime) / 1000.0f;
		prevTime = nowTimer;
		//ここの４行はマウスの状態を調べてる
		int mx, my;
		GetMousePoint(&mx, &my);//今マウスが画面のどこ（X座標、Y座標）にいるかを取得して、mx と my に入れる
		int mouse = GetMouseInput();//今マウスのボタンが押されてるかどうかをチェック
		bool click = false;//今クリックされた瞬間なのかを判定するフラグ（YES/NO）

		//クリックされているのかをtrueに変更（押しっぱなしでクリアされるのを阻止）
		if ((mouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT))
		{
			click = true;
		}
		prevMouse = mouse;

		//更新
		game.Update(dt, mx, my, click);
		//画面をきれいに
		ClearDrawScreen();
		//描画
		game.Draw();
		//表画面に表示
		ScreenFlip();
	}
	//Dxlibを終了
	DxLib_End();
	//処理を終了
	return 0;
}