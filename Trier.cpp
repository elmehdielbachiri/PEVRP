//
// Created by shaon on 2018/6/1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<iterator>
#include<algorithm>
using namespace std;

///*
// 归并排序中使用的合并函数
// a为原始数据
// tmpArray用于存放归并排序过程中的结果
// leftPos表示前一个子列的最左端的元素的下标
// rightPos表示后一个子列的最左端的元素的下标
// rightEnd表示后一个子列的最右端的元素的下标
//*/
//template<typename Comparable>
//void merge(vector<Comparable> &a,
//           vector<Comparable> &tmpArray, int leftPos, int rightPos, int rightEnd )
//{
//    int leftEnd = rightPos - 1;
//    int tmpPos = leftPos; // 用来保存在合并过程中存放结果的临时向量的下标
//    int numElements = rightEnd - leftPos + 1;
//
//    //主循环，把数据合并
//    while (leftPos <= leftEnd && rightPos <= rightEnd)
//    {
//        if (a[leftPos] > a[rightPos])
//            tmpArray[tmpPos++] = a[leftPos++];
//        else
//            tmpArray[tmpPos++] = a[rightPos++];
//    }
//    //如果是因为后边子列的数据全部放在临时向量中导致主循环结束
//    //则把前面没放完的数据依次放入临时变量中
//    while (leftPos <= leftEnd)
//        tmpArray[tmpPos++] = a[leftPos++];
//
//    //同上处理前面子列数据全部先放入向量中的情况
//    while (rightPos <= rightEnd)
//        tmpArray[tmpPos++] = a[rightPos++];
//
//    //注意！不能直接用a=tmpArray,因为可能只是复制子列
//    for (int i = 0; i < numElements; ++i, --rightEnd)
//        a[rightEnd] = tmpArray[rightEnd];
//
//}

///*
//使用循环的归并排序
//*/
//template<typename Comparable>
//void MergeSort(vector<Comparable> &a) {
//    // 循环实现的第一种编写方法
//    vector<Comparable> tmpArray(a.size()); // 定义一个临时向量
//    int numElements = a.size();//待排元素的总个数,第一个元素的下标为0，最后一个元素的下标为n-1
//    for (size_t k = 1; k < a.size(); k *= 2)
//    {
//        int leftStart = 0;//初始化左边那个子列的开始下标
//        int gap = 2 * k;//两个子列的长度（每次归并时的长度）
//        //通过循环不断的把完整的两个子列归并
//        while ((leftStart + gap) < numElements)
//        {
//            merge(a, tmpArray, leftStart, leftStart + k, leftStart + gap - 1);
//            leftStart += gap;
//        }
//        //对于向量中最后几个元素
//        //如果剩下的元素长度大于一个子列的长度，则需要归并
//        //如果剩下的元素长度小于等于一个子列的长度，不需要归并，此时该子列已经有序
//        if ((numElements - leftStart) > k)
//        {
//            merge(a, tmpArray, leftStart, leftStart + k, numElements-1);
//        }
//        //注意，每次在执行merge的时候，就把排好的子列从tmpArray中复制到了a中
//    }
//
//    /*
//    //循环实现的第二种编写方法
//    int n = a.size();
//    vector<Comparable> tmpArray(n);
//    for (int subListSize = 1; subListSize < n; subListSize *= 2)
//    {
//        int part1Start = 0;
//        while (part1Start + subListSize < n )
//        {
//            int part2Start = part1Start + subListSize;
//            int part2End = min(n-1, part2Start + subListSize - 1);
//            merge(a, tmpArray, part1Start, part2Start, part2End);
//            part1Start = part2End + 1;
//        }
//    }
//    */
//}
/*输出向量*/
//template<typename T>
//void printVector(vector<T> & v)
//{
//    copy(v.cbegin(), v.cend(), ostream_iterator<T>(cout, " "));
//    cout << endl;
//}


void merge(vector<solution> &a,
           vector<solution> &tmpArray, int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos; // 用来保存在合并过程中存放结果的临时向量的下标
    int numElements = rightEnd - leftPos + 1;

    //主循环，把数据合并
    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        if (a[leftPos].Fitness <= a[rightPos].Fitness)
            tmpArray[tmpPos++] = a[leftPos++];
        else
            tmpArray[tmpPos++] = a[rightPos++];
    }
    //如果是因为后边子列的数据全部放在临时向量中导致主循环结束
    //则把前面没放完的数据依次放入临时变量中
    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = a[leftPos++];

    //同上处理前面子列数据全部先放入向量中的情况
    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = a[rightPos++];

    //注意！不能直接用a=tmpArray,因为可能只是复制子列
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = tmpArray[rightEnd];
}

/*
Utilisation du tri par fusion:
*/
void MergeSort(vector<solution> &a) {
    vector<solution> tmpArray(a.size()); // Vecteur temporaire
    int numElements = a.size();//nombre d'élements à trier, l'indice va de 0 à numElements -1
    for (size_t k = 1; k < a.size(); k *= 2)
    {
        int leftStart = 0;//Initilisation de l'indice de sous colonne gauche
        int gap = 2 * k;//Longueur des 2 sous colonnes
        //Fusion des 2 sous-colonnes
        while ((leftStart + gap) < numElements)
        {
            merge(a, tmpArray, leftStart, leftStart + k, leftStart + gap - 1);
            leftStart += gap;
        }
        if ((numElements - leftStart) > k) {
            merge(a, tmpArray, leftStart, leftStart + k, numElements - 1);
        }
    }
}

