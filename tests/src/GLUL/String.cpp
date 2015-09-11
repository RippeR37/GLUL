#include <gtest/gtest.h>

#include <GLUL/String.h>


TEST(GLUL_String, Split) {
    std::string str1 = "text with   words";
    std::string str2 = "other text";

    std::vector<std::string> result1 = GLUL::String::split(str1, ' ', true);
    std::vector<std::string> result2 = GLUL::String::split(str1, ' ', false);
    std::vector<std::string> result3 = GLUL::String::split(str2, 't', true);
    std::vector<std::string> result4 = GLUL::String::split(str2, 't', false);

    ASSERT_EQ(3, result1.size());
    ASSERT_EQ(5, result2.size());
    ASSERT_EQ(3, result3.size());
    ASSERT_EQ(3, result4.size());

    ASSERT_EQ("text",  result1[0]);
    ASSERT_EQ("with",  result1[1]);
    ASSERT_EQ("words", result1[2]);

    ASSERT_EQ("text",  result2[0]);
    ASSERT_EQ("with",  result2[1]);
    ASSERT_EQ("",      result2[2]);
    ASSERT_EQ("",      result2[3]);
    ASSERT_EQ("words", result2[4]);
    
    ASSERT_EQ("o",    result3[0]);
    ASSERT_EQ("her ", result3[1]);
    ASSERT_EQ("ex",   result3[2]);
    
    ASSERT_EQ("o",    result4[0]);
    ASSERT_EQ("her ", result4[1]);
    ASSERT_EQ("ex",   result4[2]);
}

TEST(GLUL_String, Trim) {
    std::string templateString = "trimmed template";

    std::string str1 = " " + templateString + "  ";
    std::string str2 = "    " + templateString + "\t";
    std::string str3 = "\t\t\n" + templateString + " \t ";

    ASSERT_EQ(templateString, GLUL::String::trim(str1));
    ASSERT_EQ(templateString, GLUL::String::trim(str2));
    ASSERT_EQ(templateString, GLUL::String::trim(str3));
}

TEST(GLUL_String, Trim_Left) {
    std::string templateString = "trimmed template";

    std::string str1 = " " + templateString;
    std::string str2 = "    " + templateString;
    std::string str3 = "  \t \t   \n " + templateString;

    ASSERT_EQ(templateString, GLUL::String::ltrim(str1));
    ASSERT_EQ(templateString, GLUL::String::ltrim(str2));
    ASSERT_EQ(templateString, GLUL::String::ltrim(str3));
}

TEST(GLUL_String, Trim_Right) {
    std::string templateString = "trimmed template";

    std::string str1 = templateString + "  ";
    std::string str2 = templateString + " \t   ";
    std::string str3 = templateString + " \t \n\n  \n";

    ASSERT_EQ(templateString, GLUL::String::rtrim(str1));
    ASSERT_EQ(templateString, GLUL::String::rtrim(str2));
    ASSERT_EQ(templateString, GLUL::String::rtrim(str3));
}

TEST(GLUL_String, Starts_With) {
    std::string str1 = "hello world";
    std::string str2 = "lorem ipsum dolor sit amet";
    std::string str3 = " some text ";
    
    ASSERT_TRUE(GLUL::String::startsWith(str1, "hello"));
    ASSERT_TRUE(GLUL::String::startsWith(str2, "lorem ipsum"));
    ASSERT_TRUE(GLUL::String::startsWith(str3, " som"));
    ASSERT_TRUE(GLUL::String::startsWith(str3, str3));
    ASSERT_FALSE(GLUL::String::startsWith(str1, " " + str1));
    ASSERT_FALSE(GLUL::String::startsWith(str2, "amet"));
}

TEST(GLUL_String, Ends_With) {
    std::string str1 = "hello world";
    std::string str2 = "lorem ipsum dolor sit amet";
    std::string str3 = " some text ";
    
    ASSERT_TRUE(GLUL::String::endsWith(str1, " world"));
    ASSERT_TRUE(GLUL::String::endsWith(str2, "sit amet"));
    ASSERT_TRUE(GLUL::String::endsWith(str3, "text "));
    ASSERT_TRUE(GLUL::String::endsWith(str2, str2));
    ASSERT_FALSE(GLUL::String::endsWith(str1, str1 + " "));
    ASSERT_FALSE(GLUL::String::endsWith(str2, "lorem "));
}
