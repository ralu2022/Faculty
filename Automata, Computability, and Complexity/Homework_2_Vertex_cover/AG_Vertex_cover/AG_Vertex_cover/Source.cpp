#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>

const int POPULATION_SIZE = 350;
const int MAX_GENERATIONS = 700;
const double MUTATION_RATE = 0.10;
const double CROSSOVER_RATE = 0.8;
const double ALPHA = 200.0; // penalitate pentru varfurile care nu acopera muchiile

class Graph {
public:
    int V; // numar de varfuri
    std::vector<std::pair<int, int>> edges; // muchii graf

    Graph(int V) : V(V) {}

    void addEdge(int u, int v) {
        edges.push_back({ u, v });
    }

    void generateCompleteGraph() {
        for (int u = 1; u <= V; ++u) {
            for (int v = u + 1; v <= V; ++v) {
                addEdge(u, v);
            }
        }


    }

   };

    class VertexCoverGA {
    private:
        Graph graph;
        std::vector<std::string> population;

    public:
        VertexCoverGA(const Graph& graph) : graph(graph) {
            initializePopulation();
        }

        void initializePopulation() {
            for (int i = 0; i < POPULATION_SIZE; i++) {
                std::string chromosome;
                for (int j = 0; j < graph.V; j++) {
                    chromosome += (rand() % 2) ? "1" : "0";
                }
                population.push_back(chromosome);
            }
        }

        double fitnessFunction(const std::string& chromosome) {
            int selectedVertices = 0;
            int uncoveredEdges = 0;
            for (char bit : chromosome) {
                if (bit == '1') selectedVertices++;
            }
            for (const auto& edge : graph.edges) {
                if (chromosome[edge.first] != '1' && chromosome[edge.second] != '1') {
                    uncoveredEdges++;
                }
            }
            return selectedVertices + ALPHA * uncoveredEdges;
        }

        void randomSimpleSelection(std::string& parent1, std::string& parent2) {
            parent1 = population[rand() % POPULATION_SIZE];
            parent2 = population[rand() % POPULATION_SIZE];
        }

        void rouletteWheelSelection(std::string& parent1, std::string& parent2) {
            double fitnessSum = 0.0;

            for (const auto& individual : population) {
                fitnessSum += fitnessFunction(individual);
            }

            double slice1 = (double)rand() / RAND_MAX * fitnessSum;
            double slice2 = (double)rand() / RAND_MAX * fitnessSum;

            double tempSum = 0.0;
            for (const auto& individual : population) {
                tempSum += fitnessFunction(individual);
                if (tempSum >= slice1 && parent1.empty()) {
                    parent1 = individual;
                }
                if (tempSum >= slice2 && parent2.empty()) {
                    parent2 = individual;
                }
                if (!parent1.empty() && !parent2.empty()) break;
            }
        }

        std::vector<std::string>& getPopulation() {
            return population;
        }

        void crossover(std::string& offspring1, std::string& offspring2) {
            if ((double)rand() / RAND_MAX < CROSSOVER_RATE) {
                int crossoverPoint = rand() % offspring1.size();
                for (int i = 0; i < crossoverPoint; i++) {
                    std::swap(offspring1[i], offspring2[i]);
                }
            }
        }

        void mutate(std::string& chromosome) {
            for (char& bit : chromosome) {
                if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                    bit = (bit == '1') ? '0' : '1';
                }
            }
        }

    };

    int main() {
        srand(time(0));

        int numVertices = 4;

        Graph graph(numVertices);
        graph.generateCompleteGraph();

         //Afisare graf generat
        std::cout << "Muchii graf generat:" << std::endl;
        for (const auto& edge : graph.edges) {
            std::cout << edge.first + 1 << " - " << edge.second + 1<< std::endl;
        }

       
        VertexCoverGA ga(graph);
     
        //std::cout << "Testare cu metoda selectiei simple:" << std::endl;
        //std::cout << "Testare cu metoda selectiei de tip ruleta:" << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();

        for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
            std::vector<std::string> newPopulation;
            for (int i = 0; i < POPULATION_SIZE / 2; i++) {
                std::string parent1, parent2;
                  //ga.randomSimpleSelection(parent1, parent2);
                  ga.rouletteWheelSelection(parent1, parent2);

                std::string offspring1 = parent1, offspring2 = parent2;
                ga.crossover(offspring1, offspring2);
                ga.mutate(offspring1);
                ga.mutate(offspring2);

                newPopulation.push_back(offspring1);
                newPopulation.push_back(offspring2);
            }

            /* for (int i = 0; i < POPULATION_SIZE / 2; i++) {
                 std::string parent1, parent2;
                 ga.randomSimpleSelection(parent1, parent2);

                 std::cout << "Parinte 1: " << parent1 << std::endl;
                 std::cout << "Parinte 2: " << parent2 << std::endl;

             }*/

             // inlocuire membri mai slabi cu cei noi

            std::vector<std::string>& population = ga.getPopulation();
            std::sort(population.begin(), population.end(), [&ga](const std::string& a, const std::string& b) {
                return ga.fitnessFunction(a) < ga.fitnessFunction(b);
                });
            std::sort(newPopulation.begin(), newPopulation.end(), [&ga](const std::string& a, const std::string& b) {
                return ga.fitnessFunction(a) < ga.fitnessFunction(b);
                });
            std::copy(newPopulation.begin(), newPopulation.begin() + POPULATION_SIZE / 2, population.begin());

            // evaluare si afisare a celui mai bun candidat
            double bestFitness = std::numeric_limits<double>::max();
            std::string bestIndividual;
            for (const std::string& individual : population) {
                double fitness = ga.fitnessFunction(individual);
                if (fitness < bestFitness) {
                    bestFitness = fitness;
                    bestIndividual = individual;
                }
            }

          std::cout << "Generatie " << generation + 1 << ": cel mai bun fitness = " << bestFitness << std::endl;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = endTime - startTime;
        std::cout << "Timp procesare: " << elapsedTime.count() << " secunde" << std::endl;

        return 0;
    }
