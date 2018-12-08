#pragma once
#ifndef  GRAPH_H_INCLUDE
#define  GRAPG_H_INCLUDE

#include<bits/stdc++.h>
using namespace std;

#define MaxInt 32767                //表示最大值
#define MVNum 100                   //最大定点数
typedef int VerTexType;             //假设顶点的数据类型为字符型
typedef int ArcType;                //假设边的权值类型为整形
bool flag1[MVNum], flag2[MVNum];
/************************邻接矩阵**********************/
//邻接矩阵的存储结构
struct AMGraph
{
	VerTexType vexs[MVNum];         //顶点表  
	ArcType arcs[MVNum][MVNum];     //邻接矩阵
	int vexnum, arcnum;             //图的当前点数和边数
};

//坐标的函数
int LocateVex(AMGraph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)
			return i;
	return -1;
}
//采用邻接矩阵创建无向图
void CreateUDN_W(AMGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)
		std::cin >> G.vexs[i];
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;
	VerTexType v1, v2;
	int w;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2 >> w;
		int x = LocateVex(G, v1);
		int y = LocateVex(G, v2);

		G.arcs[x][y] = w;
		G.arcs[y][x] = G.arcs[x][y];
	}
}
//采用邻接矩阵创建有向图
void CreateUDN_Y(AMGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++)
		std::cin >> G.vexs[i];
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;
	VerTexType v1, v2;
	int w;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2 >> w;
		int x = LocateVex(G, v1);
		int y = LocateVex(G, v2);

		G.arcs[x][y] = w;
	}
}
//邻接矩阵的深搜（递归）
void DFS_AM(AMGraph G, int v)
{
	cout << v << " ";
	flag1[v] = true;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.arcs[v][i] && !flag1[i])
			DFS_AM(G, i);
	}
}
//邻接矩阵的深搜（非递归）
void DFS_AM_f(AMGraph G, int v)
{
	stack<int>s;
	bool vis[MVNum];
	memset(vis, false, sizeof(vis));
	s.push(v);
	s.push(v);
	cout << v << " ";
	vis[v] = true;
	while (!s.empty()) {
		int w = s.top();
		s.pop();

		for (int i = 0; i < G.vexnum; i++)
			if (!vis[i] && G.arcs[w][i]) {
				cout << i << " ";
				vis[i] = true;
				s.push(i);
				w = i;
				i = -1;
			}

	}
}
//邻接矩阵的BFS
void BFS_AM(AMGraph G,int v)
{
	queue<int>q;
	bool vis[MVNum];
	memset(vis, false, sizeof(vis));
	cout << v << " ";
	vis[v] = true;
	q.push(v);
	int k = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i=0;i<G.vexnum;i++)
			if (G.arcs[now][i] && !vis[i]) {
				cout << i << " ";
				vis[i] = true;
				q.push(i);
				k++;                          //加一个计算已经输出的节点的个数，当个数等于节点总数的时候，直接就结束了
				if (k == G.vexnum)
					return;
			}
	}
}
/************************邻接表**********************/
typedef struct ArcNode              //边节点
{
	int adjvex;                     //该边所指的位置
	struct ArcNode *nextarc;        //指向下一条边的指针
	//OtherInfo info;               //和边相关的信息
}*Arcp;
typedef struct VNode                //顶点信息
{
	VerTexType data;
	ArcNode *firstarc;              //指向第一条依附该顶点的边的指针
}VNode, AdjList;                     //AdjList表示邻接表类型
typedef struct
{
	AdjList vertices[MVNum];
	int vexnum, arcnum;
}ALGraph;                           //图的当前顶点书和边数

//求坐标
int LocateVex(ALGraph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}
void CreateUDG_W(ALGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;        //输入点的数量和边的数量
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vertices[i].data;      //初始化顶点值
		G.vertices[i].firstarc = NULL;       //和初始化表头节点的指针域为NULL
	}
	VerTexType v1, v2;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2;                //输入一条边的两个顶点的值
		int x = LocateVex(G, v1);            //确定V1和V2在G中的位置
		int y = LocateVex(G, v2);

		Arcp p1 = new ArcNode;
		p1->adjvex = y;                      //确定该条边所指向的点
		p1->nextarc = G.vertices[x].firstarc;//采用前插法将边插入到v1的后面
		G.vertices[x].firstarc = p1;

		Arcp p2 = new ArcNode;
		p2->adjvex = x;                      //确定该条变所指向的点
		p2->nextarc = G.vertices[y].firstarc;//采用前插法将变插入到v2的后面
		G.vertices[y].firstarc = p2;
	}
}
//采用邻接表建立有向图
void CreateUDG_Y(ALGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;        //输入点的数量和边的数量
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vertices[i].data;      //初始化顶点值
		G.vertices[i].firstarc = NULL;       //和初始化表头节点的指针域为NULL
	}
	VerTexType v1, v2;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2;                //输入一条边的两个顶点的值
		int x = LocateVex(G, v1);            //确定V1和V2在G中的位置
		int y = LocateVex(G, v2);

		Arcp p1 = new ArcNode;
		p1->adjvex = y;                      //确定该条边所指向的点
		p1->nextarc = G.vertices[x].firstarc;//采用前插法将边插入到v1的后面
		G.vertices[x].firstarc = p1;
	}
}
//邻接表的深搜（递归）
void DFS_ALG(ALGraph G, int v)
{
	cout << v << " ";
	flag2[v] = true;
	ArcNode *p = G.vertices[v].firstarc;
	while (p) {
		int w = p->adjvex;
		if (!flag2[w])
			DFS_ALG(G, w);
		p = p->nextarc;
	}
}
//邻接表的深搜（非递归）
void DFS_ALG_f(ALGraph G, int v)
{
	stack<int>s;
	s.push(v);
	bool vis[MVNum];
	memset(vis, false, sizeof(vis));
	while (!s.empty()) {
		int w = s.top();
		s.pop();
		ArcNode *p = G.vertices[w].firstarc;
		while (p) {
			if (vis[w]) {
				p = p->nextarc;
				if (!p)
					break;
				w = p->adjvex;
			}
			else {
				cout << w << " ";
				s.push(w);
				vis[w] = true;
				w = p->adjvex;
				p = G.vertices[w].firstarc;
			}
		}
	}
}
//邻接列表的BFS
void BFS_ALG(ALGraph G, int v)
{
	queue<int>q;
	bool vis[MVNum];
	memset(vis, false, sizeof(vis));
	q.push(v);
	cout << v << " ";
	vis[v] = true;
	int k = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		ArcNode *p = G.vertices[now].firstarc;
		while (p) {
			int w = p->adjvex;
			if (!vis[w]) {
				cout << w << " ";
				vis[w] = true;
				q.push(w);
				k++;                         //加一个计算已经输出的节点的个数，使得所有的节点都输出以后直接结束
				if (k == G.vexnum)
					return;
			}
			p = p->nextarc;
		}
	}
}


#endif // ! GRAPH_H_INCLUDE
