//k-means算法实现（此处只考虑成员只有两个属性的情况）

//创建k个点作为起始质心(经常是随机选择)
//当任意一个点的簇分配结果发生改变时
//	对数据集中的每个数据点
//		对每个质心
//			计算质心与数据点之间的距离
//		将数据点分配到距其最近的簇
//	对每一个簇，计算簇中所有点的均值并将均值作为质心



/*
 @ Project: K_Means
 @ File: main.cpp
 @ Author: Connor
 @ Create: 2019/10/5
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>

#include "Tuple.h"
#include "Cluster.h"

#define k 3
using namespace std;

vector<Tuple> getData();

void KMeans(vector<Tuple> tuples);


//计算两个成员间的欧几里距离
double getEucliDist(Cluster t1, Tuple t2);
//获得当前簇的均值（质心）
Tuple getMeans(vector<Tuple> tuples);
//根据质心，决定当前成员属于哪个簇
int clusterOfTuple(vector<Cluster> clusterTemp, Tuple tuple);
//获得给定簇集的平方误差
double getVar(vector<Tuple> tuplesTemp[3], vector<Cluster> clusterTemp);


int main() {

    KMeans( getData() );
    return 0;
}


vector<Tuple> getData() {
    char fname[256];
//    cout << "请输入存放数据的文件名： ";
//    cin >> fname;
//    cout << endl;
    ifstream infile;
    infile.open("../data.txt", ios::in);
    if(!infile){
        cout << "can't open file." << fname << endl;
        exit(1);
    }
    int count = 0;
    vector<Tuple> tuples;
    double a1;
    double a2;
    //Tuple temp;
    //从文件流中读入数据
    while(!infile.eof()) {
        count++;
        if(count % 2 == 1) {
            infile >> a1;
        }
        else {
            infile >> a2;
            Tuple temp(a1, a2);
            tuples.push_back( temp );
        }
    }
    //int k;
    //cout<<"请输入期望的簇的个数："
    //cin>>k;
    //cout<<endl;

    //输出文件中的成员信息
    for(vector<Tuple>::size_type ix = 0; ix != tuples.size(); ++ix)
        cout << "(" << tuples[ix].getAttr1() << ","
             << tuples[ix].getAttr2() << ")"
             << "    ";
    cout << endl;

    return tuples;
}

void KMeans(vector<Tuple> tuples){
    vector<Tuple> tuplesTemp[k];
    vector<Cluster> clusterTemp(3);
    int i = 0;

    int label = 0;

    cout << "KMeans" << endl;

    double oldVar;
    double newVar = -1;

    do {

        cout << "while" << endl;

        //根据质心获得新的簇
        for(i=0; i != tuples.size(); ++i) {
            label = clusterOfTuple(clusterTemp, tuples[i]);
            tuplesTemp[label].push_back(tuples[i]);
        }
        cout << "\nupdateCluster" << endl;
        //更新并输出当前的簇
        for(label = 0; label < 3; label++) {
            //更新每个簇的中心点
            clusterTemp[label].updateAttr(getMeans(tuplesTemp[label]).getAttr1(), getMeans(tuplesTemp[label]).getAttr2());

            cout << "cluster " << label + 1 << " (" << clusterTemp[label].getAttr1()
                 << "," << clusterTemp[label].getAttr2() << ")" << " elements:"
                 << endl;
            vector<Tuple> t = tuplesTemp[label];
            for (i = 0; i< t.size(); i++){
                cout << "(" << t[i].getAttr1()
                     << "," << t[i].getAttr2() << ")"
                     << "   ";
            }
            cout << endl;
        }

        oldVar = newVar;
        newVar = getVar(tuplesTemp, clusterTemp); //计算新的准则函数值
        for (i = 0; i < k; i++){  //清空每个簇
            tuplesTemp[i].clear();
        }
    } while(abs( newVar - oldVar ) >= 1); //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止
}


//计算两个成员间的欧几里距离
double getEucliDist(Cluster t1, Tuple t2){

    return sqrt( (t1.getAttr1() - t2.getAttr1()) * (t1.getAttr1() - t2.getAttr1())
                 + (t1.getAttr2() - t2.getAttr2()) * (t1.getAttr2() - t2.getAttr2()) );
}

//获得当前簇的均值（质心）
Tuple getMeans(vector<Tuple> tuples) {

    int num = tuples.size();
    double xMeans = 0, yMeans = 0;

    for (int i = 0; i < num; i++) {
        xMeans += tuples[i].getAttr1();
        yMeans += tuples[i].getAttr2();
    }
    Tuple mean(xMeans / num, yMeans / num);
    return mean;
    //cout<<"sum:"<<sum<<endl;
}

//根据质心，决定当前成员属于哪个簇
int clusterOfTuple(vector<Cluster> clusterTemp, Tuple tuple){

    double dist = getEucliDist(clusterTemp[0], tuple);
    double temp;
    int label = 0;  //标示属于哪一个簇
    for(int i = 1; i < k; i++){
        temp = getEucliDist(clusterTemp[i], tuple);

        if( temp < dist ) {
            dist = temp;
            label = i;
        }
    }
//    cout << "dist = " << dist << endl;
//    cout << "label = " << label << endl;
    tuple.updateLabel(label);
    return label;
}

//获得给定簇集的平方误差
double getVar(vector<Tuple> tuplesTemp[3], vector<Cluster> clusterTemp) {

    cout << "getVar" << endl;
    double var = 0;
    for (int i = 0; i < k; i++){
        //vector<Tuple> t = tuplesTemp[i];
        for (int j = 0; j < tuplesTemp[i].size(); j++){
            var += getEucliDist(clusterTemp[i], tuplesTemp[i][j]);
            //cout << "var = " << var << endl;
        }
    }

    return var;
}

