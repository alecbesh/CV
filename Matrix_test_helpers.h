#ifndef MATRIX_TEST_HELPERS_H
#define MATRIX_TEST_HELPERS_H

#include "Matrix.h"

// REQUIRES: mat1 points to a valid Matrix
//           mat2 points to a valid Matrix
// EFFECTS:  Returns true if mat1 and mat2 are the same size and
//           contain exactly the same elements. Returns false otherwise.
bool Matrix_equal(const Matrix* mat1, const Matrix* mat2);

// REQUIRES: arr1 and arr2 point to arrays of length n
// EFFECTS:  Returns true if the arrays pointed to by arr1 and arr2
//           contain exactly the same elements. Returns false otherwise.
bool array_equal(const int arr1[], const int arr2[], int n);

#endif // MATRIX_TEST_HELPERS_H
