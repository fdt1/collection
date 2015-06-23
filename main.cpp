/*
Ce qui manque:
  2. champs lexical SQL : select, when, à la place de change et filter?
  4. constructeur sur différent container: boost, stl (map), collection (cf. idées de 2012)
  4.bis fonction externe permettant de construire un objet à partir d'un C-array et d'une taille : en fait c'est mieux avec deux pointeurs begin et end!
  5. complèter les traits (cf. idées de 2013) : hériter de std::iterator!
  6. opérations mineures: first(), last(), +=, << ...
  6. union et intersection d'une Query et Collection
 11. Counter et comparaison avec un entier
 12. Pair méthodes à complèter
 13.bis exension de layer/scale/iterator avec constructeurs spéciaux : Tree/Forest, Node/Gaph, Matrix/line/column/site(case,cross)
 1. vérifier la cohérence du reverse partour et même sur le std::vector !!!!
 2. généraliser le inheritance au flow et query et faire un test plus conséquent. appliquer le inheritance au chainedStorage.
 14. fixer le ChainStorage avec 2 modifiers simultanés.
 15. régler ce problème de getConstFirst()
 16. changer en hash_map le unique
 17. remplacer le modifier par std::function
 18. remplacer Pair par tuple
 19. insérer une macro ou un élément intermédiaire pour hériter d'une collection
 0. supprimmer le content si UnorderedList et OrderedList / UnorderedMap et OrderedMap (cf. le 14/01/2015)
 0.bis constructeur move sur container.
 0.ter ambiguité sur constructeur si pas de type sur le container! (cf. le 11/01/2015)
 0.4 faire un classe Prime pour construire l'objet! (cf. 12/01/2015)
 0.5 utiliser les variadic templates ? ---> Non compatible!
 30. créer les Graphs, TREE et DAG et Matrix. Comment ajouter les méthodes d'insertion?  (cf. le 13/01/2015)
 30.bis Peut-on le généraliser pour N axes? OUI (cf. exemples de matrice du 10/01/2015)
 32. comment utiliser les graphes dans le dualStorage ?
 34. ajouter dans Collection::change_element1(std::function<T1 (T1)>) Collection::change_element1(std::function<T1 (T1, T2)>) Collection::change_elements(std::function<tuple(T1, T2) (T1, T2)>)
 35. faire content(bridge&)
 39.a. Irange : IUnorderedlist<IUnorderedlst>
 39.b. IMatrix : Ilist<Ilist>  pas d'insertion/erase juste le setter.
 40. liste d'adjacence : range ->constructeur à deux paramètres
 41.a. tester le constructeur avec deux paramètres begin + end
 41.b. tester le constructeur avec deux paramètres void* + size, n'est-ce pas la même chose que begin et end ? begin->begin+size
 44. dans lazy5 : 
 44.a implémenter le reverse;
 44.b le filter reversible (permet le unique); 
 44.c le functor reversible (permet le swap) 
 44.d la comparaison de contenu (optimisation avec la taille)
 44.e la comparaison de taille parcours partiel ou demande de la taille?
 44.f le dynamic_cast  (avec le functor reversible)? le static_cast ?
 44.g la concaténation
 44.f le flatten
 44.h le bool exist()
 44.i begin() et end() et collection()
 45. trouver comment appliquer une collection à un container i.e changer le container d'une collection : setNestedBridge(IList<>*) je crois que ce n'est pas possible à cause du apply!
 46. trouver une astuce pour ne pas dupliquer le code entre prime<vector> , prime<vector&> et prime<const vector&>
 50. tenter un héritage unknown -> element (attribute0) -> flow (++) -> iterator (colmlection) -> query -> flow
 02.a ATTENTION: règler le problème de (iterator + 5)->attribute0()  : en fait c'est une interface qui est renvoyée!!
 02.b comment faire une méthode move sans copy : clone et forward et apply !!!
 52. comment faire un value() qui soit operator[] qui retourne un non const ref ? plutôt retourner un element avec redefinition de loperator = ? est que le element doit avoir une key?
 53. tester les bounds!
 55. TODO: remplacer value par operator[] const
 56. l'operateur[] non-const retourne un content qui a l'opérateur =() définit!
 57. pouvoir redéfinir le new et shared_ptr allocator !
 58. pouvoir choisir un prime<vector> avec ou sans constant et reference! Est-ce que le cast explicit est bon dans le forward du constructeur (std::vector) ou (std::vector&) ou (const std::vector&)?
 59. problème d'interface lorsque l'on wrappe des set : index -> value
 60. faut-il coder les opérator= () avec move ? --> perfect forward!!!!!!
 65. que doit on retourner lors d'un erase() ?
 65. Implémenter une pair?
 66. ne pas oublier le resize et le clear pour une orderedList
 67. résoudre le problème de nommage de apply2()
 68. pb de typage des interfaces lors d'un apply() simple: la list doit être dégradée en query
 69. lors d'un apply2() il manque l'opérateur par move? si la fonction reverse prend en argument un &&
 70. se poser la question: quand je fais une assignation, est-ce que je veux la nouvelle valeur? idem du erase sur l'ancienne valeur? Pourquoi ne pas travailer sur un iterator alors?
 71. pb sur surcharge des value(). il faut toutes les réécrire à chaque fois. pourquoi pas faire lvalue() et rvalue(). idem pour rkey() et lkey()?
 72. faire la fonction filter
 73. faire une opération collection<element<X,Y>>::transpose() -> element<collection<X,Y>>
 74. le flatten et la concaténation doivent supporter les list et map lorsque la clef est un numérique autre solution faire un downgraded_type. A voir ...
 75. faire un specialization sur bridge<template_generic> pour factoriser certaines méthodes statiques! tel que le apply et le swap
 76. matrix<x,y,size_t rank> : list<matrix<x,y,rank-1>  matrix<x,y, 0> : element<x,y>
 77. matrix_iterator::up/down
 78. matrix : range ---> le range::erase peut éliminer la colonne et la ligne de la matrice.
 79. remplacer quand c'est possible std::is_base_of par has_all_methods_of

le 14/01/2015, OrderedList/UnorderedList (list et map)
OrderedList<X>::insert(X&)
OrderedList<X, Y>::insert(X&, Y&) 
UnorderedList<X>::push_back(X&)
UnorderedList<X, Y>::push_back(X&, Y&) 

le 13/01/2015, Graph, Tree et Matrix 
Tree -> DAG -> Graph -> Scale
DAG::flattenAll() -> DAG
DAG::unflatAll() -> DAG
Graph::push_back(Graph)
Case -> Row/Column -> Matrix -> Matrix3D -> MatrixN -> Scale
MatrixN::forward_by_row()->MatrixN{MatrixbyRow0, MatrixbyRow1, MatrixbyRow2}
MatrixN::forward_by_column()->MatrixN{MatrixbyCol0, Matrixbycol1}
Matrix::forward_by_row()->Matrix{Row0, Row1, Row2}
Matrix::forward_by_column()->Matrix{Col0, col1}
Matrix::push_back(Row/Column)
Matrix3D::push_back(Matrix)
Case{0,0}::up()->Case{1,0}
Case{1,1}::down()->Case{0,1}

le 12/01/2015, Prime
  Prime<int,int, vector> : IUnorderedMap
  Prime<int, void, vector> : IUnorderedList


le 11/01/2015, sur le constructeur
 Collection(collection& c) { _shared = c; }
 template<X,Y> Collection(ICollection<X,Y>& c) { _shared= new static_cast<Collection>(c); }
 Collection(Icollection<X,Y>* c) {_shared = c;}
 template<container> Collection(container&& c) { _shared = new Prime(c); }
 template<container> Collection(const container& c) { _shared = new Prime(c); } // différence entre ref et copie ?

le 10/01/2015, layer et Scale (ou Scheme ou encore Layer et LayerIterator) 
1 scale représente :
  - des étages ou un DAG
  - une matrice N ou une hiérarchie d'instance
1 layer représente un itérateur sur scale
 Scale::begin()/end() -> Layer
 Layer::scale() -> Scale
 Scale::forward() -> Scale Est-ce que l'on doit le nommer Scale::operator++ ?
 Scale::backward() -> Scale
 Layer::operator++ -> Layer
 Layer::operator* -> Scale
 Scale::collection() -> collection<T>
 Scale::operator+(Scale& s) -> Scale
Exemple sur graphe:
 Scale{A,B,C}::begin()->Scale{A},Scale{B},Scale{C}
 Scale{A,B,C}::forward()->Scale{A.a, A.b, AB.c, C.a, C.b}
 Scale{A.a, A.b, AB.c, C.a, C.b}::begin()->Layer{Scale{A.a}},Layer{Scale{A.b}},Scale{AB.c},Layer{Scale{C.a}},Layer{Scale{C.b}} 
 Scale{A}::begin()->Layer{{Scale{A}}
 Scale{A}::forward()->Scale{A.a, A.b, AB.c}  Doit-on le nommer flat pour forward et unflat ou split unsplit?
 Scale{A.a, A.b}::backward()->Scale{A}
 Scale{A.a}::backward()->Scale{A}
 Scale{AB.c}::backward()->Scale{A, B}
 Scale{A,B,C}::backward()->Scale{}
 Scale{A, C.a}::forward()->Scale{A.a, A.b, AB.c, C.a.a, C.a.b}
Exemple sur une matrice 2D:
 Scale{matrice2D}::begin()->Layer{Scale{matrice2D}}
 Scale{matrice2D}::forward()->Scale{Row0, Row1, Row2}
 Scale{Row0}::forward()->Scale{case0.0, case0.1}
 Scale{case0.0, case0.1}::backward()->Scale{Row0}
 Scale{case0.0}::backward()->Scale{Row0}
 Scale{case0.0, case1.0}::backward()->Scale{Row0, Row1}
 Scale{case0.0, Row1}::backward()->Scale{Row0, matrice2D}

   

 
 le 20/06/2014, La transformation vector<vector<int>> en collection<collection<int>>, c'est:
 std::map<I,std::vector<T>> _key_to_value_map;
 Flow<I, const std::vector<T>&, const std::map<I,std::vector<T>>&> collection(_key_to_value_map);
 Flow<I, Collection<const T&, void, const std::vector<T>&>, const std::map<I,std::vector<T>>& > new_collection = collection;


 
 En 2013, idée de traits dans itérateur et predicate de boost
 http://www.boost.org/doc/libs/1_44_0/libs/iterator/doc/filter_iterator.html
 http://www.boost.org/doc/libs/1_44_0/libs/iterator/doc/new-iter-concepts.html
 http://msdn.microsoft.com/fr-fr/library/ms132397(v=VS.80).aspx
 
 En 2012, idées pour container universel :
 - adjacent list (2 dimensions)
 - xtrist
 - queue
 - stack
 - set/map
 - multiset/multimap
 - hash_set et hash_map
 - simple slist
 - c-array
 - list/vector
 - string
 - (x)tree
 - boost matrice (2 dimensions)
 - hash table
 
   

/* ******* la doc **************** 
 
 A -  procrastination
 deux exemples : parcours en profondeur et en largeur.
 
 avantages: économie de mémoire, gain de temps si l'on ne veut pas le résultat dans son ensemble
 (cas d'une recherche d'un unique élèment dans une liste, comparaison de taille, 
 mauvaise utilisation de l'interface, utilisateur externe changeant d'avis) 
 si on excepte le coût de l'indirection des tables virtuelles.
 
 
 deux cas où la transformation en collection n'est pas avantageuse : 
   si on retourne une référence sur un containeur déjà existant, ni gain mémoire, ni gain temporel.
   si on consulte plusieurs fois la collection, plutôt que de conserver dans un container intermédiaire.

 B - uniformité de l'API avec collections
 les méthodes sont identiques.
 
 C - richesse de l'API avec collections
facilité de création d'aPI dédiée à partir d'API existante.
 
 D - ouverture du fonctionnement
   Tout container est à priori compatible en importation et en exportation : l'utilisateur doit fournir son adapter
   Tout modifier de collection est possible : l'utilisateur peut en rajouter
   Tout nouvelle collection est possible : à lui de construire le jeux d'interfaces,
     de bridge de fabric et de collection dédiés
 
 E - memory leak safe
 Whatever the method you choose : instanciate 
 
 F - quick and postponed copy of objects
 */

