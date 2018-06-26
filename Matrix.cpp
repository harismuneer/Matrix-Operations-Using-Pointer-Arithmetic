#include <iostream>
using namespace std;

int** AllocateMatrix (int ROWS, int COLS);
int** InputMatrix ( int& ROWS, int& COLS);
void OutputMatrix (int** matrix, const int ROWS, const int COLS);
int** AddMatrix(int** matrixA, int** matrixB, const int ROWS, const int COLS);
int** TransposeMatrix(int** matrix, const int ROWS, const int COLS);
bool IsSymmetric(int** matrix, const int ROWS, const int COLS);
void InterchangeRows(int** matrix, const int ROWS, const int COLS );
void InterchangeRows( int* &row1, int* &row2 );
void deAllocateMatrix(int** &matrix, const int ROWS);



int** AllocateMatrix (int ROWS, int COLS)
{
    //Code to Allocate a 2D Matrix
    int** matrix = new int* [ROWS];

    for ( int i = 0 ; i < ROWS ; i++)
         matrix[i] = new int [COLS];

    return matrix;
}


int** InputMatrix ( int& ROWS, int& COLS)
{
  cout << "Total Number of Rows : ";
  cin  >> ROWS ;

   while ( ROWS <=0 )
   {
        cout <<"You have entered an invalid number . Enter the Rows again : " << endl;
        cin >> ROWS;
   }

  cout << "Total Number of Columns : ";
  cin  >> COLS ;

  while ( COLS<=0 )
   {
        cout <<"You have entered an invalid number . Enter the Columns again : " << endl;
        cin >> COLS;
   }


  int** matrix = NULL;

    matrix = AllocateMatrix (ROWS , COLS);


    //Code to input numbers in the 2D Matrix
     cout <<endl<<"Enter the elements of the Matrix in 'row major order' : " << endl;

     int** endRowPtr = matrix + ROWS;

     for(int** rowPtr = matrix ; rowPtr < endRowPtr ; rowPtr++ )
     {
         int* endColPtr = *rowPtr + COLS;

         for(int* colPtr = *rowPtr ; colPtr < endColPtr ; colPtr++)
                cin >> *colPtr;
     }

     return matrix;
}


void OutputMatrix (int** matrix, const int ROWS, const int COLS)
{
    int** endRowPtr = matrix + ROWS;

     for(int** rowPtr = matrix ; rowPtr < endRowPtr ; rowPtr++ )
     {
         int* endColPtr = *rowPtr + COLS;

         cout << endl;

         for(int* colPtr = *rowPtr ; colPtr < endColPtr ; colPtr++)
              cout << *colPtr << "     ";

     }
     cout << endl;
}


int** AddMatrix(int** matrixA, int** matrixB, const int ROWS, const int COLS)
{
    //Code to allocate the third Matrix i.e. Matrix C
    int** matrixC = NULL;
    matrixC = AllocateMatrix (ROWS , COLS);

   int* colPtrA = NULL ; int*  colPtrB = NULL ; int*  colPtrC = NULL;
   int* endColPtrA = NULL ; int* endColPtrB = NULL ; int*  endColPtrC = NULL;

   int** rowPtrA = matrixA;
   int** rowPtrB = matrixB;
   int** rowPtrC = matrixC;
   int** endRowPtrA = matrixA + ROWS;
   int** endRowPtrB = matrixB + ROWS;
   int** endRowPtrC = matrixC + ROWS;

     while( (rowPtrA < endRowPtrA) && (rowPtrB < endRowPtrB) && (rowPtrC < endRowPtrC) )
     {
         endColPtrA = *rowPtrA + COLS;
         endColPtrB = *rowPtrB + COLS;
         endColPtrC = *rowPtrC + COLS;

          colPtrA = *rowPtrA;
          colPtrB = *rowPtrB;
          colPtrC = *rowPtrC;

          while( (colPtrA < endColPtrA) && (colPtrB < endColPtrB) && (colPtrC < endColPtrC) )
          {
              *colPtrC = *colPtrA + *colPtrB;

               colPtrA++;
               colPtrB++;
               colPtrC++;
          }

         rowPtrA++;
         rowPtrB++;
         rowPtrC++;
     }

   return matrixC;
}


int** TransposeMatrix(int** matrix, const int ROWS, const int COLS)
{
   //Allocate the memory of the Transpose Matrix dynamically on Heap
   int** matrixD = NULL;
   matrixD = AllocateMatrix (COLS , ROWS);

   int** rowPtr = matrix;
   int*  colPtr = *rowPtr ;
   int** endRowPtr = matrix + ROWS;
   int*  endColPtr = *rowPtr + COLS;
   int   i = 0;
   int** rowPtrD = matrixD;
   int*  colPtrD = *rowPtrD;
   int** endRowPtrD = matrixD + COLS;
   int*  endColPtrD = *rowPtrD + ROWS;

    while ( rowPtrD < endRowPtrD )
    {
       rowPtr = matrix;
       colPtrD = *rowPtrD;

          while ( rowPtr < endRowPtr )
           {
                colPtr = *rowPtr + i;
               *colPtrD  = *colPtr;

                colPtrD++;
                rowPtr++;
            }

       i++;
       rowPtrD++;
    }

  return matrixD;
}


bool IsSymmetric(int** matrix, const int ROWS, const int COLS)
{
   bool isSymmetric = true;

   for (int i = 0 ; i < ROWS && isSymmetric ; i++)
   {
       for (int j = 0 ; j < COLS && isSymmetric ; j++)
      {
        if ( matrix[i][j] != matrix[j][i] )
               isSymmetric = false;
      }
   }

   return isSymmetric;
}


