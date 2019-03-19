/*
 * Matrix_test.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: Agit
 */

/*
 * matrix algebra uit http://stattrek.com/matrix-algebra/matrix-theorems.aspx is als unittest gebruikt
 * voor bewijs dat functies werken zoals de theorie
 */
#include "Matrix.hpp"
#include <iostream>
#include <exception>

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(MatrixModule)

BOOST_AUTO_TEST_CASE(Matrix_Init)
{
	unsigned long answer = 0;
	Matrix<> m;
	BOOST_REQUIRE_EQUAL(m.getMatrixSize(),answer);

	answer = 4;
	Matrix<2,2> k;
	BOOST_REQUIRE_EQUAL(k.getMatrixSize(),answer);


	Matrix<4,2> a (
					{
						{1,2},
						{3,4},
						{5,6},
						{7,8}

					}

				  );

	Matrix<4,2> b ({1,2,3,4,5,6,7,8});

	BOOST_REQUIRE_EQUAL(a,b);

	Matrix<2,4> c (
					{
						{1,2,3,4},
						{5,6,7,8}
					}

				  );
	Matrix<2,4> d ({1,2,3,4,5,6,7,8});

	BOOST_REQUIRE_EQUAL(c,d);


    //LET OP ALS JE GEBRUIK MAAKT VAN DE DUBBELE std::initializer_list DAN GELDT ALLEEN
	//VOOR EEN MATRIX MET 1 COLUMN DE ONDERSTAANDE SYNTAX ( er moet een extra { } bij) ANDERS WEET DE COMPILER NIET
	//WELKE CONSTRUCTOR DIE MOET PAKKEN
	Matrix<4,1> i (
					{
						{{1}},
						{{2}},
						{{3}},
						{{4}}

					}

				  );

	Matrix<4,1> j ({1,2,3,4});

	BOOST_REQUIRE_EQUAL(i,j);



	Matrix<1,4> x (
					{
						{1,2,3,4}
					}

				  );
	Matrix<1,4> y ({1,2,3,4});

	BOOST_REQUIRE_EQUAL(x,y);
}

BOOST_AUTO_TEST_CASE(Matrix_Addition_and_Matrix_Multiplication)
{
	   Matrix<2,2> a(
			   	   	   {
			   	   	   {1,2},
	   	   	   	   	   {3,4}
			   	   	   }
	   	   	   	   	);

	   Matrix<2,2> b ({{1,2},{3,4}});

	BOOST_REQUIRE_EQUAL(a+b,b+a);  //(Commutative law of addition)

	   Matrix<2,2> c(
			   	   	   {
			   	   	   {5,6},
	   	   	   	   	   {7,8}
			   	   	   }
	   	   	   	   	);

	BOOST_REQUIRE_EQUAL(a+b+c,a+(b+c));  //(Associative law of addition)
	BOOST_REQUIRE_EQUAL(a+b+c,(a+b)+c);  //(Associative law of addition)

	BOOST_REQUIRE_EQUAL(a*b*c,a*(b*c)); //(Associative law of multiplication)
	BOOST_REQUIRE_EQUAL(a*b*c,(a*b)*c); //(Associative law of multiplication)

	BOOST_REQUIRE_EQUAL(a*(b+c),(a*b)+(a*c)); //(Distributive law of matrix algebra)

	long x = 2;
	BOOST_REQUIRE_EQUAL((a+b)*x,a*x + b*x);
}


BOOST_AUTO_TEST_CASE(Transposition_Rules)
{
	   Matrix<3,3> a(
			   	   	   {
			   	   	   {1,2,3},
	   	   	   	   	   {4,5,6},
					   {7,8,9}
			   	   	   }
	   	   	   	   	);
	   BOOST_REQUIRE_EQUAL(a.transpose().transpose(),a);

	   Matrix<3,3> b ({{1,2,3},{4,5,6},{7,8,9}});

	   BOOST_REQUIRE_EQUAL((a+b).transpose(),a.transpose()+b.transpose());

	   BOOST_REQUIRE_EQUAL((a*b).transpose(),b.transpose() * a.transpose());

	   Matrix<3,3> c(
			   	   	   {
			   	   	   {10,11,12},
	   	   	   	   	   {13,14,15},
					   {16,17,18}
			   	   	   }
	   	   	   	   	);

	   BOOST_REQUIRE_EQUAL((a*b*c).transpose(),c.transpose() * b.transpose() * a.transpose());

}


BOOST_AUTO_TEST_CASE(Inverse_Rules)
{
	   Matrix<3,3> a(
			   	   	   {
			   	   	   {1,2,3},
	   	   	   	   	   {4,5,6},
					   {7,8,9}
			   	   	   }
	   	   	   	   	);
	   Matrix<3,3> i(
			   	   	   {
			   	   	   {1,0,0},
	   	   	   	   	   {0,1,0},
					   {0,0,1}
			   	   	   }
	   	   	   	   	);
	  BOOST_REQUIRE_EQUAL(a*i,i*a);
	  BOOST_REQUIRE_EQUAL(a*i,a);
}

