#include "list_sommet.h"

list_vertex_t list_sommet_new(){
    return NULL;
}

int list_sommet_is_empty(list_vertex_t l){
    return NULL == l;
}

list_vertex_t list_sommet_add_first(list_vertex_t l, vertex_t s){
    list_vertex_t p = calloc( 1, sizeof(*p) );
    if(NULL == p) {
        fprintf(stderr, "list_sommet_add_first : error allocating list link\n");
        return NULL;
    }
    
    p->sommet  = s;
    p->next = l;
    return p;
}

list_vertex_t list_sommet_add_last(list_vertex_t l, vertex_t s){
    if(l == NULL){
        return list_sommet_add_first(l,s);
    }
    list_vertex_t p = l;
    while(!list_sommet_is_empty(p->next)){
        p=p->next;
    }
    list_vertex_t add = calloc( 1, sizeof(*p) );
    add->sommet = s;

    p->next = add;

    return l;
}

vertex_t list_sommet_rech_cout_min(list_vertex_t l){
    list_vertex_t p = l;
    // initialisation du cout minimal, assurance de son existence
    int cout_min = l->sommet.cout;

    // initialisation sommet minimal, assurance de son existence
    vertex_t sommet_min = l->sommet;

    while(!list_sommet_is_empty(p)){
        if(p->sommet.cout<cout_min){
            cout_min = p->sommet.cout;
            sommet_min = p->sommet;
        }
        p=p->next;   
    }
    return sommet_min;
}

int list_sommet_appartient(vertex_t v, list_vertex_t l){
    list_vertex_t p = l;
    while(!list_sommet_is_empty(p)){
        if(v.id==p->sommet.id){
            return 1;
        }
        p=p->next;
    }
    return 0;
}


list_vertex_t list_sommet_remove(list_vertex_t l, vertex_t sommet) {
    list_vertex_t prev = NULL;
    list_vertex_t curr = l;

    while (curr != NULL) {
        if (curr->sommet.id == sommet.id) {
            if (prev == NULL) {
                l = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return l;
        }
        prev = curr;
        curr = curr->next;
    }
    return l;
}