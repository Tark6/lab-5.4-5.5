#include <iostream>

using namespace std;

string FindSymbols(string& str)
{
    string SymbolsMentioned = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            if ((SymbolsMentioned.find(str[i]) == string::npos && SymbolsMentioned.find(char(int(str[i]) + 32)) == string::npos))
            {
                SymbolsMentioned += char(int(str[i]) + 32);
            }
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            if (SymbolsMentioned.find(str[i]) == string::npos && SymbolsMentioned.find(char(int(str[i]) - 32)))
            {
                SymbolsMentioned += str[i];
            }
        }
    }

    return SymbolsMentioned;
}

int* CountFrequency(string& str)
{
    string SymbolsMentioned = FindSymbols(str);

    int size = SymbolsMentioned.size();

    int* arr = new int[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }

    int index_find = 0;

    for (int i = 0; i < str.size(); i++)
    {
        while (SymbolsMentioned.find(str[i], index_find) != string::npos)
        {
            arr[SymbolsMentioned.find(str[i], index_find)]++;
            index_find = SymbolsMentioned.find(str[i], index_find) + 1;
        }

        index_find = 0;

        while (SymbolsMentioned.find(str[i] + 32, index_find) != string::npos)
        {
            arr[SymbolsMentioned.find(str[i] + 32, index_find)]++;
            index_find = SymbolsMentioned.find(str[i] + 32, index_find) + 1;
        }

        index_find = 0;
    }
    str = SymbolsMentioned;

    return arr;
}

class Huffman
{
public:
    Huffman()
    {
        head = nullptr;
        subtree = nullptr;
    }

private:
    class Node
    {
    public:
        string symbol;
        int frec;
        Node* parent;
        Node* leftchild;
        Node* rightchild;

        Node()
        {
            symbol = "";
            frec = 0;
            parent = nullptr;
            leftchild = nullptr;
            rightchild = nullptr;
        }

        Node(string symbol_, int frec_)
        {
            symbol = symbol_;
            frec = frec_;
            leftchild = nullptr;
            rightchild = nullptr;
        }
    };
    Node* head;
    Node* subtree;

    void unite(Node* f, Node* s)
    {
        if (f->parent == nullptr && s->parent == nullptr)
        {
            Node* root;
            f->parent = new Node(f->symbol + s->symbol, f->frec + s->frec);
            root = f->parent;
            s->parent = root;
            root->leftchild = f;
            root->rightchild = s;
        }
    }

    void foo(Node* nodes, int size)
    {
        InsertationSort(nodes, size);

        Node* n1 = &nodes[0], * n2;
        for (int i = 0; i < size - 1; i++)
        {
            n2 = &nodes[i + 1];
            if (n1->frec <= n2->frec)
            {
                unite(n2, n1);
                n1 = n1->parent;
            }
            else
            {
                subtree = n1;
                n1 = n2;
            }
        }
        if (subtree != nullptr)
            unite(n1, subtree);
        if (n1->parent != nullptr)
            head = n1->parent;
        else
        {
            head = n1;
        }
    }

    void InsertationSort(Node* nodes, int size)
    {
        int j;
        for (int i = 1; i < size; i++)
        {
            j = i;
            while (nodes[j].frec < nodes[j - 1].frec)
            {
                swap(nodes[j], nodes[j - 1]);
                if (j-- == 0)
                    break;
            }
        }
    }

    void coding(Node* root, char c)
    {
        if (root->symbol.find(c) != string::npos)
        {
            if (root->leftchild->symbol.find(c) != string::npos)
            {
                cout << "0";
                if (root->leftchild->symbol.size() != 1)
                    coding(root->leftchild, c);
                return;
            }
            else
            {
                cout << "1";
                if (root->rightchild->symbol.size() != 1)
                    coding(root->rightchild, c);
                return;
            }
        }
    }

public:
    void foo(string str)
    {
        int* arr;
        arr = CountFrequency(str);
        int size = str.size();

        Node* nodes = new Node[size];

        for (int i = 0; i < size; i++)
        {
            nodes[i].frec = arr[i];
            nodes[i].symbol = str[i];
        }

        foo(nodes, size);
    }

    void coding(string str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            coding(head, str[i]);
        }
    }

    void decode(string str)
    {
        Node* current = head;
        for (int i = 0; i < str.size(); i++)
        {
            switch (str[i])
            {
            case '1':
                current = current->rightchild;
                break;
            case '0':
                current = current->leftchild;
            }
            if (current->symbol.size() == 1)
            {
                cout << current->symbol;
                current = head;
            }
        }
    }
};