void InterchangeRows(int** matrix, const int ROWS, const int COLS )
{
  int rowOne , rowTwo = 0;

  cout << endl << "Enter row1 : ";
  cin >> rowOne;

    while( rowOne <= 0 || rowOne > ROWS)
    {
      cout << "You have entered an invalid Row Number . Enter a valid Row1 :"<< endl;
      cin >> rowOne;
    }

  cout << "Enter row2 : ";
  cin >> rowTwo;

    while( rowTwo <= 0 || rowTwo > ROWS)
    {
      cout << "You have entered an invalid Row Number . Enter a valid Row2 :"<< endl;
      cin >> rowTwo;
    }

  int* row1 =  *( matrix + (rowOne - 1) );
  int* row2 =  *( matrix + (rowTwo - 1) );

  InterchangeRows (row1 , row2);

  *( matrix + (rowOne - 1) )  = row1;
  *( matrix + (rowTwo - 1) )  = row2;

}


void InterchangeRows( int* &row1, int* &row2 )
{
  int* temp = NULL;

    temp = row1;
    row1 = row2;
    row2 = temp;
}


void deAllocateMatrix(int** &matrix, const int ROWS)
{
    if(matrix)
    {
     for ( int i = 0 ; i < ROWS ; i++)
           delete[] matrix[i];

     delete[] matrix;
    }

   matrix = NULL;
}



int main()
{
    int rowsA, colsA, rowsB, colsB = 0 ;
    int** matrixA  = NULL;
    int** matrixB  = NULL;
    int** matrixC  = NULL; //Matrix after addition of Matrix A and Matrix B
    int** matrixAT = NULL; //Transpose of Matrix A
    int** matrixBT = NULL; //Transpose of Matrix B

    //Code to call Input And Output Functions to get Matrices from user and display them
    cout << "Enter Matrix A : " << endl;
    matrixA = InputMatrix (rowsA , colsA);

    cout << endl <<"Enter Matrix B : " << endl;
    matrixB = InputMatrix (rowsB, colsB);

    cout << endl << "Matix A = ";
    OutputMatrix (matrixA , rowsA , colsA);

    cout << endl << "Matrix B = ";
    OutputMatrix (matrixB , rowsB , colsB);


    /////Code to call the AddMatrix Function and Display the resultant Matrix i.e MatrixC
      if ( (rowsA == rowsB) && (colsA == colsB) )
      {
         matrixC = AddMatrix (matrixA, matrixB ,rowsA ,colsA); // becuase rowsA and rowsB are same and colsA and colsB are same.
         cout << endl << "A + B = " ;
         OutputMatrix (matrixC , rowsA , colsA); //becuase matrix C will have the same rows and columns as that of Matrix A and Matrix B
      }
      else
        cout <<endl<< "Matrices CANNOT be ADDED as they are of DIFFERENT SIZE. "<<endl;


    //////Code to call the TranposeMatrix Function and Display the resultant Matrices i.e MatrixAT and MatrixBT
      cout << endl << "Transpose of A =";
      matrixAT = TransposeMatrix (matrixA , rowsA ,colsA);
      OutputMatrix (matrixAT , colsA ,rowsA);

      cout << endl << "Transpose of B =";
      matrixBT = TransposeMatrix (matrixB , rowsB ,colsB);
      OutputMatrix (matrixBT, colsB ,rowsB);


    ///////Code to call the IsSymmetric Function to check whether the matrices are Symmetric or NOT

    if (rowsA != colsA)
        cout <<endl<< "Since the MatrixA is not a square matrix." <<endl<<"So by definiton , it can NEVER be a Symmetric Matrix";

    else
    {
       if( IsSymmetric(matrixA , rowsA , colsA))
          cout <<endl<< "Matrix A is Symmetric. " << endl;
        else
          cout <<endl << "Matrix A is NOT Symmetric. "<< endl;
    }


    if (rowsB != colsB)
        cout <<endl<< "Since the MatrixB is not a square matrix." <<endl<<"So by definiton , it can NEVER be a Symmetric Matrix"<<endl;

    else
    {
       if ( IsSymmetric(matrixB , rowsB , colsB) )
          cout <<endl<< "Matrix B is Symmetric. " << endl;
        else
          cout <<endl << "Matrix B is NOT Symmetric. "<< endl;
    }

    //////Code to call the InterchangeRows Function and display the results

       cout <<endl << "Interchanging rows of Matrix A :";
       InterchangeRows(matrixA , rowsA , colsA );
       cout <<endl << "After Interchanging Rows Matrix A =";
       OutputMatrix (matrixA, rowsA , colsA);

       cout <<endl << "Interchanging rows of Matrix B :";
       InterchangeRows(matrixB , rowsB , colsB );
       cout <<endl << "After Interchanging Rows Matrix B =";
       OutputMatrix (matrixB , rowsB , colsB);


    ////Code to de-allocate all the Matrices
    deAllocateMatrix(matrixA , rowsA);
    cout<< endl<< "MatrixA has been succesfully de-allocated .";
    deAllocateMatrix(matrixB , rowsB);
    cout <<endl<< "MatrixB has been succesfully de-allocated .";
    deAllocateMatrix(matrixC , rowsA);
    cout <<endl<< "MatrixC has been succesfully de-allocated .";
    deAllocateMatrix(matrixAT , colsA);
    cout <<endl<< "MatrixAT has been succesfully de-allocated .";
    deAllocateMatrix(matrixBT , colsB);
    cout <<endl<< "MatrixBT has been succesfully de-allocated .";

  //system("pause");
  return 0;
}
