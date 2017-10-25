#include <cstdio>
int readInt() {
	char myChar = getchar();
	while (myChar<'0' || myChar>'9') {
		myChar = getchar();
	}
	int myInt = 0;
	while (myChar >= '0'&&myChar <= '9') {
		myInt *= 10;
		myInt += myChar - '0';
		myChar = getchar();
	}
	return myInt;
}
int search(int* a, int number, int low, int high) {//lowµ½high-1
	while (low < high - 1) {
		int middle = (low + high) / 2;
		if (a[middle] > number) {
			high = middle;
		}
		else {
			low = middle;
		}
	}
	return low;
}
int main() {
	int n = readInt();

	return 0;
}