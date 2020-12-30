#include <iostream>
#include <vector>
#include <queue>


struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(size_t verticesCount)  {
        graph.resize(verticesCount);
    }

    ListGraph(const IGraph&);

    virtual ~ListGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override {
        graph[from].push_back(to);
        graph[to].push_back(from);

    }

    int VerticesCount() const override { return graph.size(); }

    std::vector<int> GetNextVertices(int vertex) const  override {
        std::vector<int> result;
        result.resize(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> result;
        for (size_t i = 0; i < graph.size(); ++i) {
            for (auto child : graph[i]) {
                if (child == vertex) {
                    result.push_back(i);
                    break;
                }
            }
        }
        return result;
    }

private:
    std::vector <std::vector<int> > graph;
};

void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);

    for (auto child : graph.GetNextVertices(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited, callback);
        }
    }
}

void dfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, i, visited, callback);
        }
    }
}

void bfs(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    std::queue<int> queue;
    visited.resize(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
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

int PathsCounter(const ListGraph &graph, int &a, int &b) {
    int count = graph.VerticesCount();
    int paths[count];
    int depth[count];
    std::queue<int> queue;

    bool visited[count]; // INIT
    for (size_t i = 0; i < count; ++i){
        paths[i] = depth[i] = 0;
        visited[i] = false;
    }

    queue.push(a);
    paths[a] = 1;
    while (!queue.empty()) {
        int buf = queue.front();
        queue.pop();

        std::vector<int> vertices = graph.GetNextVertices(buf);
        for (auto i : vertices) {
            if (depth[i] == depth[buf] + 1) {
                paths[i] += paths[buf];
            } else if (!visited[i]) {
                queue.push(i);
                visited[i] = true;
                depth[i] = depth[buf] + 1;
                paths[i] = paths[buf];
            }
        }
    }
    return paths[b];
}

int main() {
    int v, n, a, b;
    std::cin >> v >> n;

    ListGraph graph(v);
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        graph.AddEdge(a, b);
    }

    std::cin >> a >> b;
    auto res = PathsCounter(graph, a, b);
    std::cout << res;
    return 0;
}