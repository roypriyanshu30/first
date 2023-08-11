#include <iostream>
#include <time.h>
// eerefrefesf
using namespace std;
struct edge;
struct vertex
{
    char data;
    bool isProcessed;
    vertex *nextVertex, *quNext;
    edge *firstEdge;
};

struct edge
{
    vertex *start, *end;
    edge *nextEdge;
};
class stack
{
public:
    vertex *head;
    stack()
    {
        head = NULL;
    }
    void push(vertex *v)
    {
        if (head == NULL)
        {
            head = v;
        }
        else
        {
            v->quNext = head;
            head = v;
        }
        v->isProcessed = true;
    }
    vertex *pop()
    {
        vertex *v = head;
        head = head->quNext;
        return v;
    }
};
class queue
{
public:
    vertex *head;
    queue()
    {
        head = NULL;
    }
    void push(vertex *v)
    {
        if (head == NULL)
            head = v;

        else
        {
            vertex *temp;
            for (temp = head; temp->quNext != NULL; temp = temp->quNext)
                ;
            temp->quNext = v;
        }
        v->isProcessed = true;
    }
    vertex *pop()
    {
        vertex *v = head;
        head = head->quNext;
        return v;
    }
};
class graph
{
public:
    vertex *firstVertex;
    int count;

    graph()
    {
        firstVertex = NULL;
        count = 0;
    }

    vertex *createVertex(char data)
    {
        vertex *vert = new vertex;
        vert->data = data;
        vert->nextVertex = vert->quNext = NULL;
        vert->firstEdge = NULL;
        return vert;
    }

