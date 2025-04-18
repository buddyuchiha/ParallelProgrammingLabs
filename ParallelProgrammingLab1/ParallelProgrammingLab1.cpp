#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 

vector<vector<int>> GenerateMatrix(int size) {
    int rows = 100;
    int columns = 100;
    vector<vector<int>> matrix(rows, vector<int>(columns));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

vector<vector<int>> CreateMatrix(string path){
    ifstream infile(path);
    if (!infile.is_open()) {
        throw "File not found";
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
    infile.close();
    return matrix;
}

vector<vector<int>> MultyMatrx(vector<vector<int>> first_matrix, vector<vector<int>> second_matrix) {
    int first_columns = first_matrix.size();
    int second_columns = second_matrix.size();
    int first_rows = first_matrix[0].size();
    int second_rows = second_matrix[0].size();
    if (first_columns != second_rows) {
        throw "first_columns != second_rows";
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

void WriteMatrix(string path, int size, vector<vector<int>> matrix) {
    string file_path = path + to_string(size) + ".txt";
    ofstream outfile(file_path, ios::app);
    if (!outfile.is_open()) {
        throw "File not found";
    }
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            outfile << matrix[i][j] << " ";
        }
        outfile << "\n";
    }
    outfile << "\n";
    outfile.close();
}

void WriteTime(string path, int size, int time) {
    string file_path = path + to_string(size) + ".txt";
    ofstream outfile(file_path, ios::app);
    if (!outfile.is_open()) {
        throw "File not found";
    }
    outfile << time;
    outfile << "\n";
    outfile.close();
}


int main()
{
    string first_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\input\\first_matrix\\first_matrix";
    string second_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\input\\second_matrix\\secind_matrix";
    string result_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\output\\result\\result";
    string time_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs\\ParallelProgrammingLab1\\ParallelProgrammingLab1\\output\\time\\time";

    int EXPIREMENTS_COUNTS = 10;
    int size = 100;

    for (int i = 0; i < EXPIREMENTS_COUNTS; i++) {
        vector<vector<int>> first_matrix = GenerateMatrix(size);
        WriteMatrix(first_matrix_path, size, first_matrix);
        vector<vector<int>> second_matrix = GenerateMatrix(size);
        WriteMatrix(second_matrix_path, size, second_matrix);
        auto start = std::chrono::high_resolution_clock::now();
        vector<vector<int>> result = MultyMatrx(first_matrix, second_matrix);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        WriteMatrix(result_path, size, result);
        WriteTime(time_path, size, duration_ms.count());
        size += 100;
    }
    cout << "complete" << endl;
}


