import numpy as np 


def read_matrix(matrix_path: str) -> np.array:
    """
    Reading matrix from file 

    Args:
        matrix_path (str) : The path of the matrix

    Returns:
        np.array/matrix
    
    """
    with open(matrix_path, 'r') as file_data:
        matrix = np.loadtxt(file_data)
    return matrix 

def read_time(time_path: str) -> int:
    """
    Reading time from file 

    Args:
        time_path (str) : The path of the time

    Returns:
        time
    
    """
    time = ''
    with open(time_path, 'r') as file_data:
        for string in file_data: 
            time += string 
    return int(time)


def result_checker(first_matrix_path: str, second_matrix_path: str, result_matrix_path: str) -> bool:
    """
    Comparting C++ and Python matrix multiplication result

    Args:
        first_matrix_path (str) : The path of the first matrix 
        second_matrix_path (str) : The path of the second matrix 
        result_matrix_path (str) : The path of the result matrix 
        
    Returns:
        True if results simillar otherwise False
    
    """
    first_matrix = read_matrix(first_matrix_path)
    second_matrix = read_matrix(second_matrix_path)
    result_matrix = read_matrix(result_matrix_path)
    return np.array_equal(np.dot(first_matrix, second_matrix), result_matrix)


