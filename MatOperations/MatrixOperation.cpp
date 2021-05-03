#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> sum(vector<vector<int>> mat1, vector<vector<int>> mat2)
{
    int n = mat1.size();
    int m = mat1[0].size();

    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            ans[i][j] += (mat1[i][j] + mat2[i][j]);
        }
    }
    return ans;
}
vector<vector<int>> multiply(vector<vector<int>> mat1, vector<vector<int>> mat2)
{
    int n = mat1.size();
    int m = mat1[0].size();

    vector<vector<int>> ans(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                ans[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }
    return ans;
}
int diagonalSum(vector<vector<int>> mat1)
{
    int sum = 0;
    for (int i = 0; i < (mat1.size()); ++i)
    {
        sum += mat1[i][i];
    }
    return sum;
}
vector<vector<int>> transpose(vector<vector<int>> mat1)
{
    int n = mat1.size();
    int m = mat1[0].size();
    vector<vector<int>> transposeMat(m, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            transposeMat[j][i] = mat1[i][j];
        }
    }
    return transposeMat;
}
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat1(n, vector<int>(m, 0));
    vector<vector<int>> mat2(n, vector<int>(m, 0));

    for (auto &v : mat1)
    {
        for (auto &el : v)
        {
            cin >> el;
        }
    }
    for (auto &v : mat2)
    {
        for (auto &el : v)
        {
            cin >> el;
        }
    }
    cout << "Sum of mat1 and mat2:" << endl;
    vector<vector<int>> sumMat = sum(mat1, mat2); //Sum of two Matricies
    for (auto v : sumMat)
    {
        for (auto el : v)
        {
            cout << el << " ";
        }
        cout << endl;
    }
    cout << "Multiplication of mat1 and mat2:" << endl;
    vector<vector<int>> mulmat = multiply(mat1, mat2); //Multiplication of two Matricies
    for (auto v : mulmat)
    {
        for (auto el : v)
        {
            cout << el << " ";
        }
        cout << endl;
    }
    cout << "Sum of diagonal elements of mat1:" << endl;
    int sum = diagonalSum(mat1);
    cout << sum << endl;

    cout << "Transpose of mat1:" << endl;
    vector<vector<int>> transposeMat = transpose(mat1);
    for (auto v : transposeMat)
    {
        for (auto el : v)
        {
            cout << el << " ";
        }
        cout << endl;
    }
}
int main()
{
    solve();
    return 0;
}