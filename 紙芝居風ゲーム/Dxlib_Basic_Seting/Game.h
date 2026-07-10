#pragma once

class Game
{
private://クラス内でのみの変数宣言
	//読み込んだ画像に番号をつけてそれを保存するための変数↓
	int backGround;
	int normalImage;
	int hitImage;

	//お化けの座標
	int ghostX;
	int ghostY;

public://外からでも呼び出せる関数
	//コンストラクタ（このクラスが作られた瞬間に自動で1回だけ実行される。初期化に使う）
	Game();
	//更新
	void Update(float dt, int mx, int my, bool click);
	//描画
	void Draw();

};

