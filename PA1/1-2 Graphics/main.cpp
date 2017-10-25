#include <cstdio>
#include <cstdlib>
#include <ctime>

int x[200100];//输入的横坐标
int y[200100];//输入的纵坐标
char buffer[200100 * 100+ 1000];//输入的数据
char* bufferChar = buffer - 1;//输入的数据的位置

//读取一个整数
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

//快速排序
void sort(int *a, int low, int high) {//从low到high-1排序
	if (low >= high - 1)
		return;
	int p = low;
	int q = high - 1;
	int number = rand() % (high - low) + low;
	int key = a[number];
	//swap a[start],a[p], get key
	a[number] = a[low];
	a[low] = key;
	//排序
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
	
	//读入数据
	for (int i = 0; i < n; i++) {//O(n)
		x[i] = readInt();
	}for (int i = 0; i < n; i++) {//O(n)
		y[i] = readInt();
	}
	int m = readInt();

	//对读入数据进行排序以便连线
	sort(x, 0, n);//O(nlogn)
	sort(y, 0, n);//O(nlogn)

	int px;
	int py;
	for (int i = 0; i < m; i++) {
		//读入待检测数据
		px = readInt();
		py = readInt();
		int low = 0;
		int high = n;
		//二分查找
		while (low < high - 1) {
			int middle = (low + high) / 2;
			//通过叉乘判断位置
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