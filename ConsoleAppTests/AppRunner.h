#pragma once
//#include <cstdio>
//#include <iostream>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <array>
#include <fstream> 
//#include <chrono>
#include <thread>


#define EXPECT_IN(subString, longString) EXPECT_PRED_FORMAT2(AssertStringIsSubstring, subString, longString)


testing::AssertionResult AssertStringIsSubstring(
    const char* m_expr,
    const char* n_expr,
    std::string subString,
    std::string longString) {
    if (longString.find(subString) != std::string::npos) 
        return testing::AssertionSuccess();

    return testing::AssertionFailure() << m_expr << "(\"" << subString << "\") was not found in "
        << n_expr << "(\"" << longString << "\")";
}


class AppRunner {
	std::string appName;
    std::string outFileName;
    FILE* inputPipe;
    std::streampos outputStreamPos{0};

public:
	AppRunner(const std::string appName):appName(appName) {
        const testing::TestInfo* const test_info =
            testing::UnitTest::GetInstance()->current_test_info();

        std::string testName{ test_info->name() };
        std::string testCaseName{ test_info->test_case_name() };

        outFileName = testName + "_" + testCaseName + ".tmp";

        std::string command = appName + ".exe >" + outFileName;

        inputPipe = _popen(command.c_str(), "w");

        outputStreamPos = 0;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }

    ~AppRunner() {
        _pclose(inputPipe);
    }

    std::string getOutput() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::ifstream  ifs;
        ifs.open(outFileName, std::ifstream::in);

        ifs.seekg(outputStreamPos);
        
        std::string output;
        char c;
        while (ifs.get(c)) {
            output += c;
            outputStreamPos = ifs.tellg();
        }

        ifs.close();

        return output;
    }

    void sendInput(const std::string& input) {
        fputs(input.c_str(), inputPipe);
        fputc('\n', inputPipe);

        fflush(inputPipe);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    bool isRunning() {
        //very hacky, find a better way
        std::cout << fputc('\n', inputPipe) << "\n";
        //App is still alive if pipe still takes chars
        return  ferror(inputPipe) == 0;
    }

};

#define EXPECT_EXITED(appRunner) EXPECT_PRED_FORMAT1(AssertAppHasExited, appRunner)

testing::AssertionResult AssertAppHasExited(
    const char* m_expr,
    AppRunner& app) {
    if (!app.isRunning())
        return testing::AssertionSuccess();

    return testing::AssertionFailure() << "Expected app to have exited, but it looks like it is still alive";
}

