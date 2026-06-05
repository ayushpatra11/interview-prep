/*
 *
 * For Graphs : focussing on BFS/DFS, Djikstra, Kahns, MST, Topo Sort, DSU
 *
 */

// The graph can be represented in two ways,
//  1. Adjacency list
//  2. Adjacency Matrix

// Graph Traversal:

vector<int> bfs(vector<vector<int>> adjList) {
  // we use a queue to perform BFS

  queue<int> q;
  vector<int> bfsOrder;
  vector<int> visited(adjList.size(), 0);

  // can choose any starting point
  q.push(0);
  visited[0] = 1;
  while (!q.empty()) {
    // get the current one and traverse from there
    int topNode = q.front();
    bfsOrder.push_back(topNode);
    q.pop();

    for (int &node : adjList[topNode]) {
      if (visited[node])
        continue;
      visited[node] = 1;
      q.push(node);
    }
  }

  return bfsOrder;
}

// to check for disconnected components, we will have to start bfs from
// each non-visited node.
// in the end, we will check if there are any nodes that are not visited...
//

bool checkDisconnected(vector<vector<int>> adjList) {
  int numOfNodes = adjList.size();

  vector<int> visited(numOfNodes, 0);

  for (int node; node < numOfNodes; node++) {
    if (visited[node])
      continue;

    // perform BFS and mark each node as visited
    queue<int> q;
    q.push(node);
    visited[node] = 1;
    while (!q.empty()) {
      int top = q.front();
      q.pop();

      for (int &visitingNode : adjList[top]) {
        if (visited[visitingNode])
          continue;
        q.push(visitingNode);
        visited[visitingNode] = 1;
      }
    }
  }

  for (int i = 0; i < numOfNodes; i++)
    if (!visited[i])
      return false;

  return true;
}

// DFS:

void dfs(vector<vector<int>> &adjList, vector<int> &visited, vector<int> &ans,
         int node) {
  // use a recursive approach.
  visited[node] = 1;

  ans.push_back(node);
  for (int ele : adjList[node]) {
    if (!visited[ele]) {
      dfs(adjList, visited, ans, ele);
    }
  }
}

// For questions like rotten oranges, we have to use BFS.
//  Why BFS? why DFS? important. BFS will find the shortest path.
//

// Cycle detection in an UG graph.

// here striver uses a queue of pairs for parent and child. Whenever we have an
// element we are traversing, we see if the parent is the one that it has in
// it's adjacency that is visited if not, then it means it has 2 parents. we
// have to use BFS here.
//

bool isCyclic(vector<vector<int>> adjList) {
  // have a queue of pairs
  //
  queue<pair<int, int>> q;
  vector<int> visited(adjList.size(), 0);

  q.push({-1, 0});
  visited[0] = 1;

  while (!q.empty()) {
    pair<int, int> top = q.front();
    q.pop();

    int parent = top.first;
    int child = top.second;

    for (int &nbr : adjList[child]) {
      if (visited[nbr] && nbr != parent)
        return true;

      if (visited[nbr])
        continue;
      visited[nbr] = 1;
      q.push({child, nbr});
    }
  }

  return false;
}


// Topo sort: can be done using DFS or BFS(called Kahn's)
// Kahn's : uses an indegree vector. as soon as the indegree
// hits 0, we add it to the queue.

// we can also use topo sort to check if there is a cycle in a DAG.
// just the size should be equal to the number of elements. Else, there is a cycle...
