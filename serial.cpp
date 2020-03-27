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
void print(string message, int x);
void printBreak();

vector<int> swap(vector<int> vect, int left_idx, int right_idx);

vector<int> fitness(const int DATA_X[], const int DATA_Y[], vector<vector<int>> vect);
vector<vector<int>> sort_by_fitness(vector<vector<int>> vect, vector<int> fit_vect);

// Crossover

vector<int> mutate(vector<int> vect);

int findIndex(vector<int> vect, int value);
vector<int> crossover(vector<int> top, vector<int> bottom, int start, int end);
// Selection Policy
// Always take the top few and then a few randomly


// Initialize
vector<vector<int>> initialize_vect(int SIZE);

int main(int argc, char **argv) {
  srand(time(NULL));
  const int SIZE = 4;
  // const int DATA_X[SIZE] = { 5, 2, 4, 6, 7, 8, 1, 3 };
  // const int DATA_Y[SIZE] = { 1, 3, 2, 7, 5, 4, 6, 8 };
  const int DATA_X[SIZE] = { 10, 2, 3, 7 };
  const int DATA_Y[SIZE] = { 1, 0, 8, 4 };
  vector<vector<int>> past_vect = initialize_vect(SIZE);
  vector<vector<int>> curr_vect = past_vect;
  vector<int> fitness_vect = fitness(DATA_X, DATA_Y, past_vect);

  curr_vect = sort_by_fitness(past_vect, fitness_vect);
  past_vect = curr_vect;

  for(int i = 0; i < SIZE; i++) {
    print("", curr_vect[i]);
  }
  cout << endl;
  printBreak();

  curr_vect[1] = crossover(curr_vect[0], curr_vect[1], 1, 3);
  for(int i = 0; i < SIZE; i++) {
    print("", curr_vect[i]);
  }
  cout << endl;

  // Compare paths and sort viability
  // Take top 1/8 paths
  // Randomly take another 1/8 
  
  // Randomly use crossover function (n times)
  return 0;
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


vector<int> fitness(const int DATA_X[], const int DATA_Y[], vector<vector<int>> vect) {
  vector<int> fitness_vect;
  fitness_vect.resize(vect.size());
  int distance;

  for(int i = 0; i < vect.size(); i++) {
    distance = 0;
    for(int j = 0; j < vect.size() - 1; j++) {
      int x1 = DATA_X[vect[i][j]];
      int y1 = DATA_Y[vect[i][j]];

      int x2 = DATA_X[vect[i][j+1]];
      int y2 = DATA_Y[vect[i][j+1]];

      int dist_x = max(x1, x2) - min(x1, x2);
      int dist_y = max(y1, y2) - min(y1, y2);

      distance += dist_x + dist_y;
    }
    int x1 = DATA_X[vect[i].front()];
    int y1 = DATA_Y[vect[i].front()];

    int x2 = DATA_X[vect[i].back()];
    int y2 = DATA_Y[vect[i].back()];

    int dist_x = max(x1, x2) - min(x1, x2);
    int dist_y = max(y1, y2) - min(y1, y2);

    distance += dist_x + dist_y;
    fitness_vect[i] = distance;
  }
  
  return fitness_vect;
}


vector<vector<int>> sort_by_fitness(vector<vector<int>> vect, vector<int> fit_vect) {
  int tmp;
  vector<int> tmp_vect;

  for(int i = 0; i < fit_vect.size(); i++) {
    for(int j = 0; j < fit_vect.size(); j++) {
      if(fit_vect[i] < fit_vect [j]) {
        tmp = fit_vect[i];
        tmp_vect = vect[i];

        fit_vect[i] = fit_vect[j];
        vect[i] = vect[j];
        fit_vect[j] = tmp;
        vect[j] = tmp_vect;
      }
    }
  }

  return vect;
}


int findIndex(vector<int> vect, int value) {
  for(int i = 0; i < vect.size(); i++) {
    if(vect[i] == value) {
      return i;
    }
  }
  return -1;
}


vector<int> crossover(vector<int> top, vector<int> bottom, int start, int end) {
  for(int i = start; i < end; i++) {
    int idx = findIndex(bottom, top[i]);
    bottom = swap(bottom, i, idx);
    print("NewBottom", bottom);
  }
  return bottom;
}


vector<vector<int>> initialize_vect(int SIZE) {
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


void print(string message, vector<int> vect) {
  cout << message << ": " << endl;

  cout << vect[0];
  for(int i = 1; i < vect.size(); i++) {
    cout << ", " << vect[i];
  }
  cout << endl;
}

void print(string message, int x) {
  cout << message << ": " << x << endl;
}

void printBreak() {
  cout << "\n--------------------------------\n";
}