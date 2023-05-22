#include <iostream>
#include <vector>
#include "KMeansCluster_vector.h"
#include "spectral.h"
#include "Eigen/Dense"

using namespace std;


int main() {
    vector<vector<double> > adjacencyMatrix = {
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0},
        {1.0, 0.0, 0.0}
    };

    int numClusters = 2;  

    vector<int> clusterLabels = spectralClustering(adjacencyMatrix, numClusters);

    for (int i = 0; i < clusterLabels.size(); i++) {
        cout << "Node " << i << " belongs to Cluster " << clusterLabels[i] << endl;
    }

    return 0;
}

