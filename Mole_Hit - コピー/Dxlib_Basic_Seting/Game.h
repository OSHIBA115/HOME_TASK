#pragma once

///=========================================
/// ゲーム全体を管理するクラス
/// ・スコア管理
/// ・終了
///=========================================
class Game
{
private:
	int backGround;
	int normalImage;
	int hitImage;
public:
	//コンストラクタ
	Game();
	//更新
	void Update(float dt, int mx, int my, bool click);
	//描画
	void Draw();

};

