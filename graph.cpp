//Brian Kim October 29, 2017
// FILE: graph.cpp (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set
using std::size_t;

namespace main_savitch_15
{
    template <class Item>
    graph<Item>::graph ( ) : many_vertices(0) {
        allocated = 10;

        edges = new bool*[allocated];
        for (size_t i = 0; i < allocated; ++i)
            edges[i] = new bool[allocated];

        labels = new Item[allocated];
    }
    template <class Item>
    graph<Item>::graph(size_t initial_allocation) : many_vertices(0) {
        allocated = initial_allocation;

        edges = new bool*[allocated];
        for (size_t i = 0; i < allocated; ++i)
            edges[i] = new bool[allocated];

        labels = new Item[allocated];
    }

    template <class Item>
    graph<Item>::graph(const graph &source) {
        allocated = source.allocated;
        many_vertices = source.many_vertices;

        edges = new bool*[allocated];
        for (size_t i = 0; i < allocated; ++i)
            edges[i] = new bool[allocated];

        labels = new Item[allocated];

        for (size_t i = 0; i < many_vertices; ++i) {
            for (size_t j = 0; j < many_vertices; ++j) {
                edges[i][j] = source.edges[i][j];
            }
        }

        for (size_t i = 0; i < many_vertices; ++i) 
            labels[i] = source.labels[i];

    }

    template<class Item>
    graph<Item>::~graph() {
        for (size_t i = 0; i < allocated; ++i)
            delete [] edges[i];

        delete [] edges;   

        delete [] labels;     
    }

    template<class Item>
    graph<Item>& graph<Item>::operator=(const graph &source) {
        if (this == &source)
            return *this;
        if (allocated != source.allocated) { 
            for (size_t i = 0; i < allocated; ++i)
                delete [] edges[i];

            delete [] edges;   

            delete [] labels; 

        edges = new bool*[source.allocated];
        for (size_t i = 0; i < source.allocated; ++i)
            edges[i] = new bool[source.allocated];

        labels = new Item[source.allocated];

        }

        allocated = source.allocated;
        many_vertices = source.many_vertices;

        for (size_t i = 0; i < many_vertices; ++i) {
            for (size_t j = 0; j < many_vertices; ++j) {
                edges[i][j] = source.edges[i][j];
            }
        }

        for (size_t i = 0; i < many_vertices; ++i) 
            labels[i] = source.labels[i];

        return *this;

    }

    template<class Item>
    void graph<Item>::resize(size_t new_allocation) {
        if (new_allocation < allocated)
            return;

        graph* temp;
        temp = new graph(new_allocation);
        temp->many_vertices = many_vertices;

        for (size_t i = 0; i < many_vertices; ++i) {
            for (size_t j = 0; j < many_vertices; ++j) {
                temp->edges[i][j] = edges[i][j];
            }
        }

        for (size_t i = 0; i < temp->many_vertices; ++i) 
            temp->labels[i] = labels[i];
        // allocated = new_allocation;

        // delete edges;
        // delete labels;

        // edges = temp->edges;
        // labels = temp->labels;
        *this = *temp;


        delete temp;

        // delete this;

        // allocated = temp->allocated;
        // many_vertices = temp->many_vertices;

        // edges = new bool*[allocated];
        // for (int i = 0; i < allocated; ++i)
        //     edges[i] = new bool[allocated];

        // labels = new Item[allocated];

        // for (int i = 0; i < many_vertices; ++i) {
        //     for (int j = 0; j < many_vertices; ++j) {
        //         edges[i][j] = temp->edges[i][j];
        //     }
        // }

        // for (int i = 0; i < many_vertices; ++i) 
        //     labels[i] = temp->labels[i];
        // delete temp;

    }


    template <class Item>
    void graph<Item>::add_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = true;
    }

    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        size_t new_vertex_number;
        size_t other_number;

        if(many_vertices == allocated) {
            resize(2 * allocated);
        }

        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }

    template <class Item>
    bool graph<Item>::is_edge(size_t source, size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        return edges[source][target];
    }

    template <class Item>
    Item& graph<Item>::operator[ ] (size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns a reference to the label
    }

    template <class Item>
    Item graph<Item>::operator[ ] (size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < size( ));
        return labels[vertex];     // Returns only a copy of the label
    }

    template <class Item>
    std::set<size_t> graph<Item>::neighbors(size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<size_t> answer;
        size_t i;

        assert(vertex < size( ));

        for (i = 0; i < size( ); ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }

    template <class Item>
    void graph<Item>::remove_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < size( ));
        assert(target < size( ));
        edges[source][target] = false;
    }
}
