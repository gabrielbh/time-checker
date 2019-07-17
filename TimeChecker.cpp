

#include "Matrix.hpp"
#include <eigen3/Eigen/Dense>
#include <chrono>
#include <stack>


using namespace std;


std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;


/**
 * tic function. was givven.
 */
void tic()
{
    tictoc_stack.push(std::chrono::system_clock::now());
}


/**
 * toc function. was given.
 */
void toc()
{

    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    std::cout << elapsed_seconds.count() << " sec\n";
    tictoc_stack.pop();
}


/**
 * main function of the time checker.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Wrong num of params";
        return 1;
    }
    unsigned int n = atoi(argv[1]);
    vector<int> vec;
    unsigned int i = 0;
    for (; i < n * n; i++)
    {
        vec.push_back(1);
    }
    Matrix<int> m(n, n, vec);
    Eigen::MatrixXd matrix = Eigen::MatrixXd::Random(n, n);
    std::cout << "size " << n << std::endl;
    std::cout << "eigen mult ";
    tic();
    Eigen::MatrixXd mulMat = matrix * matrix;
    toc();
    std::cout << "eigen add ";
    tic();
    Eigen::MatrixXd addMat = matrix + matrix;
    toc();

    std::cout << "matlib mult ";
    tic();
    Matrix<int> mul = m * m;
    toc();
    std::cout << "matlib add ";
    tic();
    Matrix<int> add = m + m;
    toc();


    return 0;
}