// FIXME : TODO: disable NO_ERROR_CONCAT
// #define NO_ERROR_CONCAT

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include "lazy4_Flow.h"
#include "lazy4_Query.h"
#include "lazy4_Iterator.h"
#include "lazy4_Iterator_std_vector.h"
#include "lazy4_Iterator_std_map.h"
#include "lazy4_Flow_std_vector.h"
#include "lazy4_Flow_std_map.h"
#include "lazy4_Flow_std_tr1_unordered_map.h"
#include "lazy4_Collection_std_vector.h"
#include "lazy4_Collection_std_map.h"
#include "lazy4_Query_std_map.h"
#include "lazy4_Query_std_vector.h"
#include "lazy4_Query_std_tr1_unordered_map.h"
#include "lazy4_Modifier.h"
#include "lazy4_Pair.h"
#include "lazy4_List.h"
#include "lazy4_Index.h"

#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_internal_IAssociativeStorage.h"
#include "lazy4_internal_ISharedStorage.h"
#include "lazy4_internal_SharedStorage.h"
#include "lazy4_internal_KeyStorage.h"
#include "lazy4_internal_SingleStorage.h"
#include "lazy4_internal_CollectionStorage.h"
#include "lazy4_internal_DualStorage.h"
#include "lazy4_internal_ChainStorage.h"

#include "lazy5_flow.h"


struct B;

struct X {
	virtual void s(){} 
	virtual bool operator== (const X& x) const { return true; }
	B* func_name(std::vector<X*>) {
		return NULL;
	}
	B* func_name2() const{
		return NULL;
	}
	B* func_name3() {
		return NULL;
	}
};

struct Y {
	virtual void t(){} 
};

struct Z {
	void u(){} 
};

struct B : public X, public Y {
	virtual void z(){} 
};

struct C : public X {
	virtual void z(){} 
	
};

struct D : public Z {
	virtual void z(){} 
	virtual void b(int){} 
	void a(){} 
};

 
static B* func_name( X* const& t, std::vector<X*>) {
	return NULL;
}

struct Cast1{
	B* operator() (X* const&) const { return NULL; }
};
struct Cast2{
	B* operator() ( X*) const { return NULL; }
};
struct Cast3{
	B* operator() (const X*) const { return NULL; }
};
struct Cast4{
	B* operator() (X* &) const { return NULL; }
};
struct Cast6{
	B* operator() (X* const) { return NULL; }
};

struct Cast1Vec{
	B* operator() (X* const&, std::vector<X*>) const { return NULL; }
};
struct Cast2Vec{
	B* operator() (X* , std::vector<X*>&) const { return NULL; }
};
struct Cast3Vec{
	B* operator() (const X*, const std::vector<X*>&) const { return NULL; }
};
struct Cast4Vec{
	B* operator() (X* &, const std::vector<X*>&) const { return NULL; }
};
struct Cast5Vec{
	B* operator() (X* const, const std::vector<X*>) const { return NULL; }
};
struct Cast6Vec{
	B* operator() (X* const, const std::vector<X*>) { return NULL; }
};

class MyCollectionType :public lazy4::Collection<int, void, std::vector<int> > {
	typedef lazy4::Collection<int, void, std::vector<int> > Collection;
public:
	//! default constructor
	MyCollectionType() : Collection() {}

	//! constructor with a container
	MyCollectionType(Collection::parameter_container_type container) : Collection(container) {}

	//! internal constructor
	template <typename Implementation>
	MyCollectionType(Implementation* implementation) : Collection(implementation) {}	
	
	
};

struct inherit1 {
	std::shared_ptr<B*> foo() { return NULL; }
};

struct inherit2:public inherit1 {
	std::shared_ptr<X*> foo() { return NULL; }
};



void myRefRef(const long& x) {}
void myRefRef(long&& x) {}

