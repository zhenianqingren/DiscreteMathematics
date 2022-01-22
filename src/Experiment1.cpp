#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <bitset>
using namespace std;

class LogicCal
{
public:
    vector<vector<int>> Order;
    vector<vector<char>> TruthTable;
    vector<char> variable;

    LogicCal();
    void show();
    void input1(int choice);
    void input2(int choice);
    void input3(int choice);
    void AndCal(vector<char> Expression);
    void OrCal(vector<char> Expression);
    void NotCal(vector<char> Expression);
    void DifferentOrCal(bool var1, bool var2);
    void SingleCondition(bool var1, bool var2);
    void DoubleCondition(bool var1, bool var2);
    bool IsElem(char e);
    vector<char> TransformSuffix(string expression);
    char CalSuffix(vector<char> suffix);
    int Pos(char ch);
    void TackleVariable(string s);
    void Output_TruthTable(string s);
    void Output_Precators();
    void Output_AllocationParadigm();
};

int main()
{
    LogicCal().show();
    system("pause");
    return 0;
}

LogicCal::LogicCal()
{
    Order.resize(7);
    for_each(Order.begin(), Order.end(), [](vector<int> &v)
             { v.resize(7); });

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (i >= j)
                Order[i][j] = 0;
            else
                Order[i][j] = 1;
}

void LogicCal::show()
{
    cout << "1--And\n";
    cout << "2--Or\n";
    cout << "3--Not\n";
    cout << "4--Different Or\n";
    cout << "5--Single Condition\n";
    cout << "6--Double Condition\n";
    cout << "7--Const Value\n";
    cout << "8--Variable\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        input1(1);
        break;
    case 2:
        input1(2);
        break;
    case 3:
        input1(3);
        break;
    case 4:
        input2(1);
    case 5:
        input2(2);
        break;
    case 6:
        input2(3);
        break;
    case 7:
        input3(2);
        break;
    case 8:
        input3(1);
        break;
    }
}

int LogicCal::Pos(char ch)
{
    switch (ch)
    {
    case '!':
        return 0;
    case '*':
        return 1;
    case '+':
        return 2;
    case '^':
        return 3;
    case '>':
        return 4;
    case '=':
        return 5;
    case '(':
        return 6;
    }
    return -1;
}

