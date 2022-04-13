#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include <vector>
#include "Matrix.hpp"
#include <string>
using namespace std;
namespace zich{
        
        // a contructor
        Matrix::Matrix(vector<double> matrix, int row, int column){
                if(column < 0 ||row < 0 ||  column*row  != matrix.size()){
                        //if  the row or column if under 0 or the size of the vector isnt equal to row*column
                        throw runtime_error("illeagal veriable");
                }
                this->matrix = std::move(matrix);
                this->row=row;
                this->column= column;   
        }

        // a decontructor
        Matrix::~Matrix(){}

        //PLUS,ADD,PLUS ONRI
        //based on + operator for sum matrix's
        Matrix& Matrix::operator+=(const Matrix& mat1){
                (*this) = (*this) + mat1;
                return (*this);
        }
        Matrix Matrix::operator+(const Matrix& mat){
                Matrix copy_mat = Matrix(*this);
                const int size = copy_mat.matrix.size();
                if(copy_mat.column != mat.column || copy_mat.row != mat.row){
                        throw runtime_error("can't sum unequal matrix");
                }
                for(int i = 0; i< size;i++){
                        copy_mat.matrix[(unsigned int)i] += mat.matrix[(unsigned int)i];
                }
                return copy_mat;
        }
        //plus onri
        Matrix Matrix::operator+(){
               return Matrix(*this);
        }

        //MINUS,SUB,SUB ONRI
        Matrix& Matrix::operator-= (const Matrix& mat){
                if(mat.column != (*this).column || mat.row != (*this).row){
                        throw runtime_error("can't sum unequal matrix");
                }
                (*this) = (*this) - mat;
                return (*this);
        }
        Matrix Matrix::operator- (const Matrix& mat){
                Matrix copy_mat = Matrix(*this);
                const int size = copy_mat.matrix.size();
                if(copy_mat.column != mat.column || copy_mat.row != mat.row){
                        throw runtime_error("can't sum unequal matrix");
                }
                for(int i = 0; i< size;i++){
                        copy_mat.matrix[(unsigned int)i] -= mat.matrix[(unsigned int)i];
                }
                return copy_mat;
        }
        //minus onri-multiply all the matrix with -1
        Matrix Matrix::operator- (){
                Matrix copy_mat = Matrix(*this);
                const int size = copy_mat.matrix.size();
                for(int i = 0; i< size;i++){
                        copy_mat.matrix[(unsigned int)i] = (-1*(*this).matrix[(unsigned int)i]);
                }
                return copy_mat;
        }

        //based on * operator for multiply matrix
        Matrix Matrix::operator *= (double number){
               (*this) = (*this)*number;
               return (*this);
        }

        //based on * operator for multiply matrix
        Matrix Matrix::operator *= (const Matrix& mat){
                const int size = mat.row;
                const int size1 = (*this).column;
                if(size != size1){
                        throw runtime_error("can't mulitiply enequal matrix");
                }
               (*this) = (*this)*mat;
               return (*this);
        }

        //multi mat x mat1
        Matrix Matrix::operator *(const Matrix& mat){
                const int size = mat.row;
                const int size1 = (*this).column;
                if(size != size1){
                        throw runtime_error("can't mulitiply enequal matrix");
                }
                
                int first_r = (*this).row;
                int second_c = mat.column;
                const int first_c = (*this).column;
                int connect_size = first_r*second_c;
                vector<double> matrix((unsigned int)connect_size);
                for(int i = 0 ; i <connect_size;i++){
                        matrix.at((unsigned int)i)=0;
                }
                Matrix mat3(matrix,first_r,second_c);
                for(int i = 0;i < first_r;i++){
                        for(int j = 0;j < second_c;j++){
                                double sum = 0.0;
                                for(int k = 0;k < first_c;k++){
                                        //sum = sum +(*this).matrix[(unsigned int)(i*first_c+k)]*mat.matrix[(unsigned int)(j+k*second_c)];
                                        //mat3.matrix[(unsigned int)(i*second_c+j)] = sum;
                                        mat3.matrix[(unsigned int)(i*second_c+j)] = mat3.matrix[(unsigned int)(i*second_c+j)]+(*this).matrix[(unsigned int)(i*first_c+k)]*mat.matrix[(unsigned int)(j+k*second_c)];
                                }
                        }
                        
                }
                
                return mat3;
        }
        //multiply matrix with scalar lest side
        Matrix Matrix::operator * (double number){
                Matrix copy_mat = Matrix(*this);
                const int size = copy_mat.matrix.size();
                for(int i = 0 ; i< size;i++){
                        double temp = copy_mat.matrix.at((unsigned int)i)*number;
                        copy_mat.matrix[(unsigned int)i] = temp;
                }
                return copy_mat;
        }
        //multiply matrix with scalar right side
        Matrix operator *(double number,const Matrix& mat){
                Matrix mat2(mat.matrix,mat.row,mat.column);
                const int size= mat.matrix.size();
                for(int i=0;i<size;i++){
                        mat2.matrix[(unsigned int)i]= mat.matrix.at((unsigned int)i)*number;
                }
                return mat2;
        }
        
