/*******************************************************************************
 *                                Includes Needed                              *
 *******************************************************************************/
#include "graph.h"

/*******************************************************************************
 *                             Class Definitions                             *
 *******************************************************************************/
/*	Constructor */
GraphNode::GraphNode(string id , string name )
{
	this->id = id;
	this->name = name;
}

/* Methods */
void GraphNode::addFollower (string follower_id)
{
	followersList.push_back(follower_id);
}

/*******************************************************************************
 *               		   Class Helper Functions Definitions                  *
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
Vec_Of_GraphNodes XMLVecOfStrToVecOfGraphNode(Vec_Of_Strings_Iterator begin, Vec_Of_Strings_Iterator end)
{
	Vec_Of_GraphNodes vecOfGraphNodes;
	Vec_Of_Strings_Iterator i = begin, endOfFollowers , temp;

	string id, name;

	/*	Loop until we save all the users and their followers */
	while(i != end)
	{
		/*	Process nth user*/
		temp = find(i, end, "<user>");

		/* Extract the user id. */
		i = find(temp, end, "<id>");
		i++;
		id = *i;

		/* Extract the user name. */
		i = find(temp, end, "<name>");
		i++;
		name = *i;

		GraphNode newGraphNode(id, name);

		/* Extract the user followers. */
		while(*i != "</user>")
		{
			if(*i == "<id>")
			{
				i++;
				id = *i;
				newGraphNode.addFollower(id);
			}
			i++;
		}

		/* Push the user node. */
		vecOfGraphNodes.push_back(newGraphNode);
		i = find(i, end, "<user>");
	}
	return vecOfGraphNodes;
}

/*
 * Arguments:
 * Vec_Of_GraphNodes reference of vec
 *
 * Description:
 * This function takes the vector of nodes of the graph and write the code that
 * the application graphviz accept to draw the graph.
 */
void createGraphVisualization(Vec_Of_GraphNodes &vec)
{
	remove("Graph.bmp");
	remove("Graph.dot");

	string temp(1,34) ;

	string dotFile_Str = "digraph test {\nnode [shape=";
	dotFile_Str += temp + "record" + temp + "  color=" + temp + "red" \
	     +  temp +  "] \n\n";

	for(auto v : vec)
	{
		dotFile_Str += v.id + "[ label = " + temp + "{Name: " + v.name + " | ID: " \
			 + v.id + "} " + temp  + "]\n" + v.id + " -> {";

		for(unsigned int i =0; i< v.followersList.size(); i++)
		{
			dotFile_Str += v.followersList.at(i);
			if(i < v.followersList.size()-1)
			{
				dotFile_Str += ",";
			}
		}
		dotFile_Str += "}\n";
	}
	dotFile_Str += "}";


	ofstream image("Graph.dot");
	image<<dotFile_Str;
	image.close();

	system("dot -Tbmp -O Graph.dot");
	rename("Graph.dot.bmp","Graph.bmp");
	system("Graph.bmp");
}