bool LogicCal::IsElem(char e)
{
    if (e == '0' || e == '1' || (e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z'))
        return true;
    else
        return false;
}

void LogicCal::input1(int choice)
{
    vector<char> input;
    char ch;
    do
    {
        cin >> ch;
        if (ch != '#')
            input.push_back(ch);
    } while (ch != '#');
    switch (choice)
    {
    case 1:
        this->AndCal(input);
        break;
    case 2:
        this->OrCal(input);
        break;
    case 3:
        this->NotCal(input);
        break;
    }
}

void LogicCal::input2(int choice)
{
    bool var1, var2;
    cin >> var1 >> var2;
    switch (choice)
    {
    case 1:
        this->DifferentOrCal(var1, var2);
        break;
    case 2:
        this->SingleCondition(var1, var2);
        break;
    case 3:
        this->DoubleCondition(var1, var2);
        break;
    }
}

void LogicCal::input3(int choice)
{
    string expression;
    cin >> expression;
    switch (choice)
    {
    case 1:
        this->TackleVariable(expression);
        this->Output_TruthTable(expression);
        this->Output_Precators();
        this->Output_AllocationParadigm();
        break;
    case 2:
        cout<<this->CalSuffix(this->TransformSuffix(expression))<<'\n';
        break;
    }
}

vector<char> LogicCal::TransformSuffix(string expression)
{
    char Stack[64];
    int top = -1;
    vector<char> suffix;
    for (int i = 0; expression[i] != '#'; i++)
    {
        if (expression[i] == ' ')
            continue;
        if (this->IsElem(expression[i]))
            suffix.push_back(expression[i]);
        else
        {
            if (expression[i] != ')')
            {
                if (top == -1 || expression[i] == '(' || Order[Pos(expression[i])][Pos(Stack[top])] == 1)
                    Stack[++top] = expression[i];
                else if (Order[Pos(expression[i])][Pos(Stack[top])] == 0)
                {
                    while (Order[Pos(expression[i])][Pos(Stack[top])] == 0)
                    {
                        suffix.push_back(Stack[top--]);
                        if (top == -1)
                            break;
                    }
                    Stack[++top] = expression[i];
                }
            }
            else
            {
                while (Stack[top] != '(')
                    suffix.push_back(Stack[top--]);
                top--;
            }
        }
    }
    while (top != -1)
        suffix.push_back(Stack[top--]);
    return suffix;
}

char LogicCal::CalSuffix(vector<char> suffix)
{
    char Stack[64];
    int top = -1;
    size_t pos = 0;
    bool var1, var2;
    do
    {
        if (this->IsElem(suffix[pos]))
            Stack[++top] = suffix[pos];
        else
        {
            var2 = Stack[top] - '0';
            if (top != 0)
                var1 = Stack[top - 1] - '0';
            switch (suffix[pos])
            {
            case '!':
                Stack[top] == '1' ? Stack[top] = '0' : Stack[top] = '1';
                break;
            case '*':
                Stack[--top] = int(var1 && var2) + '0';
                break;
            case '+':
                Stack[--top] = int(var1 || var2) + '0';
                break;
            case '>':
                Stack[--top] = int((!var1 || var2)) + '0';
                break;
            case '=':
                Stack[--top] = (var1 == var2 ? '1' : '0');
                break;
            case '^':
                Stack[--top] = int((!var1 && var2) || (var1 && !var2)) + '0';
                break;
            }
        }
        pos++;
    } while (pos != suffix.size());
    return Stack[top];
}

void LogicCal::AndCal(vector<char> Expression)
{
    if (find(Expression.begin(), Expression.end(), '0') == Expression.end())
        cout << '1';
    else
        cout << '0';
}

void LogicCal::OrCal(vector<char> Expression)
{
    if (find(Expression.begin(), Expression.end(), '1') == Expression.end())
        cout << '0';
    else
        cout << '1';
}

void LogicCal::NotCal(vector<char> Expression)
{
    transform(Expression.begin(), Expression.end(), Expression.begin(), [](char e) -> char
              { return e == '1' ? '0' : '1'; });
    for (auto e : Expression)
        cout << e << " ";
}

void LogicCal::DifferentOrCal(bool var1, bool var2)
{
    if ((!var1 && var2) || (var1 && !var2))
        cout << '1';
    else
        cout << '0';
}

void LogicCal::SingleCondition(bool var1, bool var2)
{
    if ((!var1||var2))
        cout<<'1';
    else
        cout << '0';
}

void LogicCal::DoubleCondition(bool var1, bool var2)
{
    if (var1 == var2)
        cout << '1';
    else
        cout << '0';
}

void LogicCal::TackleVariable(string s)
{
    int count = 0;
    for (size_t i = 0; i < s.size(); i++)
        if (this->IsElem(s[i]))
            if (find(variable.begin(), variable.end(), s[i]) == variable.end())
            {
                this->variable.push_back(s[i]);
                count++;
            }

    int Size = pow(2, count);
    this->TruthTable.resize(Size);
    for_each(TruthTable.begin(), TruthTable.end(), [=](vector<char> &v)
             { v.resize(count + 1); });

    for (int i = 0; i < Size; i++)
    {
        bitset<32> bit(i);
        string value = bit.to_string();
        for (int j = 32 - count, k = 0; k < count; j++, k++)
            TruthTable[i][k] = value[j];
    }
}

void LogicCal::Output_TruthTable(string s)
{
    cout << "Truth Table:" << '\n';
    for (size_t i = 0; i < variable.size(); i++)
        cout << variable[i] << " ";
    cout << "Value" << '\n';
    vector<char> suffix = this->TransformSuffix(s);
    vector<char> temp(suffix);
    int pos;

    for (size_t i = 0; i < TruthTable.size(); i++)
    {
        for (size_t j = 0; j < suffix.size(); j++)
            if (IsElem(suffix[j]))
            {
                pos = int(find(variable.begin(), variable.end(), suffix[j]) - variable.begin());
                temp[j] = TruthTable[i][pos];
            }
        TruthTable[i][TruthTable[i].size() - 1] = CalSuffix(temp);
    }

    for (size_t i = 0; i < TruthTable.size(); i++)
    {
        for (size_t j = 0; j < TruthTable[i].size(); j++)
            cout << TruthTable[i][j] << " ";
        cout << '\n';
    }
    cout << "-----------------" << '\n';
}

void LogicCal::Output_Precators()
{
    size_t len = TruthTable[0].size();
    size_t first = int(find_if(TruthTable.begin(), TruthTable.end(), [=](vector<char> &v) -> bool
                               { return v[len - 1] == '1'; }) -
                       TruthTable.begin());
    for (size_t i = 0; i < TruthTable.size(); i++)
        if (TruthTable[i][len - 1] == '1')
        {
            if (i != first)
                cout << '+';
            cout << '(';
            for (size_t j = 0; j < len - 1; j++)
            {
                TruthTable[i][j] == '0' ? cout << '!' << variable[j] : cout << variable[j];
                if (j != len - 2)
                    cout << '*';
            }
            cout << ')';
        }
    cout << "\n-----------------\n";
}

void LogicCal::Output_AllocationParadigm()
{
    size_t len = TruthTable[0].size();
    size_t first = int(find_if(TruthTable.begin(), TruthTable.end(), [=](vector<char> &v) -> bool
                               { return v[len - 1] == '0'; }) -
                       TruthTable.begin());
    for (size_t i = 0; i < TruthTable.size(); i++)
        if (TruthTable[i][len - 1] == '0')
        {
            if (i != first)
                cout << '*';
            cout << '(';
            for (size_t j = 0; j < len - 1; j++)
            {
                TruthTable[i][j] == '1' ? cout << '!' << variable[j] : cout << variable[j];
                if (j != len - 2)
                    cout << '+';
            }
            cout << ')';
        }
    cout << "\n-----------------\n";
}