        //boolean operators (sum the varibales in the matrix to see they are not equal)
        bool operator >(const Matrix& mat, const Matrix& mat1){
                int size = mat.matrix.size();
                double sum = 0;
                double sum1 = 0;
                double temp = 0;
                double temp1 = 0;
                int size1 = mat1.matrix.size();
                if(size != size1){
                        throw runtime_error("can't compare unequal matrix");
                }
                for(int i = 0 ; i< size;i++){
                        temp = mat.matrix.at((unsigned int)i);
                        temp1 = mat1.matrix.at((unsigned int)i);
                        sum = sum + temp;
                        sum1 = sum1 + temp1;
                }
                return(sum>sum1); 
        }
        //boolean operators (sum the varibales in the matrix to see they are not equal)
        bool operator >=(const Matrix& mat, const Matrix& mat1){
                int size = mat.matrix.size();
                double sum = 0;
                double sum1 = 0;
                double temp = 0;
                double temp1 = 0;
                int size1 = mat1.matrix.size();
                if(size != size1){
                        throw runtime_error("can't compare unequal matrix");
                }
                for(int i = 0 ; i< size;i++){
                        temp = mat.matrix.at((unsigned int)i);
                        temp1 = mat1.matrix.at((unsigned int)i);
                        sum = sum + temp;
                        sum1 = sum1 + temp1;
                }
                return (sum>=sum1);
        }
        //boolean operators (sum the varibales in the matrix to see they are not equal)
        bool operator < (const Matrix& mat, const Matrix& mat1){
                int size = mat.matrix.size();
                double sum = 0;
                double sum1 = 0;
                double temp = 0;
                double temp1 = 0;
                if(mat.column != mat1.column || mat.row != mat1.row){
                        throw runtime_error("can't compare unequal matrix");
                }
                for(int i = 0 ; i< size;i++){
                        temp = mat.matrix.at((unsigned int)i);
                        temp1 = mat1.matrix.at((unsigned int)i);
                        sum = sum + temp;
                        sum1 = sum1 + temp1;
                }
                return(sum<sum1);
        }
        //boolean operators (sum the varibales in the matrix to see they are not equal)
        bool operator <=(const Matrix& mat, const Matrix& mat1){
                int size = mat.matrix.size();
                double sum = 0;
                double sum1 = 0;
                double temp = 0;
                double temp1 = 0;
                if(mat.column != mat1.column || mat.row != mat1.row){
                        throw runtime_error("can't compare unequal matrix");
                }
                for(int i = 0 ; i< size;i++){
                        temp = mat.matrix.at((unsigned int)i);
                        temp1 = mat1.matrix.at((unsigned int)i);
                        sum = sum + temp;
                        sum1 = sum1 + temp1;
                }
                return(sum<=sum1);
        }
        //check if every variable is equal in the two matrix
        bool operator ==(const Matrix& mat, const Matrix& mat1){
                bool ans = true;
                const int row_size = mat.row;
                const int column_size = mat.column;
                if(mat.column != mat1.column || mat.row != mat1.row){
                        throw runtime_error("can't compare unequal matrix");
                }
                for(int i = 0 ; i< row_size;i++){
                        for(int j = 0 ; j< column_size;j++){
                                if(mat.matrix[(unsigned int)(i+j)] != mat1.matrix[(unsigned int)(i+j)]){
                                        ans = false;
                                }
                        }
                }
                
                return ans;
        }
        //check if every variable is not equal in the two matrix
        bool operator!=(const Matrix& mat, const Matrix& mat1){
                if(mat.column != mat1.column || mat.row != mat1.row){
                        throw runtime_error("can't compare unequal matrix");
                }
                return !(mat == mat1);
        }

