#include <stdio.h>
#include <string.h>
#include <iostream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <utils/FileLogger.h>
#include <db/Database.h>


using namespace CPPUNIT_NS;
using namespace std;

int main(void) {
    CppUnit::TextUi::TestRunner runner;
    FileLogger::initialize("test.out", FileLogger::LOG_DEBUG);
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run("", false);
    FileLogger::destroy();
    return !wasSuccessful;
}
