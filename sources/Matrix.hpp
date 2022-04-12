#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include <vector>

namespace zich{
    class Matrix
    {
    private:
        int row;
        int column;
        vector<double> matrix;
    public:
        
        Matrix(vector<double> matrix, int row, int column);
        ~Matrix();
        //PLUS,ADD,PLUS ONRI
        Matrix& operator+= (const Matrix& mat1);
        Matrix operator+ (const Matrix& mat1);
        Matrix operator+();

        //MINUS,SUB,SUB ONRI
        Matrix& operator-= (const Matrix& mat);
        Matrix operator-(const Matrix& mat);
        Matrix operator- ();

        //multi mat x scalar
        Matrix operator *= (double number);
        Matrix operator *= (const Matrix& mat);

        //multi mat x mat1
        Matrix operator * (const Matrix& mat);
        Matrix operator * (double number);
        friend Matrix operator * (double number,const Matrix& mat);

        //boolean operator
        friend bool operator >(const Matrix& mat, const Matrix& mat1);
        friend bool operator >=(const Matrix& mat, const Matrix& mat1);
        friend bool operator < (const Matrix& mat, const Matrix& mat1);
        friend bool operator <=(const Matrix& mat, const Matrix& mat1);
        friend bool operator ==(const Matrix& mat, const Matrix& mat1);
        friend bool operator!=(const Matrix& mat, const Matrix& mat1);

        //add/or sub 1 (increment)
        Matrix& operator++(); //prefix
        Matrix& operator--(); //prefix
        Matrix operator++(int num); //postfix
        Matrix operator--(int num); //postfix


        //IO stream operators
        friend ostream& operator<< (ostream& output, const Matrix& mat);
        friend istream& operator>> (istream& input , Matrix& mat);

    };
    
    
    
};