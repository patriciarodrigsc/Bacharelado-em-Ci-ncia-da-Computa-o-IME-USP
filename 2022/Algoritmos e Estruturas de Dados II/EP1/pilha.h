#ifndef PILHA_H
#define PILHA_H

template <class Item> 
class Pilha
{
    private:
        Item * v;
        int topo;
        int tam;
        void resize(int tam);

    public: 
        Pilha();
        ~Pilha();
        void push(Item item);
        bool isEmpty();
        int size();
        Item pop();
        Item top();
};

template <class Item>
Pilha<Item>::Pilha(): topo(0), tam(1), v(new Item[1]) {};

template <class Item>
Pilha<Item>::~Pilha() {
  if (v != nullptr)
    delete [] v;
}

template <class Item> 
void Pilha<Item>::push (Item item) 
{
  if (tam == topo)
    resize(2 * tam);
    v[topo] = item;
    topo++;
}

template <class Item>
Item Pilha<Item>::pop()
{
    int eTopo;
    eTopo = v[topo-1];
    delete(v[topo-1]);
    topo--;
    return eTopo;
}

template <class Item>
Item Pilha<Item>::top()
{
    return(v[topo-1]);
}

template <class Item>
bool Pilha<Item>::isEmpty()
{
    if(topo == 0)
        return true;
    else
        return false;
}

//template <class Item>
//int Pilha<Item>::size(Item item)
//{
//    return(int(topo));
//}

template <class Item>
void Pilha<Item>::resize(int t) {
  Item * novoV = new Item[t];
  for (int i = 0; i < tam; i++)
    novoV[i] = v[i];
  delete [] v;
  v = novoV;
  tam = t;
}

#endif