#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_
#include <queue>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <boost/dynamic_bitset.hpp>

template <typename T>
class AVLTreeNode
{
public:
	AVLTreeNode(T value):key(value), lchild(nullptr), rchild(nullptr){};
	AVLTreeNode(T value, AVLTreeNode<T>*l, AVLTreeNode<T>*r)
	:key(value), lchild(l), rchild(r){}

	T key;
	int height=0; 
	int altitude=0;
	int serialnum=0;
	int x_coor=0;
	int y_coor=0;
	std::string weight="";
	AVLTreeNode<T>* lchild;
	AVLTreeNode<T>* rchild;
};

template<typename T>
class AVLTree
{
public:
	AVLTree();			//构造函数
	~AVLTree();			//析构函数

	void preOrder();	//前序遍历AVL树
	void inOrder();		//中序遍历AVL树	
	void postOrder();	//后序遍历AVL树
	

	void destory();		//销毁AVL树

	void insert(T key);	//插入指定值的节点
	void remove(T key);	//移除指定值的节点

	AVLTreeNode<T>* search_recurse(T key);	//利用递归算法进行指定值的查找
	AVLTreeNode<T>* search_iterator(T key);	//利用迭代算法进行指定值的查找
	T minimum();		//返回AVL中的最小值
	T maximum();		//返回AVL中的最大值

	int height();		//返回树的高度
	T getroot();		//返回根节点
	
	void Inital(int value);	//初始化树结点的各项数值
	cv::Mat DrawTree(int value);	//画出树的结构

private:
	AVLTreeNode<T>* root;	//AVL树的根节点
	int radius;
private:
	void preOrder(AVLTreeNode<T>* pnode) const;
	void inOrder(AVLTreeNode<T>* pnode) const;
	void postOrder(AVLTreeNode<T>* pnode) const;

	void setWeight(AVLTreeNode<T>* pnode) const;
	void setaltitude(AVLTreeNode<T>* pnode) const;	
	void setCoord(AVLTreeNode<T>* pnode) const;	
	void set_XY(AVLTreeNode<T>* pnode) const;
	
	void setCoord();	//设置数的序号
	void setWeight();	//设置树的权重
	void setaltitude();	//设置树的高度
	void set_XY(int value);

	void destory(AVLTreeNode<T>* & pnode);

	int height(AVLTreeNode<T>* pnode) const;
	int max(int a, int b);
	

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &pnode, T key);		
	AVLTreeNode<T>* remove(AVLTreeNode<T>* & pnode, T key); //删除AVL树中节点pdel，并返回被删除的节点

	AVLTreeNode<T>* minimum(AVLTreeNode<T>*pnode)const;
	AVLTreeNode<T>* maximum(AVLTreeNode<T>*pnode)const;

	AVLTreeNode<T>* search_recurse(AVLTreeNode<T>* pnode, T key) const;
	AVLTreeNode<T>* search_iterator(AVLTreeNode<T>* pnode, T key) const;

	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* pnode);		//单旋:左旋操作
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* pnode);		//单旋:右旋操作
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* pnode);	//双旋:先左旋后右旋操作
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* pnode);	//双旋:先右旋后左旋操作

	void InDrawTree(AVLTreeNode<T>* pnode,cv::Mat& image) const;	//画出树的结构
	void DrawCircle(AVLTreeNode<T>* pnode,cv::Mat& image) const; //画圆
	void DrawLine(std::vector<double>* point,cv::Mat& image) const; //画出线段
	void DrawText(AVLTreeNode<T>* pnode,cv::Mat& image) const; //画出结点的值
	std::vector<double>* getleft(int father_x,int child_x,int father_y,int child_y,int radius) const; //得到左子树箭头的坐标
	std::vector<double>* getright(int father_x,int child_x,int father_y,int child_y,int radius) const; //得到右子树箭头的坐标

};

/*构造函数*/
template <typename T>
AVLTree<T>::AVLTree()
:root(nullptr){};

/*析构函数*/
template <typename T>
AVLTree<T>::~AVLTree()
{
	destory(root);
}

