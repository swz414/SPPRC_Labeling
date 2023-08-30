#include "Graph.h"

void Graph::addNode(int index, float_t corX, float_t corY, int demand, int readyTime, int dueTime, int serviceTime)
{
	nodes.emplace(index, Node{ index, corX, corY, demand, readyTime, dueTime, serviceTime});
}

void Graph::addEdge(int from, int to, float_t length, float_t travelTime)
{
	vector<Edge> tmpEdges = edges[from];
	tmpEdges.push_back(Edge{ from, to, length, travelTime });
	edges[from] = tmpEdges;

	previous[to].insert(from);
	successors[from].insert(to);
}

Node Graph::getNode(int index)
{
	return nodes[index];
}

vector<Node> Graph::getNodes()
{
	vector<Node> retVec;
	for (const auto& node : nodes) {
		retVec.emplace_back(node.second);
	}
	return retVec;
}

Edge Graph::getEdge(int from, int to)
{
	for (auto iter = edges[from].begin(); iter != edges[from].end(); ++iter)
	{
		if ((*iter).to == to)
		{
			return *iter;
		}
	}
	return Edge{ 0, 0, 0, 0 };
}

vector<Edge> Graph::getEdges(int from)
{
	return edges[from];
}

vector<Edge> Graph::getAllEdges()
{
	vector<Edge> retVec;
	for (const auto& edge : edges) {
		retVec.insert(retVec.end(), edge.second.begin(), edge.second.end());
	}
	return retVec;
}

vector<int> Graph::getSuccessors(int from)
{
	return vector<int>(successors[from].begin(), successors[from].end());
}

vector<int> Graph::getPrevious(int to)
{
	return vector<int>(previous[to].begin(), previous[to].end());
}


