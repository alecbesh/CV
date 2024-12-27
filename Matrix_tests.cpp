

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <cassert>

using namespace std;

TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}


TEST(test_fill_edge) {
  Matrix *mat = new Matrix; 
  const int width = 1;
  const int height = 10;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; 
}


TEST(test_fill_edge2) {
  Matrix *mat = new Matrix; 
  const int width = 10;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; 
}


TEST(test_matrix_print) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 3, 3);
  *Matrix_at(mat, 0, 0) = 0;
  *Matrix_at(mat, 0, 1) = 10;
  *Matrix_at(mat, 0, 2) = 20;
  *Matrix_at(mat, 1, 0) = 5;
  *Matrix_at(mat, 1, 1) = 15;
  *Matrix_at(mat, 1, 2) = 25;
  *Matrix_at(mat, 2, 0) = 0;
  *Matrix_at(mat, 2, 1) = 0;
  *Matrix_at(mat, 2, 2) = 0;

  // Capture our output
  ostringstream s;
  Matrix_print(mat, s);

  // Correct output
  ostringstream correct;
  correct << "3 3\n";
  correct << "0 10 20 \n";
  correct << "5 15 25 \n";
  correct << "0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}




TEST(test_matrix_print2) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 6, 1);
  *Matrix_at(mat, 0, 0) = 0;
  *Matrix_at(mat, 0, 1) = 10;
  *Matrix_at(mat, 0, 2) = 20;
  *Matrix_at(mat, 0, 3) = 5;
  *Matrix_at(mat, 0, 4) = 15;
  *Matrix_at(mat, 0, 5) = 25;
  

  // Capture our output
  ostringstream s;
  Matrix_print(mat, s);

  // Correct output
  ostringstream correct;
  correct << "6 1\n";
  correct << "0 10 20 5 15 25 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}




TEST(test_matrix_print3) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 1, 6);
  *Matrix_at(mat, 0, 0) = 0;
  *Matrix_at(mat, 1, 0) = 10;
  *Matrix_at(mat, 2, 0) = 20;
  *Matrix_at(mat, 3, 0) = 5;
  *Matrix_at(mat, 4, 0) = 15;
  *Matrix_at(mat, 5, 0) = 25;
  

  // Capture our output
  ostringstream s;
  Matrix_print(mat, s);

  // Correct output
  ostringstream correct;
  correct << "1 6\n";
  correct << "0 \n";
  correct << "10 \n";
  correct << "20 \n";
  correct << "5 \n";
  correct << "15 \n";
  correct << "25 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
}




TEST(test_fill_border_basic) {
  Matrix *mat = new Matrix; 
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if (r == 0 || c == 0 || r == (height - 1) || c == (width - 1)) {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
      }
      else {
        ASSERT_NOT_EQUAL(*Matrix_at(mat, r, c), value);
      }
    }
  }

  delete mat;
}


TEST(test_fill_border_edge) {
  Matrix *mat = new Matrix; 
  const int width = 1;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if (r == 0 || c == 0 || r == (height - 1) || c == (width - 1)) {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
      }
    }
  }

  delete mat;
}


TEST(test_fill_border_edge2) {
  Matrix *mat = new Matrix; 
  const int width = 1;
  const int height = 10;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if (r == 0 || c == 0 || r == (height - 1) || c == (width - 1)) {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
      }
    }
  }

  delete mat;
}



TEST(test_fill_border_edge3) {
  Matrix *mat = new Matrix; 
  const int width = 10;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if (r == 0 || c == 0 || r == (height - 1) || c == (width - 1)) {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(mat, r, c), 0);
      }
    }
  }

  delete mat;
}

