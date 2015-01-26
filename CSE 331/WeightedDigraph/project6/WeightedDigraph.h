/**
 * A definition of a weighted digraph
 * used for CSE 331 Project 6.
 * Note that the digraph is immutable once created
 *
 * Written by James Daly
 * Completed by [Your Name]
 */
 
#ifndef WeightedDigraph_H
#define WeightedDigraph_H

#include <list>
#include <string>
#include <vector>
#include <bits/stl_deque.h>

using namespace std;

class WeightedDigraph {
public:
	WeightedDigraph(const std::string& filename);
	~WeightedDigraph();
	
	WeightedDigraph(const WeightedDigraph&) = delete;
	WeightedDigraph& operator=(const WeightedDigraph&) = delete;
	
	int GetOrder() const { return numVertices; };
	int GetSize() const { return numArcs; };
	
	int GetOutDegree(int vertex) const;
	
	double GetArcWeight(int from, int to) const;
	double GetPathWeight(const std::list<int> & path) const;
	
	bool AreConnected(int from, int to) const;
	bool DoesPathExist(int from, int to) const;
	bool IsPathValid(const std::list<int> & path) const;
	
	std::list<int> FindMinimumWeightedPath(int from, int to) const;
	
private:
	int numVertices;
	int numArcs;
	
	// Should have used an unordered map!
	vector<list<pair<int, double>>> adjLists;

	void InsertArc(int from, int to, double weight);

	bool BreadthFirstSearch(int adjListIndex, list<int> &visitedNodes, int endVertex) const;

	void Dijkstras(int from, int to, vector<double> &distances, list<pair<int, double>> &queue) const;
};



#endif