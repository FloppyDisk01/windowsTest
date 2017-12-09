/**
 * Polytech Marseille - 163 avenue Luminy
 * 13288 Marseille CEDEX 9
 * ce code peut être librement utilisée, à la condition de l'attribuer à l'auteur en
 * citant son nom. le titulaire de droits restreint cependant son usage aux 
 *utilisations non commerciales (les utilisations commerciales restant soumises à 
 *son autorisation) et son partage doit se faire dans les mêmes conditions.
 *license creative commons (CC-BY-NC-SA)
 */

//@author Filatre Aurélien TP LISTE exo1.c 
//definition de la structure liste et des fcts associées

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

typedef int base_type;

//definition de la structure liste
typedef struct list{
	base_type val;
	struct list *suivant;
}t_maillon, *t_ptr_list;

//fonction de base des listes
t_ptr_list create_empty(void);
int is_empty (t_ptr_list liste);
base_type head (t_ptr_list liste);
t_ptr_list tail (t_ptr_list liste);
t_ptr_list add(base_type elt, t_ptr_list liste);
t_ptr_list addEnd(base_type elt, t_ptr_list liste);
void printList (t_ptr_list);
t_ptr_list createList();
//longueur de liste
int lenList(t_ptr_list l);
int lenList_butIterative(t_ptr_list l);
//copie de liste 
t_ptr_list copyList(t_ptr_list listOrigin);
t_ptr_list copyList_butWithPointer(t_ptr_list listOrigin);
//recherche d'element
t_ptr_list search(int elt, t_ptr_list liste);
//suppression des elements de la liste
t_ptr_list rm(int elt, t_ptr_list liste);
//fonctions d'inversions 
t_ptr_list invListCP(t_ptr_list liste);
t_ptr_list invListCP_butWithPointer(t_ptr_list);
t_ptr_list invList(t_ptr_list liste);
t_ptr_list invList_butWithPointer(t_ptr_list);
//fonctions d'insertion
t_ptr_list insert(base_type X, t_ptr_list listOrigin);
//test et fonctions diverses
int palindrome(t_ptr_list liste);
t_ptr_list merge(t_ptr_list l1, t_ptr_list l2);
t_ptr_list merge_noRep(t_ptr_list l1, t_ptr_list l2);
t_ptr_list prefixSum(t_ptr_list liste);

int main(){
	int valueTest;
	t_ptr_list test, copytest;
	test = createList();
	printf("%i \n", palindrome(test));
	return 0;
}

//fct de base des listes 
//fonction créant liste vide
t_ptr_list create_empty(void){ 
	return( (t_ptr_list)NULL ); 
}

//test vérifiant si la liste est vide
int is_empty (t_ptr_list liste){
	return( liste == (t_ptr_list)NULL ); 
}

//retourne la valeur en tête de liste
base_type head (t_ptr_list liste){
	assert( liste != (t_ptr_list)NULL );
	return( liste->val ); 
}

//renvoie la liste privée de son premier element (retourne la queue de liste)
t_ptr_list tail (t_ptr_list liste){
	assert( liste != (t_ptr_list)NULL );
	return( liste->suivant ); 
}

//ajoute un éléments en début de liste
t_ptr_list add (base_type elt, t_ptr_list liste){
	//création du t_maillon contenant la valeur choisie
	t_ptr_list ptr_auxil;
	ptr_auxil = (t_ptr_list)malloc(sizeof(t_maillon));
	ptr_auxil->val = elt;
	//ajout du t_maillon en début de liste
	ptr_auxil->suivant = liste;
	return( ptr_auxil );
}

//ajout de t_maillon en fin de liste
t_ptr_list addEnd(base_type elt, t_ptr_list liste){
	t_ptr_list l, ll;
	l = liste;
	ll = (t_ptr_list)malloc(sizeof(t_maillon));
	ll->val = elt;
	ll->suivant = (t_ptr_list)NULL;
	while(!is_empty(l->suivant)){
		l = l->suivant;
	}
	l -> suivant = ll;
	
	return liste;
}

//fonctions supérieures
//affichage de liste au format ( a, b, ....)
void printList (t_ptr_list l){
	printf("(");
	do{
		if(l->suivant)printf(" %i,", l->val); //tant qu'il existe un elem à la suite
		else{printf(" %i", l->val);} //dernier element de la liste
		l = tail(l);
	}while(!(is_empty(l)));
	printf(" ) \n");
	
	return;
}

//creation de nouvelle liste
t_ptr_list createList(){
	t_ptr_list newList;
	base_type newItem;
	
	newList = create_empty();
	do{
		printf("entrez le prochain t_maillon : ");
		scanf("%i", &newItem);
		if(newItem >= 0){
			newList = add(newItem, newList);
		}
	}while(newItem >= 0);
	printf("liste creee avec succes \n");
	
	return newList;
}

