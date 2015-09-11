#include <gtest/gtest.h>

#include <GLUL/File.h>


TEST(GLUL_File, Exists) {
    bool existing;
    bool nonexisting;

    existing = GLUL::File::exists("test_assets/file/textfile.txt");
    nonexisting = GLUL::File::exists("test_assets/file/nonexisting.txt");

    ASSERT_EQ(true,  existing);
    ASSERT_EQ(false, nonexisting);
}

TEST(GLUL_File, Read_Text_OneLine) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test";

    fileContent = GLUL::File::readText("test_assets/file/textfile.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(GLUL_File, Read_Text_Nonexisting_Nothrow) {
    std::string fileContent;

    ASSERT_NO_THROW({
        fileContent = GLUL::File::readText("test_assets/file/nonexisting.txt", false);
    });

    ASSERT_EQ("", fileContent);
}

TEST(GLUL_File, Read_Text_Nonexisting_Throw) {
    std::string fileContent;

    ASSERT_THROW({
        fileContent = GLUL::File::readText("test_assets/file/nonexisting.txt", true);
    }, GLUL::Exception::FatalError);
}

TEST(GLUL_File, Read_Text_MultiLine) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test\nsecond line\nthrid";

    fileContent = GLUL::File::readText("test_assets/file/multilinetextfield.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(GLUL_File, Read_Text_EmptyLines) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test\n\nthrid line\n\n\nlast line will be empty\n";

    fileContent = GLUL::File::readText("test_assets/file/emptylines.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(GLUL_File, Get_Path) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ(path1,  GLUL::File::getPath(path1 + "file.ext"));
    ASSERT_EQ(path2,  GLUL::File::getPath(path2 + "file.ext"));
    ASSERT_EQ(path3,  GLUL::File::getPath(path3 + "file.ext"));
    ASSERT_EQ(path4,  GLUL::File::getPath(path4 + "file.ext"));
}

TEST(GLUL_File, Get_Filename) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("filename.ext",  GLUL::File::getFilename(path1 + "filename.ext"));
    ASSERT_EQ("filename.ext",  GLUL::File::getFilename(path2 + "filename.ext"));
    ASSERT_EQ("filename.ext",  GLUL::File::getFilename(path3 + "filename.ext"));
    ASSERT_EQ("filename.ext",  GLUL::File::getFilename(path4 + "filename.ext"));
}

TEST(GLUL_File, Get_FilenameExtensionless) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("filename",  GLUL::File::getFilenameExtensionless(path1 + "filename.ext"));
    ASSERT_EQ("filename",  GLUL::File::getFilenameExtensionless(path2 + "filename.ext"));
    ASSERT_EQ("filename",  GLUL::File::getFilenameExtensionless(path3 + "filename.ext"));
    ASSERT_EQ("filename",  GLUL::File::getFilenameExtensionless(path4 + "filename.ext"));
}

TEST(GLUL_File, Get_Extension) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("ext",  GLUL::File::getExtension(path1 + "filename.ext"));
    ASSERT_EQ("ext",  GLUL::File::getExtension(path2 + "filename.ext"));
    ASSERT_EQ("ext",  GLUL::File::getExtension(path3 + "filename.ext"));
    ASSERT_EQ("ext",  GLUL::File::getExtension(path4 + "filename.ext"));

    ASSERT_EQ("extension",  GLUL::File::getExtension(path1 + "filename.extension"));
    ASSERT_EQ("ext",        GLUL::File::getExtension(path2 + ".ext"));
    ASSERT_EQ("a",          GLUL::File::getExtension(path3 + "a.a"));
    ASSERT_EQ("ext3",       GLUL::File::getExtension(path4 + "ext1.ext2.ext3"));
}
