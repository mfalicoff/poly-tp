
#include "test.h"


void Test::setUp() {

	this->ObjetTest = new Rabais();

}

void Test::tearDown() 
{

	delete this->ObjetTest;
}

//SRS01 et SRS02 : d1 = <{f=0, ID_client = 26000},{rabais = 0.15}> qui couvre la branche employés
void Test::TestRabais25k() 
{
    tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(26000, "Client_Nom", "Client_Nom", 35, "000", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.15, ObjetTest->getRabais(facture, 26000), FLT_EPSILON);
}

//SRS03 : d3 = <{f=0, ID_client = 26000},{rabais = 0.15}> qui s’assure que l’employé n’a pas plus de 15% de rabais
void Test::RabaisEmp()
{
	tm date;
	date.tm_year = 2003;
	ObjetTest->ajouterClient(new Client(27000, "Client_Nom", "Client_Nom", 67, "H1C", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.15, ObjetTest->getRabais(facture, 27000), FLT_EPSILON);
}

//SRS04 : d4 = <{f=0, ID_client = 420},{rabais = 0.10}> qui couvre la branchepour les plus de 55 ans.
void Test::TestRabais55() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(420, "Client_Nom", "Client_Nom", 56, "000", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.10, ObjetTest->getRabais(facture, 420), FLT_EPSILON);
}

//d5 = <{f=0, ID_client = 100},{rabais = 0.04}> qui couvre la branche H1C
void Test::TestRabaisH1C() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(100, "Client_Nom", "Client_Nom", 10, "H1C", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04, ObjetTest->getRabais(facture, 100), FLT_EPSILON);
}

//d6 = <{f=0, ID_client = 100},{rabais = 0.03}> qui couvre la branche H3P
void Test::TestRabaisH3P() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(100, "Client_Nom", "Client_Nom", 10, "H3P", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.03, ObjetTest->getRabais(facture, 100), FLT_EPSILON);
}

//d7 = <{f=0, ID_client = 100},{rabais = 0.02}> qui couvre la branche J4O
void Test::TestRabaisJ4O() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(100, "Client_Nom", "Client_Nom", 10, "J4O", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.02, ObjetTest->getRabais(facture, 100), FLT_EPSILON);
}

//d8 = <{f=0, ID_client = 12},{rabais = 0.04}> qui couvre la branche selon la date d’adhésion
void Test::TestRabais3ans() 
{
	tm date;
	date.tm_year = 2017;
	date.tm_mon = 8;
	ObjetTest->ajouterClient(new Client(12, "Client_Nom", "Client_Nom", 25, "000", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, ObjetTest->getRabais(facture, 12), FLT_EPSILON);
}

//d9 = <{f=0, ID_client = 55},{rabais = 0.10}> qui s’assure que le rabais sur l’adhésion ne dépasse pas 10%
void Test::TestRabais10() 
{
	tm date;
	date.tm_year = 2003;
	date.tm_mon = 8;
	ObjetTest->ajouterClient(new Client(12, "Client_Nom", "Client_Nom", 25, "000", date));
	Facture facture;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1, ObjetTest->getRabais(facture, 12), FLT_EPSILON);
}

//d10 = <{f=121, ID_client = 16},{rabais = 0.01}> qui couvre la branche 1% de rabais par tranche de 120$ sur la facture
void Test::TestRabaisMoins720() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(16, "Client_Nom", "Client_Nom", 25, "000", date));
	Facture facture;
	facture.ajouterItem(121);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, ObjetTest->getRabais(facture, 16), FLT_EPSILON);
}

//d11 = <{f=721, ID_client = 67},{rabais = 0.06}> qui s’assure que le rabais selon la facture ne dépasse pas 6%
void Test::TestRabaisPlus720() 
{
	tm date;
	date.tm_year = 2020;
	ObjetTest->ajouterClient(new Client(67, "Client_Nom", "Client_Nom", 25, "G4S", date));
	Facture facture;
	facture.ajouterItem(721.0);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.06, ObjetTest->getRabais(facture, 67), FLT_EPSILON);
}


