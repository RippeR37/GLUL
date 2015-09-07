#include <gtest/gtest.h>

#include <Utils/File.h>


TEST(Utils_File, Exists) {
    bool existing;
    bool nonexisting;

    existing = Util::File::exists("test_assets/file/textfile.txt");
    nonexisting = Util::File::exists("test_assets/file/nonexisting.txt");

    ASSERT_EQ(true,  existing);
    ASSERT_EQ(false, nonexisting);
}

TEST(Utils_File, Read_Text_OneLine) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test";

    fileContent = Util::File::readText("test_assets/file/textfile.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(Utils_File, Read_Text_Nonexisting_Nothrow) {
    std::string fileContent;

    ASSERT_NO_THROW({
        fileContent = Util::File::readText("test_assets/file/nonexisting.txt", false);
    });

    ASSERT_EQ("", fileContent);
}

TEST(Utils_File, Read_Text_Nonexisting_Throw) {
    std::string fileContent;

    ASSERT_THROW({
        fileContent = Util::File::readText("test_assets/file/nonexisting.txt", true);
    }, Util::Exception::FatalError);
}

TEST(Utils_File, Read_Text_MultiLine) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test\nsecond line\nthrid";

    fileContent = Util::File::readText("test_assets/file/multilinetextfield.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(Utils_File, Read_Text_EmptyLines) {
    std::string fileContent;
    std::string originalContent = "sample text for unit test\n\nthrid line\n\n\nlast line will be empty\n";

    fileContent = Util::File::readText("test_assets/file/emptylines.txt");

    ASSERT_EQ(originalContent, fileContent);
}

TEST(Utils_File, Get_Path) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ(path1,  Util::File::getPath(path1 + "file.ext"));
    ASSERT_EQ(path2,  Util::File::getPath(path2 + "file.ext"));
    ASSERT_EQ(path3,  Util::File::getPath(path3 + "file.ext"));
    ASSERT_EQ(path4,  Util::File::getPath(path4 + "file.ext"));
}

TEST(Utils_File, Get_Filename) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("filename.ext",  Util::File::getFilename(path1 + "filename.ext"));
    ASSERT_EQ("filename.ext",  Util::File::getFilename(path2 + "filename.ext"));
    ASSERT_EQ("filename.ext",  Util::File::getFilename(path3 + "filename.ext"));
    ASSERT_EQ("filename.ext",  Util::File::getFilename(path4 + "filename.ext"));
}

TEST(Utils_File, Get_FilenameExtensionless) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("filename",  Util::File::getFilenameExtensionless(path1 + "filename.ext"));
    ASSERT_EQ("filename",  Util::File::getFilenameExtensionless(path2 + "filename.ext"));
    ASSERT_EQ("filename",  Util::File::getFilenameExtensionless(path3 + "filename.ext"));
    ASSERT_EQ("filename",  Util::File::getFilenameExtensionless(path4 + "filename.ext"));
}

TEST(Utils_File, Get_Extension) {
    std::string path1 = "some/path/to/";
    std::string path2 = "C:/path/";
    std::string path3 = "some\\other\\path\\";
    std::string path4 = "C:\\other\\path\\";

    ASSERT_EQ("ext",  Util::File::getExtension(path1 + "filename.ext"));
    ASSERT_EQ("ext",  Util::File::getExtension(path2 + "filename.ext"));
    ASSERT_EQ("ext",  Util::File::getExtension(path3 + "filename.ext"));
    ASSERT_EQ("ext",  Util::File::getExtension(path4 + "filename.ext"));

    ASSERT_EQ("extension",  Util::File::getExtension(path1 + "filename.extension"));
    ASSERT_EQ("ext",        Util::File::getExtension(path2 + ".ext"));
    ASSERT_EQ("a",          Util::File::getExtension(path3 + "a.a"));
    ASSERT_EQ("ext3",       Util::File::getExtension(path4 + "ext1.ext2.ext3"));
}
