#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nume[1000];
    char tara[1000];
    int cantitate;
    float pret;
} Produs;

Produs *produs=NULL;
int numarproduse=0;


void clear_screen()
{
    system("cls || clear");
}

/// functia de citire a fisierului produsele.txt la inceput
void citire_fisier_produse()
{
    FILE *f=fopen("produsele.txt", "r");
    if (f==NULL)
    {
        printf("Fisierul nu exista sau nu poate fi deschis.\n");
        return;
    }

    produs=(Produs*)malloc(20*sizeof(Produs));
    if(produs==NULL)
    {
        printf("Eroare la alocarea memoriei!\n");
        fclose(f);
        return;
    }
    char header[1024];
    fgets(header, sizeof(header), f);
    numarproduse=0;
    while(fscanf(f, "%s %s %d %f", produs[numarproduse].nume, produs[numarproduse].tara, &produs[numarproduse].cantitate, &produs[numarproduse].pret) == 4)
    {
        numarproduse++;
        if (numarproduse%20==0)
        {
            Produs *temp =(Produs*)realloc(produs,(numarproduse+20)*sizeof(Produs));
            if(temp==NULL)
            {
                printf("Eroare la realocarea memoriei!\n");
                free(produs);
                fclose(f);
                return;
            }
            produs=temp;
        }
    }
    fclose(f);
}


///se rescrie in fisier pentru functia de stergere
void scrieProduseInFisier()
{
    FILE *f = fopen("produsele.txt", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului pentru scriere!\n");
        return;
    }
    fprintf(f, "Produs Tara Cantitate Pret\n");
    for(int i=0 ; i<numarproduse ; i++)
    {
        fprintf(f, "%s %s %d %.2f\n",produs[i].nume, produs[i].tara, produs[i].cantitate, produs[i].pret);
    }
    fclose(f);
}
void afiseaza_meniu()
{
    printf("\nMeniu principal:\n");
    printf("1. Adauga un produs nou\n");
    printf("2. Editeaza produs\n");
    printf("3. Sterge produs\n");
    printf("4. Cautare produs\n");
    printf("5. Afiseaza informatii despre produs\n");
    printf("6. Cumpara produs\n");
    printf("7. Iesire\n");
}

void  adauga_produs()
{
    int valid;
    if (produs == NULL)
    {
        produs = (Produs *)malloc(1000 * sizeof(Produs));
        if (produs == NULL)
        {
            printf("Eroare la alocarea memoriei!\n");
            return;
        }
    }
    printf("Nume produs: ");
    scanf("%999s",produs[numarproduse].nume);
    printf("\nTara de origine: ");
    scanf("%999s",produs[numarproduse].tara);

    valid=0;
    while(!valid)
    {
        printf("\nIntroduceti cantitatea produsului (bucati/kg): ");
        scanf("%d",&produs[numarproduse].cantitate);
        if (produs[numarproduse].cantitate >= 1 && produs[numarproduse].cantitate <= 100)
        {
            valid=1;
        }
        else
        {
            printf("Cantitatea trebuie sa fie intre 1 si 100. Incercati din nou.\n");
        }
    }
    valid=0;
    while(!valid)
    {
        printf("\nIntroduceti pretul produsului (xx.yy lei): ");
        scanf("%f", &produs[numarproduse].pret);
        if (produs[numarproduse].pret >= 1 && produs[numarproduse].pret <= 500)
        {
            valid = 1;
        }
        else
        {
            printf("Pretul trebuie sa fie intre 1 si 500. Incercati din nou.\n");
        }
    }

    produs = (Produs *)realloc(produs, (numarproduse + 1) * sizeof(Produs));
    FILE *f=fopen("produsele.txt","a");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }
    fprintf(f,"\n%s %s %d %.2f",produs[numarproduse].nume,produs[numarproduse].tara,produs[numarproduse].cantitate,produs[numarproduse].pret);
    fclose(f);
    numarproduse++;
    system("cls");
    printf("\nProdusul a fost adaugat!\n");
    printf("\nApasa Enter pentru a continua in submeniu...");
    getchar();
    getchar();
    system("cls");
    submeniu_pentru_adaugare();

}

void submeniu_pentru_adaugare()
{
    printf("Ati ales optiunea de a adauga un produs\n");
    printf("\nSubmeniu\n");
    printf("1. Adauga un produs\n");
    printf("2. Iesire din submeniu\n");
}



