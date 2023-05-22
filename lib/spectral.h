
#include <iostream>
#include <vector>
#include "KMeansCluster_vector.h"

template< class T> vector<int> spectralClustering(const vector<vector<T> >& adjacencyMatrix, int numClusters) {
    int N = adjacencyMatrix.size();
    Eigen::MatrixXd A(N, N);
    for (int i = 0; i < N; i++) 
	for (int j = 0; j < N; j++) 
	    A(i, j) = adjacencyMatrix[i][j];

    Eigen::MatrixXd D = A.colwise().sum().asDiagonal();
    Eigen::MatrixXd L = D - A;

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(L);
    if (eigensolver.info() != Eigen::Success) {
	cerr << "Eigenvalue decomposition failed." << endl;
	exit(1);
    }

    Eigen::MatrixXd eigenvectors = eigensolver.eigenvectors();
    Eigen::MatrixXd clusteredData = eigenvectors.block(0, 0, N, numClusters);

    std::cout<<eigenvectors<<std::endl;
    std::cout<<clusteredData<<std::endl;



    vector<int> labels(N, 0);

    labels = getKMeansClusteringAssignments(clusteredData);


    return labels;
}
#include "Eigen/Dense"
