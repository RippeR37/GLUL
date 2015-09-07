#include <gtest/gtest.h>

#include <Utils/Image.h>

#include <glm/vec2.hpp>

#include <cstring>


bool isValidImageData(unsigned char* imageData, unsigned int bits) {
    static unsigned char templateData24[16] = { 
        255, 0, 0,   255, 255, 255,   0, 0,
        0, 0, 255,   0, 255, 0,       0, 0,
    };
    static unsigned char templateData32[16] = { 
        255, 0, 0, 255,   255, 255, 255, 255,
        0, 0, 255, 255,   0, 255, 0, 255
    };
    bool areSame = true;

    if(bits == 24) {
        areSame = areSame && (0 == std::memcmp(imageData, templateData24, 6));          // ignore row alignment
        areSame = areSame && (0 == std::memcmp(imageData + 8, templateData24 + 8, 6));  // ignore row alignment
    } else {
        areSame = areSame && (0 == std::memcmp(imageData, templateData32, 16));
    }

    return areSame;
}


TEST(Utils_Image, Constructor_Empty) {
    Util::Image image;

    ASSERT_EQ(nullptr, image.getData());
    ASSERT_EQ(0u, image.getBits());
    ASSERT_EQ(0u, image.getWidth());
    ASSERT_EQ(0u, image.getHeight());
    ASSERT_EQ(0u, image.getSize());
}

TEST(Utils_Image, Constructor_Path_Format_Existing) {
    ASSERT_NO_THROW(
    {
        Util::Image image("test_assets/image/image.bmp");

        ASSERT_NE(nullptr, image.getData());
        ASSERT_EQ(24u, image.getBits());
        ASSERT_EQ(2u,  image.getWidth());
        ASSERT_EQ(2u,  image.getHeight()); 
        ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)

        ASSERT_TRUE(isValidImageData(image.getData(), 24u));
    });
}

TEST(Utils_Image, Constructor_Path_Format_Non_Existing) {
    ASSERT_THROW({
        Util::Image image("test_assets/image/nonexisting.bmp");
    }, Util::Exception::InitializationFailed);
}

TEST(Utils_Image, Constructor_Copy_Empty) {
    ASSERT_NO_THROW({
        Util::Image image;
        Util::Image imageCopy(image);

        ASSERT_EQ(nullptr, image.getData());
        ASSERT_EQ(0u, image.getBits());
        ASSERT_EQ(0u, image.getWidth());
        ASSERT_EQ(0u, image.getHeight());
        ASSERT_EQ(0u, image.getSize());
    
        ASSERT_EQ(nullptr, imageCopy.getData());
        ASSERT_EQ(0u, imageCopy.getBits());
        ASSERT_EQ(0u, imageCopy.getWidth());
        ASSERT_EQ(0u, imageCopy.getHeight());
        ASSERT_EQ(0u, imageCopy.getSize());
    });
}

TEST(Utils_Image, Constructor_Copy_Loaded) {
    ASSERT_NO_THROW({
        Util::Image image("test_assets/image/image.bmp");
        Util::Image imageCopy(image);

        ASSERT_NE(nullptr, image.getData());
        ASSERT_NE(nullptr, imageCopy.getData());
        ASSERT_NE(image.getData(), imageCopy.getData());
        ASSERT_EQ(0, std::memcmp(image.getData(), imageCopy.getData(), image.getSize()));

        ASSERT_EQ(24u, image.getBits());
        ASSERT_EQ(24u, imageCopy.getBits());
        ASSERT_EQ(2u,  image.getWidth());
        ASSERT_EQ(2u,  imageCopy.getWidth());
        ASSERT_EQ(2u,  image.getHeight());
        ASSERT_EQ(2u,  imageCopy.getHeight());
        ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
        ASSERT_EQ(16u, imageCopy.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)

        ASSERT_TRUE(isValidImageData(image.getData(), 24u));
        ASSERT_TRUE(isValidImageData(imageCopy.getData(), 24u));
    });
}

