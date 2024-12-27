

#include <cassert>
#include "processing.h"
#include "Image.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}

// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}


// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  const int width = Image_width(img);
  const int height = Image_height(img);

  Matrix_init(energy, width, height);
  Matrix_fill(energy, 0);

  for (int row = 1; row < (height - 1); ++row) {
    for (int col = 1; col < (width - 1); ++col) {
      Pixel N = Image_get_pixel(img, (row - 1), col);
      Pixel S = Image_get_pixel(img, (row + 1), col);
      Pixel E = Image_get_pixel(img, row, (col + 1));
      Pixel W = Image_get_pixel(img, row, (col - 1));

      int pix_energy = squared_difference(N, S) + squared_difference(W, E);
      *Matrix_at(energy, row, col) = pix_energy;
    }
  }
  int max = Matrix_max(energy);
  Matrix_fill_border(energy, max);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  const int width = Matrix_width(energy);
  const int height = Matrix_height(energy);

  Matrix_init(cost, width, height);

  for (int col = 0; col < width; ++col) {
    *Matrix_at(cost, 0, col) = *Matrix_at(energy, 0, col);
  }

  for (int row = 1; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      if (col == 0) {
        int min = Matrix_min_value_in_row(cost, (row - 1), 0, 2);
        int pixEnergy = *Matrix_at(energy, row, col);
        *Matrix_at(cost, row, col) = pixEnergy + min;
      }
      else if (col == (width - 1)) {
        int min = Matrix_min_value_in_row(cost, (row - 1), (col - 1), (col + 1));
        int pixEnergy = *Matrix_at(energy, row, col);
        *Matrix_at(cost, row, col) = pixEnergy + min;
      }
      else {
        int min = Matrix_min_value_in_row(cost, (row - 1), (col - 1), (col + 2));
        int pixEnergy = *Matrix_at(energy, row, col);
        *Matrix_at(cost, row, col) = pixEnergy + min;
      }
    }
  }
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  const int width = Matrix_width(cost);
  const int height = Matrix_height(cost);

  int firstColMin = Matrix_column_of_min_value_in_row(cost, (height - 1), 0, (width));
  seam[height - 1] = firstColMin;

  for (int row = (height - 2); row >= 0; row--) {
    if (seam[row + 1] == 0) {
      int colMin = Matrix_column_of_min_value_in_row(cost, row, 0, 2);
      seam[row] = colMin;
    }
    else if (seam[row + 1] == (width - 1)) {
      int colMin = Matrix_column_of_min_value_in_row(cost, row, (width - 2), (width));
      seam[row] = colMin;
    }
    else {
      int colStart = seam[row + 1] - 1;
      int colEnd = seam[row + 1] + 1;
      int colMin = Matrix_column_of_min_value_in_row(cost, row, colStart, (colEnd + 1));
      seam[row] = colMin;
    }
  }
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
void remove_vertical_seam_end(Image *img, Image *tempImg, int col, int row) {
  Pixel pix;
  const int width = Image_width(img);
  for (int col2 = (col + 1); col2 < (width); ++col2) {
    pix = Image_get_pixel(img, row, col2);
    Image_set_pixel(tempImg, row, col2 - 1, pix);
  }
}

void remove_vertical_seam(Image *img, const int seam[]) {
  Image &tempImg = *new Image;
  const int width = Image_width(img);
  const int height = Image_height(img);
  Image_init(&tempImg, width - 1, height);

  Pixel pix;
  for (int row = 0; row < (height); ++row) {
    for (int col = 0; col < (width); ++ col) {
      if (seam[row] != col) {
        pix = Image_get_pixel(img, row, col);
        Image_set_pixel(&tempImg, row, col, pix);
      }
      else {
        remove_vertical_seam_end(img, &tempImg, col, row);
        // for (int col2 = (col + 1); col2 < (width); ++col2) {
        //   pix = Image_get_pixel(img, row, col2);
        //   Image_set_pixel(&tempImg, row, col2 - 1, pix);
        col = (width - 1);
      } 
    }
  }
  *img = tempImg;
  delete &tempImg;
}



// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
void seam_carve_width(Image *img, int newWidth) {
  const int width = Image_width(img);
  const int height = Image_height(img);
  Matrix *energy = new Matrix;
  Matrix *cost = new Matrix;
  Matrix_init(energy, width, height);
  Matrix_init(cost, width, height);
  int seam[500];
  
  for (int i = newWidth; (newWidth <= i) && (i < width); ++i) {
    compute_energy_matrix(img, energy);
    compute_vertical_cost_matrix(energy, cost);
    find_minimal_vertical_seam(cost, seam);
    remove_vertical_seam(img, seam);
  }
  delete energy;
  delete cost;
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}


