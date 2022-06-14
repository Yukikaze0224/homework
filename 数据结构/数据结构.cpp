// 数据结构.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<iostream>
//常用头文件


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define UNSUCCESS 0
#define SUCCESS 1
typedef int ElemType;
typedef int Status;
typedef int KeyType;


//下方为哈希表的结构
typedef struct {
	KeyType Key;
//此为key值
}RecordType, RcdType;
typedef struct Node {                       //哈希表的链表
	RcdType r;
	struct Node* next;
}Node;//指针
typedef struct {
	Node** rcd;								//指向指针的指针，存放指针的数组
	int size;								//哈希表容量
	int count;								//当前表中含有的记录个数
	int(*hash)(KeyType key, int hashSize);	//函数指针变量，选取哈希函数
}HashTable;//哈希表本体
//下方为使用的哈希函数
int hash(int key, int hashSize)
{
	return (3 * key) % hashSize;
}


//初始化哈希表
Status InitHash(HashTable& H, int size, int(*hash)(KeyType, int))
{
	H.rcd = (Node**)malloc(size * sizeof(Node*));//分配长度为size的储存空间，元素的类型为指针Node*
	if (H.rcd != NULL)//判断分配是否成功
	{
		for (int i = 0; i < size; i++)
		{
			H.rcd[i] = NULL;//进行初始化
		}
		H.size = size;//进行初始化
		H.hash = hash;//进行初始化
		H.count = 0;//进行初始化
		return OK;//初始化成功
	}
	else
	{
		return OVERFLOW;//分配失败
	}
}


//销毁哈希表
Status DestroyHash(HashTable &H)
{

		if (H.rcd != NULL)
		{
			Node* np, * nt;
			for (int i = 0; i < H.size; i++)
			{
				np = H.rcd[i];
				while (np != NULL)//删除一整条链
				{
					nt = np;
					np = np->next;
					free(nt);//释放结点
				}
			}
			H.size = 0;//清零
			H.count = 0;//清零
			H.hash = NULL;//清零
			return OK;
		}
		else
		{
			return OVERFLOW;//H不存在，不满足前提条件
		}
	
}


//查找
Node* SearchHash(HashTable H, KeyType key)
{
	int a = H.hash(key, H.size);
	Node* c;
	for (c = H.rcd[a]; c != NULL; c = c->next) //直至c为空指针返回不存在
	{
		if (c->r.Key == key)return c;
	}
	return NULL;
}


//删除
Status DeleteHash(HashTable& H, KeyType key, RcdType& e)
{
	Node* n;
	n = SearchHash(H, key);//查找要删除的记录
	if (n == NULL)return ERROR;//要删除的记录不存在
	else
	{
		int p = H.hash(key, H.size);
		Node* np, * nq;
		np = H.rcd[p];
		nq = NULL;
		while (np != NULL)
		{
			if (np->r.Key != key)//寻找记录
			{
				nq = np;
				np = np->next;//向下继续查找记录
			}
			else
			{
				e = np->r;//用e返回记录
				if (nq == NULL)//表头
				{
					H.rcd[p] = np->next;//将要删除的表头拉出
				}
				else//不是表头
				{
					nq->next = np->next;//将要删除的表头拉出
				}
				break;//脱出循环
			}
		}
		H.count--;//count数减一，代表删除记录
		free(np);//删除记录
		return OK;
	}
}


//插入
Status InsertHash(HashTable& H, RcdType e)
{
	int p;
	Node* np;
	np = SearchHash(H, e.Key);//查找是否已有记录
	if (np == NULL)//记录不存在
	{
	
		p = H.hash(e.Key, H.size);
		np = (Node*)malloc(sizeof(Node));
		if (np != NULL){
		
			np->r = e;//将记录赋予np的指向
			np->next = H.rcd[p];
			H.rcd[p] = np;
			H.count++;//count数加一，代表插入完成
			return OK;
		}
		else
		{
			return OVERFLOW;//申请空间失败
		}
	}
	else
	{
		return ERROR;//记录已存在
	}
}


//遍历哈希表
void VisitHash(HashTable H)
{
	if (H.rcd != NULL)
	{
		Node* np, * nq;
		for (int i = 0; i < H.size; i++)
		{
			np = H.rcd[i];
			if (np == NULL)
			{
				printf("  #");//此项上无链表
			}
			else
			{
				while (np)
				{
					printf("%3d", np->r.Key);//按链表逐个输出
					np = np->next;
				}
			}
			printf("\n");//换行
		}
	}
}


//主要调试程序
int main()
{
		HashTable H;
		InitHash(H, 10, hash);
		for (int i = 0; i < 12; i++)
		{
			RcdType e;
			e.Key = i;
			InsertHash(H, e);
		}
		VisitHash(H);
		RcdType e1;
		DeleteHash(H, 9, e1);
		printf("被删数据%d\n", e1.Key);
		VisitHash(H);
		DestroyHash(H);
		printf("3120001799\n");
		printf("20级食品科学与工程2班\n");
		printf("马萌聪\n");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