BOOST_AUTO_TEST_CASE(Matrix_Equal_old)
{
	Matrix<> m;
	Matrix<> k;
	BOOST_REQUIRE_EQUAL(m,k);

	Matrix<2,2> x({{1,2},{3,4}});
	Matrix<2,2> y({{1,2},{3,4}});

	BOOST_REQUIRE_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE(MatrixAtFunction_old)
{
	Matrix<2,2> m ({{1,2},{3,4}});

	BOOST_REQUIRE_EQUAL(m.at(0,0),1);
	BOOST_REQUIRE_EQUAL(m.at(0).at(1),2);
	BOOST_REQUIRE_EQUAL(m[0][2],3);

}


BOOST_AUTO_TEST_CASE(Inverse_test)
{

	Matrix<2,2,double> a(
							{
								{1, 2},
								{3, 4}
							}

						);



	Matrix<2,2,double> b(
							{
								{1, 0},
								{0, 1}
							}

						);

	BOOST_CHECK((a*b).approxEqual(a,0.1)); //AI = A
	Matrix<3,3,double> m1(
							{
								{1, 4, 4},
								{2, 4, 8},
								{4, 8, 2}
							}

						);

	Matrix<1,1,double> c(
							{
								{{8}}
							}

						);



	Matrix<1,1,double> d({1});
	BOOST_CHECK((c*d).approxEqual(c,0.1)); //AI = A

	Matrix<3,3,double> m2(
							{
								{1, 2, 0},
								{1, 0, 1},
								{2, 2, 2}
							}

						);

	Matrix<3,3,double> m3(
							{
								{0, -3, 1},
								{-1, 2, 3},
								{4, -4, -7}
							}

						);

	Matrix<3,3,double> m4(
							{
								{1, 2, 0},
								{1, 0, 1},
								{2, 2, 2}
							}

						);


	Matrix<3,3,double> m5(
							{
								{1, 3, 3},
								{1, 4, 3},
								{1, 3, 4}
							}

						);

	Matrix<3,3,double> i(
			   	   	   {
			   	   	   {1,0,0},
	   	   	   	   	   {0,1,0},
					   {0,0,1}
			   	   	   }
	   	   	   	   	);

	Matrix<4,4,double> m6(
							{
								{1, 4, 4, -3},
								{2, 4, 8, -1},
								{4, 8, 2,  4},
								{-1, 2, 5, 2}
							}

						);

	Matrix<4,4,double> i2(
			   	   	   {
			   	   	   {1,0,0,0},
	   	   	   	   	   {0,1,0,0},
					   {0,0,1,0},
					   {0,0,0,1}
			   	   	   }
	   	   	   	   	);

	BOOST_CHECK((m1*i).approxEqual(m1,0.1)); //AI = A
	auto andersom = i*m1; //IA
	BOOST_CHECK((m1*i).approxEqual(andersom,0.1)); //AI = IA

	BOOST_CHECK((m6*i2).approxEqual(m6,0.1)); //AI = A

	BOOST_CHECK((m2*m2.inverse()).approxEqual(i,0.1)); ///AA-1 = A-1A = I

	BOOST_CHECK((m3*m3.inverse()).approxEqual(i,0.1));//AA-1 = A-1A = I

	auto andersom2 = m3.inverse()*m3; //A-1A
	BOOST_CHECK((m3*m3.inverse()).approxEqual(andersom2,0.1)); //AA-1 = A-1A = I

	BOOST_CHECK(m3.inverse().inverse().approxEqual(m3,0.1)); //( A-1 )-1 = A
	BOOST_CHECK(m4.inverse().inverse().approxEqual(m4,0.1)); //( A-1 )-1 = A

	auto andersom3 = (m2.inverse()*m1.inverse()); //B-1A-1
	BOOST_CHECK((m1*m2).inverse().approxEqual(andersom3,0.1)); //( AB )-1 = B-1A-1

	auto andersom4 = m3.inverse() * m2.inverse() * m1.inverse(); //C-1B-1A-1
	BOOST_CHECK((m1*m2*m3).inverse().approxEqual(andersom4,0.1)); //( ABC )-1 = C-1B-1A-1

	auto andersom5 = m1.inverse().transpose(); //( A-1 )'
	BOOST_CHECK(m1.transpose().inverse().approxEqual(andersom5,0.1)); //( A' )-1 = ( A-1 )'


	auto result = m1.transpose() * (m1*m1.transpose()).inverse(); //A'(AA')-

	BOOST_CHECK(m1.inverse().approxEqual(result,0.1)); //A- = A'(AA')-



	BOOST_CHECK((m4*i).approxEqual(m4,0.1)); //AI = A


	Matrix<3,3,double> m8(
							{
								{1, 2, 3},
								{4, 5, 6},
								{7, 8, 9}
							}

						);


	Matrix<3,3,double> m9(
							{
								{1, 0, 3},
								{4, 0, 6},
								{7, 0, 9}
							}

						);

	BOOST_CHECK_THROW(m8.inverse().inverse().approxEqual(m8,0.1),std::runtime_error); //( A-1 )-1 = A
	BOOST_CHECK_THROW(m9.inverse().inverse().approxEqual(m8,0.1),std::runtime_error); //( A-1 )-1 = A
}
BOOST_AUTO_TEST_SUITE_END()
