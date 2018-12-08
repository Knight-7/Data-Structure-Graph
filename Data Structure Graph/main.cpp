#include<bits/stdc++.h>
#include"graph.h"
using namespace std;
int main()
{
	//创建一个邻接矩阵
	AMGraph g;
	CreateUDN_W(g);
	for (int i = 0; i < g.vexnum; i++) {
		for (int j = 0; j < g.vexnum; j++)
			cout << g.arcs[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	DFS_AM(g, 4);
	cout << endl;
	DFS_AM_f(g, 4);
	cout << endl;
	BFS_AM(g, 1);
	cout << endl;
	//创建一个邻接表
	memset(flag1, false, sizeof(flag1));
	memset(flag2, false, sizeof(flag2));
	ALGraph gg;
	CreateUDG_W(gg);
	for (int i = 0; i < gg.vexnum; i++) {
		ArcNode *p = gg.vertices[i].firstarc;
		cout << gg.vertices[i].data << " ";
		while (p) {
			int w = p->adjvex;
			cout << w << " ";
			p = p->nextarc;
		}
		cout << endl;
	}

	DFS_ALG(gg, 0);
	cout << endl;
	DFS_ALG_f(gg, 0);
	cout << endl;
	BFS_ALG(gg, 0);
	return 0;

}
