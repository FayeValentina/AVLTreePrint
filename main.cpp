#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <cstdlib>
#include <set>
#include <vector>
#include <bitset>
#include <string>
#include <boost/dynamic_bitset.hpp>
#include "AVLtree.hpp"
using namespace cv;
using namespace std;



int main(int argc, char const *argv[]) 
{
  int times;
  cout<<"number of pic:";
  cin>>times;
  srand(time(NULL));
  for(int i=0;i<times;i++)
  {
  set<int> putin;
  AVLTree<int> tree;
  string add="C:/Users/Faye/Desktop/onedir/";
  int num =rand()%100;
  string name=to_string(num);
  name=add+name+".jpg";
  while(putin.size()<(rand()%40)+5)
  {
    putin.insert(rand()%(20*times));
  }
  for(set<int>::iterator it=putin.begin();it!=putin.end();it++)
  {
    tree.insert(*it);
  }
  Mat image=tree.DrawTree(40);
  imwrite(name,image);
  }
  return 0;
}