void editeaza_produs()
{
    char nume_cautat[1000];
    int gasit = 0;
    int ok=0;
    char k[20];
    printf("Introduceti numele produsului pe care doriti sa-l editati: ");
    scanf("%999s", nume_cautat);

    citire_fisier_produse(); // Încarcã produsele în memorie

    for(int i = 0; i < numarproduse; i++)
    {
        if (strcmp(produs[i].nume, nume_cautat) == 0)
        {
            while(ok==0)
            {
                gasit = 1;
                int optiune;
                printf("\nCe doriti sa editati?\n");
                printf("1. Nume\n");
                printf("2. Tara\n");
                printf("3. Cantitate\n");
                printf("4. Pret\n");
                printf("Alegeti optiunea (1-4): ");
                scanf("%d", &optiune);

                if (optiune == 1)
                {
                    printf("\nIntroduceti noul nume: ");
                    scanf("%999s", produs[i].nume);
                }
                else if(optiune == 2)
                {
                    printf("\nIntroduceti noua tara: ");
                    scanf("%999s", produs[i].tara);
                }
                else if (optiune == 3)
                {
                    printf("Introduceti noua cantitate: ");
                    scanf("%d", &produs[i].cantitate);
                }
                else if (optiune == 4)
                {
                    printf("\nIntroduceti noul pret: ");
                    scanf("%f", &produs[i].pret);
                }
                else
                {
                    printf("\nOptiune invalida!\n");
                    return;
                }

                scrieProduseInFisier();
                printf("\nProdusul a fost editat cu succes!\n");
                printf("\nDoresti sa mai editezi un produs?(da sau nu)\n");
                scanf("%s",k);
                if (strcmp(k, "nu") == 0)
                {
                    ok = 1;
                }
            }
        }
        if(ok==1)
            break;
    }

    if (!gasit)
    {
        printf("\nProdusul %s nu a fost gasit!\n", nume_cautat);
    }

    printf("\nApasa Enter pentru a continua...\n");
    getchar();
    getchar();
    system("cls");
    submeniu_pentru_editare();
}


void submeniu_pentru_editare()
{
    printf("Ati ales optiunea de a edita un produs\n");
    printf("\nSubmeniu\n");
    printf("1. Editeaza produsul\n");
    printf("2. Iesire din submeniu\n");
}



///functia o sa stearga un produs
void sterge_produs()
{
    char nume_produs[1000];
    int i,gasit=0;

    printf("Introduceti numele produsului pe care doriti sa-l stergeti: ");
    scanf("%999s",nume_produs);
    citire_fisier_produse(); ///citim fisierul cu produse
    for(i=0 ; i<numarproduse ; i++)
    {
        if(strcmp(produs[i].nume,nume_produs)==0)
        {
            gasit=1;
            for(int j=i ; j<numarproduse-1 ; j++)
            {
                produs[j]=produs[j+1];
            }
            numarproduse--;
            scrieProduseInFisier(); ///functia o sa rescrie in fisier produsele

            system("cls");
            printf("\nProdusul %s a fost sters!\n",nume_produs);
            printf("\nApasa Enter pentru a continua in submeniu...");
            getchar();
            getchar();
            system("cls");
            submeniu_pentru_stergere();
            return;
        }
    }
    if(gasit==0)
    {
        system("cls");
        printf("\nProdusul %s nu a fost gasit!\n",nume_produs);
        printf("\nApasa Enter pentru a continua in submeniu...");
        getchar();
        getchar();
        system("cls");
        submeniu_pentru_stergere();
    }
}

void submeniu_pentru_stergere()
{
    printf("Ati ales optiunea de a sterge un produs\n");
    printf("\nSubmeniu\n");
    printf("1. Sterge produsul\n");
    printf("2. Iesire din submeniu\n");
}



void cauta_produsul_dupa_nume()
{
    char nume_cautat[1000];
    printf("Introduceti numele produsului cautat: ");
    getchar();
    fgets(nume_cautat, sizeof(nume_cautat), stdin);
    nume_cautat[strcspn(nume_cautat, "\n")] = '\0';
    int gasit=0;
    citire_fisier_produse();
    for(int i=0 ; i<numarproduse ; i++)
    {
        if(strcmp(produs[i].nume,nume_cautat)==0)
        {
            system("cls");
            printf("\n%-12s %-12s %10s %13s\n", "Produs", "Tara", "Cantitate (bucati/kg)", "Pret (lei)");
            printf("\033[38;5;73m%-12s\033[0m ", produs[i].nume);
            printf("\033[38;5;97m%-12s\033[0m ", produs[i].tara);
            printf("\033[38;5;180m%10d\033[0m ", produs[i].cantitate);
            printf("\033[1;35m%20.2f\033[0m\n", produs[i].pret);
            gasit=1;
            printf("\nApasa Enter pentru a continua in submeniu...");
            getchar();
            system("cls");
            submeniu_pentru_cautare();
            return;
        }
    }
    if(gasit==0)
    {
        system("cls");
        printf("Produsul %s nu a fost gasit:\n", nume_cautat);
        printf("\nApasa Enter pentru a continua in submeniu...");
        getchar();
        system("cls");
        submeniu_pentru_cautare();
    }

}

