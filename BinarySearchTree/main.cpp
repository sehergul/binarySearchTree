#include <iostream>
#include<stack>

using namespace std;

struct n{
    int data;
    n *sol=NULL, *sag=NULL;
};

typedef n node;

node* ekle(node *agac, int x){
    if(agac==NULL){ //agac bos ise
        node *root = new node();
        root->sol= root->sag=NULL;
        root->data=x;
        return root;}

    if(agac->data < x)
        agac->sag = ekle(agac->sag, x);
    else
        agac->sol = ekle(agac->sol, x);
    return agac;
}


void inorder(node *agac){
    if(agac==NULL)
        return;
    else{
        inorder(agac->sol);
        cout << agac->data << " ";
        inorder(agac->sag);}
}

void inorderStack(node *agac){
    stack<node*> stack;
    node *curr= agac;

    while(!stack.empty() || curr!=NULL){

        while(curr!=NULL){
            stack.push(curr);
            curr=curr->sol;}

        curr=stack.top();
        stack.pop();
        cout << curr->data << " ";
        curr = curr->sag;
    }
}


void buyuktenKucuge(node *agac){
    if(agac==NULL)
        return;
    else{
        buyuktenKucuge(agac->sag);
        cout << agac->data << " ";
        buyuktenKucuge(agac->sol);}
}

void preorder(node *agac){
    if(agac==NULL)
        return;
    else{
        cout << agac->data << " ";}
        preorder(agac->sol);
        preorder(agac->sag);
}

void postorder(node *agac){
    if(agac==NULL)
        return;
    else{
        postorder(agac->sol);
        postorder(agac->sag);
        cout << agac->data << " ";}
}

bool bul(node *agac, int aranan){
    if(agac==NULL)
        return false;
    if(agac->data==aranan || (bul(agac->sag,aranan))==true || (bul(agac->sol,aranan))==true)
        return true;
    else
        return false;
}

int max(node *agac){
    if(agac==NULL)
        return 0;
    while(agac->sag!=NULL)
        agac = agac->sag;
    return agac->data;
}

int min(node *agac){
    if(agac==NULL)
        return 0;
    while(agac->sol!=NULL)
        agac = agac->sol;
    return agac->data;
}

int count(node *agac){
    if(agac==NULL) return 0;
    return 1 + count(agac->sol) + count(agac->sag);
}

node* sil(node *agac, int x){
    if(agac==NULL) //agac bossa
        return agac;

    if(agac->data == x){
        if(agac->sol == NULL && agac->sag == NULL){ //leaf node ise
            agac=NULL;
            return agac;}


        if(agac->sag!= NULL){ //saginda deger varsa
            agac->data = min(agac->sag); //basa sagdakilerin min'ini getirir
            agac->sag = sil(agac->sag,min(agac->sag));
            return agac;}

        else{ //saginda deger yoksa
            agac->data = max(agac->sol); //basa soldakilerin max'ini getirir
            agac->sol = sil(agac->sol,max(agac->sol));
            return agac;}
    }

    if(agac->data < x) //Silinecek deger sagdaysa
        agac->sag = sil(agac->sag,x);
    else //Silinecek deger soldaysa
        agac->sol = sil(agac->sol,x);
    return agac;

}

int main()
{
    node *agac = NULL;
    cout << "Agac bosken min deger: " << min(agac);
    agac = ekle(agac,12);
    cout << "\n12 sayisi arama sonucu: " <<  bul(agac,12);
    agac = sil(agac,12);
    agac = ekle(agac,12);
    agac = ekle(agac,200);
    agac = ekle(agac,190);
    agac = ekle(agac,213);
    agac = ekle(agac,56);
    agac = ekle(agac,24);
    agac = ekle(agac,18);
    agac = ekle(agac,28);
    cout << "\nKucukten buyuge: "; inorder(agac);
    cout << "\nBuyukten kucuge: "; buyuktenKucuge(agac);
    cout << "\nPostorder: "; postorder(agac);
    cout << "\nPreorder: "; preorder(agac);
    cout << "\n100 sayisi arama sonucu: " <<  bul(agac,100);
    cout << "\n200 sayisi arama sonucu: " <<  bul(agac,200);
    cout << "\nMax: " << max(agac);
    cout << "\nMin: " << min(agac);
    cout << "\nToplam node sayisi: " << count(agac);

    agac = sil(agac,190);
    cout << "\n190 silindikten sonra kucukten buyuge: "; inorder(agac);
    cout << "\n190 silindikten sonra buyukten kucuge: "; buyuktenKucuge(agac);

    cout << "\nStack inorder: "; inorderStack(agac);


    return 0;
}
