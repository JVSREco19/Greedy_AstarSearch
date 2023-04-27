#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

class Graph {
public:
  unordered_map<string, vector<pair<string, int>>> adjList;

  void add_node(string node) { adjList[node]; }

  void remove_node(string node) {
    adjList.erase(node);
    for (auto &n : adjList) {
      auto &neighbors = n.second;
      for (auto it = neighbors.begin(); it != neighbors.end();) {
        if (it->first == node) {
          it = neighbors.erase(it);
        } else {
          ++it;
        }
      }
    }
  }

  void add_edge(string n1, string n2, int weight) {
    adjList[n1].push_back(make_pair(n2, weight));
    adjList[n2].push_back(make_pair(n1, weight));
  }

  void remove_edge(string n1, string n2) {
    auto &neighbors1 = adjList[n1];
    for (auto it = neighbors1.begin(); it != neighbors1.end();) {
      if (it->first == n2) {
        it = neighbors1.erase(it);
      } else {
        ++it;
      }
    }
    auto &neighbors2 = adjList[n2];
    for (auto it = neighbors2.begin(); it != neighbors2.end();) {
      if (it->first == n1) {
        it = neighbors2.erase(it);
      } else {
        ++it;
      }
    }
  }

  vector<pair<string, int>> &get_neighbors(string node) {
    return adjList[node];
  }
};

// Algoritmo A* para encontrar o caminho mais curto do vertice fornecido até
// Bucareste
void A_estrela(string start_node, Graph &g,
                   unordered_map<string, int> &dist_list) {
  // Criar um conjunto para manter o controle dos nós visitados
    set<string> visited;
    vector<string> path;
  // Criar uma fila de prioridade para guardar os nós em ordem de proximidade a
  // Bucareste
  priority_queue<pair<double, string>, vector<pair<double, string>>,
                 greater<pair<double, string>>>
      frontier;

  // Adicionar o nó inicial na fila de prioridade
  frontier.push(make_pair(dist_list[start_node], start_node));

  // Enquanto a fila de prioridade não estiver vazia, remover o próximo nó da
  // fila e explorá-lo
  while (!frontier.empty()) {
    // Obter o próximo nó da fila de prioridade
    auto current = frontier.top().second;
    frontier.pop();

    // Se o nó atual já foi visitado, ignorá-lo e continuar
    if (visited.count(current)) {
      continue;
    }
        
    // Marcar o nó atual como visitado
    visited.insert(current);
    path.push_back(current);

    // Se o nó atual é o objetivo (Bucareste), mostrar o caminho e encerrar o
    // algoritmo
    if (current == "Bucharest") {
      cout << "Caminho encontrado A*: " << endl;
      
     for (auto i : path) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

      return;
    }

    // Para cada vizinho do nó atual, se ele ainda não foi visitado, adicioná-lo
    // na fila de prioridade
    for (auto &neighbor : g.get_neighbors(current)) {
      string neighbor_name = neighbor.first;
      if (!visited.count(neighbor_name)) {
        double priority = dist_list[neighbor_name] + neighbor.second;
        frontier.push(make_pair(priority, neighbor_name));
      }
    }
  }

  // Se chegou aqui, não foi possível encontrar um caminho até Bucareste
  cout << "Caminho não encontrado" << endl;
}


// Algoritmo Guloso para encontrar o caminho mais curto do vertice fornecido até
// Bucareste
void greedy_search(string start_node, Graph &g,
                   unordered_map<string, int> &dist_list) {
  // Criar um conjunto para manter o controle dos nós visitados
    set<string> visited;
    vector<string> path;
  // Criar uma fila de prioridade para guardar os nós em ordem de proximidade a
  // Bucareste
  priority_queue<pair<double, string>, vector<pair<double, string>>,
                 greater<pair<double, string>>>
      frontier;

  // Adicionar o nó inicial na fila de prioridade
  frontier.push(make_pair(dist_list[start_node], start_node));

  // Enquanto a fila de prioridade não estiver vazia, remover o próximo nó da
  // fila e explorá-lo
  while (!frontier.empty()) {
    // Obter o próximo nó da fila de prioridade
    auto current = frontier.top().second;
    frontier.pop();

    // Se o nó atual já foi visitado, ignorá-lo e continuar
    if (visited.count(current)) {
      continue;
    }
        
    // Marcar o nó atual como visitado
    visited.insert(current);
    path.push_back(current);
    

    // Se o nó atual é o objetivo (Bucareste), mostrar o caminho e encerrar o
    // algoritmo
    if (current == "Bucharest") {
      cout << "Caminho encontrado (Guloso): " << endl;
      
     for (auto i : path) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

      return;
    }

    // Para cada vizinho do nó atual, se ele ainda não foi visitado, adicioná-lo
    // na fila de prioridade
    for (auto &neighbor : g.get_neighbors(current)) {
      string neighbor_name = neighbor.first;
      if (!visited.count(neighbor_name)) {
        double priority = dist_list[neighbor_name];
        frontier.push(make_pair(priority, neighbor_name));
      }
    }
  }

  // Se chegou aqui, não foi possível encontrar um caminho até Bucareste
  cout << "Caminho não encontrado" << endl;
}

