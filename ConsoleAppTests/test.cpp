#include "pch.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream> 
#include <chrono>
#include <thread>
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ConsoleApp, TEST1) {
    const testing::TestInfo* const test_info =
        testing::UnitTest::GetInstance()->current_test_info();

    std::string testName{ test_info->name() };
    std::string testCaseName{ test_info->test_case_name() };


    std::string outputFileName = testName + "_" + testCaseName + ".txt";

 
    //EXPECT_EQ(1, 1);
    //char name[256];
    std::ifstream  ifs;
    ifs.open(outputFileName, std::ifstream::in);

    char cmd[1000] = "ConsoleApp.exe >";
    strcat_s(cmd, 1000, outputFileName.c_str());

    std::unique_ptr<FILE, decltype(&_pclose)> appInput(_popen(cmd, "w"), _pclose);

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::string output1;
    char c;
    while (ifs.get(c))          // loop getting single characters
        output1 += c;

    ifs.close();
    //ifs.getline(name, 256);
    std::cout << "output1:" << output1 << "<-\n";

    std::cout << "=========================================\n";

    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    fputs("31\n", appInput.get());
    fflush(appInput.get());

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    ifs.open(outputFileName, std::ifstream::in);

    std::string output2;
    while (ifs.get(c))          // loop getting single characters
        output2 += c;

    std::cout << "output2:" << output2 << "<-\n";
 

    EXPECT_TRUE(false);
}