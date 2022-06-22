#include "Include/Signal/SignalConsoleRenderer.hpp"

void SignalConsoleRenderer::draw(Sample* sampleArray, int sampleArrayCount)
{
    using namespace std;

    //値同士の間にある幅
    const int hSpace = 5;

    cout << right << fixed << setprecision(1);

    //横線を出力
    for (int x = 0; x < sampleArrayCount; x++) cout << "-----";
    cout << "-----" << endl;

    Sample* max = max_element(sampleArray, sampleArray + sampleArrayCount, [](const Sample& a, const Sample& b) { return a.n < b.data; });
    Sample* min = min_element(sampleArray, sampleArray + sampleArrayCount, [](const Sample& a, const Sample& b) { return a.n < b.data; });

    int upY = max->data < 0 ? 1 : max->data + 1;
    int downY = min->data > 0 ? -1 : min->data - 1;

    //マイナスの値も考慮しつつ、縦線と値の大きさを出力
    for (int y = upY; y >= downY; y--)
    {
        for (int x = 0; x < sampleArrayCount; x++)
        {
            if(y == 0) continue;
            
            int intData = (int)sampleArray[x].data;
            if(intData >= 0)
            {
                if(0 < y && y <= intData) cout << setw(hSpace) << "|";
                else
                {
                    if (y == intData + 1) cout << setw(hSpace) << sampleArray[x].data;
                    else cout << setw(hSpace) << "";
                }
            }
            else
            {
                if(0 > y && y >= intData) cout << setw(hSpace) << "|";
                else
                {
                    if (y == intData - 1) cout << setw(hSpace) << sampleArray[x].data;
                    else cout << setw(hSpace) << "";
                }
            }
        }
        if(y != 0) cout << endl;
    }

    //横線を出力
    for (int x = 0; x < sampleArrayCount; x++) cout << "-----";
    cout << "-----" << endl;

    //位置(n)を出力
    for (int x = 0; x < sampleArrayCount; x++) cout << setw(hSpace) << sampleArray[x].n;
    cout << endl;
    
    //横線を出力
    for (int x = 0; x < sampleArrayCount; x++) cout << "-----";
    cout << "-----";
}
