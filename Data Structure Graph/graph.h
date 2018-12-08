#pragma once
#ifndef  GRAPH_H_INCLUDE
#define  GRAPG_H_INCLUDE

#include<bits/stdc++.h>
using namespace std;

#define MaxInt 32767                //��ʾ���ֵ
#define MVNum 100                   //��󶨵���
typedef int VerTexType;             //���趥�����������Ϊ�ַ���
typedef int ArcType;                //����ߵ�Ȩֵ����Ϊ����
bool flag1[MVNum], flag2[MVNum];
/************************�ڽӾ���**********************/
//�ڽӾ���Ĵ洢�ṹ
struct AMGraph
{
	VerTexType vexs[MVNum];         //�����  
	ArcType arcs[MVNum][MVNum];     //�ڽӾ���
	int vexnum, arcnum;             //ͼ�ĵ�ǰ�����ͱ���
};

//����ĺ���
int LocateVex(AMGraph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)
			return i;
	return -1;
}
//�����ڽӾ��󴴽�����ͼ
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
//�����ڽӾ��󴴽�����ͼ
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
//�ڽӾ�������ѣ��ݹ飩
void DFS_AM(AMGraph G, int v)
{
	cout << v << " ";
	flag1[v] = true;
	for (int i = 0; i < G.vexnum; i++) {
		if (G.arcs[v][i] && !flag1[i])
			DFS_AM(G, i);
	}
}
//�ڽӾ�������ѣ��ǵݹ飩
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
//�ڽӾ����BFS
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
				k++;                          //��һ�������Ѿ�����Ľڵ�ĸ��������������ڽڵ�������ʱ��ֱ�Ӿͽ�����
				if (k == G.vexnum)
					return;
			}
	}
}
/************************�ڽӱ�**********************/
typedef struct ArcNode              //�߽ڵ�
{
	int adjvex;                     //�ñ���ָ��λ��
	struct ArcNode *nextarc;        //ָ����һ���ߵ�ָ��
	//OtherInfo info;               //�ͱ���ص���Ϣ
}*Arcp;
typedef struct VNode                //������Ϣ
{
	VerTexType data;
	ArcNode *firstarc;              //ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList;                     //AdjList��ʾ�ڽӱ�����
typedef struct
{
	AdjList vertices[MVNum];
	int vexnum, arcnum;
}ALGraph;                           //ͼ�ĵ�ǰ������ͱ���

//������
int LocateVex(ALGraph G, int v)
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}
void CreateUDG_W(ALGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;        //�����������ͱߵ�����
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vertices[i].data;      //��ʼ������ֵ
		G.vertices[i].firstarc = NULL;       //�ͳ�ʼ����ͷ�ڵ��ָ����ΪNULL
	}
	VerTexType v1, v2;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2;                //����һ���ߵ����������ֵ
		int x = LocateVex(G, v1);            //ȷ��V1��V2��G�е�λ��
		int y = LocateVex(G, v2);

		Arcp p1 = new ArcNode;
		p1->adjvex = y;                      //ȷ����������ָ��ĵ�
		p1->nextarc = G.vertices[x].firstarc;//����ǰ�巨���߲��뵽v1�ĺ���
		G.vertices[x].firstarc = p1;

		Arcp p2 = new ArcNode;
		p2->adjvex = x;                      //ȷ����������ָ��ĵ�
		p2->nextarc = G.vertices[y].firstarc;//����ǰ�巨������뵽v2�ĺ���
		G.vertices[y].firstarc = p2;
	}
}
//�����ڽӱ�������ͼ
void CreateUDG_Y(ALGraph &G)
{
	std::cin >> G.vexnum >> G.arcnum;        //�����������ͱߵ�����
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vertices[i].data;      //��ʼ������ֵ
		G.vertices[i].firstarc = NULL;       //�ͳ�ʼ����ͷ�ڵ��ָ����ΪNULL
	}
	VerTexType v1, v2;
	for (int i = 0; i < G.arcnum; i++) {
		std::cin >> v1 >> v2;                //����һ���ߵ����������ֵ
		int x = LocateVex(G, v1);            //ȷ��V1��V2��G�е�λ��
		int y = LocateVex(G, v2);

		Arcp p1 = new ArcNode;
		p1->adjvex = y;                      //ȷ����������ָ��ĵ�
		p1->nextarc = G.vertices[x].firstarc;//����ǰ�巨���߲��뵽v1�ĺ���
		G.vertices[x].firstarc = p1;
	}
}
//�ڽӱ�����ѣ��ݹ飩
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
//�ڽӱ�����ѣ��ǵݹ飩
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
//�ڽ��б��BFS
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
				k++;                         //��һ�������Ѿ�����Ľڵ�ĸ�����ʹ�����еĽڵ㶼����Ժ�ֱ�ӽ���
				if (k == G.vexnum)
					return;
			}
			p = p->nextarc;
		}
	}
}


#endif // ! GRAPH_H_INCLUDE
