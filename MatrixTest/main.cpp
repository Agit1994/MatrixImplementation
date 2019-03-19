/*
 * main.cpp

 *
 *  Created on: Mar 5, 2017
 *      Author: Agit
 */
//
#include "Matrix.hpp"
#include <iostream>
#include <exception>


#define BOOST_TEST_MODULE MatrixTestModule
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
int main(int argc, char **argv)
{

	return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}


/*
int main(int argc, char **argv)
{
   try
   {
	   Matrix<2,2> a(
			   	   	   {
			   	   	   {1,2},
	   	   	   	   	   {3,4}
			   	   	   }
	   	   	   	   	);

	   Matrix<2,2> i ({1,2,3,4});
	   Matrix<2,3,int> j (
			   	   	   {
			   	   	   {0,1,2},
					   {3,4,5}
			   	   	   }
	   	   	   	   	 );

	   Matrix<3,2,int> k (
			   	   	   {
		   	   	   	   	   {6,7},
						   {8,9},
						   {10,11}
			   	   	   }
	   	   	   	   	 );


	  Matrix<3,4,long>x ({
		  	  	  	  	  {88,99,25,12},
						  {112,666,23,12},
						  {44,98,100,12}
	  	  	  	  	  	 }
	  	  	  	  	   );

	  Matrix<4,3,long>y ({
						  {98,69,97},
						  {1200,55,23},
						  {12,45,34},
						  {12,12,12}
	  	  	  	  	  	 }
	  	  	  	  	   );

	  Matrix<4,2,double>z ({
						  {98,69},
						  {1200,55},
						  {12,45},
						  {12,12}
	  	  	  	  	  	 }
	  	  	  	  	   );

	   std::cout<<a<<std::endl;
	   std::cout<<i<<std::endl;
	   std::cout<<j<<std::endl;
	   std::cout<<k<<std::endl;
//	   std::cout<<j.getRowSize()<<std::endl;
//	   std::cout<<j.getColumnSize()<<std::endl;

	  std::cout<<j*k<<std::endl;
	  std::cout<<x*y<<std::endl;
	  std::cout<<x*z<<std::endl;
	  std::cout<<a+i<<std::endl;
	  std::cout<<a-i<<std::endl;

	  a+=a;
	  std::cout<<a<<std::endl;

	   Matrix<3,3,long> f(
			   	   	   {
			   	   	   {1,2,3},
	   	   	   	   	   {4,5,6},
					   {7,8,9}
			   	   	   }
	   	   	   	   	  );

	   Matrix<3,3,long> g(
			   	   	   {
			   	   	   {1,0,0},
	   	   	   	   	   {0,1,0},
					   {0,0,1}
			   	   	   }
	   	   	   	   	);

	   std::cout<<f*g<<std::endl;

   }
   catch (std::exception& e)
   {
	   std::cerr << "Exception: " << e.what() << "\n";
   }
	return 0;
}*/











