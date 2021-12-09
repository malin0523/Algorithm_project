#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

#define MAXV 100010
int V, E, counter = 0, discovered[MAXV];
bool isCutVertex[MAXV];
vector<int> graph[MAXV];
vector<pair<int, int> > edge;

int dfs(int A, int parent) {
    discovered[A] = ++counter;
    int ret = discovered[A];

    for (int i = 0; i < (int)graph[A].size(); i++) {
        int next = graph[A][i];

        if (next == parent)
            continue;

        if (!discovered[next]) {
            //low : 정점 A의 자식 노드가 갈 수 있는 노드중 가장 일찍 방문한 노드
            int low = dfs(next, A);
            if (low > discovered[A]) {
                edge.push_back(make_pair(min(A, next), max(A, next)));
            }
            ret = min(ret, low);
        }
        else {
            ret = min(ret, discovered[next]);
        }
    }
    return ret;
}

int main() {
    printf("정점의 갯수를 입력하세요.");
    scanf("%d", &V);
    while(1) {
        int a, b;
        printf("간선의 양 끝점을 입력하고 엔터를 누르시오 (-1 -1 입력 시 종료) : ");
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
        if (a == -1 && b == -1) {
            break;
        }
    }

    dfs(1, 0);

    sort(edge.begin(), edge.end());
    printf("%d\n", (int)edge.size());
    for (int i = 0; i < (int)edge.size(); i++)
        printf("%d %d\n", edge[i].first, edge[i].second);

    return 0;
}