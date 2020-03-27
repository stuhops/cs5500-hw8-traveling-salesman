#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include <time.h>
#include <chrono> 
#include <vector>

#define MCW MPI_COMM_WORLD

using namespace std;
using namespace std::chrono; 

void print(string message, vector<int> arr);

// Helper Functions
vector<int> swap(vector<int> vect, int left_idx, int right_idx);

// Fitness Function

// Crossover

// Mutation
vector<int> mutate(vector<int> vect);

// Selection Policy
// Always take the top few and then a few randomly

// Initialize
vector<vector<int>> initialize(int SIZE);

int main(int argc, char **argv) {
  // srand(NULL);
  const int SIZE = 8;
  const int DATA_X[SIZE] = { 5, 2, 4, 6, 7, 8, 1, 3 };
  const int DATA_Y[SIZE] = { 1, 3, 2, 7, 5, 4, 6, 8 };
  vector<vector<int>> past_vect = initialize(SIZE);
  vector<vector<int>> curr_vect = past_vect;

  for(int i = 0; i < SIZE; i++) {
    print("", past_vect[i]);
  }
  // Initialize program using the original order
  // Use mutation function to give n work
  
  // Compare paths and sort viability
  // Take top 1/8 paths
  // Randomly take another 1/8 
  
  // Randomly use crossover function (n times)
  return 0;
}


void print(string message, vector<int> vect) {
  cout << message << ": " << endl;

  cout << vect[0];
  for(int i = 1; i < vect.size(); i++) {
    cout << ", " << vect[i];
  }
  cout << endl;
}


vector<int> swap(vector<int> vect, int left_idx, int right_idx) {
  int tmp = vect[left_idx];
  vect[left_idx] = vect[right_idx];
  vect[right_idx] = tmp;

  return vect;
}


vector<int> mutate(vector<int> vect, int times_to_mutate) {
  // 8 seems like a probable number of good mutations
  for(int i = 0; i < times_to_mutate; i++) {
    int left_idx = rand() % vect.size();
    int right_idx = rand() % vect.size();
    vect = swap(vect, left_idx, right_idx);
  }

  return vect;
}


vector<vector<int>> initialize(int SIZE) {
  vector<vector<int>> vect;
  for(int i = 0; i < SIZE; i++) {
    vector<int> vect2;
    for(int j = 0; j < SIZE; j++) {
      vect2.push_back(j);
    }
    vect2 = mutate(vect2, SIZE / 2);

    vect.push_back(vect2);
  }
  return vect;
}