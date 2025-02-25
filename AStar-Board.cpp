
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <fstream>
#include <unordered_set>

using namespace std;

class state {
public:
	string* board;
	int heu;
	int size;
	int noLetts;
	int cost;
	string path;

	state(string* str, int n) {
		board = new string[n];
		noLetts = 0;
		for (int i = 0; i < n; i++) {
			board[i] = str[i];
			for (int j = 0; j < n; j++) {
				if (str[i][j] != '-')
					noLetts++;
			}
		}

		size = n;
		cost = 0;
		path = " ";
		heu = 0;

	}

	state(const state& obj) {
		
		heu = obj.heu;
		size = obj.size;
		noLetts = obj.noLetts;
		cost = obj.cost;
		path = obj.path;

		board = new string[size];

		for (int i = 0; i < size; i++) {
			board[i] = obj.board[i];
		}

	}

	state() {

	}

	~state() {
		delete[]board;
	}

	state& operator=(const state& obj) {
		if (this == &obj)
			return *this;


		delete[] board;

		heu = obj.heu;
		size = obj.size;
		noLetts = obj.noLetts;
		cost = obj.cost;
		path = obj.path;

		board = new string[size];

		for (int i = 0; i < size; i++) {
			board[i] = obj.board[i];	
		}

		return *this;
	}

	bool operator<(const state& obj) const {
		return heu + cost < obj.heu + obj.cost;
	}

	bool operator==(const state& obj) const {
		
		for(int i = 0 ; i < size; i++)
			if (obj.board[i] != board[i])
					return false;
			
		return true;
	}

	void display() {
		cout << "path : " << path << " cost : " << cost  << " heu : " << heu << endl;
	}
};


string* createBoard(int n, ifstream& file) {
	string* temp = new string[n];
	for (int i = 0; i < n; i++)
		file >> temp[i];

	return temp;
}


struct goalCoords {
	int x;
	int y;
};

goalCoords* getCoords(state& a) {

	goalCoords* temp = new goalCoords[a.noLetts];
	int k = 0;
	for (int i = 0; i < a.size; i++)
		for (int j = 0; j < a.size; j++) {
			if (a.board[i][j] >= 'a' && a.board[i][j] <= 'z') {
				temp[k].x = i;
				temp[k].y = j;
				k++;
			}
		}
	return temp;
}

int calHeu(goalCoords* a, state m) {
	int heur = 0;
	int k = 0;
	for (int i = 0; i < m.size; i++) {
		for (int j = 0; j < m.size; j++) {
			if (m.board[i][j] != '-') {
				heur += (abs(a[k].x - i) + abs(a[k].y - j));
				k++;
			}
		}
	}

	return heur;
}

bool isGoal(state a, state b) {

	for (int i = 0; i < a.size; i++) {
		if (a.board[i] != b.board[i]) {
				return false;
		}
		
	}

	return true;
}

vector<state>* expand(state s, state goal) {
	vector<state>* temp = new vector<state>;
	state t;
	int k = 0;
	for (int i = 0; i < s.size; i++) {
		bool flag = 0;
		for (int j = 0; j < s.size; j++) {
			if (s.board[i][j] != '-') {
				if (j - 1 >= 0 && s.board[i][j - 1] == '-') {
					t = s;
					swap(t.board[i][j], t.board[i][j - 1]);
					
					t.path += s.board[i][j];
					t.path += " left\n";
					t.cost += 1;
					t.heu = calHeu(getCoords(s), goal);
					temp->push_back(t);
					
				}
				if (j + 1 < s.size && s.board[i][j + 1] == '-') {
					
					t = s;
					swap(t.board[i][j], t.board[i][j + 1]);
					t.path += s.board[i][j];
					t.path += " right\n";
					t.cost += 1;
					t.heu = calHeu(getCoords(s), goal);
					temp->push_back(t);
					

				}
				if (i - 1 >= 0 && s.board[i - 1][j] == '-') {
					
					t = s;
					swap(t.board[i][j], t.board[i - 1][j]);
					t.path += s.board[i][j];
					t.path += " up\n";
					t.cost += 1;
					t.heu = calHeu(getCoords(s), goal);
					temp->push_back(t);
					
				}
				if (i + 1 < s.size && s.board[i + 1][j] == '-') {
					
					t = s;
					swap(t.board[i][j], t.board[i + 1][j]);
					t.path += s.board[i][j];
					t.path += " down\n";
					t.cost += 1;
					t.heu = calHeu(getCoords(s), goal);
					temp->push_back(t);
					
				}

			}
		}

	}

	
	return temp;
}


int vFind(vector<state> b, state a) {
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == a)
			return i;
	}

	return -1;
}

bool pFind( priority_queue<state> b, state a) {
	while (!b.empty()) {

		if (b.top() == a)
			return true;
		b.pop();
	}

	return false;
}

state top(vector<state> a) {
	int min = a[0].cost + a[0].heu;
	int loc = 0;
	for (int i = 1; i < a.size(); i++) {
		if (a[i].cost + a[i].heu < min) {
			min = a[i].cost + a[i].heu;
			loc = i;
		}
	}

	return a[loc];
}

void Remove(vector<state>& a, state b) {
	
	int i;
	for (i = 0; i < a.size(); i++) {
		if (a[i] == b) {
			break;
		}
	}

	for (; i < a.size() - 1; i++) {
		a[i] = a[i + 1];
	}
	a.pop_back();
}


state find(vector<state> a, state b) {
	
	for (int i = 1; i < a.size(); i++) {
		if (a[i] == b) {
			return a[i];
		}
	}

	exit(0);
}

int main()
{
	ifstream myFile("Text.txt");
	int n;

	myFile >> n;

	state init(createBoard(n,myFile), n);
	state goal(createBoard(n,myFile), n);

	init.heu = calHeu(getCoords(goal), init);

	//priority_queue<state> open;
	vector<state> open;
	open.push_back(init);

	//unordered_set<state> closed;
	vector<state> closed;


	state N;
	vector<state>* e;

	int sum = 0;

	while (!open.empty()) {
		N = top(open);
		Remove(open, N);
		closed.push_back(N);

		if (isGoal(N, goal)) {
			N.display();
			cout << "No. of states expanded : " << sum;
			return 0;
		}

		e = expand(N, goal);
		sum += e->size();

		

		
		for (int i = 0; i < e->size(); i++) {
			
			int c = vFind(closed, e->at(i));
			int o = vFind(open, e->at(i));
			
			if (c < 0 && o < 0 ) {
				open.push_back(e->at(i));
			}
			else if( o >= 0 && e->at(i).cost + e->at(i).heu < open.at(o).cost ){
				Remove(open, open.at(o));
				open.push_back(e->at(i));
				
			}
			else if (c>= 0 && e->at(i).cost + e->at(i).heu < closed.at(c).cost ) {
				Remove(closed, closed.at(c));
				open.push_back(e->at(i));
				
			}

			
		}

	}


	return 0;


}