int main (int argc, char * const argv[]) {
#if 0
	{
	int x=0;
	int& y=x;
	int&& z=std::move(x);
	myRefRef(x);
	myRefRef(y);
	myRefRef(z);
	myRefRef(x);
	myRefRef(y);
	myRefRef(z);

	}
#endif

#if 0
	std::cout << "test of lazy 4"<<std::endl;
	{
		std::cout << "compile Flow with std::vector"<<std::endl;
		std::vector<B*> myVecB;
		std::vector<int> myVec;
		std::vector<int>& myVecRef = myVec;
		const std::vector<int>& myVecConstRef = myVec;
		const std::vector<int> myVecConst;

		{
			lazy4::Flow<X*, void, std::vector<X*> > myX;
			lazy4::Flow<const B*, void, std::vector<B*> > myB_const;
			lazy4::Flow<B*, void, std::vector<B*> > myB;
			lazy4::Flow<C*, void, std::vector<C*> > myC;
			lazy4::Flow<B*, void, void > myB2(myX);
			lazy4::Flow<X*, void, void > myX2_const(myB_const);
			lazy4::Flow<const X*, void, void > myX3_const(myB_const);
			lazy4::Flow<const B*, void, void > myB3_const(myB);
			lazy4::Flow<const X*, void, void > myX4_const(myB);
			lazy4::Flow<X*, void, void > myX2(myC);
			lazy4::Flow<Z*, void, void > myZ(myC);
			lazy4::Flow<int, B*, std::vector<B*> > myBindexed(myVecB);
		}		
		{
			lazy4::Flow<int, void, std::vector<int> > myInt;
			lazy4::Flow<int&, void, std::vector<int> > myIntRef;
			lazy4::Flow<const int&, void, std::vector<int> > myIntConstRef;
			lazy4::Flow<const int, void, std::vector<int> > myIntConst;
			lazy4::Flow<const int, void, std::vector<int> > myIntConst2(myIntConst);
			lazy4::Flow<const int, void, std::vector<int> > myIntConst3(myInt);
			lazy4::Flow<void, void, void > myInt2(myInt);
			myInt2 = lazy4::Flow<void, void, void >(myInt);
		}
		{
			lazy4::Flow<int, void, std::vector<int>& > myInt;
			lazy4::Flow<int&, void, std::vector<int>& > myIntRef;
			lazy4::Flow<const int&, void, std::vector<int>& > myIntConstRef;
			lazy4::Flow<const int, void, std::vector<int>& > myIntConst;
		}
		{
			lazy4::Flow<int, void, const std::vector<int> > myInt;
			//lazy4::Flow<int&, void, const std::vector<int> > myIntRef;
			lazy4::Flow<const int&, void, const std::vector<int> > myIntConstRef;
			lazy4::Flow<const int, void, const std::vector<int> > myIntConst;
		}
		{
			lazy4::Flow<int, void, const std::vector<int>& > myInt;
			//lazy4::Flow<int&, void, const std::vector<int>& > myIntRef;
			lazy4::Flow<const int&, void, const std::vector<int>& > myIntConstRef;
			lazy4::Flow<const int, void, const std::vector<int>& > myIntConst;
		}
		
		// myVec
		{
			lazy4::Flow<int, void, std::vector<int> > myInt(myVec);
			lazy4::Flow<int&, void, std::vector<int> > myIntRef(myVec);
			lazy4::Flow<const int&, void, std::vector<int> > myIntConstRef(myVec);
			lazy4::Flow<const int, void, std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Flow<int, void, std::vector<int>& > myInt(myVec);
			lazy4::Flow<int&, void, std::vector<int>& > myIntRef(myVec);
			lazy4::Flow<const int&, void, std::vector<int>& > myIntConstRef(myVec);
			lazy4::Flow<const int, void, std::vector<int>& > myIntConst(myVec);
		}
		{
			lazy4::Flow<int, void, const std::vector<int> > myInt(myVec);
			//lazy4::Flow<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Flow<const int&, void, const std::vector<int> > myIntConstRef(myVec);
			lazy4::Flow<const int, void, const std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Flow<int, void, const std::vector<int>& > myInt(myVec);
			//lazy4::Flow<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Flow<const int&, void, const std::vector<int>& > myIntConstRef(myVec);
			lazy4::Flow<const int, void, const std::vector<int>& > myIntConst(myVec);
		}
		
		// myVecConst
		{
			lazy4::Flow<int, void, std::vector<int> > myInt(myVecConst);
			lazy4::Flow<int&, void, std::vector<int> > myIntRef(myVecConst);
			lazy4::Flow<const int&, void, std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Flow<const int, void, std::vector<int> > myIntConst(myVecConst);
		}
		{
			//lazy4::Flow<int, void, std::vector<int>& > myInt(myVecConst);
			//lazy4::Flow<int&, void, std::vector<int>& > myIntRef(myVecConst);
			//lazy4::Flow<const int&, void, std::vector<int>& > myIntConstRef(myVecConst);
			//lazy4::Flow<const int, void, std::vector<int>& > myIntConst(myVecConst);
		}
		{
			lazy4::Flow<int, void, const std::vector<int> > myInt(myVecConst);
			//lazy4::Flow<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Flow<const int&, void, const std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Flow<const int, void, const std::vector<int> > myIntConst(myVecConst);
		}
		{
			lazy4::Flow<int, void, const std::vector<int>& > myInt(myVecConst);
			//lazy4::Flow<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Flow<const int&, void, const std::vector<int>& > myIntConstRef(myVecConst);
			lazy4::Flow<const int, void, const std::vector<int>& > myIntConst(myVecConst);
		}
		
		// myVecRef
		{
			lazy4::Flow<int, void, std::vector<int> > myInt(myVecRef);
			lazy4::Flow<int&, void, std::vector<int> > myIntRef(myVecRef);
			lazy4::Flow<const int&, void, std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Flow<const int, void, std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Flow<int, void, std::vector<int>& > myInt(myVecRef);
			lazy4::Flow<int&, void, std::vector<int>& > myIntRef(myVecRef);
			lazy4::Flow<const int&, void, std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Flow<const int, void, std::vector<int>& > myIntConst(myVecRef);
		}
		{
			lazy4::Flow<int, void, const std::vector<int> > myInt(myVecRef);
			//lazy4::Flow<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Flow<const int&, void, const std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Flow<const int, void, const std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Flow<int, void, const std::vector<int>& > myInt(myVecRef);
			//lazy4::Flow<int&, void, const std::vector<int>& > myIntRef(myVecRef);
			lazy4::Flow<const int&, void, const std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Flow<const int, void, const std::vector<int>& > myIntConst(myVecRef);
		}
		
		// myVecConstRef
		{
			lazy4::Flow<int, void, std::vector<int> > myInt(myVecConstRef);
			lazy4::Flow<int&, void, std::vector<int> > myIntRef(myVecConstRef);
			lazy4::Flow<const int&, void, std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Flow<const int, void, std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			//lazy4::Flow<int, void, std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Flow<int&, void, std::vector<int>& > myIntRef(myVecConstRef);
			//lazy4::Flow<const int&, void, std::vector<int>& > myIntConstRef(myVecConstRef);
			//lazy4::Flow<const int, void, std::vector<int>& > myIntConst(myVecConstRef);
		}
		{
			lazy4::Flow<int, void, const std::vector<int> > myInt(myVecConstRef);
			//lazy4::Flow<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Flow<const int&, void, const std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Flow<const int, void, const std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			lazy4::Flow<int, void, const std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Flow<int&, void, const std::vector<int>& > myIntRef(myVecConstRef);
			lazy4::Flow<const int&, void, const std::vector<int>& > myIntConstRef(myVecConstRef);
			lazy4::Flow<const int, void, const std::vector<int>& > myIntConst(myVecConstRef);
		}
		
	}
	{
		std::cout << "compile Iterator with std::vector"<<std::endl;
		std::vector<int> myVec;
		std::vector<int>& myVecRef = myVec;
		const std::vector<int>& myVecConstRef = myVec;
		const std::vector<int> myVecConst;
		std::vector<B*> myVecB;
		{
			lazy4::Iterator<X*, void, std::vector<X*> > myX;
			lazy4::Iterator<const B*, void, std::vector<B*> > myB_const;
			lazy4::Iterator<B*, void, std::vector<B*> > myB;
			lazy4::Iterator<C*, void, std::vector<C*> > myC;
			lazy4::Iterator<B*, void, void > myB2(myX);
			lazy4::Iterator<X*, void, void > myX2_const(myB_const);
			lazy4::Iterator<const X*, void, void > myX3_const(myB_const);
			lazy4::Iterator<const B*, void, void > myB3_const(myB);
			lazy4::Iterator<const X*, void, void > myX4_const(myB);
			lazy4::Iterator<X*, void, void > myX2(myC);
			lazy4::Iterator<Z*, void, void > myZ(myC);
			lazy4::Iterator<int, B*, std::vector<B*> > myBindexed(myVecB);
		}		
		
		{
			lazy4::Iterator<int, void, std::vector<int> > myInt;
			lazy4::Iterator<int&, void, std::vector<int> > myIntRef;
			lazy4::Iterator<const int&, void, std::vector<int> > myIntConstRef;
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst;
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst2(myIntConst);
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst3(myInt);
			lazy4::Iterator<void, void, void > myInt2(myInt);
			myInt2 = lazy4::Iterator<void, void, void >(myInt);
		}
		{
			lazy4::Iterator<int, void, std::vector<int>& > myInt;
			lazy4::Iterator<int&, void, std::vector<int>& > myIntRef;
			lazy4::Iterator<const int&, void, std::vector<int>& > myIntConstRef;
			lazy4::Iterator<const int, void, std::vector<int>& > myIntConst;
		}
		{
			lazy4::Iterator<int, void, const std::vector<int> > myInt;
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef;
			lazy4::Iterator<const int&, void, const std::vector<int> > myIntConstRef;
			lazy4::Iterator<const int, void, const std::vector<int> > myIntConst;
		}
		{
			lazy4::Iterator<int, void, const std::vector<int>& > myInt;
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef;
			lazy4::Iterator<const int&, void, const std::vector<int>& > myIntConstRef;
			lazy4::Iterator<const int, void, const std::vector<int>& > myIntConst;
		}

		// myVec
		{
			lazy4::Iterator<int, void, std::vector<int> > myInt(myVec);
			lazy4::Iterator<int&, void, std::vector<int> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, std::vector<int> > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, std::vector<int>& > myInt(myVec);
			lazy4::Iterator<int&, void, std::vector<int>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, std::vector<int>& > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, std::vector<int>& > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int> > myInt(myVec);
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::vector<int> > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, const std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int>& > myInt(myVec);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::vector<int>& > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, const std::vector<int>& > myIntConst(myVec);
		}
		
		// myVecConst
		{
			lazy4::Iterator<int, void, std::vector<int> > myInt(myVecConst);
			lazy4::Iterator<int&, void, std::vector<int> > myIntRef(myVecConst);
			lazy4::Iterator<const int&, void, std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst(myVecConst);
		}
		{
			//lazy4::Iterator<int, void, std::vector<int>& > myInt(myVecConst);
			//lazy4::Iterator<int&, void, std::vector<int>& > myIntRef(myVecConst);
			//lazy4::Iterator<const int&, void, std::vector<int>& > myIntConstRef(myVecConst);
			//lazy4::Iterator<const int, void, std::vector<int>& > myIntConst(myVecConst);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int> > myInt(myVecConst);
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, const std::vector<int> > myIntConst(myVecConst);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int>& > myInt(myVecConst);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::vector<int>& > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, const std::vector<int>& > myIntConst(myVecConst);
		}
		
		// myVecRef
		{
			lazy4::Iterator<int, void, std::vector<int> > myInt(myVecRef);
			lazy4::Iterator<int&, void, std::vector<int> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, std::vector<int>& > myInt(myVecRef);
			lazy4::Iterator<int&, void, std::vector<int>& > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, std::vector<int>& > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int> > myInt(myVecRef);
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, const std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int>& > myInt(myVecRef);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, const std::vector<int>& > myIntConst(myVecRef);
		}
		
		// myVecConstRef
		{
			lazy4::Iterator<int, void, std::vector<int> > myInt(myVecConstRef);
			lazy4::Iterator<int&, void, std::vector<int> > myIntRef(myVecConstRef);
			lazy4::Iterator<const int&, void, std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			//lazy4::Iterator<int, void, std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, std::vector<int>& > myIntRef(myVecConstRef);
			//lazy4::Iterator<const int&, void, std::vector<int>& > myIntConstRef(myVecConstRef);
			//lazy4::Iterator<const int, void, std::vector<int>& > myIntConst(myVecConstRef);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int> > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, const std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			lazy4::Iterator<int, void, const std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVecConstRef);
			lazy4::Iterator<const int&, void, const std::vector<int>& > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, const std::vector<int>& > myIntConst(myVecConstRef);
		}
		
	}
	{
		std::cout << "compile Collection with std::vector"<<std::endl;
		std::vector<int> myVec;
		std::vector<int>& myVecRef = myVec;
		const std::vector<int>& myVecConstRef = myVec;
		const std::vector<int> myVecConst;
		std::vector<B*> myVecB;
		{
			lazy4::Collection<X*, void, std::vector<X*> > myX;
			lazy4::Collection<B*, void, std::vector<B*> > myB;
			lazy4::Collection<C*, void, std::vector<C*> > myC;
			lazy4::Collection<int, B*, std::vector<B*> > myBindexed(myVecB);
			lazy4::Collection<B*, void, void > myB2(myX);
			lazy4::Collection<X*, void, void > myX2(myC);
			//lazy4::Collection<Z*, void, void > myZ(myC);
		}		
		{
			lazy4::Collection<int, void, std::vector<int> > myInt;
			lazy4::Collection<int&, void, std::vector<int> > myIntRef;
			lazy4::Collection<const int&, void, std::vector<int> > myIntConstRef;
			lazy4::Collection<const int, void, std::vector<int> > myIntConst;
			lazy4::Collection<const int, void, std::vector<int> > myIntConst2(myIntConst);
			lazy4::Collection<const int, void, std::vector<int> > myIntConst3(myInt);
			lazy4::Collection<void, void, void > myInt2(myInt);
			myInt2 = lazy4::Collection<void, void, void >(myInt);
		}
		{
			lazy4::Collection<int, void, std::vector<int>& > myInt;
			lazy4::Collection<int&, void, std::vector<int>& > myIntRef;
			lazy4::Collection<const int&, void, std::vector<int>& > myIntConstRef;
			lazy4::Collection<const int, void, std::vector<int>& > myIntConst;
		}
		{
			lazy4::Collection<int, void, const std::vector<int> > myInt;
			//lazy4::Collection<int&, void, const std::vector<int> > myIntRef;
			lazy4::Collection<const int&, void, const std::vector<int> > myIntConstRef;
			lazy4::Collection<const int, void, const std::vector<int> > myIntConst;
		}
		{
			lazy4::Collection<int, void, const std::vector<int>& > myInt;
			//lazy4::Collection<int&, void, const std::vector<int>& > myIntRef;
			lazy4::Collection<const int&, void, const std::vector<int>& > myIntConstRef;
			lazy4::Collection<const int, void, const std::vector<int>& > myIntConst;
		}
		
		// myVec
		{
			lazy4::Collection<int, void, std::vector<int> > myInt(myVec);
			lazy4::Collection<int&, void, std::vector<int> > myIntRef(myVec);
			lazy4::Collection<const int&, void, std::vector<int> > myIntConstRef(myVec);
			lazy4::Collection<const int, void, std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Collection<int, void, std::vector<int>& > myInt(myVec);
			lazy4::Collection<int&, void, std::vector<int>& > myIntRef(myVec);
			lazy4::Collection<const int&, void, std::vector<int>& > myIntConstRef(myVec);
			lazy4::Collection<const int, void, std::vector<int>& > myIntConst(myVec);
		}
		{
			lazy4::Collection<int, void, const std::vector<int> > myInt(myVec);
			//lazy4::Collection<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Collection<const int&, void, const std::vector<int> > myIntConstRef(myVec);
			lazy4::Collection<const int, void, const std::vector<int> > myIntConst(myVec);
		}
		{
			lazy4::Collection<int, void, const std::vector<int>& > myInt(myVec);
			//lazy4::Collection<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Collection<const int&, void, const std::vector<int>& > myIntConstRef(myVec);
			lazy4::Collection<const int, void, const std::vector<int>& > myIntConst(myVec);
		}
		
		// myVecConst
		{
			lazy4::Collection<int, void, std::vector<int> > myInt(myVecConst);
			lazy4::Collection<int&, void, std::vector<int> > myIntRef(myVecConst);
			lazy4::Collection<const int&, void, std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Collection<const int, void, std::vector<int> > myIntConst(myVecConst);
		}
		{
			//lazy4::Collection<int, void, std::vector<int>& > myInt(myVecConst);
			//lazy4::Collection<int&, void, std::vector<int>& > myIntRef(myVecConst);
			//lazy4::Collection<const int&, void, std::vector<int>& > myIntConstRef(myVecConst);
			//lazy4::Collection<const int, void, std::vector<int>& > myIntConst(myVecConst);
		}
		{
			lazy4::Collection<int, void, const std::vector<int> > myInt(myVecConst);
			//lazy4::Collection<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Collection<const int&, void, const std::vector<int> > myIntConstRef(myVecConst);
			lazy4::Collection<const int, void, const std::vector<int> > myIntConst(myVecConst);
		}
		{
			lazy4::Collection<int, void, const std::vector<int>& > myInt(myVecConst);
			//lazy4::Collection<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Collection<const int&, void, const std::vector<int>& > myIntConstRef(myVecConst);
			lazy4::Collection<const int, void, const std::vector<int>& > myIntConst(myVecConst);
		}
		
		// myVecRef
		{
			lazy4::Collection<int, void, std::vector<int> > myInt(myVecRef);
			lazy4::Collection<int&, void, std::vector<int> > myIntRef(myVecRef);
			lazy4::Collection<const int&, void, std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Collection<const int, void, std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Collection<int, void, std::vector<int>& > myInt(myVecRef);
			lazy4::Collection<int&, void, std::vector<int>& > myIntRef(myVecRef);
			lazy4::Collection<const int&, void, std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Collection<const int, void, std::vector<int>& > myIntConst(myVecRef);
		}
		{
			lazy4::Collection<int, void, const std::vector<int> > myInt(myVecRef);
			//lazy4::Collection<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Collection<const int&, void, const std::vector<int> > myIntConstRef(myVecRef);
			lazy4::Collection<const int, void, const std::vector<int> > myIntConst(myVecRef);
		}
		{
			lazy4::Collection<int, void, const std::vector<int>& > myInt(myVecRef);
			//lazy4::Collection<int&, void, const std::vector<int>& > myIntRef(myVecRef);
			lazy4::Collection<const int&, void, const std::vector<int>& > myIntConstRef(myVecRef);
			lazy4::Collection<const int, void, const std::vector<int>& > myIntConst(myVecRef);
		}
		
		// myVecConstRef
		{
			lazy4::Collection<int, void, std::vector<int> > myInt(myVecConstRef);
			lazy4::Collection<int&, void, std::vector<int> > myIntRef(myVecConstRef);
			lazy4::Collection<const int&, void, std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Collection<const int, void, std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			//lazy4::Collection<int, void, std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Collection<int&, void, std::vector<int>& > myIntRef(myVecConstRef);
			//lazy4::Collection<const int&, void, std::vector<int>& > myIntConstRef(myVecConstRef);
			//lazy4::Collection<const int, void, std::vector<int>& > myIntConst(myVecConstRef);
		}
		{
			lazy4::Collection<int, void, const std::vector<int> > myInt(myVecConstRef);
			//lazy4::Collection<int&, void, const std::vector<int> > myIntRef(myVecRef);
			lazy4::Collection<const int&, void, const std::vector<int> > myIntConstRef(myVecConstRef);
			lazy4::Collection<const int, void, const std::vector<int> > myIntConst(myVecConstRef);
		}
		{
			lazy4::Collection<int, void, const std::vector<int>& > myInt(myVecConstRef);
			//lazy4::Collection<int&, void, const std::vector<int>& > myIntRef(myVecConstRef);
			lazy4::Collection<const int&, void, const std::vector<int>& > myIntConstRef(myVecConstRef);
			lazy4::Collection<const int, void, const std::vector<int>& > myIntConst(myVecConstRef);
		}
	}
	{
		std::cout << "compile Iterator with std::map"<<std::endl;
		std::map<int, B*> myVec;
		std::map<int, B*>& myVecRef = myVec;
		const std::map<int, B*>& myVecConstRef = myVec;
		const std::map<int, B*> myVecConst;
		{
			lazy4::Iterator<X*, B*, std::map<X*, B*> > myX;
			lazy4::Iterator<const B*, B*, std::map<B*, B*> > myB_const;
			lazy4::Iterator<B*, B*, std::map<B*, B*> > myB;
			lazy4::Iterator<C*, B*, std::map<C*, B*> > myC;
			lazy4::Iterator<B*, B*, void > myB2(myX);
			lazy4::Iterator<X*, B*, void > myX2_const(myB_const);
			lazy4::Iterator<const X*, B*, void > myX3_const(myB_const);
			lazy4::Iterator<const B*, B*, void > myB3_const(myB);
			lazy4::Iterator<const X*, B*, void > myX4_const(myB);
			lazy4::Iterator<X*, B*, void > myX2(myC);
			lazy4::Iterator<Z*, B*, void > myZ(myC);
		}		
		{
			lazy4::Iterator<int, void, std::map<int, B*> > myInt;
			//lazy4::Iterator<int&, void, std::map<int, B*> > myIntRef;
			lazy4::Iterator<const int&, void, std::map<int, B*> > myIntConstRef;
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst;
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst2(myIntConst);
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst3(myInt);
			lazy4::Iterator<void, void, void > myInt2(myInt);
			myInt2 = lazy4::Iterator<void, void, void >(myInt);
		}
		{
			lazy4::Iterator<int, void, std::map<int, B*>& > myInt;
			//lazy4::Iterator<int&, void, std::map<int, B*>& > myIntRef;
			lazy4::Iterator<const int&, void, std::map<int, B*>& > myIntConstRef;
			lazy4::Iterator<const int, void, std::map<int, B*>& > myIntConst;
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*> > myInt;
			//lazy4::Iterator<int&, void, const std::map<int, B*> > myIntRef;
			lazy4::Iterator<const int&, void, const std::map<int, B*> > myIntConstRef;
			lazy4::Iterator<const int, void, const std::map<int, B*> > myIntConst;
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*>& > myInt;
			//lazy4::Iterator<int&, void, const std::map<int, B*>& > myIntRef;
			lazy4::Iterator<const int&, void, const std::map<int, B*>& > myIntConstRef;
			lazy4::Iterator<const int, void, const std::map<int, B*>& > myIntConst;
		}
		
		// myVec
		{
			lazy4::Iterator<int, void, std::map<int, B*> > myInt(myVec);
			//lazy4::Iterator<int&, void, std::map<int, B*> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, std::map<int, B*> > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, std::map<int, B*>& > myInt(myVec);
			//lazy4::Iterator<int&, void, std::map<int, B*>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, std::map<int, B*>& > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, std::map<int, B*>& > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*> > myInt(myVec);
			//lazy4::Iterator<int&, void, const std::vector<int> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::map<int, B*> > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, const std::map<int, B*> > myIntConst(myVec);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*>& > myInt(myVec);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::map<int, B*>& > myIntConstRef(myVec);
			lazy4::Iterator<const int, void, const std::map<int, B*>& > myIntConst(myVec);
		}
		
		// myVecConst
		{
			lazy4::Iterator<int, void, std::map<int, B*> > myInt(myVecConst);
			//lazy4::Iterator<int&, void, std::map<int, B*> > myIntRef(myVecConst);
			lazy4::Iterator<const int&, void, std::map<int, B*> > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst(myVecConst);
		}
		{
			//lazy4::Iterator<int, void, std::map<int, B*>& > myInt(myVecConst);
			//lazy4::Iterator<int&, void, std::map<int, B*>& > myIntRef(myVecConst);
			//lazy4::Iterator<const int&, void, std::map<int, B*>& > myIntConstRef(myVecConst);
			//lazy4::Iterator<const int, void, std::map<int, B*>& > myIntConst(myVecConst);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*> > myInt(myVecConst);
			//lazy4::Iterator<int&, void, const std::map<int, B*> > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::map<int, B*> > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, const std::map<int, B*> > myIntConst(myVecConst);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*>& > myInt(myVecConst);
			//lazy4::Iterator<int&, void, const std::vector<int>& > myIntRef(myVec);
			lazy4::Iterator<const int&, void, const std::map<int, B*>& > myIntConstRef(myVecConst);
			lazy4::Iterator<const int, void, const std::map<int, B*>& > myIntConst(myVecConst);
		}
		
		// myVecRef
		{
			lazy4::Iterator<int, void, std::map<int, B*> > myInt(myVecRef);
			//lazy4::Iterator<int&, void, std::map<int, B*> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, std::map<int, B*> > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, std::map<int, B*>& > myInt(myVecRef);
			//lazy4::Iterator<int&, void, std::map<int, B*>& > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, std::map<int, B*>& > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, std::map<int, B*>& > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*> > myInt(myVecRef);
			//lazy4::Iterator<int&, void, const std::map<int, B*> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::map<int, B*> > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, const std::map<int, B*> > myIntConst(myVecRef);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*>& > myInt(myVecRef);
			//lazy4::Iterator<int&, void, const std::map<int, B*>& > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::map<int, B*>& > myIntConstRef(myVecRef);
			lazy4::Iterator<const int, void, const std::map<int, B*>& > myIntConst(myVecRef);
		}
		
		// myVecConstRef
		{
			lazy4::Iterator<int, void, std::map<int, B*> > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, std::map<int, B*> > myIntRef(myVecConstRef);
			lazy4::Iterator<const int&, void, std::map<int, B*> > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, std::map<int, B*> > myIntConst(myVecConstRef);
		}
		{
			//lazy4::Iterator<int, void, std::map<int, B*>& > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, std::map<int, B*>& > myIntRef(myVecConstRef);
			//lazy4::Iterator<const int&, void, std::map<int, B*>& > myIntConstRef(myVecConstRef);
			//lazy4::Iterator<const int, void, std::map<int, B*>& > myIntConst(myVecConstRef);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*> > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, const std::map<int, B*> > myIntRef(myVecRef);
			lazy4::Iterator<const int&, void, const std::map<int, B*> > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, const std::map<int, B*> > myIntConst(myVecConstRef);
		}
		{
			lazy4::Iterator<int, void, const std::map<int, B*>& > myInt(myVecConstRef);
			//lazy4::Iterator<int&, void, const std::map<int, B*>& > myIntRef(myVecConstRef);
			lazy4::Iterator<const int&, void, const std::map<int, B*>& > myIntConstRef(myVecConstRef);
			lazy4::Iterator<const int, void, const std::map<int, B*>& > myIntConst(myVecConstRef);
		}
	}
	{
		std::cout << "compile Modifier"<<std::endl;
		{
			lazy4::Modifier<X*, B*, std::vector<X*> > myX;
			lazy4::Modifier<B*, B*, std::vector<B*> > myB;
			lazy4::Modifier<C*, B*, std::vector<C*> > myC;
		}
		{
			std::cout << "compile Modifier constructors with functor"<<std::endl;			
			{
				Cast1Vec myCast1;
				Cast2Vec myCast2;
				Cast3Vec myCast3;
				Cast4Vec myCast4;
				Cast5Vec myCast5;
				Cast6Vec myCast6;
				std::vector<X*> vec;
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1(myCast1, vec);
				lazy4::Modifier<B*, X*, std::vector<X*>& > myX2(myCast2, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3(myCast3, vec);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4(myCast4, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5(myCast5, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX6(myCast6, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1_b(myCast1);
				lazy4::Modifier<B*, X*, std::vector<X*>& > myX2_b(myCast2);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3_b(myCast3);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4_b(myCast4);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5_b(myCast5);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX6_b(myCast6);
			}
			{
				Cast1 myCast1;
				Cast2 myCast2;
				Cast3 myCast3;
				Cast4 myCast4;
				Cast6 myCast6;
				lazy4::Modifier<B*, X* > myX1_b(myCast1);
				lazy4::Modifier<B*, X* > myX2_b(myCast2);
				lazy4::Modifier<B*, X* > myX3_b(myCast3);
				lazy4::Modifier<B*, X*& > myX4_b(myCast4);
				lazy4::Modifier<B*, X* > myX6_b(myCast6);
			}
			
			std::cout << "compile Modifier constructors with function"<<std::endl;
			{
				B* (*myCast1)( X* const&, std::vector<X*>) = NULL;
				//B* (*myCast2)( X* , std::vector<X*>&) = NULL;
				B* (*myCast3)( const X*, const std::vector<X*>&) = NULL;
				B* (*myCast4)( X* &, const std::vector<X*>&) = NULL;
				B* (*myCast5)( X* const, const std::vector<X*>) = NULL;
				std::vector<X*> vec;
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1(myCast1, vec);
				//lazy4::Modifier<B*, X*, std::vector<X*>& > myX2(myCast2, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3(myCast3, vec);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4(myCast4, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5(myCast5, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1_b(myCast1);
				//lazy4::Modifier<B*, X*, std::vector<X*>& > myX2_b(myCast2);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3_b(myCast3);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4_b(myCast4);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5_b(myCast5);
			}
			{
				B* (*myCast1)( X* const&) = NULL;
				B* (*myCast2)( X* ) = NULL;
				B* (*myCast3)( const X*) = NULL;
				//B* (*myCast4)( X* &) = NULL;
				B* (*myCast5)( X* const) = NULL;
				lazy4::Modifier<B*, X* > myX1(myCast1);
				lazy4::Modifier<B*, X*& > myX2(myCast2);
				lazy4::Modifier<B*, const X* > myX3(myCast3);
				//lazy4::Modifier<B*, X* > myX4(myCast4);
				lazy4::Modifier<B*, X* > myX5(myCast5);
			}
			std::cout << "compile Modifier constructors with method"<<std::endl;
			{
				B* (X::*myCast1)( std::vector<X*>) = NULL;
				//B* (X::*myCast2)( std::vector<X*>&) = NULL;
				B* (X::*myCast3)( const std::vector<X*>&) const = NULL;
				B* (X::*myCast4)( const std::vector<X*>&) = NULL;
				B* (X::*myCast5)( const std::vector<X*>) = NULL;
				std::vector<X*> vec;
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1(myCast1, vec);
				//lazy4::Modifier<B*, X*, std::vector<X*>& > myX2(myCast2, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3(myCast3, vec);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4(myCast4, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5(myCast5, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1_b(myCast1);
				//lazy4::Modifier<B*, X*, std::vector<X*>& > myX2_b(myCast2);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX3_b(myCast3);
				lazy4::Modifier<B*, X*&, std::vector<X*> > myX4_b(myCast4);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX5_b(myCast5);
			}
			{
				B* (X::*myCast3)( ) const = NULL;
				B* (X::*myCast5)() = NULL;
				lazy4::Modifier<B*, const X* > myX3(myCast3);
				lazy4::Modifier<B*, X* > myX5(myCast5);
			}
		}
		{
			std::cout << "execute Modifiers with function, method and functor"<<std::endl;
			{
				std::vector<X*> vec;
				Cast1Vec myCast1;
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1Functor(myCast1, vec);
				lazy4::Modifier<B*, X*, std::vector<X*> > myX1(&func_name, vec);
				lazy4::Modifier<B*, const X* > myX2(&X::func_name2 );
				lazy4::Modifier<B*, X* > myX3(&X::func_name3 );
				lazy4::Modifier<B*, X& > myX4(&X::func_name3 );
				X x;
				myX1Functor(NULL);
				myX1(NULL);
				myX2(&x);
				myX3(&x);
				myX4(x);
			}
		}
		std::cout << "compile serialize"<<std::endl;
		{
			lazy4::Modifier<X*, B*, std::vector<X*> > myX;
			lazy4::Modifier<B*, C*, std::vector<B*> > myC;
			lazy4::Modifier<X*, C*, std::vector<X*> > mySerialize = myC.serialize(myX);
		}
		std::cout << "compile Modifier and closure"<<std::endl;
		{
			lazy4::Modifier<X*, B*, std::vector<X*> > myX;
			const lazy4::Modifier<X*, B*, std::vector<X*> > myY;
			lazy4::Modifier<B*, B*, void > myB;
			myX.closure();
			myY.closure();
			myB.closure();
		}
		std::cout << "compile Modifier to Collection/Iterator/Flow and vice-versa"<<std::endl;
		{
			lazy4::Flow<X*, void, std::vector<X*> > my_flow;
			lazy4::Iterator<X*, void, std::vector<X*> > my_iterator;
			lazy4::Collection<X*, void, std::vector<X*> > my_collection;
			std::vector<X*> my_vector;
			
			{
				lazy4::Modifier<lazy4::Flow<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_flow.modifier();
				lazy4::Flow<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
			{
				const lazy4::Modifier<lazy4::Flow<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_flow.modifier();
				lazy4::Flow<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
			{
				lazy4::Modifier<lazy4::Iterator<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_iterator.modifier();
				lazy4::Iterator<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
			{
				const lazy4::Modifier<lazy4::Iterator<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_iterator.modifier();
				lazy4::Iterator<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
			{
				lazy4::Modifier<lazy4::Collection<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_collection.modifier();
				lazy4::Collection<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
			{
				const lazy4::Modifier<lazy4::Collection<X*, void, std::vector<X*> >, std::vector<X*>, std::vector<X*> > converter = my_collection.modifier();
				lazy4::Collection<X*, void, std::vector<X*> > myB2 = converter(my_vector);
			}
		}
		{
			std::cout << "compile Collection to Iterator"<<std::endl;
			{
				lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator = myCollection.begin();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = myCollection.end();
			}
			{
				lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator = myCollection.rbegin();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = myCollection.rend();
			}
			{
				const lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator = myCollection.begin();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = myCollection.end();
			}
			{
				const lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator = myCollection.rbegin();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = myCollection.rend();
			}
			{
				const lazy4::Collection<X*&, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X* const &, void, std::vector<X*> > myIterator = myCollection.begin();
				lazy4::Iterator<X* const &, void, std::vector<X*> > myIterator2 = myCollection.end();
			}
			{
				const lazy4::Collection<X*&, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X* const &, void, std::vector<X*> > myIterator = myCollection.rbegin();
				lazy4::Iterator<X* const &, void, std::vector<X*> > myIterator2 = myCollection.rend();
			}
			{
				const lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator(myCollection.begin());
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator3 = (lazy4::Iterator<X*, void, std::vector<X*> >) (myCollection.begin());
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = (lazy4::Iterator<X*, void, std::vector<X*> >) myCollection.end();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2Const = (lazy4::Iterator<X*, void, std::vector<X*> >) myCollection.end();
			}
			{
				const lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator(myCollection.rbegin());
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator3 = (lazy4::Iterator<X*, void, std::vector<X*> >) (myCollection.rbegin());
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator2 = (lazy4::Iterator<X*, void, std::vector<X*> >) myCollection.rend();
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator2Const = (lazy4::Iterator<X*, void, std::vector<X*> >) myCollection.rend();
			}
		}
		{
			std::cout << "compile Iterator to Collection"<<std::endl;
			{
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
				lazy4::Collection<X*, void, std::vector<X*> > myCollection = myIterator.collection();
			}
			{
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
				const lazy4::Collection<X*, void, std::vector<X*> > myCollection = (lazy4::Collection<X*, void, std::vector<X*> >) myIterator.collection();
				lazy4::Collection<X*, void, std::vector<X*> > myCollectionConst = (lazy4::Collection<X*, void, std::vector<X*> >) myIterator.collection();
			}
		}
		{
			std::cout << "compile Iterator to Pair"<<std::endl;
			{
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
				lazy4::Pair<X*, void> myPair = myIterator.pair();
			}
			{
				const lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
				const lazy4::Pair<X*, void> myPair = (lazy4::Pair<X*, void>) myIterator.pair();
				lazy4::Pair<X*, void> myCollectionConst = (lazy4::Pair<X*, void>) myIterator.pair();
			}
		}
		{
			std::cout << "compile Inherited Collection to Collection"<<std::endl;
			{
				MyCollectionType myCollection;
				lazy4::Collection<int> myCollection2 = myCollection;
			}
		}
		{
			std::cout << "compile reverse et unique operation"<<std::endl;
			{
				lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
				lazy4::Collection<X*, void, std::vector<X*> > myCollection;
				lazy4::Iterator<X*, void, std::vector<X*> > myIteratorR = myIterator.reverse();
				lazy4::Iterator<X*, void, std::vector<X*> > myIteratorU = myIterator.unique_first();
				lazy4::Collection<X*, void, std::vector<X*> > myCollectionR = myCollection.reverse();
				lazy4::Collection<X*, void, std::vector<X*> > myCollectionU = myCollection.unique_first();				
			}
		}
		{
			std::cout << "compile implicit cast operator"<<std::endl;
			{
				lazy4::Iterator<X*, B*, std::map<X*,B*> > myIterator;
				lazy4::Collection<X*, B*, std::map<X*,B*> > myCollection;
				lazy4::Modifier<X*, B*, std::map<X*,B*> > myModifier;
				lazy4::Iterator<X* > myIterator2 = myIterator;
				lazy4::Iterator<X*, B* > myIterator3 = myIterator;
				lazy4::Collection<X* > myCollection2 = myCollection;
				lazy4::Collection<X*, B* > myCollection3 = myCollection;				
				lazy4::Modifier<X* > myModifier2 = myModifier;
				lazy4::Modifier<X*, B* > myModifier3 = myModifier;				
			}
			{
				lazy4::Iterator<X*, B*> myIterator;
				lazy4::Collection<X*, B* > myCollection;
				lazy4::Modifier<X*, B* > myModifier;
				lazy4::Pair<X*, B* > myPair;
				lazy4::Iterator<X* > myIterator2 = myIterator;
				lazy4::Collection<X* > myCollection2 = myCollection;
				lazy4::Modifier<X* > myModifier2 = myModifier;
				lazy4::Pair<X* > myPair2 = myPair;
			}
			{
				lazy4::Iterator<X*> myIterator;
				lazy4::Collection<X* > myCollection;
				lazy4::Modifier<X* > myModifier;
				lazy4::Pair<X*> myPair;
				// nothing to test ...
			}
		}
		{
			std::cout << "compile dynamic_cast"<<std::endl;
			{
				{
					lazy4::Iterator<X*> myIterator;
					lazy4::Collection<X*> myCollection;
					lazy4::Iterator<B*> myIterator2 = myIterator.dynamic_cast_first<B*>();
					lazy4::Collection<B*> myCollection2 = myCollection.dynamic_cast_first<B*>();
				}
				{
					lazy4::Iterator<const X*> myIterator;
					lazy4::Collection<const X*> myCollection;
					lazy4::Iterator<const B*> myIterator2 = myIterator.dynamic_cast_first<const B*>();
					lazy4::Collection<const B*> myCollection2 = myCollection.dynamic_cast_first<const B*>();
				}
				{
					lazy4::Iterator<X* const> myIterator;
					lazy4::Collection<X* const> myCollection;
					lazy4::Iterator<B* const> myIterator2 = myIterator.dynamic_cast_first<B* const>();
					lazy4::Collection<B* const> myCollection2 = myCollection.dynamic_cast_first<B* const>();
				}
				{
					lazy4::Iterator<const X* const> myIterator;
					lazy4::Collection<const X* const> myCollection;
					lazy4::Iterator<const B* const> myIterator2 = myIterator.dynamic_cast_first<const B* const>();
					lazy4::Collection<const B* const> myCollection2 = myCollection.dynamic_cast_first<const B* const>();
				}
				{
					lazy4::Iterator<X> myIterator;
					lazy4::Collection<X> myCollection;
					lazy4::Iterator<B> myIterator2 = myIterator.dynamic_cast_first<B>();
					lazy4::Collection<B> myCollection2 = myCollection.dynamic_cast_first<B>();
				}
				{
					lazy4::Iterator<const X> myIterator;
					lazy4::Collection<const X> myCollection;
					lazy4::Iterator<const B> myIterator2 = myIterator.dynamic_cast_first<const B>();
					lazy4::Collection<const B> myCollection2 = myCollection.dynamic_cast_first<const B>();
				}
				{
					lazy4::Iterator<X&> myIterator;
					lazy4::Collection<X&> myCollection;
					lazy4::Iterator<B&> myIterator2 = myIterator.dynamic_cast_first<B&>();
					lazy4::Collection<B&> myCollection2 = myCollection.dynamic_cast_first<B&>();
				}
				{
					lazy4::Iterator<const X&> myIterator;
					lazy4::Collection<const X&> myCollection;
					lazy4::Iterator<const B&> myIterator2 = myIterator.dynamic_cast_first<const B&>();
					lazy4::Collection<const B&> myCollection2 = myCollection.dynamic_cast_first<const B&>();
				}
			}
		}
		{
			std::cout << "compile concatenation"<<std::endl;
			{
				{
					lazy4::Iterator<X*, void, std::vector<X*> > myIterator;
					lazy4::Iterator<X*, void, std::vector<X*> > myIterator2;
					lazy4::Iterator<X*, void, lazy4::Pair<std::vector<X*>&, std::vector<X*>& > > myIterator3 = myIterator + myIterator2;
					lazy4::Collection<X*, void, std::vector<X*> > myCollection;
					lazy4::Collection<X*, void, std::vector<X*> > myCollection2;
					lazy4::Collection<X*, void, lazy4::Pair<std::vector<X*>&, std::vector<X*>& > > myCollection3 = myCollection + myCollection2;
				}
				{
					lazy4::Iterator<X*> myIterator;
					lazy4::Iterator<X*> myIterator2;
					lazy4::Iterator<X*, void, lazy4::Pair<void*&, void*& > > myIterator3 = myIterator + myIterator2;
					lazy4::Collection<X*> myCollection;
					lazy4::Collection<X*> myCollection2;
					lazy4::Collection<X*, void, lazy4::Pair<void*&, void*& > > myCollection3 = myCollection + myCollection2;
				}
			}
		}
		{
			std::cout << "compile flatten"<<std::endl;
			{
				{
					lazy4::Iterator<lazy4::Iterator<X*> > myIterator;
					lazy4::Iterator<X*> myIterator2 = myIterator.flatten_first();
					lazy4::Collection<lazy4::Iterator<X*> > myCollection;
					lazy4::Collection<X*> myCollection2 = myCollection.flatten_first();
				}
				{
					lazy4::Iterator<lazy4::Iterator<X*>& > myIterator;
					lazy4::Iterator<X*> myIterator2 = myIterator.flatten_first();
					lazy4::Collection<lazy4::Iterator<X*>& > myCollection;
					lazy4::Collection<X*> myCollection2 = myCollection.flatten_first();
				}
				{
					lazy4::Iterator<const lazy4::Iterator<X*>& > myIterator;
					lazy4::Iterator<X*> myIterator2 = myIterator.flatten_first();
					lazy4::Collection<const lazy4::Iterator<X*>& > myCollection;
					lazy4::Collection<X*> myCollection2 = myCollection.flatten_first();
				}
				{
					lazy4::Iterator<const lazy4::Iterator<X*> > myIterator;
					lazy4::Iterator<X*> myIterator2 = myIterator.flatten_first();
					lazy4::Collection<const lazy4::Iterator<X*> > myCollection;
					lazy4::Collection<X*> myCollection2 = myCollection.flatten_first();
				}
			}
		}
		{
			std::cout << "compile permutation"<<std::endl;
			{
				{
					lazy4::Iterator<X*,void > myIterator;
					lazy4::Iterator<void, X*> myIterator2 = myIterator.permute();
					lazy4::Collection<X*, void > myCollection;
					lazy4::Collection<void, X*> myCollection2 = myCollection.permute();
				}
			}
		}
		{
			std::cout << "compile bounds"<<std::endl;
			{
				{
					lazy4::Iterator<X*> begin;
					lazy4::Iterator<X*> end;
					lazy4::Iterator<X*> myIterator(begin, end);
					lazy4::Collection<X*> myCollection(begin, end);
				}
			}
		}
	}
	{
		std::cout << "compile modifier boolean operators"<<std::endl;
		{
			lazy4::Modifier<X*,int > modifier1;
			lazy4::Modifier<X*,int > modifier1bis;
			lazy4::Modifier<void*,int > modifier2;
			lazy4::Modifier<bool,int, lazy4::Pair<void*&, void*& > > modifier3bis = modifier1 && modifier1bis;
			lazy4::Modifier<bool,int, lazy4::Pair<void*&, void*& > > modifier3 = modifier1 && modifier2;
			lazy4::Modifier<bool,int > modifier4 = !modifier1 ;
		}
		{
			lazy4::Modifier<X*,int, std::vector<int> > modifier1;
			lazy4::Modifier<X*,int, std::vector<int> > modifier1bis;
			lazy4::Modifier<void*,int, std::vector<long> > modifier2;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<int>& > > modifier3bis = modifier1 && modifier1bis;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<long>& > > modifier3 = modifier1 && modifier2;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<int>& > > modifier4bis = modifier1 || modifier1bis;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<long>& > > modifier4 = modifier1 || modifier2;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<int>& > > modifier5bis = modifier1 ^ modifier1bis;
			lazy4::Modifier<bool,int, lazy4::Pair<std::vector<int>&, std::vector<long>& > > modifier5 = modifier1 ^ modifier2;
			lazy4::Modifier<bool,int, std::vector<int> > modifier6 = !modifier1 ;
		}
		
	}
	{
		std::cout << "compile make_collection and make_iterator"<<std::endl;
		{
			X* x = NULL;
			B* b = NULL;
			lazy4::Collection<X* > collectionX = lazy4::make_collection(x);
			lazy4::Collection<X*,B* > collectionX_B = lazy4::make_collection(x, b);
			lazy4::Iterator<X* > iteratorX = lazy4::make_iterator(x);
			lazy4::Iterator<X*,B* > iteratorX_B = lazy4::make_iterator(x, b);
		}		
	}
	{
		std::cout << "compile List and Index"<<std::endl;
		{
			{
				lazy4::List<X*> myList;
				lazy4::Index<X*> myIndex;
			}
		}
	}
	
	{
		std::cout << "test iteration"<<std::endl;
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		{
			lazy4::Collection<int, void, std::vector<int> > collection = vector;
			lazy4::Iterator<int, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int, void, std::vector<int> > end = collection.end();
			//bool isvalid = it.valid();
			while (it != end) {
				it.first();
				it++;
				//isvalid = it.valid();
			}
		}
		{
			lazy4::Collection<int, void, std::vector<int>& > collection = vector;
			lazy4::Iterator<int, void, std::vector<int>& > it = collection.begin();
			lazy4::Iterator<int, void, std::vector<int>& > end = collection.end();
			//bool isvalid = it.valid();
			while (it != end) {
				it.first();
				it++;
				//isvalid = it.valid();
			}
		}
		{
			lazy4::Collection<int&, void, std::vector<int>& > collection = vector;
			lazy4::Iterator<int&, void, std::vector<int>& > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int>& > end = collection.end();
			//bool isvalid = it.valid();
			while (it != end) {
				it.first();
				it++;
				//isvalid = it.valid();
			}
		}
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Iterator<int&, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			//bool isvalid = it.valid();
			while (it != end) {
				it.first();
				it++;
				//isvalid = it.valid();
			}
		}
	}
	{
		std::cout << "test side effect on two iterators"<<std::endl;
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Iterator<int&, void, std::vector<int> > beg = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > it = beg;
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			std::cout << "cout<< *it and *beg;"<<std::endl;
			while (it != end) {
				std::cout << it.first() <<"  "<< beg.first() << std::endl;
				it++;
			}
		}		
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Iterator<int&, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			std::cout << "cout<< ++*it;"<<std::endl;
			while (it != end) {
				it.first() += 1;
				std::cout << it.first() << std::endl;
				it++;
			}
			std::cout << "restart on the same collection : cout<< *it"<<std::endl;
			it = collection.begin();
			while (it != end) {
				std::cout << it.first() << std::endl;
				it++;
			}
		}
	}
	{
		std::cout << "test side effect on two collections"<<std::endl;
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Collection<int&, void, std::vector<int> > collection2 = collection;
			collection2.container();
			lazy4::Iterator<int&, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > it2 = collection2.begin();
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			std::cout << "cout<< ++*it and *it2;"<<std::endl;
			while (it != end) {
				it.first() += 1;
				std::cout << it.first() <<"  "<< it2.first() << std::endl;
				it++;
				it2++;
			}
		}		
		
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Collection<int&, void, std::vector<int> > collection2 = collection;
			lazy4::Iterator<int&, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > it2 = collection2.begin();
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			std::cout << "cout<< ++*it and *it2;"<<std::endl;
			while (it != end) {
				it.first() += 1;
				std::cout << it.first() <<"  "<< it2.first() << std::endl;
				it++;
				it2++;
			}
		}
		
		{
			lazy4::Collection<int&, void, std::vector<int> > collection = vector;
			lazy4::Iterator<int&, void, std::vector<int> > it = collection.begin();
			lazy4::Iterator<int&, void, std::vector<int> > end = collection.end();
			lazy4::Collection<int&, void, std::vector<int> > collection2 = collection;
			lazy4::Iterator<int&, void, std::vector<int> > it2 = collection2.begin();
			std::cout << "cout<< ++*it and *it2;"<<std::endl;
			while (it != end) {
				it.first() += 1;
				std::cout << it.first() <<"  "<< it2.first() << std::endl;
				it++;
				it2++;
			}
		}
	}

	{
		std::cout << "compile internal::SingleStorage"<<std::endl;
		lazy4::internal2::SingleStorage<unsigned int, std::string, std::tr1::unordered_map<unsigned int, std::string> > myStorage;
	}
	
	{
		std::cout << "compile internal::CollectionStorage"<<std::endl;
		lazy4::internal2::CollectionStorage<unsigned int, std::string, std::vector<std::string> > myStorage;
	}
	
	{
		std::cout << "compile internal::KeyStorage"<<std::endl;
		lazy4::internal2::KeyStorage<unsigned int, std::string> myStorage;
	}
	
	{
		std::cout << "compile internal::SharedStorage"<<std::endl;
		lazy4::internal2::SharedStorage<unsigned int, std::string, false, unsigned short> myStorage;
		lazy4::internal2::SharedStorage<unsigned int, std::string, true,  unsigned short > myStorage2;
	}
	
	{
		std::cout << "compile internal::DualStorage"<<std::endl;
		lazy4::internal2::DualStorage<unsigned int, long, false, false> myStorage;
	}
	
	{
		std::cout << "compile internal::ChainStorage"<<std::endl;
		lazy4::internal2::ChainStorage<unsigned int, char> myStorage;
	}
	
	std::cout << "end of test of lazy 4"<<std::endl;
#endif

	//
	{
#if 1
		{
			std::cout<<"val ptr"<<std::endl;
			lazy5::flow<int, int> f((lazy5::Iflow<int, int>*)NULL);
			std::cout<<"const val ptr"<<std::endl;
			lazy5::flow<int, int> f0((const lazy5::Iflow<int, int>*)NULL);
			std::cout<<"static cast"<<std::endl;
			lazy5::flow<long, int> g(f);
			std::cout<<"const static cast"<<std::endl;
			lazy5::flow<long, int> g20(const_cast<const lazy5::flow<int, int>&>(f));
			std::cout<<"move flow"<<std::endl;
			lazy5::flow<long, int> g7 =std::move(lazy5::flow<long, int>());
			std::cout<<"const move flow"<<std::endl;
			const lazy5::flow<long, int> cg7;
			lazy5::flow<long, int> cvg7 =std::move(cg7);
			std::cout<<"flow"<<std::endl;
			const lazy5::flow<int, int> h(f);
			std::cout<<"const flow"<<std::endl;
			lazy5::flow<int, int> g2(h);
			std::cout<<"string"<<std::endl;
			std::string s;
			lazy5::generic h2(s);
			std::cout<<"const string"<<std::endl;
			const std::string cs;
			lazy5::generic ch2(cs);
			std::cout<<"const ptr"<<std::endl;
			const lazy5::Iflow<int, int>* t =NULL;
			lazy5::flow<int, int> f2(t);
			std::cout<<"variable ptr"<<std::endl;
			lazy5::Iflow<int, int>* t3 =NULL;
			lazy5::flow<int, int> f3(t3);
		}
		{
			std::cout<<"shared ptr"<<std::endl;
			std::shared_ptr<lazy5::Iflow<int, int>> t3 =NULL;
			lazy5::flow<int, int> f3(t3);
		}
		{
			std::cout<<"const shared ptr"<<std::endl;
			const std::shared_ptr<lazy5::Iflow<int, int>> t3 =NULL;
			lazy5::flow<int, int> f3(t3);
		}
		{
			std::cout<<"iterator->flow"<<std::endl;
			lazy5::iterator<int, int> i3;
			lazy5::flow<int, int> f3(i3);
		}

		{
			std::cout<<"iterator->Iflow->flow"<<std::endl;
			lazy5::iterator<int, int> i3;
			lazy5::iterator<int, int>::super_type c = i3;
			lazy5::bridge<lazy5::Iiterator<int, int>>& c2 = c;
			lazy5::Iiterator<int, int>& t4 = i3;
			lazy5::Iflow<int, int>& t3 = i3;
			// FIXME: warning how do we store the interface ?
			lazy5::flow<int, int> f3(t3);
		}

		{
			std::cout<<"iterator->Igeneric->flow"<<std::endl;
			lazy5::iterator<int, int> i3;
			lazy5::Igeneric& t3 = i3;
			//lazy5::flow<int, int> f3(t3);
			lazy5::flow<int, int> f3(dynamic_cast<lazy5::Iflow<int, int>&> (t3));
		}

		{
			lazy5::generic t3;
			std::cout<<"generic->generic"<<std::endl;
			lazy5::generic f4(t3);
		}

		{
			lazy5::flow<int,int> f2;
			std::cout<<"Flow->generic"<<std::endl;
			lazy5::generic t3(f2);
		}
		{
			std::vector<int> f2;
			std::cout<<"std::vector->list"<<std::endl;
			lazy5::list<int> t3(f2);
			std::cout<<"list->std::vector"<<std::endl;
			std::set<int> ff;
			std::map<int,int> fdf;
			std::vector<int> x = t3;
		}


		{
			std::vector<std::vector<int>> f2;
			std::cout<<"std::vector<std::vector<>>->list<list>"<<std::endl;
			lazy5::collection<std::vector<int>> t3(f2);
			lazy5::list<std::vector<int>> t3_(f2);
			lazy5::collection<lazy5::query<int>> t4(t3);
			lazy5::collection<lazy5::collection<int>> t5(t3);
			lazy5::collection<lazy5::list<int>> t4_(t3_);
			lazy5::list<lazy5::list<int>> t6(t3_);
		}



		{
			std::cout<<"matrix->collection<collection>"<<std::endl;
			lazy5::matrix<B*,B*> f2;
			lazy5::Icollection<B*, lazy5::bridge<lazy5::Icollection<B*,B*>>>& t5(f2);
			lazy5::collection<B*, lazy5::collection<B*,B*>> t3(f2);
			lazy5::collection<B*, lazy5::query<B*,B*>> t6(f2);
			lazy5::collection<B*, lazy5::collection<B*,B*>> t4;
			lazy5::collection<B*,B*> g = t4.value(0);

			lazy5::collection<B*, lazy5::collection<B*,B*>> t3_(f2);
			lazy5::collection<B*,B*> g3 = t3_.value(0);
			B* g2 = g3.value(0);
		}


		
		{
			std::cout<<"iterator.apply(fct)"<<std::endl;
			auto fct = []  (size_t d) -> long long{
				return d;
			};
			std::function< long long (size_t)> fct2= fct;
			lazy5::iterator<size_t> it;

			it.apply(fct2);
			lazy5::element< long long> x=it.apply(fct2);
			lazy5::iterator< long long> y=it.apply(fct2);

		}

		{
			std::cout<<"collection.apply(fct)"<<std::endl;
			auto fct = []  (size_t d) -> long long{
				return d;
			};
			std::function< long long (size_t)> fct2= fct;
			lazy5::collection<size_t> it;

			it.apply(fct2);
			lazy5::collection< long long> y=it.apply(fct2);

		}

		{
			std::cout<<"collection.apply(fct(&,&&))"<<std::endl;
			auto fct = []  (B*, size_t d) -> long long{
				return d;
			};
			std::function< long long (B*, size_t)> fct2= fct;
			lazy5::collection<B*, size_t> it;

			it.apply_on_two(fct2);
			lazy5::collection<B*,  long long> y=it.apply_on_two(fct2);

		}

		{
			std::cout<<"iterator.apply2(fct,fct2)"<<std::endl;
			std::function< long long (size_t)> fct = []  (size_t d) -> long long{
				return d;
			};
			std::function<size_t ( long long)> fct2 = []  ( long long d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(&&),fct2(&&))"<<std::endl;
			std::function< long long ( size_t&&)> fct = []  ( size_t&& d) -> long long{
				return d;
			};
			std::function<size_t (  long long&&)> fct2 = []  (  long long&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(const&&),fct2(const &&))"<<std::endl;
			std::function< long long (const size_t&&)> fct = []  (const size_t&& d) -> long long{
				return d;
			};
			std::function<size_t (const  long long&&)> fct2 = []  (const  long long&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);
		}

		{
			std::cout<<"iterator.apply2(fct(&),fct2(&))"<<std::endl;
			std::function< long long ( size_t&)> fct = []  ( size_t& d) -> long long{
				return d;
			};
			std::function<size_t (  long long&)> fct2 = []  (  long long& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);
		}

		{
			std::cout<<"iterator.apply2(fct(const&),fct2(const&))"<<std::endl;
			std::function< long long ( const size_t&)> fct = []  ( const size_t& d) -> long long{
				return d;
			};
			std::function<size_t (const  long long&)> fct2 = []  (const  long long& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(const &fct(),const &fct2())"<<std::endl;
			std::function<const  long long& ( size_t)> fct = []  ( size_t d) ->const  long long&{
				static  long long dx=0;
				return dx;
			};
			std::function<const size_t& ( long long)> fct2 = []  ( long long d) ->const size_t&{
				static size_t dx=0;
				return dx;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2( &fct(), &fct2())"<<std::endl;
			std::function<  long long& ( size_t)> fct = []  ( size_t d) ->  long long&{
				static  long long dx=0;
				return dx;
			};
			std::function< size_t& ( long long)> fct2 = []  ( long long d) -> size_t&{
				static size_t dx=0;
				return dx;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"collection.apply2( &fct(), &fct2())"<<std::endl;
			std::function<  long long& ( size_t)> fct = []  ( size_t d) ->  long long&{
				static  long long dx=0;
				return dx;
			};
			std::function< size_t& ( long long)> fct2 = []  ( long long d) -> size_t&{
				static size_t dx=0;
				return dx;
			};
			lazy5::list<size_t> it;

			it.apply2(fct, fct2);
			lazy5::list< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(&&),fct2(&&))"<<std::endl;
			std::function< size_t (  size_t&&)> fct = []  (  size_t&& d) -> size_t{
				return d;
			};
			std::function<size_t (  size_t&&)> fct2 = []  (  size_t&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(&),fct2(&))"<<std::endl;
			std::function< size_t (  size_t&)> fct = []  (  size_t& d) -> size_t{
				return d;
			};
			std::function<size_t (  size_t&)> fct2 = []  (  size_t& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(const &&),fct2(&&))"<<std::endl;
			std::function< size_t ( const size_t&&)> fct = []  ( const size_t&& d) -> size_t{
				return d;
			};
			std::function<size_t (  size_t&&)> fct2 = []  (  size_t&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2(fct(const &),fct2(&&))"<<std::endl;
			std::function< size_t ( const size_t&)> fct = []  ( const size_t& d) -> size_t{
				return d;
			};
			std::function<size_t (  size_t&&)> fct2 = []  (  size_t&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<size_t> it;

			it.apply2(fct, fct2);
			lazy5::element< long long> x=it.apply2(fct, fct2);
			lazy5::iterator< long long> y=it.apply2(fct, fct2);

		}

		{
			std::cout<<"iterator.apply2_on_two(fct(X*, const &),fct2(X*, &&))"<<std::endl;
			std::function< size_t ( X*, const size_t&)> fct = []  ( X*, const size_t& d) -> size_t{
				return d;
			};
			std::function<size_t (  X*, size_t&&)> fct2 = []  (  X*, size_t&& d) ->size_t{
				return (size_t) d;
			};
			lazy5::iterator<B*, size_t> it;

			it.apply2_on_two(fct, fct2);
			lazy5::element<B*,  long long> x=it.apply2_on_two(fct, fct2);
			lazy5::iterator<B*,  long long> y=it.apply2_on_two(fct, fct2);

		}


		{
			std::cout<<"content"<<std::endl;
			lazy5::content<size_t> x;
			lazy5::content<size_t> y((long long) 5);
			y = (long long) 10;
			long long c=5;
			y = c;
			long long g = y;
			y = lazy5::content<size_t>((long long) 5);
		}

		{
			std::cout<<"reference"<<std::endl;
			lazy5::reference<size_t> x;
			lazy5::reference<size_t> y((long long) 5);
			y =  10;
			long c=5;
			y = c;
			long long g = y;
			y = lazy5::reference<size_t>((long long) 5);
		}

		{
			std::cout<<"reference"<<std::endl;
			lazy5::list_iterator<size_t> x;
			lazy5::content<size_t> y =*x;
			*x=5;
		}


		{
			std::cout<<"convert element to flow or collection"<<std::endl;
			size_t s =0;
			lazy5::flow<size_t> xq = s;
			lazy5::element<size_t> d;
			lazy5::flow<size_t> x = d;
			lazy5::collection<size_t> y = d;
		}


		{
			std::cout<<"concatenation"<<std::endl;
			lazy5::flow<size_t> x;
			lazy5::flow<size_t> y;
			x << y;
			x << ((size_t) 5);
			lazy5::element<size_t> d;
			x << d;
		}


		{
			std::cout<<"flatten"<<std::endl;
			lazy5::collection<Y*, lazy5::collection<double, Z*>> y;
			lazy5::collection<double, Z*> flat = y.flatten();
			lazy5::collection<lazy5::collection<double, Z*>> y_bis;
			lazy5::collection<double, Z*> flat_bis = y_bis.flatten();
			lazy5::flow<Y*, lazy5::flow<double, Z*>> y2;
			lazy5::flow<double, Z*> flat2 = y2.flatten();
			lazy5::flow<Y*, lazy5::flow<double, Z*>> y2_bis;
			lazy5::flow<double, Z*> flat2_bis = y2_bis.flatten();
			lazy5::iterator<Y*, lazy5::iterator<double, Z*>> y3;
			lazy5::iterator<double, Z*> flat3 = y3.flatten();
			lazy5::element<Y*, lazy5::element<double, Z*>> y4;
			lazy5::element<double, Z*> flat4 = y4.flatten();
			lazy5::element<lazy5::element<double, Z*>> y4_bis;
			lazy5::element<double, Z*> flat4_bis = y4_bis.flatten();
			// FIXME: impossible !!
			lazy5::list<lazy5::list<double, Z*>> y5_bis;
			//lazy5::list<double, Z*> flat5_bis = y5_bis.flatten();
		}



		{
			std::cout<<"flatten mixte collection<flow> , element<flow> , ..."<<std::endl;
			lazy5::collection<Y*, lazy5::flow<double, Z*>> x;
			lazy5::flow<double, Z*> flat = x.flatten();
			lazy5::iterator<Y*, lazy5::collection<double, Z*>> x2;
			lazy5::collection<double, Z*> flat2 = x2.flatten();
			lazy5::element<Y*, lazy5::flow<double, Z*>> x3;
			lazy5::flow<double, Z*> flat3 = x3.flatten();
			lazy5::element<Y*, lazy5::collection<double, Z*>> x4;
			lazy5::collection<double, Z*> flat4 = x4.flatten();
			lazy5::element<lazy5::list<double, Z*>> x5;
			lazy5::list<double, Z*> flat5 = x5.flatten();
			lazy5::collection<Y*, lazy5::element<double, Z*>> x6;
			lazy5::element<double, Z*> flat6 = x6.flatten();
			lazy5::iterator<Y*, lazy5::element<double, Z*>> x7;
			lazy5::element<double, Z*> flat7 = x7.flatten();
		}

		{
			std::cout<<"swap"<<std::endl;
			lazy5::collection<Y*, Z*> x;
			lazy5::collection<Z*,Y*> x2 = x.swap();
			lazy5::iterator<Y*, Z*> y;
			lazy5::iterator<Z*, Y*> y2 = y.swap();
		}


		{
			std::cout<<"isolate"<<std::endl;
			lazy5::collection<Y*, lazy5::collection<double, Z*>> x;
			lazy5::collection<double, Z*> x2 = x.isolate(0);
			lazy5::iterator<Y*, lazy5::iterator<double, Z*>> y;
			lazy5::iterator<double, Z*> y2 = y.isolate(0);
			lazy5::iterator<Y*, lazy5::collection<double, Z*>> z;
			lazy5::collection<double, Z*> z2 = z.isolate(0);
#if 0 // disabled to debug
			lazy5::collection<Y*, lazy5::iterator<double, Z*>> a;
			lazy5::iterator<double, Z*> a2 = a.isolate(0);
			lazy5::collection<Y*, lazy5::flow<double, Z*>> b;
			lazy5::flow<double, Z*> b2 = b.isolate(0);
			lazy5::collection<Y*, lazy5::element<double, Z*>> c;
			lazy5::element<double, Z*> c2 = c.isolate(0);
			lazy5::iterator<Y*, lazy5::flow<double, Z*>> d;
			lazy5::flow<double, Z*> d2 = d.isolate(0);
			lazy5::iterator<Y*, lazy5::element<double, Z*>> e;
			lazy5::element<double, Z*> e2 = e.isolate(0);
			//TODO : the flow and element ????
			lazy5::flow<Y*, lazy5::collection<double, Z*>> f;
			lazy5::collection<double, Z*> f2 = f.isolate(0);
			lazy5::element<Y*, lazy5::collection<double, Z*>> g;
			lazy5::collection<double, Z*> g2 = g.isolate(0);
#endif
		}

		{
			//TODO
			std::cout<<"transpose"<<std::endl;
			lazy5::collection<Y*, lazy5::collection<double, Z*>> x;
			//lazy5::collection<Y*, lazy5::collection<double, Z*>> x2 = x.transpose();
			lazy5::iterator<Y*, lazy5::iterator<double, Z*>> y;
			//lazy5::iterator<Y*, lazy5::iterator<double, Z*>> y2 = y.transpose();
		}
#endif


	}
	std::cout << "end of test"<<std::endl;
	
}
