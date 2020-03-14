#pragma once

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class Matrix
{
private:
	int raws;
	int cols;
	double **element;
	bool matrix_signal;
	void check();
public:
	Matrix();
	Matrix(int praws, int pcols, double parameter = 0);
	void initialization(int praws, int pcols, double **parameter);
	void one_demation_set(int pcols, double parameter[]);
	Matrix multi_element(const Matrix &parameter);
	Matrix Transpose();
	void operator = (const Matrix &parameter);
	Matrix operator + (const Matrix &parameter);
	Matrix operator + (const double &parameter);
	Matrix operator - (const Matrix &parameter);
	Matrix operator - (const double &parameter);
	Matrix operator * (const Matrix &parameter);
	Matrix operator * (const double &parameter);
	
	double distance();
	void display();

	friend Matrix operator + (const double &parametera, const Matrix &parameterb);
	friend Matrix operator - (const double &parametera, const Matrix &parameterb);
	friend Matrix operator * (const double &parametera, const Matrix &parameterb);
	friend class Active_function;
};

inline Matrix::Matrix()
{
	raws = 1;
	cols = 1;
	matrix_signal = true;
	if (element != NULL)
	{
		free(element);
		element = NULL;
	}
	element = new double *[1];
	for (int i = 0; i < 1; i++)
	{
		element[i] = new double[1];
	}
}

inline Matrix::Matrix(int praws, int pcols, double parameter)
{
	raws = praws;
	cols = pcols;
	matrix_signal = true;
	if (element != NULL)
	{
		free(element);
		element = NULL;
	}
	element = new double *[raws];
	for (int i = 0; i < raws; i++)
	{
		element[i] = new double[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			element[i][j] = parameter;
		}
	}
}

inline void Matrix::check()
{
	if (raws == 1 && cols == 1)
	{
		matrix_signal = false;
	}
}

void Matrix::initialization(int praws, int pcols, double **parameter)
{
	if (raws != praws || cols != pcols)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	else
	{
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				element[i][j] = parameter[i][j];
			}
		}
	}
}

void Matrix::one_demation_set(int pcols, double parameter[])
{
	if (cols != pcols)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	else
	{
		for (int j = 0; j < cols; j++)
		{
			element[0][j] = parameter[j];
		}
	}
}

Matrix Matrix::multi_element(const Matrix &parameter)
{
	Matrix temp(raws, cols);
	if (raws != parameter.raws || cols != parameter.cols)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	else
	{
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				temp.element[i][j] = element[i][j] * parameter.element[i][j];
			}
		}
	}
	return temp;
}

Matrix Matrix::Transpose()
{
	Matrix temp(cols,raws);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[j][i] = element[i][j];
		}
	}
	return temp;
}

void Matrix::operator = (const Matrix &parameter)
{
	raws = parameter.raws;
	cols = parameter.cols;
	matrix_signal = parameter.matrix_signal;
	if (element != NULL)
	{
		free(element);
		element = NULL;
	}
	element = new double *[raws];
	for (int i = 0; i < raws; i++)
	{
		element[i] = new double[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			element[i][j] = parameter.element[i][j];
		}
	}
}

Matrix Matrix::operator + (const Matrix &parameter)
{
	if (raws != parameter.raws || cols != parameter.cols)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	Matrix temp(raws, cols);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[i][j] = element[i][j] + parameter.element[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator + (const double &parameter)
{
	Matrix temp(raws, cols);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[i][j] = element[i][j] + parameter;
		}
	}
	return temp;
}

Matrix Matrix::operator - (const Matrix &parameter)
{
	if (raws != parameter.raws || cols != parameter.cols)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	Matrix temp(raws, cols);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[i][j] = element[i][j] - parameter.element[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator - (const double &parameter)
{
	Matrix temp(raws, cols);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[i][j] = element[i][j] - parameter;
		}
	}
	return temp;
}

Matrix Matrix::operator * (const Matrix &parameter)
{
	if (cols != parameter.raws)
	{
		cout << "Parameter size not match Matix size!" << endl;
	}
	Matrix temp(raws, parameter.cols);
	double sum;
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < parameter.cols; j++)
		{
			sum = 0;
			for (int k = 0; k < cols; k++)
			{
				sum += element[i][k] * parameter.element[k][j];
			}
			temp.element[i][j] = sum;
		}
	}
	return temp;
}

Matrix Matrix::operator * (const double &parameter)
{
	Matrix temp(raws, cols);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.element[i][j] = element[i][j] * parameter;
		}
	}
	return temp;
}

double Matrix::distance()
{
	double result = DBL_MAX;
	double sum = 0;
	if (raws == 1 || cols == 1)
	{
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				sum += element[i][j];
			}
		}
		result = sum / (double)(raws + cols - 1);
	}
	return result;
}


void Matrix::display()
{
	cout << "The matrix has " << raws << " raws and " << cols << " cols." << endl;
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j == 0)
			{
				cout << element[i][j];
			}
			else
			{
				cout << setw(10) << element[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}


Matrix operator + (const double &parametera, const Matrix &parameterb)
{
	Matrix temp(parameterb.raws, parameterb.cols);
	for (int i = 0; i < parameterb.raws; i++)
	{
		for (int j = 0; j < parameterb.cols; j++)
		{
			temp.element[i][j] = parameterb.element[i][j] + parametera;
		}
	}
	return temp;
}

Matrix operator - (const double &parametera, const Matrix &parameterb)
{
	Matrix temp(parameterb.raws, parameterb.cols);
	for (int i = 0; i < parameterb.raws; i++)
	{
		for (int j = 0; j < parameterb.cols; j++)
		{
			temp.element[i][j] = parametera - parameterb.element[i][j];
		}
	}
	return temp;
}

Matrix operator * (const double &parametera, const Matrix &parameterb)
{
	Matrix temp(parameterb.raws, parameterb.cols);
	for (int i = 0; i < parameterb.raws; i++)
	{
		for (int j = 0; j < parameterb.cols; j++)
		{
			temp.element[i][j] = parameterb.element[i][j] * parametera;
		}
	}
	return temp;
}