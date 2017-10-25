#include <iostream>
#include <list>
#include <string>
using namespace std;
list<char> myList;
int length = 0;
int main() {
	string a;
	cin >> a;
	for (int i = 0; i < a.length(); i++) {
		myList.push_back(a[i]);
	}
	list<char>::iterator l = myList.begin();
	list<char>::iterator ll = myList.begin();
	list<char>::iterator r = myList.end(); 
	list<char>::iterator rr = myList.end();
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		char x1;
		cin >> x1;
		if (x1 == '<') {
			char x2;
			cin >> x2;
			if (x2 == 'L') {
				if (l == myList.begin())
					cout << 'F' << endl;
				else {
					--l;
					cout << 'T' << endl;
				}
			}
			else if (x2 == 'R') {
				if (r == myList.begin())
					cout << 'F' << endl;
				else {
					--r;
					cout << 'T' << endl;
				}
			}
		}
		else if (x1 == '>') {
			char x2;
			cin >> x2;
			if (x2 == 'L') {
				if (l == myList.end())
					cout << 'F' << endl;
				else {
					++l;
					cout << 'T' << endl;
				}
			}
			else if (x2 == 'R') {
				if (r == myList.end())
					cout << 'F' << endl;
				else {
					++r;
					cout << 'T' << endl;
				}
			}
		}
		else if (x1 == 'I') {
			cout << 'T' << endl;
			char x2, x3;
			cin >> x2 >> x3;
			if (x2 == 'L') {
				myList.insert(l, x3);
			}
			else if (x2 == 'R') {
				myList.insert(r, x3);
			}
		}
		else if (x1 == 'D') {
			char x2;
			cin >> x2;
			if (x2 == 'L') {
				if (l == myList.end())
					cout << 'F' << endl;
				else {
					if (l == r)
						r = l = myList.erase(l);
					else
						l = myList.erase(l);
					cout << 'T' << endl;
				}
			}
			else {
				if (r == myList.end())
					cout << 'F' << endl;
				else {
					if (l == r)
						l = r = myList.erase(r);
					else
						r = myList.erase(r);
					cout << 'T' << endl;
				}
			}
		}
		else if (x1 == 'R') {
			if (l == myList.end())
				cout << 'F' << endl;
			else if (r == myList.begin())
				cout << 'F' << endl;
			else {
				list<char>::iterator temp = l;
				++temp;
				bool flag = 0;
				while (temp != myList.end()) {
					if (temp == r) {
						flag = 1;
						break;
					}
					++temp;
				}
				if (temp == r)
					flag = 1;
				if (flag == 0)
					cout << 'F' << endl;
				else {
					cout << 'T' << endl;
					list<char>::iterator temp1 = l;
					list<char>::iterator temp2 = r;
					--temp2;
					while (temp1 != temp2 && ++temp2 != temp1) {
						--temp2;
						char c = *temp1;
						*temp1 = *temp2;
						*temp2 = c;
						++temp1;
						--temp2;
					}
				}
			}
		}
		else {
			for (list<char>::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
				cout << *iter;
			}
			cout << endl;
		}
	}

	return 0;
}