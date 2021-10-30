#include "Main.hpp"

//2つの信号
Signal x1 = Signal();
Signal x2 = Signal();

int main()
{
    using namespace std;

    //x1の信号を入力した後、グラフを出力
    cout << "X1の信号が始まる場所を入力" << endl;
    cin >> x1.startN;
    cout << "X1の信号を順番に入力 (入力し終わったら\"end\"を入力)" << endl;
    inputSignal(&x1);
    cout << x1.getStrGrouph() << endl;

    //x2の信号を入力した後、グラフを出力
    cout << "X2の信号が始まる場所を入力" << endl;
    cin >> x2.startN;
    cout << "X2の信号を順番に入力 (入力し終わったら\"end\"を入力)" << endl;
    inputSignal(&x2);
    cout << x2.getStrGrouph() << endl;

    //x1 * x2の計算をした後、左右の余計な値を消し、グラフを出力
    cout << "x1 * x2の計算結果" << endl;
    Signal result = x1 * x2;
    result.normalize();
    cout << result.getStrGrouph() << endl;
    
    return 0;
}

void inputSignal(Signal* signalP)
{
    using namespace std;

    string tmpStr;
    ostringstream oss;
    int dataCount = 0;

    //endが入力されるまでossに値を格納し続ける
    while(true)
    {
        cin >> tmpStr;
        if(tmpStr == "end") break;

        oss << tmpStr << " ";
        dataCount += 1;
    }

    //何も入力されなかった場合、0の値だけ格納する
    if(dataCount == 0)
    {
        oss << 0 << " ";
        dataCount = 1;
    }

    signalP->setDataArrayCount(dataCount);
    istringstream dataIss = istringstream(oss.str());

    //dataIssに格納された値をSignalに移す
    for (int n = signalP->startN; n <= signalP->getLastN(); n++)
    {
        double tmpData = 0;
        dataIss >> tmpData;
        signalP->setData(n, tmpData);
    }
}