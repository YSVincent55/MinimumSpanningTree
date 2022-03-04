#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Planet           // Struct for storing planet info
{
    string name;
    int x;
    int y;
    int z;
    int weight;
    int profit;
};

struct KruskalPlanet        //Struct to store edge of the planet
{
    int planet1;
    int planet2;
};

class PlanetMap             //Class to store the planet map
{
	public:
        PlanetMap(int node);
        void addEdge(int planetOne, int planetTwo, double weight);
        KruskalPlanet* kruskal();

    private:
        int *parent;
        int node;
        typedef pair<int, int> planetName;
        vector< pair<double, planetName> > edgePair;

        int findPlanet (int planet);
        void mergeSet(int set1, int set2);
};

PlanetMap:: PlanetMap(int node)
{
    this->node = node;

    parent = new int[node+1];
    for (int i = 0; i <= node; i++)
    {
        parent[i] = i;
    }
}

void PlanetMap::addEdge(int planetOne, int planetTwo, double weight)  //Add planet edge into a vector
{
    edgePair.push_back({weight, {planetOne, planetTwo}});
}

KruskalPlanet* PlanetMap::kruskal()         //Function to perform kruskal's algorithm
{
	sort(edgePair.begin(), edgePair.end());
	static KruskalPlanet kp[10];
	int i = 0;

	vector< pair<double, planetName> >::iterator a;

	for (a=edgePair.begin(); a!=edgePair.end(); a++)
	{
        double eWeight = a->first;
        int pOne = a->second.first;
        int pTwo = a->second.second;

        int set_pOne = findPlanet(pOne);
        int set_pTwo = findPlanet(pTwo);

        if (set_pOne != set_pTwo)
        {
            kp[i].planet1 = pOne;
            kp[i].planet2 = pTwo;
            cout << char(65+pOne) << " - " << char(65+pTwo) << "\t Weight = " << eWeight <<endl;
            mergeSet(set_pOne, set_pTwo);
            i++;
        }
	}

	return kp;
}

int PlanetMap::findPlanet(int planet)           //Find the parent of the planet
{
    if (planet != parent[planet])
        parent[planet] = findPlanet(parent[planet]);
    return parent[planet];
}

void PlanetMap::mergeSet(int set1, int set2)    //Merge two set into one set
{
    parent[set1] = parent[set2];
}

double getWeight(Planet one, Planet two)    //Calculate the weight of the edges
{
    double weight;

    weight = sqrt(pow((two.x - one.x),2) + pow((two.y - one.y),2) + pow((two.z - one.z),2));

    return weight;
}

void initmap(char g[7][13])                 //Initialize the graph map
{
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<13; j++)
        {
            g[i][j] = ' ';
        }
    }

    g[0][6] = 'A';
    g[4][0] = 'B';
    g[4][12] = 'C';
    g[2][0] = 'D';
    g[6][6] = 'E';
    g[2][12] = 'F';
    g[4][3] = 'G';
    g[2][9] = 'H';
    g[4][9] = 'I';
    g[2][3] = 'J';
}

void displayGraph(char g[7][13])        //Display the graph
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<13; j++)
           cout << g[i][j];
        cout << endl;
    }
}

