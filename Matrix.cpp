

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Matrix.h"
using namespace std;

int* Matrix_at();

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
void Matrix_init(Matrix* mat, int width, int height) {
  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << mat->width << " " << mat->height << endl;
  for (int row = 0; row < mat->height; ++row) {
    for (int col = 0; col < mat->width; ++col) {
      os << *Matrix_at(mat, row, col) << " ";
    }
    os << endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  int num = ptr - mat->data;
  return (num / Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  int num = ptr - mat->data;
  return (num % Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  int width = Matrix_width(mat);
  int index = row * width + column;
  int *ptr = &mat->data[index];
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  int width = Matrix_width(mat);
  int index = row * width + column;
  const int *ptr = &mat->data[index];
  return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for (int row = 0; row < mat->height; ++row) {
    for (int col = 0; col < mat->width; ++col) {
      *Matrix_at(mat, row, col) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  for (int row = 0; row < mat->height; ++row) {
    for (int col = 0; col < mat->width; ++col) {
      if (row == 0 || col == 0 || row == (mat->height - 1) || col == (mat->width - 1)) {
        *Matrix_at(mat, row, col) = value;
      }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max = 0;
  for (int row = 0; row < mat->height; ++row) {
    for (int col = 0; col < mat->width; ++col) {
      int temp = *Matrix_at(mat, row, col);
      if (temp > max) {
        max = temp;
      }
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  int min = 999999999;
  int colMin = 0;
  for (int col = column_start; col < column_end; ++col ) {
    int temp = *Matrix_at(mat, row, col);
    if (temp < min) {
      min = temp;
      colMin = col;
    }
  }
  return colMin;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  int min = 999999999;
  for (int col = column_start; col < column_end; ++col ) {
    int temp = *Matrix_at(mat, row, col);
    if (temp < min) {
      min = temp;
    }
  }
  return min;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the minimum value that occurs in either 
//           the left or right edges of the matrix.
int Matrix_min_value_in_side_edges(const Matrix* mat) {
  int min = Matrix_max(mat);
  for (int row = 0; row < (mat->height - 1); ++row ) {
    for (int col = 0; col < (mat->width - 1); ++col) {
      if (col == 0 || col == (mat->width - 1)) {
        int temp = *Matrix_at(mat, row, col);
        if (temp < min) min = temp;
      }
    }
  }
  return min;
}