    bool isPresent(vertex *vert)
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert->data)
                return true;
        }
        return false;
    }
    // inserts the vertex in the queue after checking if it is present or not
    void insertVertex(vertex *vert)
    {
        if (isPresent(vert))
        {
            cout << "Vertex already present!" << endl;
            delete vert;
            return;
        }
        if (firstVertex == NULL)
            firstVertex = vert;
        else
        {
            vertex *temp;
            for (temp = firstVertex; temp->nextVertex != NULL; temp = temp->nextVertex)
                ;
            temp->nextVertex = vert;
        }
        count++;
        cout << "Vertex inserted successfully!" << endl;
    }
    // finds the vertex with corresponding data values and returns it, returns NULL if not found
    vertex *findVertex(char vert)
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert)
                return temp;
        }
        return NULL;
    }
    // creates the edge with given source and destination vertices
    edge *createEdge(vertex *vert1, vertex *vert2)
    {
        edge *edg = new edge;
        edg->start = vert1;
        edg->end = vert2;
        edg->nextEdge = NULL;
        return edg;
    }
    // adds the edge to the vertex's edge list
    void addEdge(vertex *vert, edge *edg)
    {
        if (vert->firstEdge == NULL)
            vert->firstEdge = edg;
        else
        {
            edge *temp;
            for (temp = vert->firstEdge; temp->nextEdge != NULL; temp = temp->nextEdge)
                ;
            temp->nextEdge = edg;
        }
    }
    // checks if vertices are present, if they are, then it creates and adds the edges to both the vertices
    void insertUndirectedEdge(char vertex1, char vertex2)
    {
        vertex *vert1, *vert2;
        vert1 = findVertex(vertex1);
        if (vert1 == NULL)
        {
            cout << vertex1 << " was not found in the graph" << endl;
            return;
        }
        vert2 = findVertex(vertex2);
        if (vert2 == NULL)
        {
            cout << vertex2 << " was not found in the graph" << endl;
            return;
        }
        edge *edg1, *edg2;
        edg1 = createEdge(vert1, vert2);
        addEdge(vert1, edg1);
        edg2 = createEdge(vert2, vert1);
        addEdge(vert2, edg2);
        cout << "Edge has been inserted successfully between " << vertex1 << " and " << vertex2 << endl;
    }
    // inserts a directed edge between vertex 1 and vertex 2
    void insertDirectedEdge(char vertex1, char vertex2)
    {
        vertex *src, *dest;
        src = findVertex(vertex1);
        if (src == NULL)
        {
            cout << vertex1 << " was not found in the graph" << endl;
            return;
        }
        dest = findVertex(vertex2);
        if (dest == NULL)
        {
            cout << vertex2 << " was not found in the graph" << endl;
            return;
        }
        edge *edg;
        edg = createEdge(src, dest);
        addEdge(src, edg);
        cout << "Edge has been inserted successfully from " << vertex1 << " to " << vertex2 << endl;
    }
    void reset()
    {
        for (vertex *v = firstVertex; v != NULL; v = v->nextVertex)
        {
            v->quNext = NULL;
            v->isProcessed = false;
        }
    }
    vertex *unprocessed()
    {
        for (vertex *v = firstVertex; v != NULL; v = v->nextVertex)
        {
            if (v->isProcessed == false)
                return v;
        }
        return NULL;
    }

    void dfs()
    {
        stack s;
        reset();
        vertex *v = firstVertex;
    back_track:

        for (edge *edg = v->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (v == firstVertex)
                s.push(v);
            if (edg->end->isProcessed == false)
            {
                s.push(edg->end);
                v = s.pop();
                cout << v->data;
                edg = v->firstEdge;
            }
        }
        v = unprocessed();
        s.push(v);
        cout << v->data;
        if (v != NULL)
        {
            goto back_track;
        }
    }
    bool visited(edge *c)
    {

        if (c != NULL)
            return false;

        return true;
    }

    void bfs()
    {
        queue q;
        reset();
        vertex *v = firstVertex;

    back_track:
        edge *edg;
        for (edg = v->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (v->isProcessed == false)
            {
                q.push(v);
                v = q.pop();
                cout << v->data;
            }

            if (edg->end->isProcessed == false)
            {
                q.push(edg->end);

                break;
            }
        }
        if (!visited(edg))
            goto back_track;
        if (visited(edg))
        {
            v = q.pop();
            if (v == NULL)
                return;
            cout << v->data;
            goto back_track;
        }
    }
    // bool cycle()
    // {
    //     edge *edg;
    //     reset();
    //     vertex *v = firstVertex;
    // backtrack:
    //     for (edg = v->firstEdge; edg != NULL; edg = edg->nextEdge)
    //     {
    //         v->isProcessed = true;
    //         if (edg->end->isProcessed == false)
    //         {
    //             v = edg->end;
    //             edg = v->firstEdge;
    //             break;
    //         }
    //     }
    //     if (edg == v->firstEdge)
    //         ;
    //     {
    //         goto backtrack;
    //     }

    //     if (edg->end == v->firstEdge->end)
    //     {
    //         return true;
    //     }
    //     if (edg->end != v->firstEdge->end)
    //     {
    //         v = edg->end;
    //         goto backtrack;
    //     }
    //     if (visited(edg))
    //     {
    //         v = edg
    //     }
    // }
    // void mst()
    // {
    // }
    void printVertexWithEdges()
    {
        for (vertex *vert = firstVertex; vert != NULL; vert = vert->nextVertex)
        {
            cout << vert->data << " ----> ";
            for (edge *edg = vert->firstEdge; edg != NULL; edg = edg->nextEdge)
                cout << edg->end->data << ", ";
            cout << endl;
        }
    }
};

int main()
{
    graph g;
    int opt = 0;
    char data, v1, v2;
    while (opt != -1)
    {
        cin >> opt;
        switch (opt)
        {
        case 1:
            cin >> data;
            g.insertVertex(g.createVertex(data));
            break;
        case 2:
            cin >> v1;
            cin >> v2;
            g.insertUndirectedEdge(v1, v2);
            break;
        case 3:
            g.printVertexWithEdges();
            break;
        case 4:
            g.dfs();
            cout << "hi";
            break;
        case 5:

            g.bfs();
            break;
        case 6:
            cin >> v1;
            cin >> v2;
            g.insertDirectedEdge(v1, v2);
            break;

        }
    }
}
