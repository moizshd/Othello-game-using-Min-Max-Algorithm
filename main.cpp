#include <iostream>
#include<queue>
using namespace std;
class OthelloBoard {
public:
	int board[8][8];
	int countofone,countoftwo;
	OthelloBoard()
	{ 
		for (int i = 0; i < 8; i++)
	    {
	      for (int j = 0; j < 8; j++)
	      {
			   board[i][j]=0;
		  }
		}
		board[3][3] = 1;
		board[3][4] = 2;
		board[4][3] = 2;
		board[4][4] = 1;
		countofone = 2;
		countoftwo = 2;
	}
	void printboard()
	{
		int c = 1;
		cout << "                  ";
		cout << "    1   2   3   4   5   6   7   8" << endl<<endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "                  ";
			cout << c <<"   ";
			for (int j = 0; j < 8; j++)
			{
				cout << board[i][j] << "   ";
			}
			cout << endl<<endl;
			c++;
		}
	}
	bool checklinematch(int dr,int dc,int i,int j)
	{
		if (board[i][j] == 1)
		{
			return true;
		}
		if (board[i][j] == 0)
		{
			return false;
		}
		if ((dr + i < 0) || (dr + i > 7))
		{
			return false;
		}
		if ((dc + j < 0) || (dc + j > 7))
		{
			return false;
		}
		return checklinematch(dr, dc, i + dr, j + dc);
	}
	bool checkgameover()
	{
		bool flag;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 0)
				{
					return false;
				}
				else
					flag = 1;
			}
		}
		if (flag == 1)
		{
			return true;;
		}
	}
	void points()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 2)
				{
					countoftwo++;
				}
				if (board[i][j] == 1)
				{
					countofone++;
				}

			}
		}
	}
	bool checkdirection(int dr,int dc,int i, int j)
	{
		if ((dr + i < 0) || dr + i > 7)
		{
			return false;
		}
		if ((dc + j < 0) || dc + j > 7)
		{
			return false;
		}
		if (board[i+dr][j+dc] != 2)
		{
			return false;
		}
		if ((dr +dr + i < 0) || (dr+dr + i > 7))
		{
			return false;
		}
		if ((dc +dc+ j < 0) || (dc+dc + j > 7))
		{
			return false;
		}
		else return checklinematch(dr,dc,i+dr+dr,j+dc+dc);
	}
	bool input()
	{
		int i, j;
		cout << "Input Board rowno x colno\n";
		cin >> i;
		i = i - 1;
		cin >> j;
		j = j - 1;
		bool n, s, e, w, ne, nw, se, sw;
		if (board[i][j] == 0)
		{
			n = checkdirection(-1,0,i, j);
			s = checkdirection(1,0,i, j);
			e = checkdirection(0,1,i, j);
			w = checkdirection(0,-1,i, j);
			ne = checkdirection(-1,1,i, j);
			nw = checkdirection(-1,-1,i, j );
			se = checkdirection(1,1,i , j );
			sw = checkdirection(1,-1,i, j );
			if (n || e || s || w || ne || nw || se || sw)
			{
				board[i][j] = 1;
				fliptokens(i, j,1);
				return true;
			}
			else {
				cout << "Invalid Move \n";
				return false;
			}
		}
		else {
			cout << "Invalid Move \n";
			return false;
		}
	}
	bool flip(int dr,int dc,int i,int j,int opp)
	{
		if (board[i + dr][j + dc] == opp)
		{
			return true;
		}
		if ((dr + i < 0) || (dr + i > 7))
		{
			return false;
		}
		if ((dc + j < 0) || (dc + j > 7))
		{
			return false;
		}
		if (board[i + dr][j + dc] == 0)
		{
			return false;
		}
		else {
			if (flip(dr, dc, i + dr, j + dc,opp))
			{
				board[i + dr][j + dc] = opp;
			}
			else {
				return false;
			}
		}
	}
	void fliptokens(int i, int j,int opp)
	{
			flip(-1, 0, i, j,opp);
			flip(1, 0, i, j,opp);
			flip(0, 1, i, j,opp);
			flip(0, -1, i, j,opp);
			flip(-1, 1, i, j,opp);
			flip(-1, -1, i, j,opp);
			flip(1, 1, i, j,opp);
			flip(1, -1, i, j,opp);
	}
	
};
int heuristic(OthelloBoard *obj)
{
	int noOfBlack=0;
	int noOfWhite = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (obj->board[i][j] == 2)
			{
				noOfBlack = noOfBlack+1;
			}
		}
		for (int j = 0; j < 8; j++)
		{
			if (obj->board[i][j] == 1)
			{
				noOfWhite = noOfWhite + 1;
			}
		}
	}
	return (noOfBlack-noOfWhite);
}
bool checklinematch(int dr, int dc, int i, int j,OthelloBoard obj,int player)
{
	if (obj.board[i][j] == player)
	{
		return true;
	}
	if (obj.board[i][j] == 0)
	{
		return false;
	}
	if ((dr + i < 0) || (dr + i > 7))
	{
		return false;
	}
	if ((dc + j < 0) || (dc + j > 7))
	{
		return false;
	}
	return checklinematch(dr, dc, i + dr, j + dc,obj,player);
}
bool checkdirection(int dr, int dc, int i, int j,OthelloBoard obj,int player)
{
	int opp = 0;
	if (player == 1)
		opp = 2;
	else
		opp = 1;
	if ((dr + i < 0) || (dr + i > 7))
	{
		return false;
	}
	if ((dc + j < 0) || (dc + j > 7))
	{
		return false;
	}
	if (obj.board[i + dr][j + dc] != opp)
	{
		return false;
	}
	if ((dr + dr + i < 0) || (dr + dr + i > 7))
	{
		return false;
	}
	if ((dc + dc + j < 0) || (dc + dc + j > 7))
	{
		return false;
	}
	else return checklinematch(dr, dc, i + dr + dr, j + dc + dc,obj,player);
}
queue<OthelloBoard> generatemoves(OthelloBoard obj,int player)
{
	queue<OthelloBoard> queueofobjects;
	bool n, s, e, w, ne, nw, se, sw;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (obj.board[i][j] == 0)
			{
				n = checkdirection(-1, 0, i, j,obj,player);
				s = checkdirection(1, 0, i, j,obj, player);
				e = checkdirection(0, 1, i, j,obj, player);
				w = checkdirection(0, -1, i, j,obj, player);
				ne = checkdirection(-1, 1, i, j,obj, player);
				nw = checkdirection(-1, -1, i, j,obj, player);
				se = checkdirection(1, 1, i, j,obj, player);
				sw = checkdirection(1, -1, i, j,obj, player);
				if (n || s || e || w || ne || nw || se || sw)
				{
					OthelloBoard obj2;
					obj2 = obj;
					obj2.board[i][j] = player;
					obj2.fliptokens(i,j,player);
					queueofobjects.push(obj2);
				}
			}

		}
	}
	return queueofobjects;
}
struct node {
	OthelloBoard obj;
	int value;
	node* branch[30];
	node* parent;
	node()
	{
		for (int i = 0; i < 30; i++)
		{
			branch[i] = nullptr;
		}
	}
	~node()
	{
	
	}
};
class tree {
public: node *root;
	tree()
	{
		root = new node;
		for (int i = 0; i < 30; i++)
		{
			root->branch[i] = nullptr;
		}
		root->parent = nullptr;
		root->value = heuristic(&root->obj);
	}
	node* returnmax(node*& root)
	{
		node* result=nullptr;
		int max = -999;
		for (int i = 0; root->branch[i] != nullptr; i++)
		{
			if (root->branch[i]->value > max)
			{
				max = root->branch[i]->value;
				result = root->branch[i];
			}
		}
		root->value = max;
		return result;
	}
	int returnmin(node*& root)
	{
		int min = 999;
		for (int i = 0; root->branch[i] != nullptr; i++)
		{
			if (root->branch[i]->value < min)
			{
				min = root->branch[i]->value;
			}
		}
		root->value = min;
		return min;
	}
	void insert(node*& root, OthelloBoard obj, node* parent)
	{
		root = new node;
		root->obj = obj;
		root->value = heuristic(&root->obj);
		root->parent = parent;
	}
	int Minmax(node*& root, OthelloBoard obj,int player) 
	{
		root->obj = obj;
		OthelloBoard obj1;
		queue<OthelloBoard> obj2;
		obj2 = generatemoves(obj,player);
		int i = 0;
		while (!obj2.empty())
		{
			obj1 = obj2.front();
			insert(root->branch[i], obj1, root);
			obj2.pop();
			i++;
		}
		return i;
	}
	void makenull(node*& root)
	{
		for (int i = 0; root->branch[i] = nullptr; i++)
		{
			root->branch[i] = nullptr;
		}
	}
};
class solver {
public:
	tree* treeobj;
	solver()
	{
		treeobj = new tree;
	}
	OthelloBoard maketree(OthelloBoard obj) // generating tree and calculating min max
	{
		int i=0;
		treeobj->Minmax(treeobj->root, obj, 2);
		int j;
		for (i = 0; treeobj->root->branch[i] != nullptr; i++)
		{
			treeobj->Minmax(treeobj->root->branch[i], treeobj->root->branch[i]->obj, 1);
			for (j = 0; treeobj->root->branch[i]->branch[j] != nullptr; j++)
			{
				treeobj->Minmax(treeobj->root->branch[i]->branch[j], treeobj->root->branch[i]->branch[j]->obj, 2);
				treeobj->returnmax(treeobj->root->branch[i]->branch[j]);
			}
			treeobj->returnmin(treeobj->root->branch[i]);
		}
		node* nextmove = treeobj->returnmax(treeobj->root);
		return nextmove->obj;
	}
	void maketreenull()
	{
		int j;
		for (int i = 0; treeobj->root->branch[i] != nullptr; i++)
		{
			for (j = 0; treeobj->root->branch[i]->branch[j] != nullptr; j++)
			{
				treeobj->makenull(treeobj->root->branch[i]->branch[j]);
			}
			treeobj->makenull(treeobj->root->branch[i]);
		}
		treeobj->makenull(treeobj->root);
	}
	~solver()
	{
		int j;
		for (int i = 0; treeobj->root->branch[i] != nullptr; i++)
		{
			for (j = 0; treeobj->root->branch[i]->branch[j] != nullptr; j++)
			{
				treeobj->makenull(treeobj->root->branch[i]->branch[j]);
			}
			treeobj->makenull(treeobj->root->branch[i]);
		}
		treeobj->makenull(treeobj->root);
	}
};
int main()
{
	OthelloBoard obj;
	obj.printboard();
	int x = 0;
	while (x != 9) {
		if (obj.input())
		{
			obj.printboard();
			if (obj.checkgameover())
			{
				obj.points();
				cout << endl << "The score of 1 is " << obj.countofone << endl << "The score of 2 is " << obj.countoftwo;
				return 0;
			}
			solver obj1;
			obj = obj1.maketree(obj);
			obj1.maketreenull();
			obj.printboard();
			if (obj.checkgameover())
			{
				obj.points();
				cout << endl << "The score of 1 is " << obj.countofone << endl << "The score of 2 is " << obj.countoftwo;
				return 0;
			}
		}
		else
		{
			cout << endl << "Try again with a valid move ";
		}
	}
}