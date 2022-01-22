#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;
struct Int
{
    unsigned bit : 1;
};
ostream &operator<<(ostream &cout, const Int &Bit);
struct TreeNode
{
    char elem;
    int weight;
    TreeNode *parent;
    TreeNode *lchild;
    TreeNode *rchild;
    vector<Int> Code;
    TreeNode(int w, TreeNode *p, TreeNode *l, TreeNode *r) : weight(w), parent(p), lchild(l), rchild(r) {}
    TreeNode(char e, int w, TreeNode *p = NULL, TreeNode *l = NULL, TreeNode *r = NULL) : elem(e), weight(w), parent(p), lchild(l), rchild(r) {}
};

class Tree
{
public:
    TreeNode *root;
    vector<TreeNode *> NodeSet;
    vector<TreeNode *> Assist;
    vector<int> Dictionary;
    string File;

    Tree();
    void input_weight();
    void Print_Weight(int ElemVisited = 0);
    void input_file(string file);
    void Print_File(string file);
    void Generate_HuffmanTree();
    void OutPut_Code();
    void PrintZipFile();
};
void TestWeight(Tree Test);
void TestFile(Tree Test, string file);
int main()
{
    TestWeight(Tree());
    cout << "\n\n"
         << endl;
    TestFile(Tree(), "HuffmanTest.txt");
    system("pause");
    return 0;
}
void TestWeight(Tree Test)
{
    Test.input_weight();
    Test.Generate_HuffmanTree();
    Test.OutPut_Code();
    Test.Print_Weight();
}

void TestFile(Tree Test, string file)
{
    Test.input_file(file);
    Test.Generate_HuffmanTree();
    Test.OutPut_Code();
    Test.Print_File(file);
    Test.PrintZipFile();
    cout << endl;
}
ostream &operator<<(ostream &cout, const Int &Bit)
{
    cout << Bit.bit;
    return cout;
}

Tree::Tree()
{
    root = NULL;
    Dictionary.resize(128, 0);
}

void Tree::input_weight()
{
    int w;
    TreeNode *createNode = NULL;
    cout << "input w=-1, programme end\n";
    while (cin >> w)
    {
        if (w == -1)
            break;
        createNode = new TreeNode(w, NULL, NULL, NULL);
        NodeSet.push_back(createNode);
    }
    Assist = NodeSet;
}

void Tree::Generate_HuffmanTree()
{
    TreeNode *Temp = NULL;
    int last;
    while (NodeSet.size() > 1)
    {
        sort(NodeSet.begin(), NodeSet.end(), [](TreeNode *&N1, TreeNode *&N2) -> bool
             { return N1->weight > N2->weight; });
        last = NodeSet.size() - 1;
        Temp = new TreeNode(NodeSet[last - 1]->weight + NodeSet[last]->weight, NULL, NodeSet[last - 1], NodeSet[last]);
        NodeSet[last - 1]->parent = NodeSet[last]->parent = Temp;
        NodeSet[last - 1] = Temp;
        NodeSet.pop_back();
    }
    root = NodeSet[0];
}

void Tree::OutPut_Code()
{
    TreeNode *Temp = NULL;
    for (auto &node : Assist)
    {
        Temp = node;
        while (Temp != root)
        {
            if (Temp == Temp->parent->lchild)
                node->Code.insert(node->Code.begin(), Int{0});
            else
                node->Code.insert(node->Code.begin(), Int{1});
            Temp = Temp->parent;
        }
    }
}

void Tree::Print_Weight(int ElemVisited)
{
    sort(Assist.begin(), Assist.end(), [](TreeNode *&N1, TreeNode *&N2) -> bool
         { return N1->weight > N2->weight; });
    ostream_iterator<Int> Printer(cout, "");
    for (auto &Node : this->Assist)
    {
        if (ElemVisited)
            cout << "Elem: " << Node->elem << "   ";
        cout << "Weight: " << Node->weight << "   Code: ";
        copy(Node->Code.begin(), Node->Code.end(), Printer);
        cout << endl;
    }
}

void Tree::input_file(string file)
{
    ifstream filestream(file);
    istream_iterator<char> Reader(filestream);
    while (true)
    {
        Dictionary[int(*(Reader++))]++;
        if (filestream.peek() == EOF)
            break;
    }
    filestream.close();
    int ascal = 0;
    for_each(Dictionary.begin(), Dictionary.end(), [&](int n)
             {
                 if (n != 0)
                     NodeSet.push_back(new TreeNode(char(ascal), n));
                 ascal++;
             });
    Assist = NodeSet;
}

void Tree::Print_File(string file)
{
    char ch;
    ifstream Reader(file);
    while (Reader.get(ch))
    {
        cout << ch;
        File.push_back(ch);
    }
    Reader.close();
    cout << "\n\n"
         << endl;
    Print_Weight(true);
}

void Tree::PrintZipFile()
{
    ostream_iterator<Int> Printer(cout, "");
    for_each(File.begin(), File.end(), [&](char c)
             {
                 vector<TreeNode *>::iterator Find = find_if(Assist.begin(), Assist.end(), [&](TreeNode *&node) -> bool

                                                             { return node->elem == c; });
                 if (Find != Assist.end())
                     copy((*Find)->Code.begin(), (*Find)->Code.end(), Printer);
                 cout.clear();
             });
}