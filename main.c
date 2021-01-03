#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node;
struct node {
    int x;
    char *word;
    struct node* next;
};


void bastir(node* r) {
    while (r!= NULL) {
        printf("%s \n", r->word);
        r = r->next;
    }
}

void sona_ekle(node* r,char *kelime,int a) {
    while(r->next!=NULL){
        r = r->next;
    }
    r->next = (node*)malloc(sizeof (struct node));
    r->next->word = malloc(strlen(kelime)+1);
    strcpy(r->next->word,kelime);
    r->next->x = a;
    //printf("%s ",r->next->word);
    r->next->next = NULL;

}

node* araya_ekle(node* r,char *kelime, int a){
    if(r==NULL){
        r = (node*)malloc(sizeof(struct node));
        r->next = NULL;
        r->x = a;
        return r;
    }
    if(r->x < a){
        node *  temp = (node*)malloc(sizeof(struct node));
        temp->x = a;
        temp->word = malloc(strlen(kelime)+1);
        strcpy(temp->word,kelime);
        temp->next = r;
        return temp;
    }
    node * iter = r;
    while (iter->next != NULL && iter->next->x > a){
        iter = iter->next;
    }
    node *  temp = (node*)malloc(sizeof(struct node));
    temp->next = iter->next;
    iter->next = temp;
    temp->x = a;
    temp->word = malloc(strlen(kelime)+1);
    strcpy(temp->word,kelime);
    return r;
}

int nodeda_varmi(node* root){
    node* iter = root;
    while(root->next!=NULL){
        root = root->next;
    }//suan root son kelimede

    while(iter!=root){
        if(!strcmp(iter->word,root->word)){
            //printf("aynisindan var.");
            return 1;
        }
        else{
            //bu esit degilse.
            iter = iter->next;
        }
    }
    return 0;
}

void sonu_sil(node *r){
    node *temp;
    node *iter = r;
    while (iter->next->next!=NULL){
        iter = iter->next;
    }
    iter->next = iter->next->next;

    free(iter->next);
}

void silici(node *r, char* kelime){
    node*temp;
    node *iter = r;
    while(strcmp(iter->next->word,kelime)){
        iter = iter->next;
    }
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
}

int main() {

    FILE *dosya;//çatonun aramsının içinde yapacuk
    dosya = fopen("C:\\Users\\BUGRA\\CLionProjects\\pro_lab_3\\metin.txt","r");

    node* root;
    int kelime_buyukluk = 0;
    int i;
    char kelime[100];
    char kelime_2[100];
    int kontrol;
    int sayac = 1;

    root = (node*)malloc(sizeof(node));
    root->x = 10;
    root->word = malloc(strlen("madir")+1);
    strcpy(root->word,"madir");
    root->next = (node*)malloc(sizeof(node));
    root ->next = NULL;
    node* baslangic = root;

    /*fscanf(dosya,"%s",&kelime);
    sona_ekle(root,&kelime,1);*/


    if(dosya==NULL){
        printf("Dosya bulunamadi...");
    }
    else {
        int k = 0;
        int boyutu=0;
        int kelime_harf=0;

        int a = 0;
        fpos_t pos;

        while (!feof(dosya)) {
            int b=a;
            fscanf(dosya, "%s", &kelime);

            while(!feof(dosya)){
                fscanf(dosya,"%s",&kelime_2);

                //printf("%s kelimesi %s kelimesiyle karsilastirliyor...\n",kelime,kelime_2);

                kontrol = strcmp(kelime,kelime_2);

                if(kontrol == 0) {

                    //printf("%s kelimesi %s kelimesine esittir.\n",kelime,kelime_2);
                    sayac++;

                }

                //printf("%s : %d\n",kelime,sayac);

                boyutu = ftell(dosya);

            }

            kelime_harf += strlen(kelime-1);

            fseek(dosya,kelime_harf,SEEK_SET);

            if(kelime_harf==boyutu+1){
                break;
            }

            sona_ekle(root, &kelime, sayac);//bunun öncesinde kaç kelime olduğunu bulup 'a' yerine onu göndericez (aynısından olsa bile sonradan silinecek).
            //root = araya_ekle(root,&kelime,sayac);
            sayac = 1;

            int kosul = nodeda_varmi(root); //şimdi silmeyi öğrenmeliyim
            if(kosul==1){
                //printf("VAR ");//silme burda.
                sonu_sil(root);/*aslında başta aynı node dan varsa hiç bi şey yapmadan devam ettirdim ama
                nodeda_varmi fonksiyonu sürekli ayni şeyi kontrol eder bu yüzden oluşturup siliyorum ki bir sonraki
                kelimenin de kontrolünü yapabileyim*/
            }
            else {
                //printf("YOK ");
            }
        }

        //bastir(baslangic);
        char deneme[] = "arayaeklendimi";
        root = araya_ekle(root,deneme,11);
        for(int madifaki = 0;madifaki<11;madifaki++) {
            printf("%s kelimesinden %d tane var\n",root->word,root->x);
            root = root->next;
        }
        return 0;
    }
}