void cauta_produsul_dupa_tara()
{
    char tara_cautata[1000];
    int gasit=0,nr=0;
    printf("Introduceti tara produsului dorit: ");
    scanf("%999s",tara_cautata);
    citire_fisier_produse();
    system("cls");
    for(int i=0 ; i<numarproduse ; i++)
    {
        if(strcmp(produs[i].tara,tara_cautata)==0)
        {
            if(gasit==0)
                printf("\n%-3s %-12s %-12s %10s %13s\n", "Nr.", "Produs", "Tara", "Cantitate (bucati/kg)", "Pret (lei)");
            nr++;
            printf("%-3d ",nr);
            printf("\033[38;5;73m%-12s\033[0m ", produs[i].nume);
            printf("\033[38;5;97m%-12s\033[0m ", produs[i].tara);
            printf("\033[38;5;180m%10d\033[0m ", produs[i].cantitate);
            printf("\033[1;35m%20.2f\033[0m\n", produs[i].pret);
            gasit=1;
        }
    }
    if(gasit==0)
    {
        system("cls");
        printf("Nu exista produs/produse din %s.\n",tara_cautata);
    }
    printf("\nApasa Enter pentru a continua in submeniu...");
    getchar();
    getchar();
    system("cls");
    submeniu_pentru_cautare();
}

void submeniu_pentru_cautare()
{
    printf("Ati ales optiunea de cautare produs\n");
    printf("\nSubmeniu\n");
    printf("1. Cauta produsul dupa nume\n");
    printf("2. Cauta produsul dupa tara\n");
    printf("3. Iesire din submeniu\n");
}



void afisare()
{
    system("cls");
    printf("Afisare produse:\n");
    citire_fisier_produse();
    if (numarproduse == 0)
    {
        printf("Nu sunt produse disponibile.\n");
    }
    else
    {
        printf("\n%-4s %-15s %-10s %-10s %13s\n", "Nr.", "Produs", "Tara", "Cantitate (bucati/kg)", "Pret (lei)");

        for (int i = 0; i < numarproduse; i++)
        {
            printf("%-4d", i + 1);
            printf("\033[38;5;73m%-15s\033[0m", produs[i].nume);
            printf("\033[38;5;97m%-10s\033[0m", produs[i].tara);
            printf("\033[38;5;180m%10d\033[0m ", produs[i].cantitate);
            printf("\033[1;35m%25.2f\033[0m\n", produs[i].pret);
        }
    }
    printf("\nApasa Enter pentru a afisa submeniul...\n");
    getchar();
    getchar();
    system("cls");
    submeniu_pentru_afisarea_informatiilor();
}

void submeniu_pentru_afisarea_informatiilor()
{
    printf("Ati ales optiunea de a afisa informatiile despre produse\n");
    printf("\nSubmeniu\n");
    printf("1. Afiseaza informatii despre produse\n");
    printf("2. Iesire din submeniu\n");
}


void cumpara_produs()
{
    char nume_produs[1000];
    int cantitate_dorita;
    int gasit=0;
    printf("Introduceti numele produsului pe care doriti sa-l cumparati: ");
    scanf("%999s",nume_produs);
    printf("Introduceti cantitatea dorita: ");
    scanf("%d",&cantitate_dorita);
    citire_fisier_produse();
    for(int i=0; i<numarproduse; i++)
    {
        if(strcmp(produs[i].nume,nume_produs)==0)
        {
            gasit=1;
            if(produs[i].cantitate>=cantitate_dorita)
            {
                produs[i].cantitate=produs[i].cantitate-cantitate_dorita;
                printf("\nAti cumparat %d din produsul %s!\n",cantitate_dorita, produs[i].nume);

                if(produs[i].cantitate == 0)
                {
                    printf("\nProdusul %s s-a epuizat!\n",produs[i].nume);
                    for(int j=i; j<numarproduse-1; j++)
                    {
                        produs[j]=produs[j+1];
                    }
                    numarproduse--;
                    scrieProduseInFisier();
                }
                else
                {
                    scrieProduseInFisier();
                }
                break;
            }
            else
            {
                int ramas=produs[i].cantitate;
                produs[i].cantitate=0;
                printf("\nNu avem suficienta cantitate din produsul %s. Ai putut cumpara doar %d.\n", produs[i].nume, ramas );
                printf("\nProdusul %s s-a epuizat!\n",produs[i].nume);
                for(int j=i; j<numarproduse-1; j++)
                {
                    produs[j]=produs[j+1];
                }
                numarproduse--;
                scrieProduseInFisier();
            }
        }
    }
    if(gasit==0)
    {
        printf("\nProdusul %s nu a fost gasit!\n",nume_produs);
    }
    printf("\nApasa Enter pentru a continua...\n");
    getchar();
    getchar();
    system("cls");
    submeniu_pentru_cumpararea_produsului();
}


