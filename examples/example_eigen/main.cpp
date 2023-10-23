#include <iostream>

#include <Eigen/Dense>

using Eigen::MatrixXd;

/**
 * @brief Eigen库的测试
 * 
 * @note Eigen库的测试
 *       输出结果：
 *        3 -1
 *       2.5 1.5
 */

int main()
{
	MatrixXd m(2,2);
	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	std::cout << m << std::endl;
}