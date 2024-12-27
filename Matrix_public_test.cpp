

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using std::ostringstream;

TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 5);

  Matrix_fill(mat, 0);

  int *ptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 42;

  const int *cptr = Matrix_at(mat, 2, 3);
  ASSERT_EQUAL(*cptr, 42);

  Matrix_fill_border(mat, 2);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 2);

  ASSERT_EQUAL(Matrix_max(mat), 42);

  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST_MAIN()
