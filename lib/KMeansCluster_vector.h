
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <cassert>
#include "Eigen/Dense"


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


template< class T >  KMeansCluster<T>::KMeansCluster(){}

template< class T >  KMeansCluster<T>::KMeansCluster(const std::vector<T>& data): data(data){}

template< class T >  void KMeansCluster<T>::setData(std::vector<T> data){
	this->data = data;
}

template< class T >  void KMeansCluster<T>::setK(int k){
	this->k = k;
}


template<class T> double KMeansCluster<T>::getDistance(const  T& a, const T& b ) {
	assert( a.size() == b.size() ) ;


	double result = 0 ; 

	for(int i = 0 ; i < a.size() ; i++ ){
		result += (a[i] - b[i]) * (a[i] - b[i]);
	}

	return result;
}


// Function to assign data Ts to clusters based on centroids
template< class T >  void KMeansCluster<T>::assignClusters(const std::vector<T>& data, const std::vector<T>& centroids, std::vector<int>& assignments) {
    for (size_t i = 0; i < data.size(); ++i) {
        double minDistance = std::numeric_limits<double>::max();
        int closestCentroid = -1;


        for (size_t j = 0; j < centroids.size(); ++j) {
            double distance = getDistance( data[i], centroids[j] ) ; 
            if (distance < minDistance) {
                minDistance = distance;
                closestCentroid = j;
            }
        }
        assignments[i] = closestCentroid;
    }
}


template< class T> T  KMeansCluster<T>::getSum(const T& a, const T& b) {
	T result(a.size() , 0.0 );
	int N = a.size();
	for(int i = 0; i  < N ;i ++ ) {
			result[i] = a[i] + b[i];
	}

	return result;
}

template<class T> T  KMeansCluster<T>::divideBy(const T& a, double divisor) {
	T  result(a.size() , 0.0 );
	int N = a.size();
	for(int i = 0; i  < N ;i ++ ) {
			result[i] = a[i] /divisor;
	}

	return result;
}

// Function to update centroids based on assigned data Ts
template< class T >  void KMeansCluster<T>::updateCentroids(const std::vector<T>& data, const std::vector<int>& assignments, std::vector<T>& centroids) {
	if(data.empty() ) return;
	T _empty_vector(data[0].size(), 0.0) ;
    std::vector<int> clusterCounts(centroids.size(), 0.0);
    std::vector<T> clusterSums(centroids.size(), _empty_vector  );
    //std::vector<double> clusterSumsY(centroids.size(), 0.0);

    for (size_t i = 0; i < data.size(); ++i) {
        int cluster = assignments[i];
        clusterCounts[cluster]++;
        clusterSums[cluster] = getSum(clusterSums[cluster], data[i]);
    }

    for (size_t i = 0; i < centroids.size(); ++i) {
        if (clusterCounts[i] > 0) {
            centroids[i] = divideBy( clusterSums[i] , clusterCounts[i] ) ;
        }
    }
}

// Function to initialize centroids randomly
template< class T >  std::vector<T> KMeansCluster<T>::initializeCentroids(const std::vector<T>& data, int k) {
    std::vector<T> centroids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, data.size() - 1);

    for (int i = 0; i < k; ++i) {
        size_t index = dist(gen);
        centroids.push_back(data[index]);
    }

    return centroids;
}

// Function to perform K-means clustering
template< class T >  std::vector<int> KMeansCluster<T>::kMeansClustering() {

    std::vector<T> centroids = initializeCentroids(data, k);

    std::vector<int> assignments(data.size(), -1);

    bool converged = false;
    while (!converged) {
        std::vector<int> oldAssignments = assignments;

  	assignClusters(data, centroids, assignments);

 	updateCentroids(data, assignments, centroids);

        converged = assignments == oldAssignments;
    }

    return assignments;
}


template< class T > std::vector<int> getKMeansClusteringAssignments( Eigen::MatrixXd data ) ;
