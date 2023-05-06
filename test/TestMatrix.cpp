#include "gtest/gtest.h"
#include "data-structures/Matrix.h"

// Sprawdzenie tworzenia macierzy o rozmiarze 0
TEST(CreateMatrix, ZeroDegree){

    Matrix matrix(0);
    
    ASSERT_EQ(matrix.getDegree(), 0);
    ASSERT_EQ(matrix.get(0,0), nullptr);

}


// Sprawdzenie tworzenia macierzy o dowolnym rozmiarze
TEST(CreateMatrix, AnyDegree){

    Matrix* matrix;
    for(int n = 1; n < 100; n++){
        matrix = new Matrix(n, 2*n);
        ASSERT_EQ(matrix->getDegree(), n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                ASSERT_EQ(*matrix->get(i,j), 2*n);
        
        delete matrix;
    }

}

// Uzupełnienie macierzy wartościami
TEST(Fill, FillMatrix){

    // Stworznenie
    Matrix matrix(3);
    int elements[] = {
        0, 1, 4,
        6, 8, 11,
        1, 4, 78
    };

    // Wypełnienie
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            *matrix.get(i, j) = elements[i * 3 + j];
    
    // Sprawdzenie
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ASSERT_EQ(*matrix.get(i,j), elements[i * 3 + j]);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
