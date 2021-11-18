#include "pch.h"
#include "AppRunner.h"

TEST(ConsoleApp, ASKS_FOR_ONE_NUMBER) {
 
    AppRunner a("ConsoleApp");

    EXPECT_EQ("Please enter a number:", a.getOutput()) << "Program should ask for a number";

}

TEST(ConsoleApp, ASKS_FOR_SECOND_NUMBER) {

    AppRunner a("ConsoleApp");

    std::cout <<a.getOutput();

    a.sendInput("42");

    EXPECT_EQ("Please enter another number:", a.getOutput()) << "Program should ask for a second number";

}

TEST(ConsoleApp, ASKS_FOR_INPUTS) {

    AppRunner a("ConsoleApp");

    EXPECT_EQ("Please enter a number:", a.getOutput()) << "Program should ask for a number";
    a.sendInput("42");

    EXPECT_EQ("Please enter another number:", a.getOutput()) << "Program should ask for a second number";
    a.sendInput("42");

    EXPECT_EQ("Please enter operator", a.getOutput()) << "Program should ask for a operator";

}

TEST(ConsoleApp, CAN_ADD) {

    AppRunner a("ConsoleApp");

    a.sendInput("42");

    a.sendInput("43");

    a.sendInput("+");


    EXPECT_IN("85", a.getOutput()) << "Program should add";

}

TEST(ConsoleApp, CAN_SUBTRACT) {

    AppRunner a("ConsoleApp");

    a.sendInput("42");

    a.sendInput("23");

    a.sendInput("-");

    EXPECT_IN("19", a.getOutput()) << "Program should subtract";

}

TEST(ConsoleApp, CAN_MULT) {

    AppRunner a("ConsoleApp");

    a.sendInput("4");

    a.sendInput("5");

    a.sendInput("*");

    EXPECT_IN("20", a.getOutput()) << "Program should multiply";

}

TEST(ConsoleApp, CAN_DIVIDE) {

    AppRunner a("ConsoleApp");

    a.sendInput("20");

    a.sendInput("5");

    a.sendInput("/");

    EXPECT_IN("4", a.getOutput()) << "Program should divide";

}

TEST(ConsoleApp, DEALS_WITH_BAD_INPUT) {

    AppRunner a("ConsoleApp");

    std::cout << "running" << a.isRunning();
    a.sendInput("xyz\n\n\n");

    EXPECT_IN("Bad", a.getOutput()) << "Program should show error";

    a.sendInput("xyz\n\n\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    EXPECT_EXITED(a);
}