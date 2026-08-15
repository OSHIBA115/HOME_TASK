#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    //変数宣言
    int answer = -1;//数字の正誤判定用
    int question;   //正解入れ用　
    int count = 0;  //挑戦回数カウント用

    //乱数初期化
    srand((unsigned int)time(nullptr));

    //0～100までの乱数を生成
    question = rand() % 101;

    cout << "数字当てゲーム" << endl;
    cout << "0～100までの数字を当ててください。" << endl;

    //正解の数字を当てるまでゲームループ
    while (question != answer)
    {
        //挑戦回数＋１
        count++;

        //入力チェック
        while (true)
        {
            cout << "0～100の数字を入力してください：" << endl;
            //プレイヤー解答入力
            cin >> answer;

            //解答が0以下、または100以上の場合に再入力を催促
            if (answer < 0 || answer > 100)
            {
                cout << "入力に誤りがあります。再入力してください。" << endl;
            }
            else
            {
                break;
            }
        }

        //ヒント表示
        //解答が正解より小さい場合
        if (question > answer)
        {
            cout << "もっと大きい数字です。" << endl;
        }
        //解答が正解より大きい場合
        else if (question < answer)
        {
            cout << "もっと小さい数字です。" << endl;
        }
    }

    //正解を当てられた後の処理
    cout << endl;
    cout << "おめでとうございます！正解です！" << endl;
    cout << "正解：" << answer << endl;
    cout << count << "回目で当てることができました。" << endl;

    return 0;
}