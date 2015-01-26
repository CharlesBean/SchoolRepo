/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6
 * Written by James Daly
 * Completed by Charles Bean
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <bits/stl_queue.h>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename) : numVertices(0), numArcs(0) {
	ifstream in(filename);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	getline(in, line);
	istringstream vertexStream(line);
	vertexStream >> numVertices;
	
	// TODO : You can initialize your data structure here.
	adjLists.resize((unsigned long)numVertices + 1);
	
	while(getline(in,line))
	{
		istringstream iss(line);
		int u, v;
		float weight;
		iss >> u >> v >> weight;
		InsertArc(u, v, weight);
	}
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
	// Intentionally left empty
	// You may do any needed cleanup here
	for (unsigned int i = 0; i < adjLists.size(); i++)
	{
		adjLists[i].clear();
	}

	adjLists.clear();
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight)
{
	adjLists[from].push_back(pair<int, double> (to, weight));

	numArcs += 1;
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const
{
	// error handling
	if (adjLists.size() > (unsigned int)vertex)
		return (int)adjLists[vertex].size();

	return 0;
}

/**
 * Finds the weight of the arc between the two vertices
 * Returns infinity if there is no such arc
 */
double WeightedDigraph::GetArcWeight(int from, int to) const
{
	// Iterate
	if (adjLists.size() > (unsigned int)from)
	{
		for (pair<int, double> lPair : adjLists[from])
		{
			if (lPair.first == to) {
				return lPair.second;
			}
		}
	}

	return numeric_limits<double>::infinity();
}

/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const
{
	double pathTotal = 0.0;

	auto itr = path.begin();
	unsigned int count = 0;

	while (path.size() > count)
	{
		int head = *itr;
		itr++;
		int tail = *itr;

		count++;

		// If they are connected and the last int is found
		if (AreConnected(head, tail) && tail == *path.rbegin())
		{
			// Add the weight
			for (pair<int, double> arc : adjLists[head])
			{
				if (arc.first == tail)
				{
					pathTotal += arc.second;
				}
			}

			return pathTotal;
		}
		// If they are just connected
		else if (AreConnected(head, tail))
		{
			// Add the weight
			for (pair<int, double> arc : adjLists[head])
			{
				if (arc.first == tail)
				{
					pathTotal += arc.second;
				}
			}
		}
		else if (!AreConnected(head, tail)) // If they aren't connected anymore :(
			return numeric_limits<double>::infinity();
	}

	return numeric_limits<double>::infinity();
}

/**
 * Checks whether an arc exists between two vertices.
 */
bool WeightedDigraph::AreConnected(int from, int to) const
{
	if (adjLists.size() > (unsigned int)from)
	{
		for (pair<int, double> lPair : adjLists[from])
		{
			if (lPair.first == to)
			{
				return true;
			}
		}
	}

	return false;
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const
{
	list<int> visitedNodes;

	bool answer = BreadthFirstSearch(from, visitedNodes, to);

	return answer;
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const
{
	auto itr = path.begin();
	unsigned int count = 0;

	while (path.size() > count)
	{
		int head = *itr;
		itr++;
		int tail = *itr;

		count++;

		// If they are connected and the last int is found
		if (AreConnected(head, tail) && tail == *path.rbegin())
		{
			return true; // We've found it!
		}
		else if (!AreConnected(head, tail)) // If they aren't connected anymore :(
			return false;
	}

	return false;
}

/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const
{
	// Assume the path exists


	// Vector for keeping track of distances to the start vertex
	vector<double> distances;

	// A queue of smallest neighbor arcs
	list<pair<int, double>> queue;

	// The final path (smallest)
	list<int> finalPath;

	// Resize to the size of our initial storage (number of vertices) and start all neighbors at infinity (undiscovered)
	distances.resize(adjLists.size(), numeric_limits<double>::infinity());
	distances[from] = 0.0; // Make the distance from start to start equal to 0

	// Use dijkstras (recursion) - gives us a queue
	Dijkstras(from, to, distances, queue);

	// Create path
	finalPath.push_back(from);
	for (auto arc : queue)
	{
		// Add the arcs verteces to the final path
		finalPath.push_back(arc.first);
	}
	finalPath.push_back(to);

	return finalPath;
}

/**
* Recursive function for seeing if a path exists
*/
bool WeightedDigraph::BreadthFirstSearch(int adjListIndex, list<int> &visitedNodes, int endVertex) const
{
	// Set default return flag (this is recursive function)
	bool ret = false;

	// Add the starting node to the list of visited (we are visiting now)
	visitedNodes.push_back(adjListIndex);

	// If the index exists
	if (adjLists.size() > (unsigned int)adjListIndex)
	{
		// For each arc
		for (pair<int, double> arc : adjLists[adjListIndex])
		{
			// If the pointed-to vertex is the endVertex
			if (arc.first == endVertex)
				ret =  true; // We are connected

			// If the node has not been visited
			if ((find(visitedNodes.begin(), visitedNodes.end(), arc.first) == visitedNodes.end()))
			{
				if (!adjLists[arc.first].empty())
				{
					ret = BreadthFirstSearch(arc.first, visitedNodes, endVertex); // Recursion
				}
			}
		}
	}

	return ret;
}

/**
* Dijkstras algorithm - for calculating the smallest path (weighted)
*/
void WeightedDigraph::Dijkstras(int from, int to, vector<double> &distances, list<pair<int, double>> &queue) const
{
	// Create storage to remember the smallest local path (to a neighbor)
	pair<int, double> smallestNeighbor(-1, numeric_limits<double>::infinity());

	// For each arc coming from this vertex
	for (auto arc : adjLists[from])
	{
		// If the distance has yet to be discovered
		if (distances[arc.first] == numeric_limits<double>::infinity())
		{
			distances[arc.first] = arc.second; // Init path weight
		}

		// If we have a new smallest neighbor vertex
		if (distances[arc.first] < smallestNeighbor.second)
			smallestNeighbor = arc; // Remember it
	}

	// If smallest neighbor is not the end
	if (smallestNeighbor.first != to && smallestNeighbor.first != -1)
	{
		// Add current smallest to queue
		queue.push_back(smallestNeighbor);

		// Recursive
		Dijkstras(smallestNeighbor.first, to, distances, queue);
	}
}
