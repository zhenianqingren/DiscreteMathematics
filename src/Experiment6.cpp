#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#define MAX 9999999
using namespace std;

class Graph
{
public:
    vector<vector<int>> Matrix; //邻接矩阵
    int VexNum;                 //顶点数
    int EdgeNum;                //边数
    vector<int> prev;           //前驱数组
    vector<int> distance;       //顶点i到各点的最短距离
    vector<int> visited;        //标记是否被访问过
    vector<vector<int>> FloydMatrix;
    vector<vector<int>> MidMatrix;

    Graph(int N);
    void AddEdge(int x, int y, int w);
    void Dijkstra(int i); //求顶点i到其余各点的最短距离
    void PrintMinPath(const int &pos);
    void FloydWarshall();
    void FindFloydPath(int s, int e, vector<int> &path);//递归打印
};

void Test_Dijkstra(Graph &Test, int start);
void Test_FloydWarshall(Graph &Test);

int main()
{
    Graph graph = Graph(7);
    Test_Dijkstra(graph, 0);
    cout << '\n'
         << endl;
    Test_FloydWarshall(graph);
    system("pause");
    return 0;
}

void Test_Dijkstra(Graph &Test, int start)
{
    Test.Dijkstra(start);
    for (int i = 0; i < Test.VexNum; i++)
        if (i != start)
            Test.PrintMinPath(i);
}

void Test_FloydWarshall(Graph &Test)
{
    Test.FloydWarshall();
    ostream_iterator<int> printer(cout, " ");
    for (auto &v : Test.FloydMatrix)
    {
        copy(v.begin(), v.end(), printer);
        cout << endl;
    }
    cout << "\n\n";
    cin.clear();
    int s, e;
    cout << "Please input the path you want to check\n";
    cin >> s >> e;
    vector<int> path;
    Test.FindFloydPath(s, e, path);
    for_each(path.begin(), path.end(), [](int e)
             { cout << e << " "; });
    if (path.empty())
        cout << "Disconnected" << endl;
}

Graph::Graph(int N)
{
    Matrix.resize(N, vector<int>(N, MAX));
    VexNum = N;
    prev.resize(N);
    distance.resize(N);
    visited.resize(N, 0);
    while (true)
    {
        int x, y, w;
        cout << "Please input start end weight\n";
        if (cin >> x >> y >> w)
            this->AddEdge(x, y, w);
        else
            break;
        system("pause");
        system("cls");
    }
    FloydMatrix = Matrix;
}

void Graph::AddEdge(int x, int y, int w)
{
    if (x < 0 || y >= this->VexNum || Matrix[x][y] != MAX || Matrix[y][x] != MAX || w < 0 || w > MAX)
        cout << "Illegal Operation Of Adding Edge\n";
    else
    {
        Matrix[x][y] = Matrix[y][x] = w;
        cout << "Success\n";
        EdgeNum++;
    }
}

void Graph::Dijkstra(int start)
{
    for (int i = 0; i < VexNum; i++)
    {
        distance[i] = (Matrix[start][i] == MAX ? MAX : Matrix[start][i]);
        prev[i] = (Matrix[start][i] == MAX ? -1 : start);
        visited[i] = 0;
    }
    distance[start] = 0;
    visited[start] = 1;
    int min, pos;
    for (int i = 0; i < VexNum - 1; i++)
    {
        min = MAX;
        for (int j = 0; j < VexNum; j++)
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                pos = j;
            }

        for (int k = 0; k < VexNum; k++)
            if (distance[k] > distance[pos] + Matrix[pos][k])
            {
                distance[k] = distance[pos] + Matrix[pos][k];
                prev[k] = pos;
            }

        visited[pos] = 1;
    }
}

void Graph::PrintMinPath(const int &pos)
{
    int *stack = new int[VexNum];
    int top = -1;
    stack[++top] = pos;
    int pre = prev[pos];
    while (pre != -1)
    {
        stack[++top] = pre;
        pre = prev[pre];
    }

    while (top != -1)
    {
        cout << stack[top--];
        if (top + 1 != 0)
            cout << "-->";
    }
    cout << "\nMin Distance:" << distance[pos] << endl;
}

void Graph::FloydWarshall()
{
    MidMatrix.resize(VexNum, vector<int>(VexNum));

    for (int i = 0; i < VexNum; i++)
        for (int j = 0; j < VexNum; j++)
            MidMatrix[i][j] = (Matrix[i][j] == MAX ? -2 : -1);

    for (int i = 0; i < VexNum; i++)
        for (int j = 0; j < VexNum; j++)
            for (int k = 0; k < VexNum; k++)
                if (j != k && j != i && k != i && FloydMatrix[j][k] > FloydMatrix[j][i] + FloydMatrix[i][k])
                {
                    FloydMatrix[j][k] = FloydMatrix[j][i] + FloydMatrix[i][k];
                    MidMatrix[j][k] = i;
                }

    for_each(FloydMatrix.begin(), FloydMatrix.end(), [=](vector<int> &v)
             { for_each(v.begin(), v.end(), [=](int &e)
                        { e == MAX ? e = 0 : e = e; }); });
}

void Graph::FindFloydPath(int s, int e, vector<int> &path)
{
    if (MidMatrix[s][e] == -2)
        return;
    if (MidMatrix[s][e] == -1)
    {
        if (find(path.begin(), path.end(), s) == path.end())
            path.push_back(s);
        if (find(path.begin(), path.end(), e) == path.end())
            path.push_back(e);
        return;
    }
    else
    {
        FindFloydPath(s, MidMatrix[s][e], path);
        FindFloydPath(MidMatrix[s][e], e, path);
    }
}