/*返回两者中的较大者*/
template<typename T>
int AVLTree<T>::max(int a, int b)
{
	return a > b ? a : b;
};

/*返回树中最大节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* pnode)const
{
	if (pnode != nullptr)
	{
		while (pnode->rchild != nullptr)
			pnode = pnode->rchild;
		return pnode;
	}
	return nullptr;
};

template<typename T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T>* presult = maximum(root);
	if (presult != nullptr)
		return presult->key;
};

/*返回树中最小节点值*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* pnode)const
{
	if (pnode != nullptr)
	{
		while (pnode->lchild != nullptr)
			pnode = pnode->lchild;
		return pnode;
	}
	return nullptr;
};

template<typename T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T>* presult = minimum(root);
	if (presult != nullptr)
		return presult->key;
};

/*返回一棵树的高度*/
template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		return pnode->height;
	}
	return 0;																//如果是空树，高度为0
};


template <typename T>
int AVLTree<T>::height()
{
	return height(root);
};

//获得根节点的值
template <typename T>
T AVLTree<T>::getroot()
{
	if(root!=nullptr)
		return root->key;
	else
		return 0;
};

/*左旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* proot)
{
	AVLTreeNode<T>* prchild = proot->rchild;
	proot->rchild = prchild->lchild;
	prchild->lchild = proot;

	proot->height = max(height(proot->lchild),height(proot->rchild))+1;     //更新节点的高度值
	prchild->height = max(height(prchild->lchild), height(prchild->rchild)) + 1; //更新节点的高度值

	return prchild;					 
};

/*右旋转操作*/
/*pnode为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename  T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>*proot)
{
	AVLTreeNode<T>* plchild = proot->lchild;
	proot->lchild = plchild->rchild;
	plchild->rchild = proot;

	proot->height = max(height(proot->lchild), height(proot->rchild)) + 1;     //更新节点的高度值
	plchild->height = max(height(plchild->lchild), height(plchild->rchild)) + 1; //更新节点的高度值

	return plchild;
};

/*先左后右做旋转*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* proot)
{
	proot->lchild= leftRotation(proot->lchild);
	return rightRotation(proot);
};
/*先右旋再左旋*/
/*参数proot为最小失衡子树的根节点*/
/*返回旋转后的根节点*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* proot)
{
	proot->rchild = rightRotation(proot->rchild);
	return leftRotation(proot);
};

/*插入操作*/
/*递归地进行插入*/
/*返回插入后的根节点*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &pnode, T key)
{
	if (pnode == nullptr)	//寻找到插入的位置
	{
		pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
	}
	else if (key > pnode->key)	//插入值比当前结点值大，插入到当前结点的右子树上
	{
		pnode->rchild = insert(pnode->rchild, key);
		if (height(pnode->rchild) - height(pnode->lchild) == 2) //插入后出现失衡
		{
			if (key > pnode->rchild->key) //情况一：插入右子树的右节点，进行左旋
				pnode=leftRotation(pnode);
			else if (key < pnode->rchild->key)  //情况三：插入右子树的左节点,进行先右再左旋转
				pnode=rightLeftRotation(pnode);
		}
	}
	else if (key < pnode->key) //插入值比当前节点值小，插入到当前结点的左子树上
	{
		pnode->lchild = insert(pnode->lchild, key);
		if (height(pnode->lchild) - height(pnode->rchild) == 2) //如果插入导致失衡
		{
			if (key < pnode->lchild->key)		//情况二：插入到左子树的左孩子节点上，进行右旋
				pnode = rightRotation(pnode);
			else if (key>pnode->lchild->key)
				pnode = leftRightRotation(pnode);//情况四：插入到左子树的右孩子节点上，进行先左后右旋转
		}
	}
	pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
	return pnode;
};

template <typename T>
void AVLTree<T>::insert(T key)
{
	insert(root, key);
};


/*递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(T key)
{
	return search_recurse(root,key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(AVLTreeNode<T>* pnode, T key) const
{
	if (pnode != nullptr)
	{
		if (key == pnode->key)
			return pnode;
		if (key > pnode->key)
			return search_recurse(pnode->rchild,key);
		else
			return search_recurse(pnode->lchild,key);
	}
	return nullptr;
};

/*非递归查找指定元素*/
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(T key)
{
	return search_iterator(root, key);
};
template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(AVLTreeNode<T>* pnode, T key) const
{
	while (pnode != nullptr)
	{
		if (pnode->key == key)
			return pnode;
		else if (key > pnode->key)
			pnode = pnode->rchild;
		else
			pnode = pnode->lchild;
	}
	return nullptr;
};


