#include<bits/stdc++.h>
#include"graph.h"
using namespace std;
int main()
{
	//����һ���ڽӾ���
	AMGraph g;
	CreateUDN_W(g);
	for (int i = 0; i < g.vexnum; i++) {
		for (int j = 0; j < g.vexnum; j++)
			cout << g.arcs[i][j] << " ";
		cout << endl;
	}
	DFS_AM(g, 4);
	cout << endl;
	DFS_AM_f(g, 4);
	//����һ���ڽӱ�
	memset(flag1, false, sizeof(flag1));
	memset(flag2, false, sizeof(flag2));
	ALGraph gg;
	CreateUDG(gg);
	DFS_ALG(gg, 0);
	cout << endl;
	DFS_ALG_f(gg, 0);
	return 0;

}
