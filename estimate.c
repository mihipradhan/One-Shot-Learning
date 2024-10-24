#include <stdio.h>
#include <stdlib.h>

// float **matrix;
// float **transpose;  
// float **inverse; 



double **mat (int rows, int columns){
    double **m = malloc (rows * sizeof(double *));
    m[0] = malloc(rows * columns * sizeof(double));
    
    int i; 
    for (i = 1; i < rows; i ++) m[i] = &m[0][i* columns]; 
    return m; 
}

void freeAll (double ** m, int row, int columns){

//     int i;
//    // int j; 

//     for (i =0; i < row; i++){
//         free(m[i]);
//     }
//     free(m);

    free (m[0]); 
    free (m); 
}

void transpose (double **matrix, double **returnMatrix, int rows, int columns){


    //double **returnMatrix = mat(columns, rows); 
    int i; 
    int j; 

    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){

            returnMatrix[j][i] = matrix[i][j]; 
            //printf("%lf ", returnMatrix[i][j]);
        }
        //putchar('\n');
    }
//putchar('\n');

    //return returnMatrix; 
}

void multiply (double **matrix1, double **matrix2, double **new, int rows1, int rows2, int columns1, int columns2){

    if (columns1 != rows2){
        printf("error"); 
        exit(EXIT_FAILURE); 
    }

    else{

        //double ** new = mat(rows1, columns2); 
        int t; 
        int s; 
        int a; 
        

        for (t = 0; t < rows1; t++){    /* this is traversing through the resulting matrix*/
            for (s = 0; s < columns2; s++){

                double dot = 0.0; 
                for (a = 0; a < rows2; a++){

                    dot = dot + matrix1[t][a] * matrix2[a][s]; 

                }
                new[t][s] = dot;

            }
        }

        //for (i = 0, )

        //return new; 

    }

    
}

double **divide (double **matrix, int pivotRow, int column, double divisor){

    
    int j;
    

    for (j = 0; j < column; j++){
        
        matrix[pivotRow][j] = matrix[pivotRow][j] / divisor; 
        
        // printf("%f ", matrix[pivotRow][j]);

    } 
    // putchar('\n');
    // putchar('\n');

    return matrix; 
}



double **subtract (double **matrix, int pivotRow, int rows){

    int i; 
    int j; 

    for (i = 0; i < rows; i++){

        if (i != pivotRow){

            if (matrix[i][pivotRow] != 0){
                double multiplier = matrix[i][pivotRow]; 

                for (j = 0; j < rows; j++){

                    matrix[i][j] = matrix [i][j] - (matrix[pivotRow][j] * multiplier);
                
                }
                
            }

        }


    }

    return matrix; 

}


double **subtractIdentity (double** matrix, double **identity, int pivotRow, int rows){

    int i; 
    int j; 

    for (i = 0; i < rows; i++){

        if (i != pivotRow){

            if (matrix[i][pivotRow] != 0){
                double multiplier = matrix[i][pivotRow];

                for (j = 0; j < rows; j++){
                    
                    identity[i][j] = identity [i][j] - (identity[pivotRow][j] * multiplier);
                   
                }   

            }
        }

    }

    return identity; 

}


void inverse (double **matrix, double **identity, int rows, int columns){

   // double **identity = mat(rows, columns); 

    int i; 
    int j; 
    

    //create identity matrix

    for (i = 0; i < rows; i ++){
        for (j = 0; j < columns; j++){
            if (i != j){
                identity[i][j] = 0; 
            }
            else{
                identity[i][j] = 1; 
            }
        }
    }

    for (i = 0; i < rows; i++){
       
       if (matrix[i][i] != 1){
            double divisor = matrix[i][i]; 
            matrix = divide(matrix, i, columns, divisor); 
            identity = divide(identity, i, columns, divisor); 
        }

    
       
        identity = subtractIdentity(matrix, identity, i, rows); 
      
        matrix = subtract( matrix, i, rows); 
        
        

    }

    
   
    //return identity;
}

int main(int argc, char **argv){

    FILE *t = fopen(argv[1], "r");
    FILE *d = fopen(argv[2], "r");

    int trainAtt; 
    int trainHouses; 

    int dataAtt; 
    int dataHouses; 

    char train[6]; 
    char data[6]; 

    fscanf(t, "%s", train); 
    fscanf(d, "%s", data); 

    fscanf(t, "%d", &trainAtt);
    fscanf(t, "%d", &trainHouses);
    fscanf(d, "%d", &dataAtt); 
    fscanf(d, "%d", &dataHouses); 

    if (trainAtt != dataAtt){
        printf("error"); 
        putchar('\n');
        exit(EXIT_FAILURE);
        
    }
    trainAtt = trainAtt + 1; 
    dataAtt = dataAtt +1; 

    int i; 
    int j; 

    double **trainMat = mat(trainHouses, trainAtt); 
    double **dataMat = mat(dataHouses, dataAtt);

    double **prices = mat(trainHouses, 1);

    for (i = 0; i < dataHouses; i ++){
        for (j = 0; j < dataAtt; j++){
            if (j == 0){
                dataMat[i][j] = 1.0;
            }
            else {
                fscanf(d, "%lf", &dataMat[i][j]); 
            }
           // fscanf(d, "%lf", &dataMat[i][j]); 
            //printf("%lf ", dataMat[i][j]);
        }
    }


    for (i = 0; i < trainHouses; i ++){
        for ( j = 0; j < trainAtt + 1; j++){
            if (j != trainAtt){
                if (j == 0){
                    trainMat[i][j] = 1.0; 
                }
                else {
                    fscanf(t, "%lf", &trainMat[i][j]);
                }
                
                //printf("%lf ", trainMat[i][j]);
            }
            else{
                fscanf(t, "%lf", &prices[i][0]);
            }
           
        }
    }


    double **transposeMat = mat(trainAtt, trainHouses);
    double **multiplied = mat(trainAtt, trainAtt);
    double **inversed = mat(trainAtt, trainAtt);

     

    transpose(trainMat, transposeMat, trainHouses, trainAtt);
    multiply (transposeMat, trainMat, multiplied, trainAtt, trainHouses, trainHouses, trainAtt);


    inverse(multiplied, inversed, trainAtt, trainAtt);

    double **multipliedAgain = mat(trainAtt, trainHouses);
    multiply(inversed, transposeMat, multipliedAgain, trainAtt, trainAtt, trainAtt, trainHouses);


    double **weight = mat(trainAtt,1);
    multiply(multipliedAgain, prices, weight, trainAtt, trainHouses, trainHouses, 1);
    
    //putchar('\n');
    double **newPrices = mat(dataHouses, 1);
    multiply(dataMat, weight, newPrices, dataHouses, dataAtt, trainAtt, 1);

    for (i = 0; i < dataHouses; i++){
        printf("%.0f\n", newPrices[i][0]);
       // putchar('\n');
    }

    freeAll(trainMat,trainHouses, trainAtt);
    freeAll(dataMat, dataHouses, dataAtt);
    freeAll(transposeMat, trainAtt, trainHouses);
    freeAll(multiplied, trainAtt, trainAtt);
    freeAll(inversed, trainAtt, trainAtt);
    freeAll(multipliedAgain, trainAtt, trainAtt);
    freeAll(weight, trainAtt, 1);
    freeAll(newPrices, dataHouses, 1);

    exit(EXIT_SUCCESS);
    

}