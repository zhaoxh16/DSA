#include <cstdio>
#include <cstdlib>
#include <ctime>
int x[200100];
int y[200100];
char buffer[200100 * 100+ 1000];
char* bufferChar = buffer - 1;

int readInt() {
	char myChar = *(++bufferChar);
	while (myChar<'0' || myChar>'9') {
		myChar = *(++bufferChar);
	}
	int myInt = 0;
	while (myChar >= '0'&&myChar <= '9') {
		myInt *= 10;
		myInt += myChar - '0';
		myChar = *(++bufferChar);
	}
	return myInt;
}

void sort(int *a, int low, int high) {//¥”lowµΩhigh-1≈≈–Ú
	if (low >= high - 1)
		return;
	int p = low;
	int q = high - 1;
	int number = rand() % (high - low) + low;
	int key = a[number];
	//swap a[start],a[p], get key
	a[number] = a[low];
	a[low] = key;
	//≈≈–Ú
	while (p < q) {
		while (p < q&& a[q] >= key) {
			--q;
		}a[p] = a[q];
		while (p < q&& a[p] <= key) {
			++p;
		}a[q] = a[p];
	}
	a[p] = key;
	sort(a, low, p);
	sort(a, p + 1, high);
}
char output[100 * 200100];
char temp[200];
char* outputChar = output;

void doOutput(int myOutput) {
	if (myOutput == 0) {
		*outputChar = '0';
		++outputChar;
	}
	else {
		char* tempChar = temp;
		while (myOutput != 0) {
			*tempChar = '0' + myOutput % 10;
			++tempChar;
			myOutput /= 10;
		}
		while (tempChar != temp) {
			*outputChar = *(--tempChar);
			++outputChar;
		}
	}
	*outputChar = '\n';
	++outputChar;
}

int main() {
	srand(unsigned(time(0)));
	fread(buffer, 1, 200000 * 100 + 1000, stdin);
	int n;
	n = readInt();
	for (int i = 0; i < n; i++) {//O(n)
		//scanf("%d", &x[i]);
		x[i] = readInt();
	}for (int i = 0; i < n; i++) {//O(n)
		//scanf("%d", &y[i]);
		y[i] = readInt();
	}
	int m = readInt();
	sort(x, 0, n);//O(nlogn)
	sort(y, 0, n);//O(nlogn)
	//test
	int px;
	int py;
	for (int i = 0; i < m; i++) {
		//scanf("%d", &px);
		px = readInt();
		//scanf("%d", &py);
		py = readInt();
		int low = 0;
		int high = n;
		while (low < high - 1) {
			int middle = (low + high) / 2;
			if ((long long)(px - x[middle])*y[middle] + (long long)py*x[middle] >= 0) {
				low = middle;
			}
			else {
				high = middle;
			}
		}
		if((long long)(px-x[0])*y[0]+(long long)py*x[0] >= 0)
			++low;
		doOutput(low);
	}
	fwrite(output, 1, outputChar - output, stdout);
	return 0;
}