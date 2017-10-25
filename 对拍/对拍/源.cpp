#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>
#define random(a,b) ((a)+rand()%((b)-(a)+1))
using namespace std;
stringstream ss;
int main(int argc, char* argv[]) {
	printf("500\n");
	int seed = time(NULL);
	if (argc)//如果有参数
	{
		ss.clear();
		ss << argv[1];
		ss >> seed;//把参数转换成整数赋值给seed
	}
	srand(seed);
	for (int i = 0; i < 1000; i++) {
		int m = random(1, 10);
		for (int j = 0; j < m; j++) {
			int c = random(0, 9);
			if (j == 0)
				c = random(1, 9);
			printf("%d", c);
		}
		printf("\n");
	}
	return 0;
}