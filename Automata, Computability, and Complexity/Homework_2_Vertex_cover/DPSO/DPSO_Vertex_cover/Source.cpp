#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <cmath>
#include <chrono>

class Particle {
public:
    std::vector<int> position;
    std::vector<double> velocity;
    std::vector<int> bestPosition;
    int bestValue;

    Particle(int numVertices) {
        position.resize(numVertices);
        velocity.resize(numVertices);
        bestPosition.resize(numVertices);
        bestValue = std::numeric_limits<int>::max();
    }
};

class Graph {
public:
    int V; 
    std::vector<std::vector<int>> edges; 

    Graph(int V) : V(V) {
        edges.resize(V);
    }

    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void generateCompleteGraph() {
        for (int u = 0; u < V; ++u) {
            for (int v = u + 1; v < V; ++v) {
                addEdge(u, v);
            }
        }


    }


};

int objectiveFunction(const Graph& graph, const std::vector<int>& position, double alpha) {
    int coverCount = std::count(position.begin(), position.end(), 1);
    int uncoverCount = 0;

    for (int u = 0; u < graph.V; ++u) {
        if (position[u] == 0) {
            for (int v : graph.edges[u]) {
                if (position[v] == 0) {
                    uncoverCount++;
                    break;
                }
            }
        }
    }

    return coverCount + static_cast<int>(alpha * uncoverCount);
}

void initializeParticles(std::vector<Particle>& particles, int swarmSize, int numVertices) {
    for (int i = 0; i < swarmSize; i++) {
        Particle p(numVertices);
        for (int j = 0; j < numVertices; ++j) {
            p.position[j] = rand() % 2; 
            p.velocity[j] = static_cast<double>(rand()) / RAND_MAX; 
            p.bestPosition[j] = p.position[j];
        }
        p.bestValue = std::numeric_limits<int>::max();
        particles.push_back(p);
    }
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

void updateVelocity(Particle& particle, const std::vector<int>& globalBestPosition, double w, double c1, double c2) {
    for (int i = 0; i < particle.position.size(); ++i) {
        double r1 = static_cast<double>(rand()) / RAND_MAX;
        double r2 = static_cast<double>(rand()) / RAND_MAX;

        double newVelocity = w * particle.velocity[i] +
            c1 * r1 * (particle.bestPosition[i] - particle.position[i]) +
            c2 * r2 * (globalBestPosition[i] - particle.position[i]);
        particle.velocity[i] = sigmoid(newVelocity); 
    }
}

void updatePosition(Particle& particle) {
    for (int i = 0; i < particle.position.size(); ++i) {
        if (static_cast<double>(rand()) / RAND_MAX < particle.velocity[i]) {
            particle.position[i] = 1 - particle.position[i]; 
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    const int swarmSize = 300;
    const int maxIterations =600;
    const double w = 0.55;
    const double c1 = 1.2;
    const double c2 = 1.1;
    const double alpha = 750.0;

    int numVertices = 40;
    Graph graph(numVertices);
    graph.generateCompleteGraph();

    // Afisare graf generat
    std::cout << "Varfuri graf:" << std::endl;
    for (int u = 0; u < graph.V; ++u) {
        for (int v : graph.edges[u]) {
            if (u < v) {
                std::cout << u + 1 << " - " << v + 1 << std::endl;
            }
        }
    }
        std::vector<Particle> particles;
        initializeParticles(particles, swarmSize, graph.V);

        std::vector<int> globalBestPosition(graph.V);
        int globalBestValue = std::numeric_limits<int>::max();

        auto start = std::chrono::high_resolution_clock::now();

        for (int iter = 0; iter < maxIterations; ++iter) {
            for (auto& particle : particles) {
                int currentValue = objectiveFunction(graph, particle.position, alpha);
                if (currentValue < particle.bestValue) {
                    particle.bestValue = currentValue;
                    particle.bestPosition = particle.position;
                }
                if (currentValue < globalBestValue) {
                    globalBestValue = currentValue;
                    globalBestPosition = particle.position;
                }
            }

            for (auto& particle : particles) {
                updateVelocity(particle, globalBestPosition, w, c1, c2);
                updatePosition(particle);
            }

            std::cout << "Iteratie " << iter << ": Cea mai buna valoare = " << globalBestValue << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now(); // End timer
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Timp: " << elapsed.count() << " secunde" << std::endl;

        std::cout << "Cea mai buna valoare finala: " << globalBestValue << std::endl;
        std::cout << "Vertex: ";
        for (int i = 0; i < graph.V; ++i) {
            if (globalBestPosition[i] == 1) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;

        return 0;
}
