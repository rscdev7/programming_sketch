#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

template <class T> class Nodo {
	private:
		T* key;
		Nodo<T>* next;
	public:
		Nodo (T* key,Nodo<T>* next=NULL) {
			this->key=NULL;
			if (key) this->key=key;
			this->next=next;
		}
		T* getKey () {
			return key;
		}
		Nodo<T>* getNext () {
			return next;
		}
		void setKey (T* key) {
			this->key=key;
		}
		void setNext (Nodo<T>* next) {
			this->next=next;
		}
};

template <class T> class Listasl {
	private:
		Nodo<T>* header;
		Nodo<T>* trailer;
		Nodo<T>* current;
		int n;
		Nodo<T>* _search (T x) {
			Nodo<T>* s=header->getNext();
			while (s!=trailer) {
				if (x==*s->getKey()) return s;
				s=s->getNext();
			}
			return NULL;
		}
	public:
		Listasl () {
			n=0;
			trailer=new Nodo<T> (NULL);
			header=new Nodo<T> (NULL,trailer);
			current=trailer;
		}
		Listasl<T>* ins (T x) {
			Nodo<T>* p=header;
			Nodo<T>* t=header->getNext();
			while (t!=trailer && x>*t->getKey()) {
				p=t;
				t=t->getNext();
			}
			Nodo<T>* nd=new Nodo<T> (new T(x),t);
			p->setNext(nd);
			n++;
			return this;
		}
		Listasl<T>* canc (T x) {
			Nodo<T>* c=_search (x);
			if (c) {
				n--;
				Nodo<T>* p=header;
				Nodo<T>* t=header->getNext();
				while (t!=trailer && *c->getKey()!=*t->getKey()) {
					p=t;
					t=t->getNext();
				}
				p->setNext (c->getNext());
			}
			return this;
		}
		int search (T x) {
			return (_search (x)!=NULL);
		}
		void print () {
			Nodo<T>* h=header->getNext();
			while (h!=trailer) {
				cout<<*h->getKey()<<"-";
				h=h->getNext();
			}
			cout<<endl;
		}
		T* begin () {
			current=header->getNext ();
			if (current!=trailer) return current->getKey();
			return NULL;
		}
		int hasNext () {
			return (current!=trailer && current->getNext()!=trailer);
		}
		T* next () {
			if (hasNext()) {
				current=current->getNext ();
				return current->getKey();
			}
			return NULL;
		}
};

int main () {
	Listasl<int>* a=new Listasl<int> ();
	a->ins(40)->ins(30)->ins(90)->ins(20)->print();
	a->canc (40)->canc(140)->print();
	cout<<a->search (40)<<endl;
	cout<<a->search (30)<<endl;
	int* i=a->begin();
	while (i!=NULL) {
		cout<<*i<<" - ";
		i=a->next();
	}
	cout<<endl;
}