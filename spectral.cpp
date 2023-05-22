#include <iostream>
#include <vector>
#include <Eigen/Dense>  // Eigen library for linear algebra operations

using namespace std;
using namespace Eigen;

// Function to perform spectral clustering
vector<int> spectralClustering(const vector<vector<double> >& adjacencyMatrix, int numClusters) {
    // Convert adjacency matrix to Eigen MatrixXd
    int N = adjacencyMatrix.size();
    MatrixXd A(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A(i, j) = adjacencyMatrix[i][j];
        }
    }

    // Compute the Laplacian matrix
    MatrixXd D = A.colwise().sum().asDiagonal();
    MatrixXd L = D - A;

    // Perform eigenvalue decomposition
    SelfAdjointEigenSolver<MatrixXd> eigensolver(L);
    if (eigensolver.info() != Success) {
        cerr << "Eigenvalue decomposition failed." << endl;
        exit(1);
    }

    // Extract the eigenvectors corresponding to the smallest eigenvalues
    MatrixXd eigenvectors = eigensolver.eigenvectors();
    MatrixXd clusteredData = eigenvectors.block(0, 0, N, numClusters);

    std::cout<<eigenvectors<<std::endl;
    std::cout<<clusteredData<<std::endl;

    // Perform k-means clustering on the eigenvectors
    // Replace this step with your own k-means implementation if desired
    vector<int> labels(N, 0);


    return labels;
}

int main() {
    // Example input adjacency matrix
    vector<vector<double>> adjacencyMatrix = {
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}
    };

    int numClusters = 2;  // Number of clusters to be formed

    // Apply spectral clustering
    vector<int> clusterLabels = spectralClustering(adjacencyMatrix, numClusters);

    // Print the cluster labels
    for (int i = 0; i < clusterLabels.size(); i++) {
        cout << "Node " << i << " belongs to Cluster " << clusterLabels[i] << endl;
    }

    return 0;
}

