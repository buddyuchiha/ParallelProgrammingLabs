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

vector<vector<int>> MultyMatrx(vector<vector<int>> first_matrix, vector<vector<int>> second_matrix) {
    int first_columns = first_matrix.size();
    int second_columns = second_matrix.size();
    int first_rows = first_matrix[0].size();
    int second_rows = second_matrix[0].size();
    if (first_columns != second_rows) {
        throw "EXCEPTION: first_columns != second_rows";
    }  
    vector<vector<int>> result_matrix(second_rows, vector<int>(first_columns));
    for (int i = 0; i < first_rows; i++) {
        for (int j = 0; j < second_columns; j++) {
            result_matrix[i][j] = 0;
            for (int k = 0 ; k < first_rows; k++) {
                result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
            }
        }
    }
    return result_matrix;
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
    vector<vector<int>> second_matrix = CreateMatrix();
    PrintMatrix(second_matrix);
    vector<vector<int>> result_matrix = MultyMatrx(first_matrix, second_matrix);
    PrintMatrix(result_matrix);

}