t_ptr_list createList_butWithPointer(){
	t_ptr_list newList,ll;
	int newItem;
	printf("entrez le prochain t_maillon (valeur <0 pour sortir) : ");
	scanf("%i", &newItem);
	
	if(newItem>=0){
		newList = (t_ptr_list)malloc(sizeof(t_maillon));
		newList->val = newItem;
		ll = newList;
		do{
			printf("Entrez un entier >= 0 : ");
			scanf("%d", &newItem);
			printf("\n");
			if(newItem >= 0) {
				ll->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
				ll = ll->suivant;
				ll->val = newItem;
			}
		} while(newItem >= 0);
	}
	printf("nouvelle liste cree avec succes");
	return newList;
}

//calcul de longueur de liste
int lenList(t_ptr_list l){
	if(is_empty(l)) return 0;
	else{
		return 1 + lenList(tail(l));
	}
}

int lenList_butIterative(t_ptr_list l){
	int compt = 0;
	while(!is_empty(l)){
		compt ++;
		l = l-> suivant;
	}
	return compt;
}

//copie de liste recursive avec fonction 
t_ptr_list copyList(t_ptr_list listOrigin){
	if(is_empty(listOrigin)) return listOrigin;
	else	
		return add(head(listOrigin), copyList(tail(listOrigin)));
}

//copie de liste avec pointeur
t_ptr_list copyList_butWithPointer(t_ptr_list listOrigin){
	t_ptr_list newList;
	t_ptr_list tempList;
	newList = (t_ptr_list) malloc(sizeof(t_maillon));
	tempList = newList;
	//on ajoute a la fin de notre newlist ce que pointe tempList et on fait avancer templist
	while(listOrigin->suivant != (t_ptr_list)NULL){
		tempList->val = listOrigin->val;
		tempList->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
		tempList = tempList->suivant;
		listOrigin = listOrigin->suivant;
	}
	tempList->val = listOrigin->val;
	tempList->suivant =(t_ptr_list)NULL;
	return newList;
}

t_ptr_list search(int elt, t_ptr_list liste){
	//si la liste est vide on retourne -1 code erreur 
	//sinon on continue de parcourir jusqu'a trouver
	if(is_empty(liste)){
		return (t_ptr_list)NULL;
	}
	else if(liste->val == elt){
		return liste;
	}
	else{
		return search(elt, tail(liste));
	}
}

//fonction qui supprime les occurences de l'element dans la liste
t_ptr_list rm(int elt, t_ptr_list liste){
	assert(!is_empty(liste));
	t_ptr_list newList, temp;
	newList = liste;
	while(newList->suivant->suivant != (t_ptr_list)NULL){
		if(newList->suivant->val == elt){
			newList->suivant = newList->suivant->suivant;
			}
		else{
			newList = newList->suivant;
		}
	}
	
	return liste;
}

//inverse de liste en utilisant les fonction, avec recopie
t_ptr_list invListCP(t_ptr_list listOrigin){
	t_ptr_list cp_list_inv;
	cp_list_inv = create_empty();
	while(!is_empty(listOrigin)){
		cp_list_inv = add(head(listOrigin), cp_list_inv);
		listOrigin = tail(listOrigin);
	}
	return cp_list_inv;
}

//inverse de liste en utilisant les pointeurs avec recopie
t_ptr_list invListCP_butWithPointer(t_ptr_list listOrigin){
	t_ptr_list cp_list_inv, cp_list_tmp;
	
	if(listOrigin==(t_ptr_list)NULL || listOrigin->suivant == (t_ptr_list)NULL) return listOrigin;
	
	else{
		cp_list_inv = (t_ptr_list)malloc(sizeof(t_maillon)); 
		cp_list_inv->suivant = (t_ptr_list)NULL;
	
	
		while(listOrigin->suivant != (t_ptr_list)NULL){
			cp_list_inv -> val = listOrigin->val;
			cp_list_tmp = (t_ptr_list)malloc(sizeof(t_maillon));
			cp_list_tmp->suivant = cp_list_inv;
			cp_list_inv = cp_list_tmp;
			listOrigin = listOrigin->suivant;
		}
		cp_list_inv->val = listOrigin->val;
	
		return cp_list_inv;
	}
}

//inverse sans recopie avec fonction
t_ptr_list invList(t_ptr_list liste){
	t_ptr_list inv, temp;
	
	if(is_empty(liste)){
		return liste;
	}
	inv = liste;
	liste = tail(liste);
	inv->suivant = create_empty();
	while(!is_empty(liste)){
		temp = liste;
		liste = tail(liste);
		temp->suivant = inv;
		inv = temp;
	}
	return inv;
}

