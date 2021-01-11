#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// Le fichier � tester, qui se trouve dans un r�pertoire diff�rent.
#include "../../src/rabais.h"

class Test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Test);
	CPPUNIT_TEST(TestRabais25k);
	CPPUNIT_TEST(RabaisEmp);
	CPPUNIT_TEST(TestRabais55);
	CPPUNIT_TEST(TestRabaisH1C);
	CPPUNIT_TEST(TestRabaisH3P);
	CPPUNIT_TEST(TestRabaisJ4O);
	CPPUNIT_TEST(TestRabais3ans);
	CPPUNIT_TEST(TestRabais10);
	CPPUNIT_TEST(TestRabaisMoins720);
	CPPUNIT_TEST(TestRabaisPlus720);
	CPPUNIT_TEST_SUITE_END();
	
private:
	Rabais* ObjetTest;

public:
	// Fonctions d'�chafaudage

	void setUp();
	void tearDown();

	// Fonctions de tests

	void TestRabais25k();
	void RabaisEmp();
	void TestRabais55();
	void TestRabaisH1C();
	void TestRabaisH3P();
	void TestRabaisJ4O();
	void TestRabais3ans();
	void TestRabais10();
	void TestRabaisMoins720();
	void TestRabaisPlus720();
	
};




