#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    //変数宣言
    int player;     //プレイヤー解答入れ
    int cpu;        //CPU解答入れ
    int result;     //じゃんけん勝敗決めに使う計算の答え用
    int i;          //五回カウント用
    int win = 0;    //勝ちカウント
    int lose = 0;   //負けカウント
    int draw = 0;   //引き分けカウント

    //乱数初期化
    srand((unsigned int)time(nullptr));
    
    cout << "じゃんけんゲームを開始します。" << endl;

    //回数が５回に達するまでの間ゲームループ
    for (i = 0; i < 5; i++)
    {
        //何回戦か表示
        cout << endl;
        cout << "-------- " << i + 1 << "回戦 --------" << endl;

        //入力チェック含むプレイヤーの選択入力
        while (true)
        {
            cout << "0：グー　1：チョキ　2：パー" << endl;
            cout << "プレイヤーの手を入力してください：" << endl;

            //入力
            cin >> player;

            //入力数が0以上２以下の場合ループを抜ける
            if (player >= 0 && player <= 2)
            {
                break;
            }

            cout << "入力に誤りがあります。再入力してください。" << endl;
        }

        //cpuの手をランダムで決定
        cpu = rand() % 3;

        //プレイヤーの選択した手を表示
        switch (player)
        {
        case 0:
            cout << "PLAYER：グー" << endl;
            break;

        case 1:
            cout << "PLAYER：チョキ" << endl;
            break;

        case 2:
            cout << "PLAYER：パー" << endl;
            break;
        }

        //CPUが選択した手を表示
        switch (cpu)
        {
        case 0:
            cout << "CPU：グー" << endl;
            break;

        case 1:
            cout << "CPU：チョキ" << endl;
            break;

        case 2:
            cout << "CPU：パー" << endl;
            break;
        }

        //じゃんけんの結果を表示するための計算
        result = player - cpu;

        //計算結果をもとに勝敗を判定
        if (result == -1 || result == 2)
        {
            cout << "PLAYER WIN!" << endl;
            //勝ち点を＋１
            win++;
        }
        else if (result == 0)
        {
            cout << "DRAW" << endl;
            //引き分け点を＋１
            draw++;
        }
        else
        {
            cout << "CPU WIN!" << endl;
            //負け点を＋1
            lose++;
        }
    }

    //終了後の表示処理
    cout << endl;
    cout << "==============================" << endl;
    cout << "5回勝負終了！" << endl;
    cout << win << "勝 "
        << draw << "分 "
        << lose << "敗" << endl;
    cout << "==============================" << endl;

    return 0;
}