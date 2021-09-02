#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
template <class T> class Stack {
	private:
		T* v;
		int size;
		int pos;
		int len; 
	protected:
	public:	
		Stack () {
			len=10;
			v=new T (len);
			size=0;
			pos=-1;
		}
		Stack (int l) {
			len=l;
			v=new T (len);
			size=0;
			pos=-1;
		}
		Stack<T>* push (T x) {
			if (!isFull ()) {
				pos++;
				size++;
				v[pos]=x;
				return this;
			}else{
				return NULL;
			}
		}
		T* pop () {
			if (!isEmpty ()) {
				size--;
				pos--;
				return &v[pos+1];
			}else{
				return NULL;	
			}
		}
		int isEmpty () {
			return (size==0);
		}
		int isFull () {
			return (size==len);
		}
		void print () {
			for (int i=size-1;i>=0;i--) {
				cout<<v[i]<<" "<<endl;
			}
		}
		int get_Size () {
			return size;
		}
};
int main () {
} 
