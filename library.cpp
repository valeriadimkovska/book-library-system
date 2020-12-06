#include<iostream>
#include<string.h>
using namespace std;
 
class NoGradeException{
    public:
    NoGradeException(){}
};
 
class Lice {
private:
    char ime[20];
    char drzava[20];
public:
    Lice(char *ime, char* drzava) {
        strcpy(this->ime, ime);
        strcpy(this->drzava, drzava);
    }
    Lice() {
        strcpy(this->ime, "");
        strcpy(this->drzava, "");
    }
    bool operator==(char *ime) {
        return strcmp(this->ime, ime) == 0;
    }
    char const * getIme() const {
        return ime;
    }
    void pecati() const {
        cout << ime << " (" << drzava << ")"<<endl;
    }
};
 
class Kniga {
protected:
    Lice avtori[10];
    int brojAvtori;
    int *ocenki;
    int brojOcenki;
    char naziv[30];
 
public:
    Kniga(char *naziv, Lice *avtori, int brojAvtori, int *ocenki, int brojOcenki) {
        strcpy(this->naziv, naziv);
        this->brojAvtori = brojAvtori;
        for (int i = 0; i<brojAvtori; i++) this->avtori[i] = avtori[i];
        this->brojOcenki = brojOcenki;
        this->ocenki = new int[brojOcenki];
        for (int i = 0; i<brojOcenki; i++) this->ocenki[i] = ocenki[i];
    }
 
    Kniga(const Kniga &k) {
        strcpy(this->naziv, k.naziv);
        this->brojAvtori = k.brojAvtori;
        for (int i = 0; i<k.brojAvtori; i++) this->avtori[i] = k.avtori[i];
        this->brojOcenki = k.brojOcenki;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i<k.brojOcenki; i++) this->ocenki[i] = k.ocenki[i];
    }
    Kniga operator=(const Kniga &k) {
        if (&k == this) return *this;
        strcpy(this->naziv, k.naziv);
        this->brojAvtori = k.brojAvtori;
        for (int i = 0; i<k.brojAvtori; i++) this->avtori[i] = k.avtori[i];
        this->brojOcenki = k.brojOcenki;
        delete[] ocenki;
        this->ocenki = new int[k.brojOcenki];
        for (int i = 0; i<k.brojOcenki; i++) this->ocenki[i] = k.ocenki[i];
        return *this;
    }
 
    virtual ~Kniga() {
        delete[] ocenki;
    }
 
    int getBrojAvtori() const {
        return brojAvtori;
    }
 
    Lice operator[](int i) const {
        if (i<brojAvtori&&i >= 0)
            return avtori[i];
        else
            return Lice();
    }
 
 
    virtual float getVkupnaOcenka(){
       
        try{
            if(brojOcenki==0)
                throw NoGradeException();
        }
        catch(NoGradeException){
            cout<<"Knigata "<<naziv<<" nema ocenki od chitatelite"<<endl;
            return 0;
        }
       
       float suma=0.0;
        for(int i=0; i<brojOcenki;i++){
       
            suma+=ocenki[i];
       
        }
       
        float prosek=suma/(float)brojOcenki;
        return prosek;
   
    }
   
    virtual void pecati(){
       cout<<naziv<<endl;
       cout<<"Avtori:"<<endl;
       
        for(int i=0; i<brojAvtori; i++){
             avtori[i].pecati();
        }
   
    }
   
    Lice * getAvtori(){
       return avtori;
    }
   
 
};
 
class VebStranica {
protected:
    char *url;
    int brojPristapuvanja;
 
public:
    VebStranica(char *url, int brojPristapuvanja) {
        this->brojPristapuvanja = brojPristapuvanja;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }
 
    VebStranica(const VebStranica &v) {
        this->brojPristapuvanja = v.brojPristapuvanja;
        this->url = new char[strlen(v.url) + 1];
        strcpy(this->url, v.url);
    }
 
    VebStranica operator=(const VebStranica &v) {
        if (this == &v) return *this;
        this->brojPristapuvanja = v.brojPristapuvanja;
        delete[] url;
        this->url = new char[strlen(v.url) + 1];
        strcpy(this->url, v.url);
        return *this;
    }
 
    ~VebStranica() {
        delete[] url;
    }
 
    void pecati() const {
        cout << "url: " << url << endl;
    }
   
 
};
 
