#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(void)
{
	//定数
	const int CARD = 3;			//カード枚数＝３枚
	const int CARD_NUMBER = 10;	//カードの内容＝10まで

	//変数宣言int型
	int i, hit = 0;			//繰り返し用i、当たったカードの枚数カウント用hit
	int playerCard[CARD];	//プレイヤーの手札
	int enemyCard[CARD];	//CPUの手札
	int plyChoice[CARD];	//プレイヤーが選んだカード用
	int emyChoice[CARD];	//CPUが選んだカード用

	//変数宣言bool型
	bool trunFlag = true;		//ターン入れ替え用
	bool judgementFlag = false;	//勝ち負け判定用

	//乱数初期化
	srand((unsigned int)time(NULL));

	//手札をランダムに配布
	for (i = 0; i < CARD; i++)
	{
		playerCard[i] = rand() % CARD_NUMBER;
		enemyCard[i] = rand() % CARD_NUMBER;
	}
	cout << "===================   Hit & Blow   ============================" << "\n";
	cout << "3マスの数字あてゲームプレイヤーとCPUが、お互いに隠し持った3つの数字を当てるターン制のゲーム" << "\n";
	cout << "あなたの配られてカードは," << "\n";

	//プレイヤーに配ったカードの内容を表示
	for (i = 0; i < CARD; i++)
	{
		cout << i + 1 << "番目" << playerCard[i] << "\n";
	}

	cout << "===================   GAME STRAT   ============================" << "\n";

	//ゲームループ
	while (true)
	{
		//trueflagがtrueの場合はプレイヤーのターン
		if (trunFlag)
		{
			//hit初期化
			hit = 0;
			cout << "PLAYER TRUN 「数字の0から9までの数字を3つ選んでください」\n";
			//プレイヤー数字選択（３回繰り返し）
			for (i = 0; i < CARD; i++)
			{
				//入力チェック含めた入力
				while (true)
				{
					cin >> plyChoice[i];
					if (0 > plyChoice[i] || 9 < plyChoice[i])
					{
						cout << "入力に誤りがあります。再度入力してください。\n";
					}
					else
					{
						break;
					}

				}
			}

			//選択された数があっているか確認
			for (i = 0; i < CARD; i++)
			{
				//正しい場合hitを＋１
				if (plyChoice[i] == enemyCard[i])
				{
					cout << "Hit,";
					hit++;
				}
				else
				{
					cout << "Blow,";
				}
			}
			cout << "\n";
			//もし3つあっていたら勝ち負け判定をプレイヤーの勝ちに設定してループを終了
			if (hit == 3)
			{
				cout << "3Hit!!\n";
				judgementFlag = true;
				break;
			}
			//当たった数が３つ未満の場合ターンを変更
			cout << "\n";
			trunFlag = false;
		}
		//CPUのターンの処理
		else
		{
			//hit初期化
			hit = 0;

			cout << "ENEMY TRUN \n";
			//CPUの選択をランダムで決定＆表示
			for (i = 0; i < CARD; i++)
			{
				emyChoice[i] = rand() % CARD_NUMBER;

				cout << i + 1 << "番目" << emyChoice[i] << "\n";
			}
			//CPUの選択の正否をチェック
			for (i = 0; i < CARD; i++)
			{
				//当たっている数だけhitを＋
				if (emyChoice[i] == playerCard[i])
				{
					cout << "Hit,";
					hit++;
				}
				else
				{
					cout << "Blow,";
				}
			}
			cout << "\n";
			//３つ当たったらループ終了
			if (hit == 3)
			{
				cout << "3Hit!!\n";
				break;
			}
			//ターン切り替え
			cout << "\n";
			trunFlag = true;
		}


	}

	//勝ち負けを表示
	if (judgementFlag)
	{
		cout << "PLAYER WINNER\n";
	}
	else
	{
		cout << "ENEMY WINNER\n";
	}

	return 0;
}