void submeniu_pentru_cumpararea_produsului()
{
    printf("Ati ales optiunea de a cumpara un produs\n");
    printf("\nSubmeniu\n");
    printf("1. Cumpara un produs\n");
    printf("2. Iesire din submeniu\n");
}



int main()
{

    int optiune;
    while(1)
    {
        afiseaza_meniu();
        printf("\nAlege optiunea dorita: ");
        scanf("%d", &optiune);
        system("cls");
        if(optiune==7)
        {
            printf("Iesire din aplicatie.\n");
            free(produs);
            break;
        }
        else if(optiune<1 || optiune>7)
        {
            printf("Optiune invalida! Te rog sa alegi din nou\n");
        }
        else if(optiune==1)
        {
            ///Partea de submeniu pentru adaugarea unui produs
            submeniu_pentru_adaugare();
            while(1)
            {

                printf("\nAlege optiunea dorita: ");
                scanf("%d", &optiune);

                if(optiune==2) ///iesire din submeniu
                {
                    system("cls");
                    break;
                }
                else if(optiune==1) ///apelarea functiei de adaugare produs
                {
                    system("cls");
                    adauga_produs();
                }
                else if(optiune<1 || optiune>2)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-3\n");
                }
            }

        }
        else if(optiune==2)
        {
            ///Partea de submeniu pentru editarea unui produs
            submeniu_pentru_editare();
            while(1)
            {

                printf("\nAlege optiunea dorita: ");
                scanf("%d", &optiune);
                if(optiune==2) ///Daca vrem sa iesim din submeniu
                {
                    system("cls");
                    break;
                }
                else if(optiune==1) ///daca vrem sa editam un produs
                {
                    system("cls");
                    editeaza_produs();
                }
                else if(optiune<1 || optiune>2)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-2\n");
                }
            }
        }
        else if(optiune==3) ///Partea de submeniu pentru stergerea unui produs
        {
            submeniu_pentru_stergere();
            while(1)
            {
                printf("\nAlege optiunea dorita: ");
                scanf("%d",&optiune);
                if(optiune==2) /// daca vrem sa iesim din submeniu
                {
                    system("cls");
                    break;
                }
                else if(optiune==1) ///daca vrem sa stergem un produs
                {
                    system("cls");
                    sterge_produs();
                }
                else if(optiune<1 || optiune>2)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-2\n");
                }
            }

        }
        else if(optiune==4) ///Partea de submeniu pentru cautarea unui produs
        {

            submeniu_pentru_cautare();
            while(1)
            {
                printf("\nAlege optiunea dorita: ");
                scanf("%d", &optiune);
                if(optiune==3) ///daca vrem sa iesim din submeniu
                {
                    system("cls");
                    break;
                }
                else if(optiune==1) ///optiunea de cautare dupa nume
                {
                    system("cls");
                    cauta_produsul_dupa_nume();
                }
                else if(optiune==2) ///optiunea de cautare dupa tara
                {
                    system("cls");
                    cauta_produsul_dupa_tara();
                }
                else if(optiune<1 || optiune>3)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-3\n");
                }
            }
        }

        else if(optiune==5)
        {
            submeniu_pentru_afisarea_informatiilor();
            while(1)
            {
                printf("\nAlege optiunea dorita: ");
                scanf("%d",&optiune);
                if(optiune==2)
                {
                    system("cls");
                    break;
                }
                else if(optiune==1)
                {
                    system("cls");
                    afisare();
                }
                else if(optiune<1 || optiune>2)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-2\n");
                }
            }
        }
        else if(optiune==6)
        {
            submeniu_pentru_cumpararea_produsului();
            while(1)
            {
                printf("\nAlege optiunea dorita: ");
                scanf("%d", &optiune);
                if(optiune==2)
                {
                    system("cls");
                    break;
                }
                else if(optiune==1)
                {
                    system("cls");
                    cumpara_produs();
                }
                else if(optiune<1 || optiune>2)
                {
                    printf("Optiunea e invalida! Te rog sa alegi un numar intre 1-2\n");
                }
            }
        }
    }
    return 0;
}
