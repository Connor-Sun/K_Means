//创建k个点作为起始质心(经常是随机选择)
//当任意一个点的簇分配结果发生改变时
//	对数据集中的每个数据点
//		对每个质心
//			计算质心与数据点之间的距离
//		将数据点分配到距其最近的簇
//	对每一个簇，计算簇中所有点的均值并将均值作为质心

/*kmeans算法实现（此处只考虑元组只有两个属性的情况）
*@File:k_means.cpp
*@Author:Cai0538
*@Create:2011-12-10
*@Last Modified:2011-12-10
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>

#define k 3
using namespace std;

//存放成员的属性信息
class Tuple {

public:
    Tuple( const int, const int);

    double getAttr1();
    double getAttr2();

private:
    double attr1;
    double attr2;
    unsigned int lable;
};

Tuple::Tuple(const int attr1, const int attr2) {
    this -> attr1 = attr1;
    this -> attr2 = attr2;
}

double Tuple::getAttr1() {
    return attr1;
}

double Tuple::getAttr2() {
    return attr2;
}


class Cluster : public Tuple {

public:
    Cluster();

    double getAttr1();
    double getAttr2();

    void updateAttr(const int, const int);

private:
    double attr1;
    double attr2;
    unsigned int lable;
};

Cluster::Cluster() {
    attr1 = rand() % 10;
    attr2 = rand() % 10;
}

double Cluster::getAttr1() {
    return attr1;
}

double Cluster::getAttr2() {
    return attr2;
}

void Cluster::updateAttr(const int attr1, const int attr2) {
    this -> attr1 = attr1;
    this -> attr2 = attr2;
}

//计算两个成员间的欧几里距离
double getEucliDist(Tuple t1, Tuple t2){

    return sqrt( (t1.getAttr1() - t2.getAttr1()) * (t1.getAttr1() - t2.getAttr1())
                 + (t1.getAttr2() - t2.getAttr2()) * (t1.getAttr2() - t2.getAttr2()) );
}

//根据质心，决定当前成员属于哪个簇
int clusterOfTuple(Cluster means[], Tuple tuple){

    double dist = getEucliDist(means[0], tuple);
    double temp;
    int label = 0;  //标示属于哪一个簇
    for(int i = 1; i < k; i++){
        temp = getEucliDist(means[i], tuple);
        if( temp < dist ) {
            dist = temp;
            label = i;
        }
    }
    return label;
}

//获得给定簇集的平方误差
double getVar(vector<Tuple> clusters[], Tuple means[]){

    double var = 0;
    for (int i = 0; i < k; i++){
        vector<Tuple> t = clusters[i];
        for (int j = 0; j < t.size(); j++){
            var += getEucliDist(t[j], means[i]);
        }
    }
    //cout<<"sum:"<<sum<<endl;
    return var;
}

//获得当前簇的均值（质心）
Cluster getMeans(vector<Tuple> cluster){

    int num = cluster.size();
    double xMeans = 0, yMeans = 0;
    Cluster mean;
    for (int i = 0; i < num; i++) {
        xMeans += cluster[i].getAttr1();
        yMeans += cluster[i].getAttr2();
    }
    mean.updateAttr(xMeans / num, yMeans / num);
    return mean;
    //cout<<"sum:"<<sum<<endl;
}


void KMeans(vector<Tuple> tuples){
    vector<Tuple> clusters[k];
    vector<Cluster> means[k];
    int i = 0;
    //默认一开始将前K个成员的值作为k个簇的质心（均值）
//    for(i = 0; i < k; i++){
//        means[i]();
//    }
    int lable = 0;
    //根据默认的质心给簇赋值
    for(i = 0; i != tuples.size(); ++i){
        lable = clusterOfTuple(means, tuples[i]);
        clusters[lable].push_back(tuples[i]);
    }
    //输出刚开始的簇
    for(lable = 0; lable < 3; lable++){
        cout << "第" << lable + 1 << "个簇：" << endl;
        vector<Tuple> t = clusters[lable];
        for (i = 0; i < t.size(); i++){
            cout << "(" << t[i].getAttr1()
                 << "," << t[i].getAttr2() << ")"
                 << "   ";
        }
        cout << endl;
    }
    double oldVar = -1;
    double newVar=getVar(clusters, means);
    while(abs( newVar - oldVar ) >= 1) { //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止

        for (i = 0; i < k; i++){ //更新每个簇的中心点
            means[i] = getMeans(clusters[i]);
            //cout<<"means["<<i<<"]:"<<means[i].attr1<<"  "<<means[i].attr2<<endl;
        }
        oldVar = newVar;
        newVar = getVar(clusters, means); //计算新的准则函数值
        for (i = 0; i < k; i++){  //清空每个簇
            clusters[i].clear();
        }
        //根据新的质心获得新的簇
        for(i=0; i != tuples.size(); ++i) {
            lable = clusterOfTuple(means, tuples[i]);
            clusters[lable].push_back(tuples[i]);
        }
        //输出当前的簇
        for(lable = 0; lable < 3; lable++) {
            cout << "第" << lable + 1 << "个簇：" << endl;
            vector<Tuple> t = clusters[lable];
            for (i = 0; i< t.size(); i++){
                cout << "(" << t[i].getAttr1()
                     << "," << t[i].getAttr2() << ")"
                     << "   ";
            }
            cout << endl;
        }
    }
}


int main() {

    char fname[256];
    cout << "请输入存放数据的文件名： ";
    cin >> fname;
    cout << endl;
    ifstream infile;
    infile.open(fname, ios::in);
    if(!infile){
        cout << "不能打开输入的文件" << fname << endl;
        return 0;
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

    //输出文件中的元组信息
    for(vector<Tuple>::size_type ix = 0; ix != tuples.size(); ++ix)
        cout << "(" << tuples[ix].getAttr1() << ","
             << tuples[ix].getAttr2() << ")"
             << "    ";
    cout << endl;
    KMeans(tuples);
    return 0;
}
