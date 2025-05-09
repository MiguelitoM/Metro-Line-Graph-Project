#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <sstream>
#include <string>

using namespace std;

vector<vector<int>> getInput() {
    int stations_size, connections_size, lines_size;
    cin >> stations_size >> connections_size >> lines_size;
    vector<vector<int>> data;
    data.push_back({stations_size, connections_size, lines_size});

    for (int i = 0; i < connections_size; i++) {
        int station1, station2, line;
        cin >> station1 >> station2 >> line;
        data.push_back({station1, station2, line});
    }
    return data;
}

vector<set<int>> transform_graph(const vector<vector<int>>& data) {
    int stations_size = data[0][0];
    int lines_size = data[0][2];

    vector<set<int>> stations(stations_size);
    vector<set<int>> lines(lines_size);

    for (size_t i = 1; i < data.size(); i++) {
        int line = data[i][2];
        for (int station_index = 0; station_index < 2; station_index++) {
            int station = data[i][station_index];
            if (!stations[station-1].count(line)) {
                stations[station-1].insert(line);
                for (int connected_line : stations[station-1]) {
                    if (connected_line != line  && !lines[line-1].count(connected_line)) {
                        lines[line-1].insert(connected_line);
                        lines[connected_line-1].insert(line);
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < stations.size(); i++) {
        if (stations[i].empty()) {
            cout << i << endl;
        }
    }
    for (set<int> station : stations) {
        if (station.empty()) {
            cout << "aqui\n";
            return {{-1}}; // Return -1 if any station has no connections.
        }
    }

    for (int line = 0; line < lines_size; line++) {
        bool fully_connected = true;
        for (set<int> station : stations) {
            if (!station.count(line)) {
                fully_connected = false;
                break;
            }
        }
        if (fully_connected) {
            return {{0}}; // Return 0 if all stations are connected to this line.
        }
    }

    return lines;
}


int bfs(const vector<set<int>>& graph, int start) {
    queue<pair<int, int>> q;
    set<int> visited;

    q.push({start + 1, 0});
    visited.insert(start + 1);

    int max_distance = 0;

    while (!q.empty()) {
        int node = q.front().first;
        int dist = q.front().second;
        q.pop();

        max_distance = max(max_distance, dist);

        for (int neighbor : graph[node - 1]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push({neighbor, dist + 1});
            }
        }
    }

    if (visited.size() != graph.size()) {
        return -1;
    }

    return max_distance;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<vector<int>> data = getInput();
    int max_distance = 0;

    vector<set<int>> graph = transform_graph(data);

    /* for (set<int> line : graph) {
        for (int element: line) {
            cout << element << " ";
        }
        cout << endl;
    } */

    if (graph.size() == 1 && graph[0].count(-1)) {
        cout << -1 << endl;
        return 0;
    }
    if (graph.size() == 1 && graph[0].count(0)) {
        cout << 0 << endl;
        return 0;
    }

    for (size_t line = 0; line < graph.size(); line++) {
        int dist = bfs(graph, line);
        if (dist == -1) {
            max_distance = -1;
            cout << "different size\n";
            break;
        }
        max_distance = max(bfs(graph, line), max_distance);
    }

    cout << max_distance << endl;
    return 0;
}