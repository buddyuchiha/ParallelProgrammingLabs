#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 

vector<vector<int>> CreateMatrix(string path){
    ifstream infile(path);
    if (!infile.is_open()) {
        throw "File found error";
    }
    string line;
    vector <vector<int>> matrix;
    while (getline(infile, line)) {
        istringstream iss(line);
        vector<int> row;
        int number;

        while (iss >> number) {  
            row.push_back(number);
        }
        matrix.push_back(row);
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
    cout << " " << endl;
}

int main()
{
    string first_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\input\\first_matrix_values.txt";
    string second_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\input\\second_matrix_values.txt";
    vector<vector<int>> first_matrix = CreateMatrix(first_matrix_path);
    PrintMatrix(first_matrix);
    vector<vector<int>> second_matrix = CreateMatrix(second_matrix_path);
    PrintMatrix(second_matrix);
    vector<vector<int>> result_matrix = MultyMatrx(first_matrix, second_matrix);
    PrintMatrix(result_matrix);

}


