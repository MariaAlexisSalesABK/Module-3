#include <iostream>
#include <chrono>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <set>

#define ARRAY_SIZE 100

using namespace std;

uint32_t GetNanos();
void FillArray(int ArrayToFill[], int SizeOfArray);
void BubbleSort(int ArrayToSort[], int SizeOfArray);
void AStarAlgorithm(map<char, vector<pair<char, int>>> adjList, char start, char end);
void printPath(queue<char> path, int weight);

struct Edge {
    char edge;
    int weight;
};

int main() 
{
    // Sort with chrono library profile
    int Dataset[ARRAY_SIZE];
    srand(time(nullptr));
    FillArray(Dataset, ARRAY_SIZE);

    uint32_t StartNanos = GetNanos();
    BubbleSort(Dataset, ARRAY_SIZE);
    uint32_t EndNanos = GetNanos();

    cout << "Bubble Sort took: " << (EndNanos - StartNanos) << "ns\n" << endl;

    // A* algorithm
    map<char, vector<pair<char, int>>> adjList;
    
}

uint32_t GetNanos() {
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

void FillArray(int ArrayToFill[], int SizeOfArray) {
    for(int i = 0; i < ARRAY_SIZE; i++) {
        ArrayToFill[i] = rand() % ARRAY_SIZE + 1;
    }
}

void BubbleSort(int ArrayToSort[], int SizeOfArray) {
    for(int i = 0; i < SizeOfArray; i++) {
        for(int j = 0; j < SizeOfArray - 1; j++) {
            if(ArrayToSort[j] > ArrayToSort[j + 1]) {
                int temp = ArrayToSort[j];
                ArrayToSort[j] = ArrayToSort[j + 1];
                ArrayToSort[j + 1] = temp;
            }
        }
    }
}

void AStarAlgorithm(map<char, vector<pair<char, int>>> adjList, char start, char end) {
    priority_queue<pair<int, char>> pq;
    map<char, int> dist;
    queue<char> path;
    int finalW = 0;

    dist[start] = 0;

    for(auto& e : adjList) {
        if(e.first == start) continue;
        dist[e.first] = INT_MAX;
    }

    pq.push(make_pair(0, start));

    while(!pq.empty()) {
        finalW = pq.top().first;
        char u = pq.top().second;
        path.push(pq.top().second); // For printing path later
        pq.pop();

        vector<pair<char, int>> temp = adjList[u]; // Grabs the vector of connecting vertices

        for(auto& e : temp) {
            char v = e.first;
            int weight = e.second;

            if(v == end) {
                
                printPath(path, finalW);
            }
            else if(dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void printPath(queue<char> path, int weight) {
    cout << "The path is: " << endl;

    while(!path.empty()) {
        cout << path.front() << "->";
    }

    cout << "\n For a total cost of " << weight << endl;
}