        //add/or sub 1 (increment)
        Matrix& Matrix::operator++(){
                int size = (*this).matrix.size();
                for (int i = 0; i < size; i++){
                        (*this).matrix[(unsigned int)i]= (*this).matrix[(unsigned int)i]+1;
                }
                return (*this);
        } 
        // prefix  
        Matrix& Matrix::operator--(){
                int size = (*this).matrix.size();
                for (int i = 0; i < size ; i++){
                        (*this).matrix[(unsigned int)i]= (*this).matrix[(unsigned int)i]-1;
                }
                return (*this);
        }   
        // postfix
        Matrix Matrix::operator++(int num){ 
                Matrix mat_copy = *this;
                int size = mat_copy.matrix.size();
                for (int i = 0; i < size; i++){
                        (*this).matrix[(unsigned int)i]= (*this).matrix[(unsigned int)i]+1;
                }
                return mat_copy;       
        }   
        // postfix
        Matrix Matrix::operator--(int num){
                Matrix mat_copy = *this;
                int size = mat_copy.matrix.size();
                for (int i = 0; i < size; i++){
                        (*this).matrix[(unsigned int)i]= (*this).matrix[(unsigned int)i]-1;
                }
                return mat_copy;
        }   


        //IO stream operators
        ostream& operator<< (ostream& output, const Matrix& mat){
                for(int i = 0; i <mat.row; i++){
                        for(int j= 0; j< mat.column;j++){
                                if(j==0){
                                        output<<'[';
                                }
                                //add the number to the osstream
                                output<< mat.matrix.at((unsigned int)(i*mat.row+j));
                                if(j != mat.column-1){
                                        char spa = ' ';
                                        output<< spa;
                                }
                                //add the ] and \n to the osstream
                                if(j == mat.column-1){
                                        output<<']';
                                        if(i!= mat.row-1){
                                                if(i!= mat.column-1){
                                                        output<<'\n';
                                                }
                                        }
                                        
                                }
                        }
                }
                return output;
        }
        
        istream& operator>> (istream& input , Matrix& mat){
                string line;
                bool flag = false;
                bool spa = false;
                while(getline(input,line)){
                       for(int i = 0; i < line.size();i++){
                                if(flag){
                                        //if we dont get ',' aftet ] we throw error
                                        if(line[(unsigned int)i] == ',' ||line[(unsigned int)i] == '\n'){
                                                flag = false;
                                                spa = true;
                                                continue;
                                        }
                                        throw ("can't get the input mat");
                                }
                                if(spa){
                                        //if we dont get ' ' aftet , we throw error
                                        if(line[(unsigned int)i] != ' '){
                                                throw ("can't get the input mat");
                                        }
                                        spa = false;
                                }
                                if(line[0] != '['){
                                        //if we dont get in the start [ we throw error
                                        throw ("can't get the input mat");
                                }
                                if(line[(unsigned int)i] >= '0' && line[(unsigned int)i] <= '9'){
                                        double number = line[(unsigned int)i] - '0';
                                        if(mat.matrix.size() >= (i)){
                                                mat.matrix[(unsigned int)i] = number;
                                        }
                                        if(mat.matrix.size() < (i)){
                                                mat.matrix.resize(mat.matrix.size()+2,1);
                                                mat.matrix[(unsigned int)(i)] = number;
                                                
                                        }
                                }
                                if(line[(unsigned int)i] == ']'){
                                        flag = true;
                                }
                               
                       }
                }
                return input;
        }



}