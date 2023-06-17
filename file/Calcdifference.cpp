#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// 读取矩阵文件，并返回矩阵数据
std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> matrix;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            int value;

            while (iss >> value) {
                row.push_back(value);
            }

            matrix.push_back(row);
        }
        file.close();
    }

    return matrix;
}

// 计算两个矩阵对应位置的差值的和
int calculateMatrixDifferenceSum(const std::vector<std::vector<int>> &matrix1, const std::vector<std::vector<int>> &matrix2)
{
    int sum = 0;
    int numRows = matrix1.size();
    int numCols = matrix1[0].size();

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            sum += matrix1[i][j] - matrix2[i][j];
        }
    }

    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Please Input Tow FileName like This:\n"
                  << "Calc file1 file2" << std::endl;
    }
    std::string filename1 = argv[1];
    std::string filename2 = argv[2];

    // 从文件读取两个矩阵
    std::vector<std::vector<int>> matrix1 = readMatrixFromFile(filename1);
    std::vector<std::vector<int>> matrix2 = readMatrixFromFile(filename2);

    // 检查矩阵是否为空或维度不匹配
    if (matrix1.empty() || matrix2.empty() || matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
    {
        std::cout << "Error: Matrix dimensions do not match." << std::endl;
        return 1;
    }

    // 计算矩阵差值的和
    int differenceSum = calculateMatrixDifferenceSum(matrix1, matrix2);
    std::cout << "Matrix Size: " << matrix1.size() << "*" << matrix1[0].size() << std::endl;
    // 输出结果
    std::cout << "Sum of differences: " << differenceSum / 3 << std::endl;

    return 0;
}
