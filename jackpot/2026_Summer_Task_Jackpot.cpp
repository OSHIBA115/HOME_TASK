#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(void)
{
	//定数
	const int DISE = 6;
	const int DISE_ROLL = 2;
	const int FIELD = 9;

	//変数
	int i;
	int plDise[DISE_ROLL] = {};
	int enDise[DISE_ROLL] = {};
	int plSum = 0;
	int enSum = 0;
	int plSelect = 0;
	int enSelect = 0;
	int Field[FIELD] = {};
	int ClearCheck = 0;

	bool trunFlag = true;
	bool judgementFlag = false;

	//乱数初期化
	srand((unsigned int)time(NULL));

	cout << "===================   Jackpot   ============================" << "\n";
	cout << "CPUとプレイヤーが交互に２つの六面サイコロを振り、1から9までのマスを陣取りするゲームです。" << "\n";
	cout << "===================   GAME STRAT   ============================" << "\n";

	while (true)
	{

		if (trunFlag)
		{
			cout << "PLAYER TRUN \n";

			for (i = 0; i < DISE_ROLL; i++)
			{

				plDise[i] = rand() % 6 + 1;

				plSum += plDise[i];
			}

			cout << "次の３つのマスから取るマスを選んでください。すでに取られているマスは取れません \n" << endl;
			cout << plDise[0] << " , " << plDise[1] << " , " << plSum << "\n";

			while (true)
			{
				cin >> plSelect;

				if (plSelect == plDise[0] || plSelect == plDise[1] || plSelect == plSum)
				{
					break;
				}
				else
				{
					cout << "入力に誤りがあります。再度入力してください。\n";
				}

			}

			if (Field[plSelect] == 0)
			{

				Field[plSelect] = 1;

				ClearCheck++;

			}

			cout << "現在のマスの状況はこちらです" << endl;

			for (i = 0; i < FIELD; i++)
			{
				cout << Field[i];
				cout << " , ";
			}

			cout << "\n";

			if (ClearCheck >= 9)
			{
				cout << "全てのマスが埋まったためゲームを終了します\n";
				judgementFlag = true;
				break;
			}

			cout << "\n";
			trunFlag = false;
		}
		else
		{
			cout << "ENEMY TRUN \n";

			for (i = 0; i < DISE_ROLL; i++)
			{
				enDise[i] = rand() % 6 + 1;

				enSum += enDise[i];
			}

			enSelect = rand() % 3;

			switch(enSelect)
			{
			case 0:
				if (Field[enDise[0]] == 0)
				{
					Field[enDise[0]] = 2;

					ClearCheck++;

				}
				break;

			case 1:
				if (Field[enDise[1]] == 0)
				{
					Field[enDise[1]] = 2;

					ClearCheck++;

				}
				break;

			case 2:
				if (Field[enSum] == 0)
				{
					Field[enSum] = 2;

					ClearCheck++;

				}
				break;
			}

			cout << "現在のマスの状況はこちらです" << endl;

			for (i = 0; i < FIELD; i++)
			{
				cout << Field[i];
				cout << " , ";
			}

			if (ClearCheck >= 9)
			{
				cout << "全てのマスが埋まったためゲームを終了します\n";
				judgementFlag = false;
				break;
			}

			cout << "\n";
			trunFlag = true;
		}


	}

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