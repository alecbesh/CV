

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;

TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue); // <- problem is here
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}




TEST(test_print_edge) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 4, 1);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 0, 2, blue); 
  Image_set_pixel(img, 0, 3, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n4 1\n255\n";
  correct << "255 0 0 0 255 0 0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}



TEST(test_print_edge2) {
  Image *img = new Image; 

  const Pixel red = {255, 0, 0};
  const Pixel black = {0, 0, 0};
  const Pixel white = {255, 255, 255};
  const Pixel color = {100, 150, 200};

  Image_init(img, 1, 4);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 1, 0, black);
  Image_set_pixel(img, 2, 0, color); 
  Image_set_pixel(img, 3, 0, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 4\n255\n";
  correct << "255 0 0 \n";
  correct << "0 0 0 \n";
  correct << "100 150 200 \n";
  correct << "255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}


TEST(test_image_get_and_set_pixel) {
  Image *img = new Image; 

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), white));

  delete img;
}




TEST(test_image_get_and_set_pixel2) {
  Image *img = new Image; 

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  const Pixel color = {100, 150, 200};
  const Pixel black = {0, 0, 0};

  Image_init(img, 2, 3);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  Image_set_pixel(img, 2, 0, color);
  Image_set_pixel(img, 2, 1, black);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), white));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), color));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 1), black));

  delete img;
}


TEST(test_image_fill) {
  Image *img = new Image;

  const Pixel color = {100, 100, 200};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, color);
  Image_set_pixel(img, 0, 1, color);
  Image_set_pixel(img, 1, 0, color);
  Image_set_pixel(img, 1, 1, color);

  Image *img2 = new Image;
  Image_init(img2, 2, 2);
  Image_fill(img2, color);

  ASSERT_TRUE(Image_equal(img, img2));

  delete img;
  delete img2;
}


TEST(test_image_fill_edge) {
  Image *img = new Image;

  const Pixel color = {100, 100, 200};

  Image_init(img, 1, 4);
  Image_set_pixel(img, 0, 0, color);
  Image_set_pixel(img, 1, 0, color);
  Image_set_pixel(img, 2, 0, color);
  Image_set_pixel(img, 3, 0, color);

  Image *img2 = new Image;
  Image_init(img2, 1, 4);
  Image_fill(img2, color);

  ASSERT_TRUE(Image_equal(img, img2));

  delete img;
  delete img2;
}

TEST(test_image_fill_edge2) {
  Image *img = new Image;

  const Pixel color = {100, 150, 200};

  Image_init(img, 4, 1);
  Image_set_pixel(img, 0, 0, color);
  Image_set_pixel(img, 0, 1, color);
  Image_set_pixel(img, 0, 2, color);
  Image_set_pixel(img, 0, 3, color);

  Image *img2 = new Image;
  Image_init(img2, 4, 1);
  Image_fill(img2, color);

  ASSERT_TRUE(Image_equal(img, img2));

  delete img;
  delete img2;
}


/*TEST(test_image_init_stream) {
  ifstream fin;
  fin.open("dog_4x5.correct.ppm");
  if (!fin.is_open()) {
    ASSERT_EQUAL(1, 2);
  }

  Image *img = new Image;
  const Pixel c1 = {126, 66, 0};
  const Pixel black = {0, 0, 0};
  const Pixel white = {255, 255, 250};
  const Pixel c2 = {255, 219, 183};
  const Pixel c3 = {134, 0, 0};


  Image_init(img, 4, 5);
  Image_set_pixel(img, 0, 0, black);
  Image_set_pixel(img, 0, 1, white);
  Image_set_pixel(img, 0, 2, black);
  Image_set_pixel(img, 0, 3, black);
  Image_set_pixel(img, 1, 0, white);
  Image_set_pixel(img, 1, 1, c1);
  Image_set_pixel(img, 1, 2, c1);
  Image_set_pixel(img, 1, 3, white);
  Image_set_pixel(img, 2, 0, c1);
  Image_set_pixel(img, 2, 1, black);
  Image_set_pixel(img, 2, 2, black);
  Image_set_pixel(img, 2, 3, c1);
  Image_set_pixel(img, 3, 0, c2);
  Image_set_pixel(img, 3, 1, c2);
  Image_set_pixel(img, 3, 2, c2);
  Image_set_pixel(img, 3, 3, c2);
  Image_set_pixel(img, 4, 0, c2);
  Image_set_pixel(img, 4, 1, c3);
  Image_set_pixel(img, 4, 2, black);
  Image_set_pixel(img, 4, 3, c2);

  Image *img2 = new Image;
  Image_init(img2, fin);

  ASSERT_TRUE(Image_equal(img, img2));

  delete img;
  delete img2;
}
*/



TEST(test_set_pixel) {
    Image *img = new Image;
    Pixel pix = {0, 0, 0};
    Image_init(img, 100, 100);
    bool test = true;
    for (int height = 0; height < Image_height(img); ++height) {
        for (int column = 0; column < Image_width(img); ++column) {
            Image_set_pixel(img, height, column, pix);
        }
    }
    for (int row = 0; row < Image_height(img); ++row) {
        for (int col = 0; col < Image_width(img); ++col) {
            if (Image_get_pixel(img, row, col).r != pix.r) {
                test = false;
            }
            if (Image_get_pixel(img, row, col).g != pix.g) {
                test = false;
            }
            if (Image_get_pixel(img, row, col).b != pix.b) {
                test = false;
            }
        }
    }
    assert(test == true);
    delete img;
}



// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