//inverse la liste avec pointeur sans recopie
t_ptr_list invList_butWithPointer(t_ptr_list liste){
	t_ptr_list temp, inv;
	
	if(liste == (t_ptr_list)NULL){
		return liste;
	}
	
	inv = liste;
	liste = liste->suivant;
	inv->suivant = (t_ptr_list)NULL;
	while(liste != (t_ptr_list)NULL){
		temp = liste;
		liste = liste->suivant;
		temp->suivant = inv;
		inv = temp;
	}
	return inv;
}

//insertion dans liste ordonnée
t_ptr_list insert(base_type X, t_ptr_list listOrigin){
	t_ptr_list node, search;
	//création du t_maillon a inserer
	node = (t_ptr_list)malloc(sizeof(t_maillon));
	node->val = X;
	//recherche du rang ou inserer le t_maillon
	//test si t_maillon doit etre au premier rang
	if(listOrigin->val >= X){
		node->suivant = listOrigin;
		return node;
	}
	//test pour le reste de la liste sinon
	else{
		search = listOrigin;
		while(search->suivant->val <= X){
			search = search->suivant;
		}
		node->suivant = search->suivant;
		search->suivant = node;
	
		return listOrigin;
	}
}

//liste palindrome
int palindrome(t_ptr_list liste){
	int i, n;
	t_ptr_list inv;
	//creation d'une liste inverse pour comparer les valeurs de debut et de fin
	inv = invListCP(liste);
	
	n = lenList_butIterative(liste);
	for(i = 0; i<=(n/2)+1; i++){
		if(inv->val != liste->val){
			return 0;
		}
		else{
			inv = inv->suivant;
			liste = liste->suivant;
		}
	}
	return 1;
}

//fusion de listes
t_ptr_list merge(t_ptr_list l1, t_ptr_list l2){
	t_ptr_list ltemp, newList;
	//retourner liste vide si les deux listes sont vides
	if(is_empty(l1) && is_empty(l2))
		return l1;
	//sinon commencer fusion
	else {
		newList = (t_ptr_list)malloc(sizeof(t_maillon));
		ltemp = newList;
		while(!is_empty(l1) && !is_empty(l2)){
			//test sur les valeurs l1 et l2 pour choisir la valeur a ajouter en premier
			if(l1->val <= l2->val){
				ltemp->val = l1->val;
				l1 = l1->suivant;
			} else {
				ltemp->val = l2->val;
				l2 = l2->suivant;
			}
			ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
			ltemp = ltemp->suivant;
		}
		//ajout du reste d'une liste si les tailles de liste étaient différentes
		while(!is_empty(l1)){
			ltemp->val = l1->val;
			l1 = l1->suivant;
			if(!is_empty(l1)){ 
				ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
				ltemp = ltemp->suivant;
			}
		}
		while(!is_empty(l2)){
			ltemp->val = l2->val;
			l2 = l2->suivant;
			if(!is_empty(l2)){ 
				ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
				ltemp = ltemp->suivant;
			}
		}
		return newList;
	}
}

//fusion de liste sans repetition de termes identiques
t_ptr_list merge_noRep(t_ptr_list l1, t_ptr_list l2){
	t_ptr_list l, ltemp;
	if(is_empty(l1) && is_empty(l2))
		return l1;
	else {
		l = (t_ptr_list)malloc(sizeof(t_maillon));
		ltemp = l;
		if(l1->val < l2->val){
			ltemp->val = l1->val;
			l1 = l1->suivant;
		} else {
			ltemp->val = l2->val;
			l2 = l2->suivant;
		}
		while(!is_empty(l1) && !is_empty(l2)){
			if(l1->val < l2->val){
				// On vérifie que la valeur de la liste finale est différente de la valeur à insérer
				if(ltemp->val != l1->val){
					ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
					ltemp = ltemp->suivant;
					ltemp->val = l1->val;
				}
				l1 = l1->suivant;
			} else {
				if(ltemp->val != l2->val){
					ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
					ltemp = ltemp->suivant;
					ltemp->val = l2->val;
				}
				l2 = l2->suivant;
			}
		}
		while(!is_empty(l1)){
			if(ltemp->val != l1->val){
				ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
				ltemp = ltemp->suivant;
				ltemp->val = l1->val;
			}
			l1 = l1->suivant;

		}
		while(!is_empty(l2)){
			if(ltemp->val != l2->val){
				ltemp->suivant = (t_ptr_list)malloc(sizeof(t_maillon));
				ltemp = ltemp->suivant;
				ltemp->val = l2->val;
			}
			l2 = l2->suivant;
		}
		return l;
	}
}

//calcul de somme préfixe
t_ptr_list prefixSum(t_ptr_list liste){
	t_ptr_list ltemp;
	if(is_empty(liste))
		return liste;
	else{
		ltemp = liste;
		while(!is_empty(ltemp->suivant)){
			ltemp->suivant->val = ltemp->val + ltemp->suivant->val;
			ltemp = ltemp->suivant;
		}
		return liste;
	}
}