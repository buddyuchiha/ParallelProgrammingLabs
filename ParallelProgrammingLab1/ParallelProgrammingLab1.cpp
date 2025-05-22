#include <mpi.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 

vector<vector<int>> GenerateMatrix(int size) {
    int rows = size;
    int columns = size;
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

vector<vector<int>> MultyMatrxMPI(vector<vector<int>>& first_matrix, vector<vector<int>>& second_matrix, int world_size, int world_rank) {
    int n = first_matrix.size();
    vector<vector<int>> result_matrix(n, vector<int>(n, 0));

    int rows_per_proc = n / world_size;
    int start_row = world_rank * rows_per_proc;
    int end_row = (world_rank == world_size - 1) ? n : start_row + rows_per_proc;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < n; j++) {
            result_matrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
            }
        }
    }

    if (world_rank == 0) {
        for (int src = 1; src < world_size; src++) {
            int src_start = src * rows_per_proc;
            int src_end = (src == world_size - 1) ? n : src_start + rows_per_proc;

            for (int i = src_start; i < src_end; i++) {
                MPI_Recv(result_matrix[i].data(), n, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }
    else {
        for (int i = start_row; i < end_row; i++) {
            MPI_Send(result_matrix[i].data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD);
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

vector<vector<int>> ReadMatrix(string path, int size) {
    string file_path = path + to_string(size) + ".txt";
    ifstream infile(file_path, ios::out);
    if (!infile.is_open()) {
        throw "File not found";
    }
    vector<vector<int>> matrix(size, vector<int>(size));
    int rows = size;
    int columns = size;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            infile >> matrix[i][j];
        }
    }
    return matrix;
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
    string first_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs-1\\ParallelProgrammingLab1\\input\\first_matrix\\first_matrix";
    string second_matrix_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs-1\\ParallelProgrammingLab1\\input\\second_matrix\\secind_matrix";
    string result_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs-1\\ParallelProgrammingLab1\\output\\result\\result";
    string time_path = "C:\\Users\\Pro10\\OneDrive\\Рабочий стол\\ParallelProgrammingLabs-1\\ParallelProgrammingLab1\\output\\time\\time";

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


