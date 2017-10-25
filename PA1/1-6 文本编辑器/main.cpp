#include <cstdio>
#include <cstdlib>
struct Node {
	char c;
	Node* previous;
	Node* next;
};
Node list[8000100];
int listPos = -1;
char buffer[4000000 + 6 * 4000000 + 1000];
int bufferPos = -1;
Node* l = NULL;
Node* r = NULL;
int lNum = 0;
int rNum = 0;
bool isRev = 0;
char output[30000000];
char* charPos = output - 1;
int main() {
	Node* header = list + 8000098;
	header->c = 0;
	header->previous = NULL;
	Node* tailer = list + 8000099;
	tailer->c = 0;
	tailer->previous = header;
	tailer->next = NULL;
	header->next = tailer;
	Node* nodeNow = header;
	fread(buffer, 1, 4000000 + 6 * 4000000 + 1000, stdin);
	//读入初始数据
	while (buffer[++bufferPos] != '\n') {
		nodeNow->next = list + (++listPos);
		nodeNow->next->previous = nodeNow;
		nodeNow = nodeNow->next;
		nodeNow->c = buffer[bufferPos];
	}
	nodeNow->next = tailer;
	tailer->previous = nodeNow;
	l = header->next;
	r = tailer;
	rNum = listPos + 1;
	//读入正整数
	char myChar = buffer[++bufferPos];
	int n = 0;
	while (myChar >= '0'&&myChar <= '9') {
		n *= 10;
		n += myChar - '0';
		myChar = buffer[++bufferPos];
	}
	//开始操作
	++bufferPos;
	Node* temp = NULL;
	for (int i = 0; i < n; i++) {
		myChar = buffer[bufferPos];
		if (myChar == '<') {
			bufferPos += 2;
			if (isRev) {
				if (buffer[bufferPos] == 'L') {
					if (l == header->next){
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						temp = l->previous;
						l->previous = temp->previous;
						l->previous->next = l;
						temp->previous = r->previous;
						temp->next = r;
						r->previous->next = temp;
						r->previous = temp;
						--lNum;
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
				else {
					temp = r;
					r = l;
					l = l->next;
					l->previous = r->previous;
					l->previous->next = l;
					r->previous = temp->previous;
					r->next = temp;
					temp->previous->next = r;
					temp->previous = r;
					--rNum;
					*(++charPos) = 'T';
					*(++charPos) = '\n';
					if (l == r->previous)
						isRev = 0;
				}
			}
			else {
				if (buffer[bufferPos] == 'L') {
					if (l == header->next) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						l = l->previous;
						--lNum;
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
				else {
					if (r == header->next) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						r = r->previous;
						--rNum;
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
			}
		}
		else if (myChar == '>') {
			bufferPos += 2;
			if (isRev) {
				if (buffer[bufferPos] == 'L') {
					temp = r->previous;
					r->previous = temp->previous;
					r->previous->next = r;
					temp->previous = l->previous;
					temp->next = l;
					l->previous->next = temp;
					l->previous = temp;
					++lNum;
					*(++charPos) = 'T';
					*(++charPos) = '\n';
					if (l == r->previous)
						isRev = 0;
				}
				else {
					if (r == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						temp = l;
						l = r;
						r = r->next;
						r->previous = l->previous;
						l->previous->next = r;
						l->previous = temp->previous;
						l->next = temp;
						temp->previous->next = l;
						temp->previous = l;
						++rNum;
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
			}
			else {
				if (buffer[bufferPos] == 'L') {
					if (l == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						l = l->next;
						++lNum; 
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
				else {
					if (r == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						r = r->next;
						++rNum;
						*(++charPos) = 'T';
						*(++charPos) = '\n';
					}
				}
			}
		}
		else if (myChar == 'I') {
			*(++charPos) = 'T';
			*(++charPos) = '\n';
			bufferPos += 2;
			if (isRev) {
				if (buffer[bufferPos] == 'L') {
					temp = list + (++listPos);
					l->previous->next = temp;
					temp->previous = l->previous;
					temp->next = l;
					l->previous = temp;
					bufferPos += 2;
					temp->c = buffer[bufferPos];
				}
				else {
					temp = list + (++listPos);
					bufferPos += 2;
					temp->c = buffer[bufferPos];
					temp->previous = l->previous;
					temp->next = l;
					l->previous = temp;
					temp->previous->next = temp;
					l = temp;
					++rNum;
				}
			}
			else {
				if (buffer[bufferPos] == 'L') {
					temp = list + (++listPos);
					l->previous->next = temp;
					temp->previous = l->previous;
					temp->next = l;
					l->previous = temp;
					bufferPos += 2;
					temp->c = buffer[bufferPos];
					if (lNum > rNum)
						++lNum;
				}
				else {
					temp = list + (++listPos);
					r->previous->next = temp;
					temp->previous = r->previous;
					temp->next = r;
					r->previous = temp;
					bufferPos += 2;
					temp->c = buffer[bufferPos];
					if (lNum < rNum)
						++rNum;
				}
			}
		}
		else if (myChar == 'D') {
			bufferPos += 2;
			if (isRev) {
				if (buffer[bufferPos] == 'L') {
					*(++charPos) = 'T';
					*(++charPos) = '\n';
					r->previous = r->previous->previous;
					r->previous->next = r;
					--rNum;
					if (l == r->previous)
						isRev = 0;
				}
				else {
					if (r == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						*(++charPos) = 'T';
						*(++charPos) = '\n';
						r = r->next;
						r->previous = r->previous->previous;
						r->previous->next = r;
					}
				}
			}
			else {
				if (buffer[bufferPos] == 'L') {
					if (l == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						*(++charPos) = 'T';
						*(++charPos) = '\n';
						if (l == r)
							r = r->next;
						l = l->next;
						temp = l->previous->previous;
						temp->next = l;
						l->previous = temp;
						if (lNum < rNum)
							++lNum;
					}
				}
				else {
					if (r == tailer) {
						*(++charPos) = 'F';
						*(++charPos) = '\n';
					}
					else {
						*(++charPos) = 'T';
						*(++charPos) = '\n';
						if (r == l)
							l = l->next;
						r = r->next;
						temp = r->previous->previous;
						temp->next = r;
						r->previous = temp;
						if (rNum < lNum)
							++rNum;
					}
				}
			}

		}
		else if (myChar == 'R') {
			if (lNum >= rNum) {
				*(++charPos) = 'F';
				*(++charPos) = '\n';
			}
			else {
				*(++charPos) = 'T';
				*(++charPos) = '\n';
				if(l!=r->previous)
					isRev = !isRev;
			}
		}
		else{
			if (isRev) {
				Node* i = l;
				Node* j = r->previous;
				while (i != j&&j != i->previous) {
					char c = i->c;
					i->c = j->c;
					j->c = c;
					i = i->next;
					j = j->previous;
				}
				isRev = 0;
			}
			temp = header->next;
			while (temp != tailer) {
				*(++charPos) = temp->c;
				temp = temp->next;
			}
			*(++charPos) = '\n';
		}
		bufferPos += 2;
	}
	fwrite(output, 1, charPos-output+1, stdout);
	return 0;
}