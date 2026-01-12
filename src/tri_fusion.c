#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tri_fusion.h"

list_edge_t creationOf_array_from_graph(graph_t graph) {
    if (graph == NULL)
        return NULL;

    list_edge_t head = NULL;
    list_edge_t tail = NULL;
    list_edge_t list_tempo = NULL;

    for (long int i = 0; i < graph->numOf_vertices; i++) {
        list_tempo = graph->data[i].edges;
        while (list_tempo != NULL) {
            list_edge_t new_edge = (list_edge_t)malloc(sizeof(link_edge_t));
            if (new_edge == NULL) {
                perror("Erreur d'allocation mémoire");
                exit(EXIT_FAILURE);
            }
            new_edge->val = list_tempo->val;
            new_edge->next = NULL;
            if (head == NULL) {
                // Si la liste principale est vide, initialiser avec la liste actuelle
                head = new_edge;
                tail = new_edge;
            } else {
            // Ajouter la liste principale à la fin de la liste actuelle
                tail->next = new_edge;
                tail = new_edge;
            }
            list_tempo = list_tempo->next;
        }
    }

    return head;
}

void split_list_inHalf(list_edge_t root, list_edge_t* split_front, list_edge_t* split_back) {
    list_edge_t slow = root;
    list_edge_t fast = root->next;

    // Permet d'avoir slow qui arrive à la moitié lorsque fast est arrivé à la fin.
    // Ainsi, on n'est pas obligé de connaître l'adresse de fin de root
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    *split_front = root;
    *split_back = slow->next;
    slow->next = NULL; // On sépare les deux listes
}

list_edge_t sorted_merge(list_edge_t list1, list_edge_t list2) {
    list_edge_t result = NULL;
    list_edge_t *lastPtrRef = &result;

    while (1) {
        if (list1 == NULL) {
            *lastPtrRef = list2;
            break;
        } else if (list2 == NULL) {
            *lastPtrRef = list1;
            break;
        }

        if (list1->val.cost <= list2->val.cost) {
            *lastPtrRef = list1;
            list1 = list1->next;
        } else {
            *lastPtrRef = list2;
            list2 = list2->next;
        }

        lastPtrRef = &(*lastPtrRef)->next;
    }

    return result;
}

void merge_sort(list_edge_t* list_toSort) {
    list_edge_t head = *list_toSort;
    list_edge_t list_a;
    list_edge_t list_b;

    // Si la liste est vide ou ne contient qu'un seul élément
    if ((head == NULL) || (head->next == NULL))
        return;

    split_list_inHalf(head, &list_a, &list_b);

    // Permet de trier récursivement chaque moitié
    merge_sort(&list_a);
    merge_sort(&list_b);

    // Fusionner les deux moitiés triées
    *list_toSort = sorted_merge(list_a, list_b);
}

list_edge_t sorted_ascending_graph_merge(graph_t graphTo_sort) {
    list_edge_t listTo_sort = creationOf_array_from_graph(graphTo_sort);

    if ((listTo_sort == NULL) || (listTo_sort->next == NULL))
        return listTo_sort;

    merge_sort(&listTo_sort);

    return listTo_sort;
}

/*list_edge_t creationOf_array_from_graph(graph_t graph) {
    if (graph == NULL)
        return NULL;

    list_edge_t head = NULL;
    list_edge_t tail = NULL;
    list_edge_t list_tempo = NULL;

    for (long int i = 0; i < graph->numOf_vertices; i++) {
        list_tempo = graph->data[i].edges;
        if (list_tempo != NULL) {
            if (head == NULL) {
                // Si la liste principale est vide, initialiser avec la liste actuelle
                head = list_tempo;
            } else {
                // Ajouter la liste principale à la fin de la liste actuelle
                tail = list_tempo;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = head;
                head = list_tempo;
            }
        }
    }

    return head;
}

void split_list_inHalf(list_edge_t root, list_edge_t* split_front, list_edge_t* split_back) {
    list_edge_t slow = root;
    list_edge_t fast = root->next;

    // Permet d'avoir slow qui arrive à la moitié lorsque fast est arrivé à la fin.
    // Ainsi, on n'est pas obligé de connaître l'adresse de fin de root
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    *split_front = root;
    *split_back = slow->next;
    slow->next = NULL; // On sépare les deux listes
}

list_edge_t sorted_merge(list_edge_t list1, list_edge_t list2) {
    list_edge_t result = NULL;

    if (list1 == NULL)
        return list2;
    else if (list2 == NULL)
        return list1;

    if (list1->val.cost <= list2->val.cost) {
        result = list1;
        result->next = sorted_merge(list1->next, list2);
    } else {
        result = list2;
        result->next = sorted_merge(list1, list2->next);
    }

    return result;
}


void merge_sort(list_edge_t* list_toSort) {
    list_edge_t head = *list_toSort;
    list_edge_t list_a;
    list_edge_t list_b;

    // Si la liste est vide ou ne contient qu'un seul élément
    if ((head == NULL) || (head->next == NULL))
        return;

    split_list_inHalf(head, &list_a, &list_b);

    // Perme de trier récursivement chaque moitié
    merge_sort(&list_a);
    merge_sort(&list_b);

    // Fusionner les deux moitiés triées
    *list_toSort = sorted_merge(list_a, list_b);
}



list_edge_t sorted_ascending_graph_merge(graph_t graphTo_sort) {
    list_edge_t listTo_sort = creationOf_array_from_graph(graphTo_sort);

    if ((listTo_sort == NULL) || (listTo_sort->next == NULL))
        return listTo_sort;

    merge_sort(&listTo_sort);

    return listTo_sort;
}*/