/*删除指定元素*/
template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* & pnode, T key)
{
	if (pnode != nullptr)
	{
		if (key == pnode->key)			//找到删除的节点
		{
			//因AVL也是二叉排序树，删除节点要维护其二叉排序树的条件
			if (pnode->lchild != nullptr&&pnode->rchild != nullptr)		//若左右都不为空
			{
				if (height(pnode->lchild) > height(pnode->rchild))		//左子树比右子树高
				{
					//使用左子树最大节点来代替被删节点，而删除该最大节点
					AVLTreeNode<T>* ppre = maximum(pnode->lchild);		//左子树最大节点
					pnode->key = ppre->key;								//将最大节点的值覆盖当前结点
					pnode->lchild = remove(pnode->lchild, ppre->key);	//递归地删除最大节点
				}
				else
				{
					//使用最小节点来代替被删节点，而删除该最小节点
					AVLTreeNode<T>* psuc = minimum(pnode->rchild);		//右子树的最小节点
					pnode->key = psuc->key;								//将最小节点值覆盖当前结点
					pnode->rchild = remove(pnode->rchild, psuc->key);	//递归地删除最小节点
				}

			}
			else
			{
				AVLTreeNode<T> * ptemp = pnode;
				if (pnode->lchild != nullptr)
					pnode = pnode->lchild;
				else if (pnode->rchild != nullptr)
					pnode = pnode->rchild;
				delete ptemp;
				return nullptr;
			}
		
		}
		else if (key > pnode->key)		//要删除的节点比当前节点大，则在右子树进行删除
		{
			pnode->rchild =  remove(pnode->rchild, key);
			if (height(pnode->lchild) - height(pnode->rchild) == 2) //删除右子树节点导致不平衡:相当于情况二或情况四
			{
				if (height(pnode->lchild->rchild)>height(pnode->lchild->lchild))
					pnode = leftRightRotation(pnode);				//相当于情况四
				else
					pnode = rightRotation(pnode);					//相当于情况二
			}
		}
		else if (key < pnode->key)		//要删除的节点比当前节点小，则在左子树进行删除
		{
			pnode->lchild= remove(pnode->lchild, key);
			if (height(pnode->rchild) - height(pnode->lchild) == 2)  //删除左子树节点导致不平衡：相当于情况三或情况一
			{
				if (height(pnode->rchild->lchild)>height(pnode->rchild->rchild))
					pnode = rightLeftRotation(pnode);				
				else
					pnode = leftRotation(pnode);
			}
		}
		return pnode;
	}
	return nullptr;
};
template<typename T>
void AVLTree<T>::remove(T key)
{
	root =remove(root, key);
};
/*中序遍历*/
template<typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		inOrder(pnode->lchild);
		std::cout << "value: "<<pnode->key << " layer: "<< pnode->altitude<<" x: "<<pnode->x_coor<<" y: "<<pnode->y_coor<<" serial: "<<pnode->serialnum;
		if(pnode->lchild!=nullptr)
			std::cout << " lchild: " << pnode->lchild->key;
		if (pnode->rchild != nullptr)
			std::cout << " rchild: " << pnode->rchild->key;
		std::cout << std::endl;
		inOrder(pnode->rchild);
	}
};

template<typename T>
void AVLTree<T>::inOrder()
{
	inOrder(root);
};

/*使用层序遍历设置每个结点的权值*/
template<typename T>
void AVLTree<T>::setWeight(AVLTreeNode<T>* pnode) const
{
	std::queue<AVLTreeNode<T>*> que;
	if(pnode == nullptr)
		return;
	else
		que.push(pnode);
	while(!que.empty())
	{
		AVLTreeNode<T>* ptemp = que.front();
		que.pop();
		if (ptemp->lchild != nullptr)
			{
				ptemp->lchild->weight=ptemp->weight+"0";
				que.push(ptemp->lchild);
			}
		if (ptemp->rchild != nullptr)
			{
				ptemp->rchild->weight=ptemp->weight+"1";
				que.push(ptemp->rchild);
			}
	}
};

