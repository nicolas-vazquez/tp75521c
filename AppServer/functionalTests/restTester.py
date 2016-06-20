import unittest
from AccountTestCases import AccountTest
from MatchTestCases import MatchTest

if __name__ == '__main__':
	suite = unittest.TestSuite()

	tests = unittest.TestLoader().loadTestsFromTestCase(AccountTest)
	suite.addTests(tests)
	
	tests = unittest.TestLoader().loadTestsFromTestCase(MatchTest)
	suite.addTests(tests)

	unittest.TextTestRunner().run(suite)

