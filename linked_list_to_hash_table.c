#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct cell {
    char *anahtar;
    struct cell *next;
};

struct table_node{
    int count;
    struct cell *header;
};

struct hash_tablosu{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

unsigned int hash(char *s, int multiplier, int table_size){
    int i=0;
    unsigned int value =0;
    while(s[i] != '\0'){
        value=(s[i]+multiplier*value) % table_size;
        i++;
    }
    return value;
}

void print_list(struct cell *l){
    if(l!=NULL){
        printf("%s ", l->anahtar);
        print_list(l->next);
    }
}
void initialize_hash_table(struct hash_tablosu **htable, 
        int multiplier, int table_size){
    int i;
    *htable=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   if(*htable==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
   }    
    (*htable)->tablo_basi=
       (struct table_node *)malloc(table_size*sizeof(struct table_node));
    if((*htable)->tablo_basi==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
    }
    (*htable)->tablo_uzunlugu= table_size;
    (*htable)->multiplier= multiplier;
    
    for(i=0; i<table_size; i++){
        ((*htable)->tablo_basi+i)->count = 0;
        ((*htable)->tablo_basi+i)->header = NULL;
    }
}

int insert(char *anahtar, struct cell **l){
    if(*l==NULL){
        *l=(struct cell*)malloc(sizeof(struct cell));
        (*l)->anahtar=(char*)malloc((strlen(anahtar)+1)*sizeof(char));
        strcpy((*l)->anahtar,anahtar);
        (*l)->next=NULL;
        return 1;
    }
    else if(strcmp(anahtar,(*l)->anahtar)) 
        return insert(anahtar, &((*l)->next));
    else return 0;
}



void linked_list_to_hash_table(struct hash_tablosu *htable,struct cell **liste_basi){
    struct cell **l = &(*liste_basi);
    while((*l) != NULL){
        int hash_index = hash((*l)->anahtar,htable->multiplier,htable->tablo_uzunlugu);
        struct cell **yeni = &((htable->tablo_basi +hash_index)->header);
        if((*yeni) == NULL){
            (*yeni)= (*l);
            (htable->tablo_basi +hash_index)->count++;
            if((*l)->next == NULL){
                (*l) = (*l)->next;
                break;
            }
            (*l) = (*l)->next;
            (*yeni)->next = NULL;
        }
        else{                                  
            struct cell *m = (*yeni);
            int rose = 0;
            struct cell *k = (*yeni);
            while(k!=NULL){
                if(strcmp((k)->anahtar,(*l)->anahtar)==0){
                    rose = 1;
                    (*l) = (*l)->next;
                    break;
                }
                k = k->next;
            }
            if(rose == 0){
                while ((*yeni)->next !=NULL){
                    (*yeni) = (*yeni)->next;
                }
                (*yeni)->next = (*l);
                (*l) = (*l)->next;
                (*yeni)->next->next = NULL;
                (*yeni) = m;
                (htable->tablo_basi +hash_index)->count++;
            }
        }
    }
}



void print_hash_table(struct hash_tablosu *htable){
    if(htable){
        int index;
        printf("\n----- HASH TABLOSU -----\n");
        for(index=0; index<htable->tablo_uzunlugu; index++){
            printf("%5d : (%2d) ",index,(htable->tablo_basi +index)->count);
          //  printf("%5d : (%2d) ",index,hash_table->tablo_basi[index].counter);
            print_list(((htable->tablo_basi+index)->header));
            printf("\n");
        }
    }
    else printf("Hash Tablosu Bos ...\n"); 
    
}


struct cell* hucre_olustur(char *anahtar){
    struct cell *a;
    a=(struct cell*)malloc(sizeof(struct cell));
    if(a==NULL){
        printf("Heap alaninda yer ayrilamadi ...\n");
        exit(1);
    }
    a->anahtar=anahtar;
    a->next=NULL;
    return a;
}

void liste_basina_ekle(char *anahtar,struct cell **liste_basi){
    struct cell* a=hucre_olustur(anahtar);
    a->next=*liste_basi;
    *liste_basi=a;
}

void liste_yaz(struct cell *liste_basi){
    while(liste_basi!=NULL){
        printf("%s ",liste_basi->anahtar);
        liste_basi=liste_basi->next;
    }
    printf("\n");
}


int main(int argc, char** argv) {
    
    struct cell *liste1=NULL;
    liste_basina_ekle("blue",&liste1);
    liste_basina_ekle("red",&liste1);
    liste_basina_ekle("green",&liste1);
    liste_basina_ekle("yellow",&liste1);
    liste_basina_ekle("black",&liste1);
    liste_basina_ekle("blue",&liste1);

    
   
    
    
    
    liste_yaz(liste1);
     
     
    struct hash_tablosu *htable=NULL;
    initialize_hash_table(&htable,3,5);
    //print_hash_table(htable); 
    linked_list_to_hash_table(htable,&liste1);
  
    print_hash_table(htable);
    liste_yaz(liste1);

    return (EXIT_SUCCESS);
}