template<typename T>
void AVLTree<T>::setWeight()
{
	setWeight(root);
};

/*设置每个结点的绝对高度*/
template<typename T>
void AVLTree<T>::setaltitude(AVLTreeNode<T>* pnode) const
{
	if(pnode==this->root)
	{
		pnode->altitude=1;
	}
	if(pnode!=nullptr)
	{
		if(pnode->lchild!=nullptr)
		{
			pnode->lchild->altitude=pnode->altitude+1;
			setaltitude(pnode->lchild);
		}
		if(pnode->rchild!=nullptr)
		{
			pnode->rchild->altitude=pnode->altitude+1;
			setaltitude(pnode->rchild);
		}
	}
};

template<typename T>
void AVLTree<T>::setaltitude()
{
	setaltitude(root);
};

/*设置每个结点的序号*/
template<typename T>
void AVLTree<T>::setCoord(AVLTreeNode<T>* pnode) const
{
if (pnode != nullptr)
	{
		if(pnode==root)
			pnode->serialnum=1;
		else
		{
			boost::dynamic_bitset<> bit(pnode->weight);
			pnode->serialnum=bit.to_ulong()+1;
		}
		setCoord(pnode->lchild);
		setCoord(pnode->rchild);
	}
};

template<typename T>
void AVLTree<T>::setCoord()
{
	setCoord(root);
};

/*设置每个结点的XY坐标*/
template<typename T>
void AVLTree<T>::set_XY(AVLTreeNode<T>* pnode) const
{
	if(pnode!=nullptr)
	{
		int Hel=height(root);
		int power=Hel-pnode->altitude;
		pnode->x_coor=pow(2,power)*(2*pnode->serialnum-1)*this->radius;
		pnode->y_coor=(2*pnode->altitude-1)*this->radius;
		set_XY(pnode->lchild);
		set_XY(pnode->rchild);
	}
};

template<typename T>
void AVLTree<T>::set_XY(int value)
{
	this->radius=value;
	set_XY(root);
};

/*初始化结点坐标*/
template<typename T>
void AVLTree<T>::Inital(int value)
{
	setWeight();
	setaltitude();
	setCoord();
	set_XY(value);
};

/*前序遍历*/
template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		std::cout << "value: "<<pnode->key << " height: " << pnode->height << "altitude: "<<pnode->altitude<<std::endl;
		preOrder(pnode->lchild);
		preOrder(pnode->rchild);
	}
};
template<typename T>
void AVLTree<T>::preOrder()
{
	preOrder(root);
};

/*后列遍历*/
template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		postOrder(pnode->lchild);
		postOrder(pnode->rchild);
		std::cout << pnode->key << ' ';
	}
};
template<typename T>
void AVLTree<T>::postOrder()
{
	postOrder(root);
};


/*销毁AVL树*/
template<typename T>
void AVLTree<T>::destory(AVLTreeNode<T>* & pnode)
{
	if (pnode != nullptr)
	{
		destory(pnode->lchild);
		destory(pnode->rchild);
		delete pnode;
		pnode = nullptr;
	}
};
template<typename T>
void AVLTree<T>::destory()
{
	destory(root);
};



template<typename T>
std::vector<double>* AVLTree<T>::getright(int father_x,int child_x,int father_y,int child_y,int radius) const
{
  std::vector<double>* arr=new std::vector<double>;
  double temp_father_x=(double)father_x;
  double temp_child_x=(double)child_x;
  double temp_father_y=(double)father_y;
  double temp_child_y=(double)child_y;
  double row_side=abs(temp_father_x-temp_child_x);
  double col_side=abs(temp_child_y-temp_father_y);
  double diagnoal=sqrt(pow(row_side,2)+pow(col_side,2));
  double final_father_x=temp_father_x+radius*(row_side/diagnoal);
  double final_father_y=temp_father_y+radius*(col_side/diagnoal);
  double final_child_x=temp_child_x-radius*(row_side/diagnoal);
  double final_child_y=temp_child_y-radius*(col_side/diagnoal);
  arr->push_back(final_father_x);                                 //前四个数分别是父节点的横坐标，纵坐标，子节点的横坐标，纵坐标
  arr->push_back(final_father_y);
  arr->push_back(final_child_x);
  arr->push_back(final_child_y);
  return arr;
};

