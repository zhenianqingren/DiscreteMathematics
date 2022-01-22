#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Matrix
{
public:
    int size;
    vector<vector<int>> matrix;
    vector<vector<int>> reverse_matrix;
    vector<vector<int>> symmetrical_matrix;
    vector<vector<int>> pass_matrix;

    Matrix();
    void ReverseClosure();
    void SymmetricalClosure();
    void Floyd_Warshall();
    void Print();
    void Print_Matrix(vector<vector<int>> M);
};

int main()
{
    Matrix().Print();
    system("pause");
    return 0;
}

Matrix::Matrix()
{
    cout << "Please input size of matrix:\n";
    cin >> this->size;
    matrix.resize(size);
    reverse_matrix.resize(size);
    symmetrical_matrix.resize(size);
    pass_matrix.resize(size);
    for_each(matrix.begin(), matrix.end(), [=](vector<int> &v)
             { v.resize(size); });
    for_each(reverse_matrix.begin(), reverse_matrix.end(), [=](vector<int> &v)
             { v.resize(size); });
    for_each(symmetrical_matrix.begin(), symmetrical_matrix.end(), [=](vector<int> &v)
             { v.resize(size); });
    cout << "Please input matrix:\n";
    string s;
    int pos;
    for (int i = 0; i < size; i++)
    {
        cin >> s;
        pos = 0;
        for_each(matrix[i].begin(), matrix[i].end(), [&](int &num)
                 { num = s[pos++] - '0'; });
        s.clear();
    }
    pass_matrix = matrix;
}

void Matrix::ReverseClosure()
{
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->size; j++)
            if (i == j)
                this->reverse_matrix[i][j] = 1;
            else
                this->reverse_matrix[i][j] = this->matrix[i][j];
}

void Matrix::SymmetricalClosure()
{
    for (int i = 0; i < this->size; i++)
        for (int j = 0; j < this->size; j++)
            if (this->matrix[i][j] || this->matrix[j][i])
                this->symmetrical_matrix[i][j] = 1;
            else
                this->symmetrical_matrix[i][j] = 0;
}

void Matrix::Floyd_Warshall()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (pass_matrix[j][k] == 0 && (pass_matrix[j][i] == 1 && pass_matrix[i][k] == 1))
                    pass_matrix[j][k] = 1;
}

void Matrix::Print()
{
    this->ReverseClosure();
    this->SymmetricalClosure();
    this->Floyd_Warshall();
    cout << "init matrix:" << '\n';
    Print_Matrix(this->matrix);
    cout << "reverse matrix:" << '\n';
    Print_Matrix(this->reverse_matrix);
    cout << "symmetrical matrix:\n";
    Print_Matrix(this->symmetrical_matrix);
    cout<<"pass matrix:\n";
    Print_Matrix(this->pass_matrix);
}

void Matrix::Print_Matrix(vector<vector<int>> M)
{
    for (size_t i = 0; i < M.size(); i++)
    {
        for (size_t j = 0; j < M.size(); j++)
            cout << M[i][j] << " ";
        cout << '\n';
    }
    cout << "\n";
}