int main() {
  // Criando a lista da distancia reta até bucharest
  unordered_map<string, int> linearDistList;

  linearDistList["Oradea"] = 380;
  linearDistList["Zerind"] = 374;
  linearDistList["Arad"] = 366;
  linearDistList["Timisoara"] = 329;
  linearDistList["Lugoj"] = 244;
  linearDistList["Mehadia"] = 241;
  linearDistList["Drobeta"] = 242;
  linearDistList["Sibiu"] = 253;
  linearDistList["Rimnieu Vilcea"] = 193;
  linearDistList["Craiova"] = 160;
  linearDistList["Fagaras"] = 176;
  linearDistList["Pitesti"] = 100;
  linearDistList["Bucharest"] = 0;
  linearDistList["Giurgiu"] = 77;
  linearDistList["Urziceni"] = 80;
  linearDistList["Vaslui"] = 199;
  linearDistList["Neamt"] = 234;
  linearDistList["Iasi"] = 226;
  linearDistList["Hirsova"] = 151;
  linearDistList["Eforie"] = 161;

  // Cria um novo grafo
  Graph g;

  // Adiciona alguns nósg.add_node("Oradea");
  g.add_node("Zerind");
  g.add_node("Arad");
  g.add_node("Timisoara");
  g.add_node("Lugoj");
  g.add_node("Mehadia");
  g.add_node("Drobeta");
  g.add_node("Sibiu");
  g.add_node("Rimnieu Vilcea");
  g.add_node("Craiova");
  g.add_node("Fagaras");
  g.add_node("Pitesti");
  g.add_node("Bucharest");
  g.add_node("Giurgiu");
  g.add_node("Urziceni");
  g.add_node("Vaslui");
  g.add_node("Neamt");
  g.add_node("Iasi");
  g.add_node("Hirsova");
  g.add_node("Eforie");

  // Adiciona algumas arestas com pesos
  g.add_edge("Oradea", "Zerind", 71);
  g.add_edge("Oradea", "Sibiu", 151);
  g.add_edge("Zerind", "Arad", 75);
  g.add_edge("Arad", "Timisoara", 118);
  g.add_edge("Arad", "Sibiu", 140);
  g.add_edge("Timisoara", "Lugoj", 111);
  g.add_edge("Lugoj", "Mehadia", 70);
  g.add_edge("Mehadia", "Drobeta", 75);
  g.add_edge("Drobeta", "Craiova", 120);
  g.add_edge("Sibiu", "Fagaras", 99);
  g.add_edge("Sibiu", "Rimnieu Vilcea", 80);
  g.add_edge("Rimnieu Vilcea", "Craiova", 146);
  g.add_edge("Rimnieu Vilcea", "Pitesti", 97);
  g.add_edge("Pitesti", "Bucharest", 101);
  g.add_edge("Pitesti", "Craiova", 138);
  g.add_edge("Fagaras", "Bucharest", 211);
  g.add_edge("Bucharest", "Giurgiu", 90);
  g.add_edge("Bucharest", "Urziceni", 85);
  g.add_edge("Urziceni", "Vaslui", 142);
  g.add_edge("Urziceni", "Hirsova", 98);
  g.add_edge("Vaslui", "Iasi", 92);
  g.add_edge("Hirsova", "Eforie", 86);
  g.add_edge("Iasi", "Neamt", 87);

  string startinCity;
  do{
  cout<<"Cidade de inicio: ";
  cin>> startinCity;
    if(linearDistList[startinCity] || startinCity=="Bucharest"){
      
    greedy_search(startinCity,g,linearDistList);
    cout<<endl;
    cout<<endl;
    cout<<endl;

    A_estrela(startinCity,g,linearDistList);
    cout<<endl;
    }else{
      cout<<"Fim do programa";
    }
    

  }while(linearDistList[startinCity] || startinCity=="Bucharest");

  return 0;
}