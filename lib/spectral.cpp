#include <iostream>
#include <vector>
#include <Eigen/Dense>  

using namespace std;
using namespace Eigen;

vector<int> spectralClustering(const vector<vector<double> >& adjacencyMatrix, int numClusters) {
    int N = adjacencyMatrix.size();
    MatrixXd A(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A(i, j) = adjacencyMatrix[i][j];
        }
    }

    MatrixXd D = A.colwise().sum().asDiagonal();
    MatrixXd L = D - A;

    SelfAdjointEigenSolver<MatrixXd> eigensolver(L);
    if (eigensolver.info() != Success) {
        cerr << "Eigenvalue decomposition failed." << endl;
        exit(1);
    }

    MatrixXd eigenvectors = eigensolver.eigenvectors();
    MatrixXd clusteredData = eigenvectors.block(0, 0, N, numClusters);

    std::cout<<eigenvectors<<std::endl;
    std::cout<<clusteredData<<std::endl;

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

