#include <stdio.h>
#include <string.h>
#include <iostream>

#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace CPPUNIT_NS;
using namespace std;

int main(void) {
    TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();

    // run all tests if none specified on command line
    Test *test_to_run = registry.makeTest();
    runner.addTest(test_to_run);
    bool failed = runner.run("", false);
    return !failed;
}
