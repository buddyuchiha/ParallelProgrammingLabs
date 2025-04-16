#include <iostream>
#include <vector>

using namespace std; 

vector<vector<int>> CreateMatrix() {
    int columns, rows;
    cout << "Input the number of rows: " << endl;
    cin >> rows;
    cout << "Input the number of columns: " << endl;
    cin >> columns;
    vector<vector<int>> matrix(rows, vector<int>(columns));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

void PrintMatrix(vector<vector<int>> matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "" << endl;
    }
}

int main()
{
    vector<vector<int>> first_matrix = CreateMatrix();
    PrintMatrix(first_matrix);

}


