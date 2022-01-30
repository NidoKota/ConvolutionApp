#include "Main.hpp"

//2つの信号
Signal x1 = Signal();
Signal x2 = Signal();
int tmpInput = 0;

int main()
{
    using namespace std;

    //x1の信号を入力した後、グラフを出力
    cout << "Input n where the X1 signal starts" << endl;
    cin >> tmpInput;
    x1.setStartN(tmpInput);
    cout << "Input the signals of X1 in order (Input \"end\" when finished inputting)" << endl;
    inputSignal(&x1);

    cout << endl;
    cout << "X1" << endl;
    cout << x1.getStrGrouph() << endl;
    cout << endl;

    //x2の信号を入力した後、グラフを出力
    cout << "Input n where the X2 signal starts" << endl;
    cin >> tmpInput;
    x2.setStartN(tmpInput);
    cout << "Input the signals of X2 in order (Input \"end\" when finished inputting)" << endl;
    inputSignal(&x2);
    
    cout << endl;
    cout << "X2" << endl;
    cout << x2.getStrGrouph() << endl;
    cout << endl;

    //x1 * x2の計算をした後、左右の余計な値を消し、グラフを出力
    Signal result = x1 * x2;
    result.normalize();

    cout << endl;
    cout << "x1 * x2" << endl;
    cout << result.getStrGrouph() << endl;
    cout << endl;
    
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
    for (int n = signalP->getStartN(); n <= signalP->getLastN(); n++)
    {
        double tmpData = 0;
        dataIss >> tmpData;
        signalP->setData(n, tmpData);
    }
}