TEST(Utils_Image, Constructor_Move) {
    ASSERT_NO_THROW({
        Util::Image image("test_assets/image/image.bmp"); // this should be empty after being moved
        Util::Image image2(std::move(image)); // this should be image.bmp

        ASSERT_EQ(nullptr, image.getData());
        ASSERT_EQ(0u, image.getBits());
        ASSERT_EQ(0u, image.getWidth());
        ASSERT_EQ(0u, image.getHeight());
        ASSERT_EQ(0u, image.getSize());

        ASSERT_NE(nullptr, image2.getData());
        ASSERT_EQ(24u, image2.getBits());
        ASSERT_EQ(2u,  image2.getWidth());
        ASSERT_EQ(2u,  image2.getHeight()); 
        ASSERT_EQ(16u, image2.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
        ASSERT_TRUE(isValidImageData(image2.getData(), 24u));
    });
}

TEST(Utils_Image, Assignment_Existing) {
    ASSERT_NO_THROW({
        Util::Image image("test_assets/image/image.bmp");
        Util::Image image2;

        image2 = image;

        ASSERT_NE(nullptr, image.getData());
        ASSERT_EQ(24u, image.getBits());
        ASSERT_EQ(2u,  image.getWidth());
        ASSERT_EQ(2u,  image.getHeight()); 
        ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
        ASSERT_TRUE(isValidImageData(image.getData(), 24u));

        ASSERT_NE(nullptr, image2.getData());
        ASSERT_EQ(24u, image2.getBits());
        ASSERT_EQ(2u,  image2.getWidth());
        ASSERT_EQ(2u,  image2.getHeight()); 
        ASSERT_EQ(16u, image2.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
        ASSERT_TRUE(isValidImageData(image2.getData(), 24u));

        ASSERT_NE(image.getData(), image2.getData());
    });
}

TEST(Utils_Image, Load_Unsupported) {
    Util::Image image;

    ASSERT_THROW({
        image.load("test_assets/image/image.unsupported_extension");
    }, Util::Exception::InitializationFailed);

    ASSERT_EQ(nullptr, image.getData());
    ASSERT_EQ(0u, image.getBits());
    ASSERT_EQ(0u, image.getWidth());
    ASSERT_EQ(0u, image.getHeight());
    ASSERT_EQ(0u, image.getSize());
}

TEST(Utils_Image, Load_From_Array) {
    Util::Image image("test_assets/image/image.bmp");
    Util::Image image2;

    image2.load(image.getWidth(), image.getHeight(), image.getBits(), image.getData(), true);

    ASSERT_NE(image.getData(), image2.getData());
    ASSERT_NE(nullptr, image.getData());
    ASSERT_EQ(24u, image.getBits());
    ASSERT_EQ(2u,  image.getWidth());
    ASSERT_EQ(2u,  image.getHeight()); 
    ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)

    ASSERT_TRUE(isValidImageData(image.getData(), 24u));
}

TEST(Utils_Image, Load_BMP) {
    Util::Image image;

    image.load("test_assets/image/image.bmp");

    ASSERT_NE(nullptr, image.getData());
    ASSERT_EQ(24u, image.getBits());
    ASSERT_EQ(2u,  image.getWidth());
    ASSERT_EQ(2u,  image.getHeight()); 
    ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)

    ASSERT_TRUE(isValidImageData(image.getData(), 24u));
}

TEST(Utils_Image, Load_TGA) {
    Util::Image image;

    image.load("test_assets/image/image.tga");

    ASSERT_NE(nullptr, image.getData());
    ASSERT_EQ(24u, image.getBits());
    ASSERT_EQ(2u,  image.getWidth());
    ASSERT_EQ(2u,  image.getHeight()); 
    ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
    
    ASSERT_TRUE(isValidImageData(image.getData(), 24u));
}

TEST(Utils_Image, Load_PNG) {
    Util::Image image;

    image.load("test_assets/image/image.png");

    ASSERT_NE(nullptr, image.getData());
    ASSERT_EQ(32u, image.getBits());
    ASSERT_EQ(2u,  image.getWidth());
    ASSERT_EQ(2u,  image.getHeight()); 
    ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)
    
    ASSERT_TRUE(isValidImageData(image.getData(), 32u));
}

TEST(Utils_Image, Load_JPG) {
    Util::Image image;

    image.load("test_assets/image/image.jpg");

    ASSERT_NE(nullptr, image.getData());
    ASSERT_EQ(24u, image.getBits());
    ASSERT_EQ(2u,  image.getWidth());
    ASSERT_EQ(2u,  image.getHeight()); 
    ASSERT_EQ(16u, image.getSize()); // size = (bits / 8) * height * rowStride (where rowstride is aligned row's size)

    /**
     * Due to JPEG compression some color data are lost on write, so we have special test case for this format.
     */
    static unsigned char templateData[16] = { 
        254, 0, 0,   255, 255, 255,   0, 0,
        0, 0, 254,   0, 255, 1,       0, 0,
    };

    ASSERT_EQ(0, std::memcmp(image.getData(), templateData, 1));
}

TEST(Utils_Image, Load_Reset) {
    Util::Image image;

    image.load("test_assets/image/image.bmp");
    ASSERT_NE(nullptr, image.getData());
    ASSERT_NE(0u, image.getBits());
    ASSERT_NE(0u, image.getWidth());
    ASSERT_NE(0u, image.getHeight());
    ASSERT_NE(0u, image.getSize());

    image.reset();
    ASSERT_EQ(nullptr, image.getData());
    ASSERT_EQ(0u, image.getBits());
    ASSERT_EQ(0u, image.getWidth());
    ASSERT_EQ(0u, image.getHeight());
    ASSERT_EQ(0u, image.getSize());
}

