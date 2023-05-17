#ifndef GRAPH_H_
#define GRAPH_H_

/*******************************************************************************
 *                                Includes Needed                              *
 *******************************************************************************/
#include <bits/stdc++.h>
#include "xml.h"
using namespace std;

/*******************************************************************************
 *                             Class Decelerations                             *
 *******************************************************************************/
class GraphNode
{
public:
	string id;
	string name;
	vector<string> followersList;

	/*	Constructor */
	GraphNode(string id , string name );

	/* Methods */
	void addFollower (string follower_id);

};

/*******************************************************************************
 *                             Types Decelerations                             *
 *******************************************************************************/
typedef  vector<GraphNode> 	Vec_Of_GraphNodes;

/*******************************************************************************
 *               		 Class Helper Functions Prototypes                     *
 *******************************************************************************/
/*
 * Arguments:
 * Vec_Of_Strings_Iterator begin
 * Vec_Of_Strings_Iterator end
 *
 * Description:
 * This function takes the XML vector of strings extract the user's name id and followers
 * and return a vector of these nodes.
 */
Vec_Of_GraphNodes XMLVecOfStrToVecOfGraphNode(Vec_Of_Strings_Iterator begin, Vec_Of_Strings_Iterator end);


/*
 * Arguments:
 * Vec_Of_GraphNodes reference of vec
 *
 * Description:
 * This function takes the vector of nodes of the graph and write the code that
 * the application graphviz accept to draw the graph.
 */
void createGraphVisualization(Vec_Of_GraphNodes &vec);



#endif /* GRAPH_H_ */
