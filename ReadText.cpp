#include <iostream>//iostream 是输入输出流库标准文件(它没有后缀)它包含 cout 的信息,这对我们的程序是必需的 #include 是预处理器指示符 preprocessor directive 它把 iostream 的内容读入我们的文本文件中
#include <fstream>
#include<typeinfo>
#include<sstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// 分割数据文件
void SplitCString(const string strSource, vector<string>& vDest, string strDdivision)
{
    if (strDdivision == "")
    {
        strDdivision = ",";
    }
    string strTmp(strSource);
    if(strTmp.empty())
    {
        return;
    }

    int pos = strTmp.find(strDdivision);
    while (pos != -1)
    {
        string strT = strTmp.substr(0, pos);
        if (strT.length() > 0)  {
            vDest.push_back(strT);
        }
        strTmp = strTmp.substr(pos+1);
        pos = strTmp.find(strDdivision);
    }
    if (strTmp.length() > 0) {
        vDest.push_back(strTmp);
    }
}
//完成所有处理过程//参数：//@strInFile 读入文件路径 //@strOutFile 写入文件路径，如果文件不存在，会重新创建 //@iBeginLine 从第几行开始处理，这里要求是第6行
int Process(string strInFile, string strOutFile, int iBeginLine, int iEndLine, int numColumn, int iColumn)
{
    if (strInFile.length() <= 0)
    {
        return -1;
    }
    ifstream fReader;
    ofstream fWriter;
    int iLineIndex = 0; //打开文件
    fReader.open(strInFile.c_str(), ios::in);
    if (!fReader.good())
    {
        cout<<"Open in file failed."<<endl;
        return -1;
    }
    fWriter.open(strOutFile.c_str(), ios::app);
    if (!fWriter.good())
    {
        cout<<"Open Out file failed."<<endl;
        return -1;
    }

    //每行文字不要超过500个字符，也可自己修改大小
    char cBuf[500] = {0};
    while (fReader.getline(cBuf, 500)) {
        ++iLineIndex;
        //输出每行到屏幕，便于观察
        //cout << cBuf << endl;
        if (iLineIndex < iBeginLine) {
            //不满足行号要求，不处理
            continue;
        }
        if (iLineIndex > iEndLine) {
            //不满足行号要求，不处理
            continue;
        }
        vector<string> vTest;  //切割字符串，没有明确的分隔符将不好处理，这里假定是空格符
        SplitCString(cBuf, vTest, "\t");
        if (vTest.size() < numColumn) {
            //如果分割出来不是6列，不处理
            //不能可以不用return ,而是continue
            cout << "Col of data is incorrect." << endl;
            cout << vTest.size() << endl;
            return -1;
        }

        string strData = vTest[0];
        for (int i = 1; i < iColumn; i++) {
            strData = strData + "\t"+ vTest[i]+ "\n";
        }
        //strData = strData + "\r";
        fWriter<<strData;
        memset(cBuf, 0, 500);//库函数memset()是针对字节操作的，其中第二个参数值被赋给第一个参数指向的内存地址开始的每一个字节
    }
    //关闭文件 fReader.close();
    fWriter.close();
    return 0;
}

//把数据存入数组
double ReadParameter(string strInFile, double arr[1][11], int numLine, int numColumn){
    ifstream fileinput;
    fileinput.open(strInFile);
    for (int i=0;i<1;i++)
    {
        for (int j=0;j<11;j++)
        {
            fileinput>>arr[i][j];
        }
    }
    fileinput.close();
    return 0;
}


