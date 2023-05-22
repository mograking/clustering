#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the dot product of two vectors
double dot_product(const vector<double>& vec1, const vector<double>& vec2) {
    double result = 0.0;
    for (size_t i = 0; i < vec1.size(); i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

// Function to calculate the magnitude of a vector
double vector_magnitude(const vector<double>& vec) {
    double magnitude = 0.0;
    for (double value : vec) {
        magnitude += value * value;
    }
    return sqrt(magnitude);
}

// Function to calculate the cosine similarity between two vectors
double cosine_similarity(const vector<double>& vec1, const vector<double>& vec2) {
    double dot_product_result = dot_product(vec1, vec2);
    double magnitude1 = vector_magnitude(vec1);
    double magnitude2 = vector_magnitude(vec2);
    return dot_product_result / (magnitude1 * magnitude2);
}

// Function to create a similarity matrix from a 2D vector
vector<vector<double>> create_similarity_matrix(const vector<vector<double>>& data) {
    size_t num_vectors = data.size();
    vector<vector<double>> similarity_matrix(num_vectors, vector<double>(num_vectors));

    for (size_t i = 0; i < num_vectors; i++) {
        for (size_t j = 0; j < num_vectors; j++) {
            if (i == j) {
                similarity_matrix[i][j] = 1.0;  // Diagonal elements represent self-similarity (1.0)
            } else {
                double similarity = cosine_similarity(data[i], data[j]);
                similarity_matrix[i][j] = similarity;
            }
        }
    }

    return similarity_matrix;
}

// Function to print the similarity matrix
void print_matrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Example input 2D vector
    vector<vector<double>> input_vector = {
        {1.0, 0.0, -3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    // Create the similarity matrix
    vector<vector<double>> similarity_matrix = create_similarity_matrix(input_vector);

    // Print the similarity matrix
    print_matrix(similarity_matrix);

    return 0;
}

