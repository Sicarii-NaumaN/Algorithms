#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() {
    }
    virtual void AddEdge(int from, int to) = 0;
    virtual int VertisesCount() const = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> SetNextVertices(int vertex) const = 0;
};
class ListGraph: IGraph {
public:
    ListGraph(size_t vetices_count) {
        graph.resize(vetices_count);
    }
    ListGraph(const IGraph&);
    virtual ~ListGraph() {
    }
    void AddEdge(int from, int to) override {
        graph[from].push_back(to);
    }
    virtual int VertisesCount() const {return graph.size();};
    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> result;
        result.resize(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }
    std::vector<int> SetNextVertices(int vertex) const {
        std::vector<int> result;
        for (size_t i = 0; i < graph.size(); ++i) {
            for (auto child : graph[i]) {
                if (child == vertex) {
                    result.push_back(i);
                    break;
                }
            }
        }
    }

private:
    std::vector<std::vector<int>> graph;
};
void dfs_aux(const IGraph& graph, int vertex, std::vector<bool> &visited, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);
    for (auto child : graph.GetNextVertices(vertex)) {
        if (!visited[child])
            dfs_aux(graph, child, visited, callback);
    }
}

void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    visited.resize(graph.VertisesCount(), false);

    for (int i = 0; i< graph.VertisesCount(); ++i) {
        if (!visited[i])
            dfs_aux(graph, i, visited, callback);
    }
}

void bfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    std::queue<int> queue;
    visited.resize(graph.VertisesCount(), false);

    for (int i = 0; i< graph.VertisesCount(); ++i) {
        if (!visited[i]) {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                callback(vertex);
                for (auto child : graph.GetNextVertices(vertex)) {
                    if (!visited[child]) {
                        queue.push(child);
                        visited[child] = true;
                    }
                }
            }
        }
    }
}

int main() {
    ListGraph graph(6);
    graph.AddEdge(0,1);
    graph.AddEdge(1,2);
    graph.AddEdge(1,5);
    graph.AddEdge(2,3);
    graph.AddEdge(3,4);
    graph.AddEdge(4,2);
    /*dfs(graph, [](int  v)) {
        std::

    }*/

    return 0;
}