TEST(Utils_Image, Swap_Components_One_Line) {
    unsigned char rgbData[12]  = { 0, 0, 1,  1, 0, 0,  2, 0, 1,  3, 2, 1 };
    unsigned char bgrData[12]  = { 1, 0, 0,  0, 0, 1,  1, 0, 2,  1, 2, 3 };
    unsigned char rgbaData[16] = { 0, 0, 1, 5,  1, 0, 0, 5,  2, 0, 1, 5,  3, 2, 1, 5 };
    unsigned char bgraData[16] = { 1, 0, 0, 5,  0, 0, 1, 5,  1, 0, 2, 5,  1, 2, 3, 5 };

    unsigned char array1[12]; std::copy(std::begin(rgbData), std::end(rgbData), std::begin(array1));
    unsigned char array2[12]; std::copy(std::begin(bgrData), std::end(bgrData), std::begin(array2));
    unsigned char array3[16]; std::copy(std::begin(rgbaData), std::end(rgbaData), std::begin(array3));
    unsigned char array4[16]; std::copy(std::begin(bgraData), std::end(bgraData), std::begin(array4));

    Util::Image::swapComponents(4, 1, 24, array1);
    Util::Image::swapComponents(4, 1, 24, array2);
    Util::Image::swapComponents(4, 1, 32, array3);
    Util::Image::swapComponents(4, 1, 32, array4);

    ASSERT_EQ(0, std::memcmp(array1, bgrData, 12));
    ASSERT_EQ(0, std::memcmp(array2, rgbData, 12));
    ASSERT_EQ(0, std::memcmp(array3, bgraData, 16));
    ASSERT_EQ(0, std::memcmp(array4, rgbaData, 16));
}

TEST(Utils_Image, Swap_Components_Multiline) {
    unsigned char rgbData[16]  = { 0, 0, 1,  1, 0, 0,  9, 9,    2, 0, 1,  3, 2, 1,  9, 9 }; // 9s are rowStride
    unsigned char bgrData[16]  = { 1, 0, 0,  0, 0, 1,  9, 9,    1, 0, 2,  1, 2, 3,  9, 9 }; // 9s are rowstride
    
    unsigned char array1[16]; std::copy(std::begin(rgbData), std::end(rgbData), std::begin(array1));
    unsigned char array2[16]; std::copy(std::begin(bgrData), std::end(bgrData), std::begin(array2));
    
    Util::Image::swapComponents(2, 2, 24, array1);
    Util::Image::swapComponents(2, 2, 24, array2);

    ASSERT_EQ(0, std::memcmp(array1, bgrData, 16));
    ASSERT_EQ(0, std::memcmp(array2, rgbData, 16));
}

TEST(Utils_Image, Get_Aligned_Row_Size) {
    ASSERT_EQ(0u,  Util::Image::getAlignedRowSize(0, 24));
    ASSERT_EQ(4u,  Util::Image::getAlignedRowSize(1, 24));
    ASSERT_EQ(8u,  Util::Image::getAlignedRowSize(2, 24));
    ASSERT_EQ(12u, Util::Image::getAlignedRowSize(3, 24));
    ASSERT_EQ(12u, Util::Image::getAlignedRowSize(4, 24));
    ASSERT_EQ(16u, Util::Image::getAlignedRowSize(5, 24));
    
    ASSERT_EQ(0u,  Util::Image::getAlignedRowSize(0, 32));
    ASSERT_EQ(4u,  Util::Image::getAlignedRowSize(1, 32));
    ASSERT_EQ(8u,  Util::Image::getAlignedRowSize(2, 32));
    ASSERT_EQ(12u, Util::Image::getAlignedRowSize(3, 32));
    ASSERT_EQ(16u, Util::Image::getAlignedRowSize(4, 32));
    ASSERT_EQ(20u, Util::Image::getAlignedRowSize(5, 32));
}

TEST(Utils_Image, Algorithm_Crop) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image.bmp");
    image.load("test_assets/image/image_cropping_test.bmp");
    image.crop(glm::uvec2(1u, 1u), glm::uvec2(2u, 2u));

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Rotate_90) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_r90.bmp");
    image.load("test_assets/image/image.bmp");
    image.rotate90CW();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Rotate_180) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_r180.bmp");
    image.load("test_assets/image/image.bmp");
    image.rotate180();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Rotate_270) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_r270.bmp");
    image.load("test_assets/image/image.bmp");
    image.rotate90CCW();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Invert_Horizontal) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_invert_h.bmp");
    image.load("test_assets/image/image.bmp");
    image.invertHorizontal();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Invert_Vertical) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_invert_v.bmp");
    image.load("test_assets/image/image.bmp");
    image.invertVertical();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Invert_Colors) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_invert_colors.bmp");
    image.load("test_assets/image/image.bmp");
    image.invertColors();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}

TEST(Utils_Image, Algorithm_Grayscale) {
    Util::Image imgTemplate;
    Util::Image image;
    
    imgTemplate.load("test_assets/image/image_greyscale.bmp");
    image.load("test_assets/image/image.bmp");
    image.toGrayscale();

    ASSERT_EQ(0, std::memcmp(imgTemplate.getData(), image.getData(), image.getSize()));
}