template<typename T>
std::vector<double>* AVLTree<T>::getleft(int father_x,int child_x,int father_y,int child_y,int radius) const
{
  std::vector<double>* arr=new std::vector<double>;
  double temp_father_x=(double)father_x;
  double temp_child_x=(double)child_x;
  double temp_father_y=(double)father_y;
  double temp_child_y=(double)child_y;
  double row_side=abs(temp_father_x-temp_child_x);
  double col_side=abs(temp_child_y-temp_father_y);
  double diagnoal=sqrt(pow(row_side,2)+pow(col_side,2));
  double final_father_y=temp_father_y+radius*(col_side/diagnoal);
  double final_father_x=temp_father_x-radius*(row_side/diagnoal);
  double final_child_y=temp_child_y-radius*(col_side/diagnoal);
  double final_child_x=temp_child_x+radius*(row_side/diagnoal);
  arr->push_back(final_father_x);                                 //前四个数分别是父节点的横坐标，纵坐标，子节点的横坐标，纵坐标
  arr->push_back(final_father_y);                                 
  arr->push_back(final_child_x);                                  
  arr->push_back(final_child_y);                                  
  return arr;
};

/*画出树的结构*/
template<typename T>
void AVLTree<T>::InDrawTree(AVLTreeNode<T>* pnode,cv::Mat& image) const
{
	
	if(pnode!=nullptr)
	{
		DrawCircle(pnode,image);
		DrawText(pnode,image);
		if(pnode->lchild!=nullptr)
		{
			std::vector<double>* point=getleft(pnode->x_coor,pnode->lchild->x_coor,pnode->y_coor,pnode->lchild->y_coor,this->radius);
			DrawLine(point,image);
			InDrawTree(pnode->lchild,image);
		}
		if(pnode->rchild!=nullptr)
		{
			std::vector<double>* point=getright(pnode->x_coor,pnode->rchild->x_coor,pnode->y_coor,pnode->rchild->y_coor,this->radius);
			DrawLine(point,image);
			InDrawTree(pnode->rchild,image);
		}
	}
};

template<typename T>
cv::Mat AVLTree<T>::DrawTree(int value)	//画出树的结构
{
	this->Inital(value);
	int tree_height=height(root);
	int img_height=2*tree_height*this->radius;
	int img_width=pow(2,tree_height)*this->radius;
	cv::Mat image=cv::Mat::zeros(img_height,img_width,CV_8UC1);
	image.setTo(cv::Scalar(255,255,255));
	InDrawTree(root,image);
	return image;
};

template<typename T>
void AVLTree<T>::DrawCircle(AVLTreeNode<T>* pnode,cv::Mat& image) const //画出圆
{
	cv::circle(image,cv::Point(pnode->x_coor,pnode->y_coor),this->radius,cv::Scalar(0,0,0),1,8,0);
};

template<typename T>
void AVLTree<T>::DrawLine(std::vector<double>* point,cv::Mat& image) const //画出箭头线线段
{
	cv::arrowedLine(image,cv::Point(point->at(0),point->at(1)),cv::Point(point->at(2),point->at(3)),cv::Scalar(0,0,0),1,8,0,0.1);
};

template<typename T>
void AVLTree<T>::DrawText(AVLTreeNode<T>* pnode,cv::Mat& image) const //画出节点的值
{	
	std::string str=std::to_string(pnode->key);
	int excursion=str.size()*10;
	cv::putText(image,str,cv::Point(pnode->x_coor-excursion,pnode->y_coor+10),cv::FONT_HERSHEY_COMPLEX,1.0,cv::Scalar(0,0,0),2,8,false);
};



#endif