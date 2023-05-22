
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <cassert>


/*
 * Template parameter T must be a vector<numeric_type> class
 *
 */


template<class T> class KMeansCluster{

	public:
		/* Constructor
		 */

		KMeansCluster();

		KMeansCluster( const std::vector<T>& data );


		/* SET
		 */
		void setData(std::vector<T> data);

		void setK(int k);

		void assignClusters(const std::vector<T>& , const std::vector<T>& , std::vector<int>& ) ;

		void updateCentroids(const std::vector<T>& , const std::vector<int>& , std::vector<T>& ) ;

		std::vector<T> initializeCentroids(const std::vector<T>& , int ) ;

		std::vector<int> kMeansClustering() ;

		double getDistance( const T& a, const T& b) ;
		T  getSum(const T& a ,const T& b);
		T divideBy(const T& a, double divisor) ;


	private:
		
		std::vector<T> data;
		
		int k;
};