void connect(char g[7][13], int a, int b)   //Connect the edges of the graph
{
    switch (a) {
    case 0:     // A
        if (b == 3)     // connect to D
        {
            g[0][0] = '+';
            g[0][1] = '-';
            g[0][2] = '-';
            g[0][3] = '+';
            g[0][4] = '-';
            g[0][5] = '-';
            g[1][0] = '|';
        }
        if (b == 5)     // connect to F
        {
            g[0][12] = '+';
            g[0][11] = '-';
            g[0][10] = '-';
            g[0][9] = '+';
            g[0][8] = '-';
            g[0][7] = '-';
            g[1][12] = '|';
        }
        if (b == 9)     // connect to J
        {
            g[0][3] = '+';
            g[0][4] = '-';
            g[0][5] = '-';
            g[1][3] = '|';
        }
        if (b == 7)      // connect to H
        {
            g[0][9] = '+';
            g[0][8] = '-';
            g[0][7] = '-';
            g[1][9] = '|';
        }
        break;
    case 1:     // B
        if (b == 3)     // connect to B
        {
            g[3][0] = '|';
        }
        if (b == 4)     // connect to E
        {
            g[6][0] = '+';
            g[6][1] = '-';
            g[6][2] = '-';
            g[6][3] = '+';
            g[6][4] = '-';
            g[6][5] = '-';
            g[5][0] = '|';
        }
        if (b == 6)     // connect to G
        {
            g[4][1] = '-';
            g[4][2] = '-';
        }
        break;
    case 2:     // C
        if (b == 4)     // connect to E
        {
            g[6][12] = '+';
            g[6][11] = '-';
            g[6][10] = '-';
            g[6][9] = '+';
            g[6][8] = '-';
            g[6][7] = '-';
            g[5][12] = '|';
        }
        if (b == 5)     // connect to F
        {
            g[3][12] = '|';
        }
        if (b == 8)     // connect to C
        {
            g[4][10] = '-';
            g[4][11] = '-';
        }
        break;
    case 3:     // D
        if (b == 9)     // connect to J
        {
            g[2][1] = '-';
            g[2][2] = '-';
        }
        break;
    case 5:     // F
        if (b == 7)     // connect to H
        {
            g[2][10] = '-';
            g[2][11] = '-';
        }
        break;
    case 6:     // G
        if (b == 4)     // connect to E
        {
            g[6][3] = '+';
            g[6][4] = '-';
            g[6][5] = '-';
            g[5][3] = '|';
        }
        if (b == 8)     // connect to I
        {
            g[4][4] = '-';
            g[4][5] = '-';
            g[4][6] = '-';
            g[4][7] = '-';
            g[4][8] = '-';
        }
        break;
    case 7:     // H
        if (b == 8)     // connect to I
        {
            g[3][9] = '|';
        }
        if (b == 9)     // connect to J
        {
            g[2][4] = '-';
            g[2][5] = '-';
            g[2][6] = '-';
            g[2][7] = '-';
            g[2][8] = '-';
        }
        break;
    case 8:     //I
        if (b == 4)     // connect to E
        {
            g[6][9] = '+';
            g[6][8] = '-';
            g[6][7] = '-';
            g[5][9] = '|';
        }
        break;
    case 9:     // J
        if (b == 6)     // connect to G
        {
            g[3][3] = '|';
        }
    }

}

int main()
{
    const int planetNum = 10;
    Planet planetList[planetNum];
    string tempName;
    int tempX, tempY, tempZ, tempWeight, tempProfit, edge, tempP1, tempP2;
    KruskalPlanet *kp;
    KruskalPlanet ep[100];
    fstream planetFile;
    fstream edgeFile;
	PlanetMap map(10);

	char graph[7][13];
	char graphAfter[7][13];

	initmap(graph);
	initmap(graphAfter);

    planetFile.open("generated-data/A2planets.txt", ios::in);
    edgeFile.open("generated-data/planet-edges.txt", ios::in);

    if(planetFile)                      //Load data from the file into an array of Planet class
    {
        for(int i=0; i<planetNum; i++)
        {
            Planet temp;
            planetFile >> tempName;
            temp.name = tempName;
            planetFile >> tempX;
            temp.x = tempX;
            planetFile >> tempY;
            temp.y = tempY;
            planetFile >> tempZ;
            temp.z = tempZ;
            planetFile >> tempWeight;
            temp.weight = tempWeight;
            planetFile >> tempProfit;
            temp.profit = tempProfit;

            planetList[i] = temp;
        }
        planetFile.close();
    }
    else
    {
        cout << "File not found" << endl;
    }

    if(edgeFile)                      //Load data from the file into an array of Planet class
    {
        edgeFile >> edge;

        for(int i=0; i<edge; i++)
        {
            KruskalPlanet tempEdge;

            edgeFile >> tempP1;
            tempEdge.planet1 = tempP1;

            edgeFile >> tempP2;
            tempEdge.planet2 = tempP2;

            ep[i] = tempEdge;
        }
        edgeFile.close();
    }
    else
    {
        cout << "File not found" << endl;
    }

    cout << "Before applying Kruskal Algorithm" << endl;
    cout << "Edges of Graph are: " << endl;

    for(int i=0; i<edge; i++)
    {
        map.addEdge(ep[i].planet1, ep[i].planet2, getWeight(planetList[ep[i].planet1], planetList[ep[i].planet2]));
        connect(graph, ep[i].planet1, ep[i].planet2);
        cout << char(65+ep[i].planet1) << " - " << char(65+ep[i].planet2) << "\t Weight = " << getWeight(planetList[ep[i].planet1], planetList[ep[i].planet2]) <<endl;
    }

    cout << "\n\nThe graph of the planet location: ";
    displayGraph(graph);

    cout << "\n\n------------------------------------------------------------------" << endl;
    cout << "After applying Kruskal Algorithm" << endl;
	cout << "Edges of Minimum Spanning Tree are: " << endl;
	kp = map.kruskal();

	for(int i=0; i<sizeof(kp)+1;i++)
    {
        connect(graphAfter, kp[i].planet1, kp[i].planet2);
    }

    cout << "\n\nGraph of the Minimum Spanning Tree: ";
    displayGraph(graphAfter);

	return 0;
}