TEST(test_matrix_width_and_height) {
  Matrix *mat = new Matrix;
  const int width = 500;
  const int height = 100;

  Matrix_init(mat, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}


TEST(test_matrix_width_and_height_edge) {
  Matrix *mat = new Matrix;
  const int width = 1;
  const int height = 1;

  Matrix_init(mat, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}



TEST(test_matrix_max) {
  Matrix *mat = new Matrix; 
  
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat,0,0) = 45;
  *Matrix_at(mat,0,1) = 0;
  *Matrix_at(mat,0,2) = -69;
  *Matrix_at(mat,1,0) = 68;
  *Matrix_at(mat,1,1) = 69;
  *Matrix_at(mat,1,2) = 0;
  *Matrix_at(mat,2,0) = 69;
  *Matrix_at(mat,2,1) = 70;
  *Matrix_at(mat,2,2) = 21;

  ASSERT_EQUAL(Matrix_max(mat), 70);


  delete mat;
} 



TEST(test_matrix_max_edge) {
  Matrix *mat = new Matrix; 
  
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat,0,0) = 100;
  *Matrix_at(mat,0,1) = 0;
  *Matrix_at(mat,0,2) = -69;
  *Matrix_at(mat,1,0) = 68;
  *Matrix_at(mat,1,1) = 69;
  *Matrix_at(mat,1,2) = 0;
  *Matrix_at(mat,2,0) = 69;
  *Matrix_at(mat,2,1) = 70;
  *Matrix_at(mat,2,2) = 21;

  ASSERT_EQUAL(Matrix_max(mat), 100);


  delete mat;
}



TEST(test_matrix_max_edge2) {
  Matrix *mat = new Matrix; 
  
  Matrix_init(mat, 3, 3);
  *Matrix_at(mat,0,0) = 100;
  *Matrix_at(mat,0,1) = 0;
  *Matrix_at(mat,0,2) = -69;
  *Matrix_at(mat,1,0) = 68;
  *Matrix_at(mat,1,1) = 69;
  *Matrix_at(mat,1,2) = 0;
  *Matrix_at(mat,2,0) = 69;
  *Matrix_at(mat,2,1) = 70;
  *Matrix_at(mat,2,2) = 101;

  ASSERT_EQUAL(Matrix_max(mat), 101);


  delete mat;
}



TEST(test_column_of_min_value_in_row) {
  Matrix *mat = new Matrix; 
  
  Matrix_init(mat, 4, 4);
  *Matrix_at(mat,0,0) = 0;
  *Matrix_at(mat,0,1) = 70;
  *Matrix_at(mat,0,2) = 68;
  *Matrix_at(mat,1,2) = 21;
  *Matrix_at(mat,1,1) = 70;
  *Matrix_at(mat,1,0) = 21;
  *Matrix_at(mat,2,0) = 7;
  *Matrix_at(mat,2,1) = 7;
  *Matrix_at(mat,2,2) = 6;
  *Matrix_at(mat,3,0) = 7;
  *Matrix_at(mat,3,1) = 1;
  *Matrix_at(mat,3,2) = 6;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 3), 2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 3, 0, 3), 1);


  delete mat;
}



TEST(test_min_value_in_row) {
  Matrix *mat = new Matrix; 
  
  Matrix_init(mat, 5, 5);
  *Matrix_at(mat,0,0) = 1;
  *Matrix_at(mat,0,1) = 70;
  *Matrix_at(mat,0,2) = 68;
  *Matrix_at(mat,0,3) = -2;
  *Matrix_at(mat,0,4) = 20;
  *Matrix_at(mat,1,4) = 0;
  *Matrix_at(mat,1,3) = 100;
  *Matrix_at(mat,1,2) = 21;
  *Matrix_at(mat,1,1) = 70;
  *Matrix_at(mat,1,0) = 20;
  *Matrix_at(mat,2,0) = 100;
  *Matrix_at(mat,2,1) = 999;
  *Matrix_at(mat,2,2) = 101;
  *Matrix_at(mat,2,3) = 120;
  *Matrix_at(mat,2,4) = 1700;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), (-2));
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 5), 100);



  delete mat;
}


TEST(test_matrix_row_and_col) {
  const int* ptr;
  Matrix *mat = new Matrix;

  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 1);

  ptr = (Matrix_at(mat,2,2));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 2);

  ptr = (Matrix_at(mat,0,0));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

  ptr = (Matrix_at(mat,0,4));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);

  ptr = (Matrix_at(mat,4,0));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

  ptr = (Matrix_at(mat,4,4));
  ASSERT_EQUAL(Matrix_row(mat, ptr), 4);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 4);

  delete mat;
}


TEST(test_matrix_at) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  *Matrix_at(mat,0,0) = 69;

  cout << "TEST PTR: " << Matrix_at(mat,0,0) << endl;
  cout << "TEST ELEMENT: " << *Matrix_at(mat,0,0) << endl;

  ASSERT_EQUAL(69, *Matrix_at(mat,0,0));
  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

