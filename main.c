#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    int data;
    char *kelime;
    struct node *next
};

typedef struct n node;

struct node* start = NULL;
struct node* temp = NULL;
struct node* q = NULL;
struct node* son = NULL;
struct node* iter = NULL;
struct node* iter_2 = NULL;

void sona_ekle(int veri,char *word)
{
    struct node* eklenecek = (struct node*)malloc(sizeof(struct node));
    eklenecek->data = veri;
    eklenecek->kelime = malloc(strlen(word)+1);
    strcpy(eklenecek->kelime,word);
    eklenecek->next = NULL;

    if(start == NULL)
    {
        start = eklenecek;
    }
    else
    {
        q = start;
        while (q->next != NULL){
            q = q ->next;
        }
        q->next = eklenecek;
    }
}
void basa_ekle(int basa,char *word_2)
{
    struct node *basagelecek = (struct node*)malloc(sizeof(struct node));
    basagelecek->data = basa;
    basagelecek->kelime = malloc(strlen(word_2)+1);
    strcpy(basagelecek->kelime,word_2);
    basagelecek->next = start;
    start = basagelecek;
}

void araya_ekle(int y, char *word_3)
{
    struct node* arayaEklenecek = (struct node*)malloc(sizeof(struct node));
    arayaEklenecek->data = y;
    arayaEklenecek->kelime = malloc(strlen(word_3)+1);
    strcpy(arayaEklenecek->kelime,word_3);
    q=start;
    while (q->next->data > y){
        q = q->next;
    }
    struct node* onune = (struct node*)malloc(sizeof(struct node));
    onune = q->next;
    q->next = arayaEklenecek;
    arayaEklenecek->next = onune;

}

void yazdir(char *world_5)
{
    q = start;

    while(q->next != NULL){
        printf("%s : %d\n",q->next->kelime,q->next->data);
        q = q->next;
    }

}


int nodeVarmi(char *word_4){
    iter = start;

    while(iter->next != NULL){
        if(!strcmp(iter->kelime,word_4)){
            return 0;
        }
        iter = iter->next;

    }
    return 1;

}

int main() {

    node* root;
    node* iter = root;
    start = (struct node*)malloc(sizeof(struct node));
    iter = (struct node*)malloc(sizeof(struct node));
    iter_2 = (struct node*)malloc(sizeof(struct node));
    iter =start;
    iter_2 = start;
    son = start;
    start->data = 1000;
    start->kelime = malloc(strlen("olbeyavrum")+1);
    strcpy(start->kelime,"olbeyavrum");
    start->next = (struct node*)malloc(sizeof(struct node));
    start->next = NULL;


    FILE *devam;
    devam = fopen("C:\\Users\\BUGRA\\CLionProjects\\prolab3\\abi.txt","r+");

    int i = 0;
    char kelime[100];
    char kelime_2[100];
    char sayilan_kelimeler[100];
    int kontrol;
    int selam = 0;
    int sayac=1;
    int m;
    if(devam==NULL){
        printf("Dosya bulunamadi...");
    }
    else {

        int k = 0;
        int boyutu=0;
        int kelime_harf=0;
        int a = 0;
        int b;

        while (!feof(devam)) {

            b=a;
            fscanf(devam,"%s",&kelime);


            while(!feof(devam)){
                fscanf(devam,"%s",&kelime_2);

                kontrol = strcmp(kelime,kelime_2);

                if(kontrol == 0) {
                    sayac++;

                }

                boyutu = ftell(devam);

            }

            kelime_harf += strlen(kelime-1);

            fseek(devam,kelime_harf,SEEK_SET);

            if(kelime_harf==boyutu+1){
                if(son->data >= sayac ){
                    if(nodeVarmi(&kelime)){
                        sona_ekle(sayac,&kelime);
                    }

                }
                else if(sayac >= start->data){
                    if(nodeVarmi(&kelime)){
                        basa_ekle(sayac,&kelime);
                    }
                }
                else if(sayac < start->data && son->data < sayac)
                {
                    if(nodeVarmi(&kelime)){
                        araya_ekle(sayac,&kelime);
                    }
                }

                sayac = 1;

                break;

            }
            while (son->next != NULL){

                son = son->next;
            }
            if(son->data >= sayac ){
                if(nodeVarmi(&kelime)){
                    sona_ekle(sayac,&kelime);
                }

            }
            else if(sayac >= start->data){
                if(nodeVarmi(&kelime)){
                    basa_ekle(sayac,&kelime);
                }
            }
            else if(sayac < start->data && son->data < sayac)
            {
                if(nodeVarmi(&kelime)){
                    araya_ekle(sayac,&kelime);
                }
            }
            sayac = 1;
        }
    }

    yazdir(&kelime);

    fclose(devam);

    return 0;
}