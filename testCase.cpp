#include <iostream>
#include <cmath>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};


void runTestLoop(TestStruct testCases[], int testSize){
    int i;
    for (i = 0; i< testSize; i++){
        std::cout << testCases[i].testName + ": ";
        if (testCases[i].result == testCases[i].expected)
        {
            std::cout << "PASSED \n";
        }
        else
        {
            std::cout << testCases[i].errorMsg;
            exit(1);
        }
    }
}

class Test: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testSmallestSum);
  CPPUNIT_TEST_SUITE_END();
}

public:
  void setUp(void) {}
  void tearDown(void) {}

protected:

void testSmallestSum(void){
    int testSize = 2;
    std::string sharedName = "[Plus test] ";
    TestStruct cosTestCases[testSize]  = 
    {
    {
        sharedName + "test normal 1", 
        smallestSum(3,4,5,2,1) == 20, 
        true, 
        " result should be equal to " + std::to_string(20) << "\n"
    },
    {
        sharedName + "test normal 2", 
        smallestSum(3,2,1) == 4,  
        true, 
        " result should be equal to" + std::to_string(4) + " \n"
    },
    };
    runTestLoop(cosTestCases, testSize);
//   exit(0);
}

  void successTestExit(void){
    std::cout << "all tests passed! \n";
    exit(0);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()
{
  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  return result.wasSuccessful() ? 0 : 1;
}