class OnlajnKniga:public Kniga, VebStranica{
   private:
    int brojSimnuvanja;
   
   
   public:
     OnlajnKniga(char *naziv, Lice *avtori, int brojAvtori, int *ocenki, int brojOcenki, char *url, int brojPristapi,int  br):Kniga(naziv,avtori,brojAvtori,ocenki, brojOcenki)
        ,VebStranica(url, brojPristapi){
        brojSimnuvanja=br;
        }
 
    float getVkupnaOcenka(){
       
        float prosek=Kniga::getVkupnaOcenka();
        float koeficient=(float)brojSimnuvanja/(float)brojPristapuvanja;
       
        return prosek*koeficient;
    }
   
    void pecati(){
   
        Kniga::pecati();
        cout<<"url: "<<url<<endl;
   
    }
   
    int getBrojAvtori(){
        return brojAvtori;
    }
 
};
 
void pecatiOnlajnKnigi ( Kniga** knigi, int n){
 
    for(int i=0; i<n; i++){
   
        OnlajnKniga *ok=dynamic_cast<OnlajnKniga*>(knigi[i]);
       
        if(ok){
       
           knigi[i]->pecati();
        }
   
    }
 
}
 
double prosechnaOcenka (char *avtor, Kniga** knigi, int n ){
    float suma=0.0;
    int br=0;
   
    for(int i=0; i<n; i++){
   
        for(int j=0; j<knigi[i]->getBrojAvtori(); j++){
         
            if(strcmp(avtor, knigi[i]->getAvtori()[j].getIme() )==0)
            {
                suma+=knigi[i]->getVkupnaOcenka();
                br++;
           
            }
       
        }
     
    }
   
    return suma/br;
 
 
}
 
 
int main() {
 
    Lice avtori[10];
    int brojAvtori, ocenki[20], ocenka, brojOcenki, tip, brojPristapi, brojSimnuvanja;
    char naslov[20], ime[40], drzava[20], url[50];
 
    cin >> tip;
 

    if (tip == 1) { //pecati kniga i avtorite za taa kniga
        cout << "-----TEST pecati-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i<brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i<brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
 
        Kniga k(naslov, avtori, brojAvtori, ocenki, brojOcenki);
        k.pecati();
 
    }
    else if (tip == 3) { //funkcija za presmetka na vkupnata ocenka na knigata
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i<brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i<brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
 
        Kniga k(naslov, avtori, brojAvtori, ocenki, brojOcenki);
        cout << "Vkupna ocenka: " << k.getVkupnaOcenka() << endl;
 
    }
    
    else if (tip == 5) { //funkcija pecati vo OnlajnKniga
        cout << "-----TEST pecati -----" << endl;
        cin >> naslov >> brojAvtori;
        for (int i = 0; i<brojAvtori; i++) {
            cin >> ime >> drzava;
            avtori[i] = Lice(ime, drzava);
        }
        cin >> brojOcenki;
        for (int i = 0; i<brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> url >> brojPristapi >> brojSimnuvanja;
 
        OnlajnKniga ok(naslov, avtori, brojAvtori, ocenki, brojOcenki, url, brojPristapi, brojSimnuvanja);
        ok.pecati();
 
    }
   
 
    else if (tip == 7) { //funkcija prosechnaOcenka
        cout << "-----TEST prosechnaOcenka-----" << endl;
        int k, opt;
        cin >> k;
        Kniga **knigi = new Kniga*[k];
        for (int j = 0; j<k; j++) {
            cin >> opt; //1 kniga 2 onlajnkniga
            cin >> naslov >> brojAvtori;
            for (int i = 0; i<brojAvtori; i++) {
                cin >> ime >> drzava;
                avtori[i] = Lice(ime, drzava);
            }
            cin >> brojOcenki;
            for (int i = 0; i<brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                knigi[j] = new Kniga(naslov, avtori, brojAvtori, ocenki, brojOcenki);
            }
            else {
                cin >> url >> brojPristapi >> brojSimnuvanja;
                knigi[j] = new OnlajnKniga(naslov, avtori, brojAvtori, ocenki, brojOcenki, url, brojPristapi, brojSimnuvanja);
            }
        }
        cin >> ime;
        double prosecna=prosechnaOcenka(ime, knigi, k);
        cout << "Prosecna ocenka e za knigite na " << ime << " e " << prosecna;
        for (int j = 0; j<k; j++) delete knigi[j];
        delete[] knigi;
    }
    
 
 
    return 0;
}

