/*
 *  deprecated_main.cpp
 *  collection
 *
 *  Created by Francois et Fabienne on 15/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "deprecated_main.h"

/*
 
 ----- Wrapper
 - itérateur et predicate de boost
 http://www.boost.org/doc/libs/1_44_0/libs/iterator/doc/filter_iterator.html
 http://www.boost.org/doc/libs/1_44_0/libs/iterator/doc/new-iter-concepts.html
 http://msdn.microsoft.com/fr-fr/library/ms132397(v=VS.80).aspx
 - traits de STL et boost
 - méthode d'accès de boost, et c#
 - proposition d'Wrapper:
 - push_back, push_front, pop, erase(elem), bool exist, iterator find_first/last, begin, end, alCompare count_occurrences([elem]), operator[] const, at(int) const 
 - alCompare >,<,==, exist contient l'élèment et la collection. automatic cast en int.
 - classe filter ou predicate qui peut prendre des bornes ou index de la collection. fait aussi le skip.
 - ContainerWrapper et IteratorWrapper -> ...Wrapper/Callback/design pattern name
 - renommer ReferenceDriver en OccurrenceDriver
 - deplacer les create_driver dans la classe driver ou alors les supprimer ?
 - faire un find avec des itérateurs.
 - implémenter collection<T> operator=(const collection <T>&)
 - implémenter collection<T> operator=(const collection <collection<T> >&)
 - implémenter collection<T>(const collection <T>&) { _driver = c._driver->clone(); }
 - implémenter collection<T>(const Iterator<T>&) et (const Iterator& begin, const Iterator& end)
 - remplir une collection, insertion ou supression
 + à partir d'un index : operator []
 + à partir de l'itérateur : operator *
 + autres : concat, erase, push_back
 - le flatten peut être un cast implicite/explicite : alCollection<T>(const alCollection<alCollection<T> >&)
 - est-ce que c'est Const ou NonMutable ? Read/Write ?
 - implémenter template <IT> collection(const I& begin, const Iterator& end)
 - selection(filter)
 - transform(accessor)
 - flatten()
 - concat, +, +=
 - opérateur de cast
 - accessor qui transforme le collection(vector<vector<T> >) en collection<T>
 
 
 
 ---- features
 
 - une collection qui contient une autre collection c'est une référence sur son driver ou bien le contenu de son driver ou bien une reference/copie sur la collection elle-même (je pense plus à une copie) ?
 
 - share pointer pour les set partagés
 copie rapide d'iterateur et de collection cf. share pointer
 
 - peut-on supprimer l'indirection supplémentaire sur l'Wrapper ?
 
 - faire un EmptyCollectionDriver et EmptyIteratorDriver : ils seront des variables static de Iterator et Collection. C'est le constructeur par défaut de ces classes qui créé les instances empty. L'opérateur d'égalité est parfait.
 
 - héritage des Collection Driver -> MutableDriver -> InstanceDriver
 -> OccurrenceDriver
 -> ConstDriver -> ConstOccurrenceDriver
 
 - faire une vrai Wrapper pour les drivers :
 ConstContainerWrapper {
 const C& get_container() const;
 // read function
 }
 MutableContainerWrapper {
 C& get_container() const;
 // write function
 }
 ----> héritage multiple
 ConstContainerWrapper -> ConstOccurrenceContainer
 -> InstanceDriver
 -> OccurrenceDriver
 MutableContainerWrapper -> InstanceDriver
 -> OccurrenceDriver
 
 - constructeur Collection :
 supprimer Collection(C& c) : aucun sens !
 Collection() -> EmptyDriver
 Collection(const C&) -> ConstOcccurrenceDriver
 MutableCollection() -> InstanceDriver<vector>
 MutableCollection(C&) -> OccurrenceDriver (sauf si non-mutable alors InstanceDriver)
 MutableCollection(const C&) -> InstanceDriver
 
 
 - héritage des collections :
 Collection<T> -> ConstCollection<T>
 -> MutableCollection<T>
 virtual Collection<T>::get_driver() const { return empty; }
 
 
 - Iterator <T, K = bool> et Collection <T, K = bool>
 - faire une clef sur les drivers Driver<T, K>
 Driver<T, K>::find_by_key(const K& k) const
 iterator MutableDriver<T, K>::insert(const K& k, const T& t)
 - IteratorDriver<T, K>
 Driver<T,K>::get_key() const
 
 
 - wrapper<set<T>> : public set<T> {
 };
 template<C>
 RefContainerDriver : Driver {
 wrapper<C>::ref _container;
 };
 
 
 - wrapper<map<T,K>> : map<T,K> {
 typedef K key
 bool exist(const K& const;
 };
 
 KeyDriver<T,K> : Driver<T> {
 virtual bool exist(const K&) const = 0;
 };
 
 template <K>
 Collection::exist(const K&) const { key_driver = dynamic_cast<KeyDriver<T,K>>(_driver); return key_driver ? key_driver->exist(key) : false; }
 
 ================= idées pour container universel =======================
 
 principe :décider de la taille de l'objet qui encapsule la data dans le template
 simple liste / double chainée / tree / hash ...
 
 - adjacent list (2 dimensions)
 - xtrist
 - queue
 - stack
 - set/map
 - multiset/multimap
 - simple slist
 - c-array
 - list/vector
 - string
 - (x)tree
 - boost matrice (2 dimensions)
 - hash table
 
 
 =====================
 ** Non-Enumerate : Generic
 first
 empty
 valid ?
 
 ** Collection : Enumerate, Equality_Comparer<col,col> , Inequality_comparer<col>
 valid ?
 empty
 begin
 end
 size
 at
 []
 first
 last
 exist(elem)
 exist(elem, begin, end)
 exist(elem, pos1, pos2)
 union
 intersect
 concat
 cast sur value
 col(const T&)
 col(const col<T>&)
 col(const col&)
 col(const T& begin, const T& end)
 col=col
 col+col
 col +=col
 substract, - ?
 find(elem)
 find(elem, begin, end)
 find(elem, pos1, pos2)
 position(elem)
 position(elem, begin, end)
 position(elem, pos1, pos2)
 col==col, col<col
 col = col >> transformation
 size
 Comparer<int>()
 col<associate,prime> get_associate()
 T = col (T as vector) fill the vector via adapter
 export () copie des datas vers un container
 
 ** reverse_collection:
 rbegin, rend, 
 rfind(elem)
 rfind(elem, begin, end)
 rfind(elem, pos1, pos2)
 rposition(elem)
 rposition(elem, rbegin, rend)
 rposition(elem, pos1, pos2)
 
 ** mutable_collection:
 insert(elem)
 insert_back(elem)
 insert_front(elem)
 insert(it, elem)
 erase_front
 erase_back
 erase(it)
 fill(begin, end)
 
 ** Iterator: Equality_Comparer<it>, Inequality_comparer<it>, diff_iterator
 valid ? empty ?
 it++
 it + int
 it+= int
 it==it, it!=it
 it = it >> transformation
 it < it
 it - it = int
 distance
 
 ** Reverse_iterator:
 it--
 it -= int
 it - int
 
 ** Comparer<X,Y>: X
 X < Y
 X == Y
 
 ** Transformation<prime,associate>
 trans = trans >> trans
 forbid constructor
 Que change la transformation : insert,erase / rbegin,-- 
 
 ** Selection (select) : Transformation
 constructor with accessor
 
 ** Condition (when) : Transformation
 constructor with boolean func
 
 -----------------
 collection<int, string>  : non-mutable
 collection<int&,const string&> : mutable prime non-mutable associate
 iterator<int&,string&> : mutable prime and associate
 --------------------
 current_trait<T> {
 T ref
 T base
 const false
 ref false
 }
 
 current_trait<const T> et current_trait<T&> et <const T&> et les vecteurs ? (si oui prendre celui de la stl?)
 
 à utiliser dans static_type<T, X> {
 current_trait<T>::base base_t;
 current_trait<X>::ref ref_x;
 }
 
 adapter_traits<T, container> : static_type<T> {
 current_trait<container>::base base_container
 }
 
 
 ====================================
 
 IGeneric<X,Y> :Interface {
 private:
 share_pointer<Implementation*> _shared_impl;
 // empty constructor forbidden
 IGeneric();
 protected:
 IGeneric(Implementation* impl) : _shared_impl(impl) {}
 public:
 Implementation* get_implementation() { return _impl; }
 template <T> T* cast_implementation(bool abort = false) { return dynamic_cast<T*> (get_impelemtnation()); }
 
 }
 
 --------------
 IEnumerate<X,Y=X, Interfaces=IGeneric<X,Y> > : IEnumerate<X, Y, interface >, Interfaces 
 {
 public:
 // fonctions bridge ici
 // Operators sur self non virtuel ici
 }
 
 IEnumerate<X, Y=X, interface > : interface 
 {
 public:
 //fonctions abstraites ici
 }
 
 ----------
 IList<X, Y, Interfaces=IEnumerate<X,Y> > : IList<X, Y, interface >, Interfaces 
 {
 public:
 // fonctions bridge ici
 // Operators sur self non virtuel ici
 }
 
 IList<X, Y=X, interface > : interface 
 {
 public:
 //fonctions abstraites ici
 }
 
 ----------
 List<X, Y> : IList<X, Y> {
 public:
 typedef IList<X,Y, Interface> list_interface;
 private:
 list_interface& get_interface() { return *cast_implementation<list_interface*> (true); }
 public:
 List() { ... }
 template<T> List(const T& container) { ... }
 // Operators sur self non virtuel ici
 }
 
 Enumerate<X,Y> : IEnumerate<X,Y> {
 private:
 enumerate_interface& get_interface() { return *cast_implementation<enumerate_interface*> (true); }
 Enumerate() { ... }
 template<T> Enumerate(const T& container) { ... }
 // Operators sur self non virtuel ici
 }
 
 
 ----------
 
 Pour les transformers selection
 Intersection<I1, I2> : Intersection<I1, I2::Inherits> {
 Inherits = Intersection<I1, I2::Inherits>
 }
 Intersection<I1, Generic<X,Y> > : Generic<X,Y> {
 Inherits = Generic<X,Y>
 }
 Intersection<I1, I1> : I1 {
 Inherits = I1
 }
 
 */
/** TODO: FIXME: pour les ++++++++ ITERATOR +++++++
 interface:
 - get_contains_comparator() renvoie un comparateur de contenu depuis l'iterateur courant
 - get_size_comparator() renvoie un comparateur de taille depuis l'iterateur courant
 - get_size() renvoie la taille depuis l'iterateur courant
 - get_sorted() renvoie une collection triée -> Transformer
 - get_reverse() renvoie une collection inverse -> Transformer
 - get_first() si ValueTemplate=pair renvoie Iterator<FirstValue> idem pour second.
 Est-ce un transformer ? En tout cas il y a de la specialisation d'iterateur
 - insert_value() à partir de l'iterateur courant (devant celui-ci?)
 - renommer les adapteur : trouver un ensemble générique.
 - renommer is_valid par is_empty et restart par clear, get_value par get_data et get_instance par get_value ?
 - PB avec le nom des typedefs nom homogènes et des traits 
 a. ex: ValueType qui peut etre une ref ou autre
 b. ex: des fois on met Type des fois non
 c. quels sont que l'ont veut montrer public ?
 - renommer BasicIterator par Generic et InputIterator par DataAccess
 - renommer PtrDiffIterator en DiffIterator parce que tout n'est pas une différence de pointeur!
 - renommer Iterator en ContainerIterator lorsque cela concerne les adapters et factory.
 - renommer diff par distance ?
 feature:
 - traiter le std::reverse et const_reverse dans adapter
 - Est-ce que le duplicate doit-etre dans le IGeneric ?
 - Pouvoir retourner un nouvel objet commet le duplicate mais en copie!
 - ajouter les constructeurs manquant au RandomIteratorFactory. en particulier les template...
 - Est-ce que l'itérateur doit hériter d'une collection?
 - a. changer le nom de is_valid en is_end ou autre...
 b. doit on pouvoir former des iterateurs à partir de rien : constructeur par défaut ?
 c. faire un iterateur vide à partir d'un vector pour le constructeur par défaut de RandomIterator et Iterator
 d. la fonction end() doit donc etre dans reverse_collection
 - faire un BidirIterator
 - ajouter les std traits 
 - un iterateur qui pop à chaque fois que l'on itère si c'est un bag. PopIterator ? où alors c'est caché.
 - ajouter l'opérateur -> utile qd on a une pair dans l'iterateur.
 - j'ai du enelver des protected par public dans le set_implementation. ils sont tous marqués par des FIXME
 - changer le int en size_t dans increment(int offset) et decrement(int offset) car cela implique d'avoir le backward!
 **/


/* les modifiers
 
 class Modifier<Iterator1, Iterator2=Iterator1>
 {
 template <Iterator3>
 Modifier<Iterator1, Iterator3> apply(Modifier<Iterator2,Iterator3>&);
 }
 
 class Iterator1 {
 template <Iterator2>
 Iterator2 apply(Modifier<Iterator1,Iterator2>&);
 }
 */

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
struct ft{
	void f() {}
};
struct ht{
	void f() {}
};

struct gt {
	//	void t(){}
	short _d;
	ft _ft;
	//	void* f;
	//	ht _ht;
	
};
struct xt {
	void t(){}
	void* _d;
	void* _d2;
	ft _ft;
	//	void* f;
	//	ht _ht;
	
};



#include <iostream>
#include <vector>
#include <list>
#include <set>

class publicList:public   
std::_List_base <int, std::allocator<int> > {
public:
	typedef std::_List_base <int, std::allocator<int> >::_List_impl _List_impl;
	typedef std::_List_base <int, std::allocator<int> >::_Node_alloc_type _Node_alloc_type;
};


struct _List_impl 
: public publicList::_Node_alloc_type
{
	std::_List_node_base _M_node;
	
};

struct _List_impl2 

{
	std::_List_node_base _M_node;
	publicList::_Node_alloc_type _a;
};


#if 0
#include "vector_wrapper.h"
#include "set_wrapper.h"
#include "collection.h"
#include "variety_iterator.h"
#include "variety_output_iterator.h"
//#include "variety_collection.h"
#include "variety_std_vector_adapter.h"
//#include "variety_std_map_adapter.h"
#include "variety_std_rb_tree_const_iterator_adapter.h"
#include "variety_gnu_cxx_normal_iterator_adapter.h"
//#include "variety_List.h"

#include "variety_internal_IteratorBridge.h"
#include "variety_internal_PtrDiffIteratorInterface.h"
#include "variety_internal_AdapterIterator_gnu_cxx_normal_iterator.h"
#include "variety_internal_AdapterIterator_std_Rb_tree_iterator.h"
#include "variety_internal_AdapterIterator_std_List_iterator.h"
#include "variety_internal_AdapterIterator_std_Bit_iterator.h"
#include "variety_internal_AdapterIterator_std_Deque_iterator.h"
#include "variety_internal_AdapterIterator_std_Rb_tree_const_iterator.h"
#include "variety_internal_AdapterIterator_std_List_const_iterator.h"
#include "variety_internal_AdapterIterator_std_Bit_const_iterator.h"
#include "variety_internal_AdapterContainer_std_vector.h"
#include "variety_RandomIterator.h"
#include "variety_IteratorFactory.h"
#include "variety_internal_InputIteratorInterface.h"
#include "variety_internal_InputIteratorImplementation.h"
#include "variety_internal_MethodAccessorImplementation.h"
#include "variety_Accessor.h"
#include "variety_Modifier.h"
#include "lazy_Collection.h"
#include "lazy_Iterator.h"
#include "lazy_Modifier.h"



#if 0
class foobar {
public:
	foobar(){}
	template <typename bar>
	bar apply(variety::Accessor<foobar, bar>& accessor) const { return 2;}
};
#endif		  

typedef variety::internal::AdapterIteratorImplementation<variety::internal::RandomIteratorInterface<int>, std::vector<int>::iterator, std::vector<int> > AdapterIteratorImplementationType;
typedef variety::internal::AdapterContainerImplementation<variety::internal::BasicContainerInterface, std::vector<int> > AdapterContainerImplementationType;

#ifdef SHARED_DEBUG

std::set<variety::internal::Implementation*> _ff;
std::set<variety::internal::Implementation*> _gg;
#endif


#endif


#if 0
#include "lazy2_Collection.h"
#include "lazy2_Iterator.h"
#include "lazy2_std_vector.h"
#include "lazy2_Accessor.h"

template <typename OutValue, typename InValue>
inline lazy2::Collection<OutValue> incCollection2(InValue i)
{
	lazy2::Collection<OutValue>f= lazy2::Collection<OutValue>(i+1);
	std::cout <<"temp collection: " <<f[0]<<std::endl;
	
	return f;
}


template <typename OutValue, typename InValue>
inline lazy2::Collection<OutValue> incCollection(InValue i)
{
	return lazy2::Collection<OutValue>(i+1);
}

typedef lazy2::internal::PublishedBridge<lazy2::internal::CollectionInterface<int>, lazy2::Collection<int, void, void, true> > CollectionBridge;



static void myTest() {
	//CollectionBridge c(NULL);
	//c.lazy2::internal::CollectionInterface<int>::createBeginIterator();
}

#endif


#if 0
#include "lazy3_Flow.h"
#include "lazy3_Collection.h"
#include "lazy3_Accessor.h"
#include "lazy3_std_vector.h"
static lazy3::Flow<double> doubleToFlow(double d, int aux) {
	return lazy3::Flow<double> (d + aux);
}


#endif




typedef std::set<int> my_set;

template<typename T, typename Y = T> 
struct foo{
	
	void toto() { std::cout << __LINE__<<std::endl;}
};


template<typename T> 
struct foo<T>{
	void toto() { std::cout << __LINE__<<std::endl;}
};


template <typename OutValue, typename InValue>
inline OutValue inc(InValue i)
{
	return i+1;
}


template <typename OutValue, typename InValue>
inline OutValue identity(InValue i)
{
	static int j =0;
	return j;
}


static double intTodouble(int i) {
	return i;
}




int deprecated_main (int argc, char * const argv[]) {
	
#if 0
	{
		foo<int> f;
		f.toto();
		foo<int,long> f2;
		f2.toto();
		foo<int, int> f3;
		f3.toto();
		foo<int, bool> f4;
		f4.toto();
	}	
	
    // insert code here...
    std::cout << "Hello, World!\n";
#endif
	
	
	
#if 0
#if 0
	{
		std::vector<int> foo;
		std::set<int> foo2;
		my_set foo4;
		Collection<int> dd(foo4);
		const std::vector<int> foo3;
		Collection<int> collection(foo);
		Collection<int> collection4(foo3);
		Collection<int> collection2(foo2);
		Collection<int> collection3;
		MutableCollection<int> collect1;
		std::cout << collection.size() << std::endl;
		
		std::vector<int>::const_iterator it;
		Iterator<int> ite(it);
		return IteratorWrapper<std::vector<int>::const_iterator>::is_mutable;
		//	return IteratorWrapper<__gnu_cxx::__normal_iterator<const int*, std::vector<int, std::allocator<int> > > >::is_mutable;
	}
#endif
#if 0
	{
		std::vector<int> vec;
		variety::iterator<int> it;
		variety::iterator<long> it_long = it;
		variety::output<variety::iterator<int> > it_out(it);
		std::vector<int>::iterator it_vec;
		variety::iterator<int> it_vec2 = it_vec;
		// FIXME:		std::advance(it_vec2, 2);
		variety::collection<int> collect(vec);
		//		variety::output_iterator<variety::iterator<int> > it2(it);
	}
	//    return 0;
#endif
	
	{
		//variety::List<int> l;
		//		variety::List<int> l((variety::Implementation*) NULL);
	}
	
	{
		std::cout << "Start block" << std::endl;
		std::cout << "std::vector<int> a;" << std::endl;
		std::vector<int> a;
#if 1
		
		std::cout << "variety::IteratorFactory<variety::Iterator<int&> > iter3;" << std::endl;
		variety::IteratorFactory<variety::Iterator<int&> > iter3;
		//ContainerImplementationType foo(a);
		//IteratorImplementationType foo2(a.begin(), &foo);
		//IteratorImplementationType foo3(&foo);
#endif
		
#if 1
		std::cout << "variety::IteratorFactory<variety::Iterator<int&> > iter4(a.begin(), a);" << std::endl;
		variety::IteratorFactory<variety::Iterator<int&> > iter4(a.begin(), a);
#endif		
#if 1
		std::cout << "a.push_back(9);" << std::endl;
		a.push_back(9);
		std::cout << "a.push_back(10);" << std::endl;
		a.push_back(10);
		std::cout << "variety::IteratorFactory<variety::RandomIterator<int&> > iter(a);" << std::endl;
    	variety::IteratorFactory<variety::RandomIterator<int&> > iter(a);
#if 1
		
		std::cout << "variety::RandomIterator<int&> iter2 = iter;" << std::endl;
		variety::RandomIterator<int&> iter2 = iter;
		
		std::cout << "iter2.is_valid() "<< iter2.is_valid() << std::endl;
		std::cout << "*iter2 "<< *iter2 << std::endl;
		std::cout << "iter.is_shared_implementation() "<< iter.is_shared_implementation() << std::endl;
		std::cout << "iter2.is_shared_implementation() "<< iter2.is_shared_implementation() << std::endl;
		std::cout << "++iter2; " << std::endl;
		++iter2;
		std::cout << "iter.is_shared_implementation() "<< iter.is_shared_implementation() << std::endl;
		std::cout << "iter2.is_shared_implementation() "<< iter2.is_shared_implementation() << std::endl;
		std::cout << "iter2.is_valid() "<< iter2.is_valid() << std::endl;
		std::cout << "*iter2 "<< *iter2 << std::endl;
		std::cout <<"variety::IRandomIterator<int> iter6 = iter;"<< std::endl;
		variety::RandomIterator<int> iter6 = iter;
		std::cout << "iter6.is_shared_implementation() "<< iter6.is_shared_implementation() << std::endl;
		std::cout << "iter6.is_valid() " <<iter6.is_valid() << std::endl;
		std::cout << "*iter6 "<< *iter6 << std::endl;
		std::cout <<"variety::IRandomIterator<int&> iter5 = iter++;"<< std::endl;
		variety::RandomIterator<int&> iter5 = iter++;
		std::cout << "iter.is_shared_implementation() "<< iter.is_shared_implementation() << std::endl;
		std::cout << "iter5.is_shared_implementation() "<< iter5.is_shared_implementation() << std::endl;
		std::cout << "iter5.is_valid() " <<iter5.is_valid() << std::endl;
		std::cout << "iter.is_valid() "<<iter.is_valid() << std::endl;
		std::cout << "*iter5 "<< *iter5 << std::endl;
		std::cout << "hhh3" << std::endl;
#endif
#endif
		
		
		std::cout<<"variety::IteratorFactory<variety::RandomIterator<int&> > iter8(a.begin(), a);"<<std::endl;
		variety::IteratorFactory<variety::RandomIterator<int&> > iter8(a.begin(), a);
		std::cout<<"variety::RandomIterator<int&> iter10 = iter8;"<<std::endl;
		variety::RandomIterator<int&> iter10 = iter8;
#if 0
		
		std::cout << "variety::TransformIteratorFactory<variety::RandomIterator<int&>> iter7(iter8)"<< std::endl;
		variety::TransformIteratorFactory<variety::RandomIterator<int&> > iter7(iter8);
		
		std::cout << "iter7.is_valid() "<<iter7.is_valid() << std::endl;
		std::cout << "*iter7 "<< *iter7 << std::endl;
#endif
#if 0
		foobar toto;
		variety::Accessor<foobar, int>  accessor2;
		int i = toto.apply(accessor2);
		std::cout <<"toto.apply(accessor2)  "<<i <<std::endl;
#endif
#if 0
		
		variety::Accessor<variety::RandomIterator<int&>, variety::RandomIterator<long&> >  accessor;
		std::cout << "variety::TransformIteratorFactory<variety::RandomIterator<int&>> iter9(iter10, accessor)"<< std::endl;
		variety::TransformIteratorFactory<variety::RandomIterator<long&> > iter9(accessor, iter10);
		
#endif
		std::cout << "free all"<<std::endl;
		
	}
	std::cout << "new test"<<std::endl;
	
	{
		std::vector<std::pair<int,long> > v;
		v.push_back(std::make_pair(1,1000));
		v.push_back(std::make_pair(2,2000));
		v.push_back(std::make_pair(3,3000));
		v.push_back(std::make_pair(2,2000));
		v.push_back(std::make_pair(4,4000));
		std::cout << "variety::IteratorFactory<variety::RandomIterator<std::pair<int, long>& > >  iter1(v)"<<std::endl;
		variety::IteratorFactory<variety::RandomIterator<std::pair<int, long>& > >  iter1(v);
		std::cout << "iter1.is_valid  " << iter1.is_valid() << std::endl;
		std::cout << "(*iter1).second  " << (*iter1).second << std::endl;
		variety::RandomIterator<std::pair<int, long>& > iter2 = iter1;
		std::cout << "(*iter2).second " <<(*iter2).second << std::endl;
		std::cout << "(*iter2).first  " << (*iter2).first << std::endl;
		std::cout << "++iter2  " << std::endl;
		++iter2;
		
		std::cout << "(*iter2).first  " << (*iter2).first << std::endl;
		
		std::cout << "variety::FirstPairFabric b;" << std::endl;
		variety::FirstPairFabric b;
		std::cout << "variety::RandomIterator< int& > iter4 = b.apply( iter2);"<< std::endl;
		variety::RandomIterator< int& > iter4 = b.apply(iter2);
#if 1
#if 1
		std::cout << "iter4.is_valid  " << iter4.is_valid() << std::endl;
		std::cout << "++iter4  " << std::endl;
		++iter4;
		std::cout << "iter4.is_valid  " << iter4.is_valid() << std::endl;
		
		std::cout << "variety::RandomIterator< const int& > iter3 = b.apply(iter2);"<< std::endl;
		variety::RandomIterator< const int& > iter3 = b.apply( iter2);
		std::cout << "*iter3  " <<std::flush << *iter3 << std::endl;
		std::cout << "(*iter2).first  " << (*iter2).first << std::endl;
#endif
		
#if 1
		variety::ReverseFabric rf;
		//std::cout << "iter3++;"<< std::endl;
		//iter3++;
		std::cout << "variety::RandomIterator<int> iter5 = rf.apply(iter3);"<< std::endl;
		variety::RandomIterator<int> iter5 = rf.apply(iter3);
		std::cout << "*iter5  " << *iter5 << std::endl;
		std::cout << "*iter3  " << *iter3 << std::endl;
		std::cout<<"--iter5"<<std::endl;
		--iter5;
		std::cout << "*iter5  " << *iter5 << std::endl;
		
		std::cout << "variety::IteratorFactory<variety::Iterator<std::pair<int, long>& > >  iter6(v);"<< std::endl;
		variety::IteratorFactory<variety::Iterator<std::pair<int, long>& > >  iter6(v);
		std::cout << "variety::Iterator< const int& > iter7 = b.apply(iter6);"<< std::endl;
		variety::Iterator< const int& > iter7 = b.apply( iter6);
		std::cout << "*iter7  " << *iter7 << std::endl;
		std::cout << "(*iter6).first  " << (*iter6).first << std::endl;
#endif
		
#if 0
		// it shouldn't compile ...
		std::cout << "variety::Iterator<int> iter8 = rf.apply(iter7);"<< std::endl;
		variety::Iterator<int> iter8 = rf.apply(iter7);
		std::cout << "*iter8  " << *iter8 << std::endl;
#endif	
		
#if 1
		variety::UniqueFabric unique;
		std::cout << "iter7.restart();"<< std::endl;
		iter7.restart();
		std::cout << "variety::RandomIterator<int> iter10 = unique.apply(iter7);"<< std::endl;
		variety::Iterator<const int&> iter10 = unique.apply(iter7);
		
		while (iter7.is_valid()) {
			std::cout << "*iter7  " << *iter7 << std::endl;
			if (iter10.is_valid()) {
				std::cout << "*iter10 " << *iter10 << std::endl;
			}
			std::cout<<"++iter7"<<std::endl;
			++iter7;
			if (iter10.is_valid()) {
				std::cout<<"++iter10"<<std::endl;
				++iter10;
			}
		}
		
		std::cout << "variety::Iterator<int> ax=iter5;" << std::endl;
		variety::Iterator<int> ax=iter5;
		std::cout <<"*ax " << *ax << std::endl;
		std::cout << "variety::RandomIterator<int> bx = (variety::RandomIterator<int>) ax;"<<std::endl;
		variety::RandomIterator<int> bx = (variety::RandomIterator<int>) ax;
		std::cout <<"*bx " << *bx << std::endl;
		std::cout << "++bx"<<std::endl;
		++bx;
		std::cout <<"*bx " << *bx << std::endl;
		std::cout << "--bx"<<std::endl;
		--bx;
		std::cout <<"*bx " << *bx << std::endl;
		std::cout << "free all"<<std::endl;
		
		std::cout << "variety::RandomIterator<int> cx = (variety::RandomIterator<int>) iter10;"<<std::endl;
		variety::RandomIterator<int> cx = (variety::RandomIterator<int>) iter10;
		std::cout <<"cx.get_implementation() " << cx.get_implementation() << std::endl;
		
#endif
#endif
		
	}
	
	{
		std::cout<< "test Accessor"<<std::endl;
		
		std::cout<< "std::vector<int> vector;"<<std::endl;
		std::vector<int> vector;
		std::cout<< "vector.push_back(0);"<<std::endl;
		vector.push_back(0);
		std::cout<< "vector.push_back(1);"<<std::endl;
		vector.push_back(1);
		std::cout<< "vector.push_back(2);"<<std::endl;
		vector.push_back(2);
		
		std::cout << "variety::IteratorFactory<variety::RandomIterator<int&> > iter_vec(vector);" << std::endl;
		variety::IteratorFactory<variety::RandomIterator<int&> > iter_vec(vector);
		
		
		std::cout<< "variety::Accessor<int> inc_accessor(inc<int, const int&>);"<<std::endl;
		variety::Accessor<int> inc_accessor(inc<int, const int&>);
		
		
		{
			// for compile check
			variety::Accessor<int> accessor0(identity<int, const int&>);
			variety::Accessor<int> accessor1(identity<int, const int>);
			variety::Accessor<int> accessor2(identity<int, int>);
			variety::Accessor<int> accessor3(identity<const int&, const int&>);
			variety::Accessor<int> accessor4(identity<const int&, const int>);
			variety::Accessor<int> accessor5(identity<const int&, int>);
			variety::Accessor<int> accessor6(identity< int&, const int&>);
			variety::Accessor<int> accessor7(identity< int&, const int>);
			variety::Accessor<int> accessor8(identity< int&, int>);
#if 0			//FIXME : not checked !!!
			int (*x) (const int*);
			variety::Accessor<int, int*> accessor10(x);
			//variety::Accessor<int, int*> accessor9(identity<int, const int*>);
#endif	
#if 0  // for debug purpose, it shouldn't compile
			variety::Accessor<int> accessor3(identity<int, int&>);
#endif
		}
		
		variety::Iterator<int> inc_iter_vec = iter_vec.apply(inc_accessor);
		
		while (iter_vec.is_valid()) {
			std::cout<<"*iter_vec " << *iter_vec << std::endl;
			std::cout<<"*inc_iter_vec " << *inc_iter_vec << std::endl;
			std::cout<<"++iter_vec;"<<std::endl;
			++iter_vec;
			std::cout<<"++inc_iter_vec;"<<std::endl;
			++inc_iter_vec;
		}
		
		
		std::cout<<"Free all"<<std::endl;
	}
#if 0
	{
		std::cout << "begin test of lazy"<<std::endl;
		{
			lazy::Collection<int> c(0);
			lazy::Modifier<int> m;
			lazy::Iterator<int> it;
		}
		
		
		std::cout << "end test of lazy"<<std::endl;
	}
#endif
	
#endif
	
	
#if 0
	
	{
		std::cout << "begin test of lazy2"<<std::endl;
		{
			std::cout << "lazy2::Collection<int> t(6);" << std::endl;
			lazy2::Collection<int> t(6);
			std::cout << "t.size() " <<t.size() << std::endl;
			std::cout << "t[0] "<< t[0] << std::endl;
			std::cout << "lazy2::Iterator<int> d(5);" << std::endl;
			lazy2::Iterator<int> d(5);
			std::cout << "lazy2::Iterator<int> d2=d;" << std::endl;
			lazy2::Iterator<int> d2=d;
			std::cout << "*d " << *d << std::endl;
			std::cout << "++d;" << std::endl;
			++d;
			std::cout << "d++;" << std::endl;
			d++;
			std::cout << "d=d+2;" << std::endl;
			d=d+2;
			std::cout << "d+=3;" << std::endl;
			d+=3;
			std::cout << "d2+=7;" << std::endl;
			d2+=7;
			std::cout << "d2==d " << (d2==d) << std::endl;
			
			std::cout << "lazy2::Iterator<int> c2 = t.begin();" << std::endl;
			lazy2::Iterator<int> c2 = t.begin();
			std::cout << "*c2 " << *c2 << std::endl;
			std::cout << "c2==t.begin() " << (c2==t.begin()) << std::endl;
			std::cout << "*c2 " << *c2 << std::endl;
			std::cout << "c2+1==t.begin() " << (c2+1==t.begin()) << std::endl;
			std::cout << "*c2 " << *c2 << std::endl;
			std::cout << "*(c2+1) " << *(c2+1) << std::endl;
			std::cout << "c2==t.end() " << (c2==t.end()) << std::endl;
			std::cout << "c2!=t.end() " << (c2!=t.end()) << std::endl;
			std::cout << "c2+1==t.end() " << ((c2+1)==t.end()) << std::endl;
			std::cout << "c2+1!=t.end() " << ((1+c2)!=t.end()) << std::endl;
			std::cout << "c2!=t.end() " << (c2!=t.end()) << std::endl;
			std::cout << "*c2 "<<*c2 << std::endl;
			
			std::cout<<"lazy2::Iterator<int> c();"<<std::endl;			
			lazy2::Iterator<int> c();
			std::cout<<"lazy2::Iterator<int> e=d;"<<std::endl;
			lazy2::Iterator<int> e=d;
			
			
			std::cout<<"std::vector<int> v;"<<std::endl;
			std::vector<int> v;
			std::cout<<"v.push_back(5);"<<std::endl;
			v.push_back(5);
			std::cout<<"v.push_back(6);"<<std::endl;
			v.push_back(6);
			
			
			std::cout<<"lazy2::Collection<int> t2((const std::vector<int>&) v);"<<std::endl;
			lazy2::Collection<int> t2((const std::vector<int>&) v);
			std::cout<< "t2.size() " <<t2.size()<< std::endl;
			std::cout<< "t2[0] " <<t2[0] << std::endl;
			for (lazy2::Iterator<int> xx = t2.begin(); xx != t2.end(); ++xx) {
				std::cout << "*xx " << *xx << std::endl;
			}
			
			
			std::cout<<"lazy2::Iterator<int> it3(v);"<<std::endl;
			lazy2::Iterator<int> it3(v);
			std::cout<< "*it3  "<<*it3 <<std::endl;
			
			{
				std::cout<<""<<std::endl;
				std::cout<<"checkin out of scope access"<<std::endl;
				std::cout<< "lazy2::Collection<int> f;"<< std::endl;
				lazy2::Collection<int> f;
				std::cout<<"{  // enter scope"<<std::endl;
				{
					std::cout<< "    lazy2::Collection<int> f2(2);"<< std::endl;
					lazy2::Collection<int> f2(2);
					std::cout<< "    f = f2;"<< std::endl;
					f = f2;
					std::cout<< "    f[0] "<<f[0] << std::endl;
				}
				std::cout<<"}  // outside scope"<<std::endl;
				std::cout<< "f[0] "<< f[0] << std::endl;
				std::cout<<"end test of scope scope"<<std::endl;
				
				
				
				std::cout<<""<<std::endl;
			}
			
#if 1
			{
				std::cout<<""<<std::endl;
				int t = 2;
				lazy2::Collection<int*> pt(&t);
				std::cout<< "pt[0] " << pt[0] << "==" << &t << std::endl;
#if 0
				lazy2::Collection<int&> ref(t);
				std::cout<< "ref[0] " << ref[0] << std::endl;
				lazy2::Collection<const int&> cstref(t);
				std::cout<< "cstref[0] " << cstref[0] << std::endl;
				lazy2::Collection<const int> cst(t);
				std::cout<< "cst[0] " << cst[0] << std::endl;
#endif
			}
#endif
			{
				std::cout<<""<<std::endl;
				//lazy2::internal::FlattenIteratorImplementation<lazy2::Collection<int> > impl(NULL, NULL);
				//lazy2::internal::FlattenCollectionImplementation<lazy2::Collection<int> > impl2(NULL);
				std::cout << "lazy2::Collection<lazy2::Collection<int> > g;" << std::endl;
				lazy2::Collection<lazy2::Collection<int> > g;
				std::cout << "lazy2::Iterator<lazy2::Collection<int> > it2;" << std::endl;
				lazy2::Iterator<lazy2::Collection<int> > it2;
				//std::cout << "lazy2::Collection<int> c2 = *it2;" << std::endl;
				//lazy2::Collection<int> c2 = *it2;
				//std::cout << "c2.size() "<< std::flush<< c2.size() << std::endl;
				//std::cout << "c2[0] "<< std::flush<< c2[0] << std::endl;
				std::cout << "lazy2::Iterator<lazy2::Collection<int> > it = g.begin();" << std::endl;
				lazy2::Iterator<lazy2::Collection<int> > it = g.begin();
				//std::cout << "lazy2::Collection<int> c = *it;" << std::endl;
				//lazy2::Collection<int> c = *it;
				//std::cout << "lazy2::Iterator<int> subIt = c.begin();" << std::endl;
				//lazy2::Iterator<int> subIt = c.begin();
				//std::cout << "*subIt "<< std::flush<< *subIt << std::endl;
				//std::cout << "c[0] "<< std::flush<< c[0] << std::endl;
				std::cout << "g.begin() == g.end() "<< std::flush<< (g.begin() == g.end()) << std::endl;
				assert(g.begin() == g.end());
				std::cout << "g.size() "<< std::flush<< g.size() << std::endl;
				assert(g.size() == 0);
				std::cout << "g[0].size() "<< std::flush<< g[0].size() << std::endl;
				std::cout << "g[0][0] "<< std::flush<< g[0][0] << std::endl;
				std::cout << "g.flatten().size() "<< std::flush << g.flatten().size() << std::endl;
				assert(g.flatten().size() == 0);
				
				
			}
			{
				std::cout<<"" <<std::endl;
				std::cout<<"*** testing Temp obj collection ...." <<std::endl;
				std::cout<<"lazy2::Collection<int> d=incCollection2<int>(5);"<<std::endl;
				lazy2::Collection<int> d=incCollection2<int>(5);
				std::cout<<"6?  d[0] = "<< d[0]<<" "<<d.size()<<std::endl;
				
			}
			{
				std::cout<<"" <<std::endl;
				std::cout<<"*** testing now Accessor ...." <<std::endl;
				std::vector<int> vec;
				vec.push_back(3);
				vec.push_back(4);
				vec.push_back(5);
				int (*func)(int);
				func = inc<int,int>;
				std::cout<<"lazy2::Accessor<int> acc(func);" <<std::endl;
				lazy2::Accessor<int> acc(func);
				std::cout<<"lazy2::Collection<int> c(vec);  // vec = 3 4 5" <<std::endl;
				lazy2::Collection<int> c(vec);
				std::cout << "c.size() = "<< std::flush<< c.size() << std::endl;
				assert(c.size() == 3);
				std::cout<<"lazy2::Collection<int> a = c.associate(acc);" <<std::endl;
				lazy2::Collection<int> a = c.associate(acc);
				std::cout << "a.size() = "<< std::flush<< a.size() << std::endl;
				assert(a.size() == 3);
				std::cout << "a[0] ==3+1 ? "<< std::flush<< a[0] << std::endl;
				assert(a[0] == 4);
				std::cout<<"lazy2::Accessor<int> acc2(inc<int,int>);" <<std::endl;
				lazy2::Accessor<int> acc2(inc<int,int>);
				
				
				std::cout<<"lazy2::Accessor<int> acc3(lazy2::incCollection<int,int>);" <<std::endl;
				lazy2::Accessor<lazy2::Collection<int>, int> acc3(incCollection<int,int>);
				std::cout<<"lazy2::Collection<lazy2::Collection<int> > a3 = c.associate(acc3);" <<std::endl;
				lazy2::Collection<lazy2::Collection<int> > a3 = c.associate(acc3);
				std::cout << "c.size()"<< std::flush<< c.size() << std::endl;
				assert(c.size() == 3);
				std::cout << "a3.size()"<< std::flush<< a3.size() << std::endl;
				assert(a3.size() == 3);
				std::cout<<"lazy2::Collection<int> elem_a3 = a3[0];" <<std::endl;
				lazy2::Collection<int> elem_a3 = a3[0];
				std::cout << "elem_a3.size()"<< std::flush<< elem_a3.size() << std::endl;
				assert(elem_a3.size() == 1);
				
				std::cout << "a3[0][0] ==3+1 ? "<< std::flush<< a3[0][0] << std::endl;
				assert(a3[0][0] == 4);
				std::cout << "elem_a3[0] ==3+1 ? "<< std::flush<< elem_a3[0] << std::endl;
				assert(elem_a3[0] == 4);
				std::cout<<"lazy2::Collection<int> flatten_a3=a3.flatten();" <<std::endl;
				lazy2::Collection<int> flatten_a3=a3.flatten();
				std::cout << "flatten_a3.size()"<< std::flush<< flatten_a3.size() << std::endl;
				assert(flatten_a3.size() == 3);
				std::cout << "flatten_a3[0] ==3+1 ? "<< std::flush<< flatten_a3[0] << std::endl;
				assert(flatten_a3[0] == 4);
				
			}
			
			{
				std::cout<<"" <<std::endl;
				std::cout<<"*** testing now Inheritance between Collection ...." <<std::endl;
				std::cout << 
				"lazy2::Collection<int, long> C_int_long;"  << std::endl <<
				"lazy2::Collection<int, void> C_int_void = C_int_long;"  << std::endl <<
				"lazy2::Collection<int, long, std::vector<int> > C_int_long_vector;"  << std::endl <<
				""  << std::endl <<
				"lazy2::Collection<int, void, std::vector<int> > C_int_void_vector;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int> > C_int_void_c_int;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int, long, lazy2::Collection<int> > > C_int_void_c_int_long_c_int;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int, long, std::vector<int> > > C_int_void_c_int_long_vector;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int, void> > C_int_void_c_void_void;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int, void> > C_int_void_c_void_void2 = C_int_void_c_int_long_vector;"  << std::endl <<
				"lazy2::Collection<int, void, lazy2::Collection<int, void> > C_int_void_c_void_void3(C_int_void_c_int_long_vector);"  << std::endl <<
				"lazy2::Collection<int, void, void> C_int_void_void = C_int_void_c_int_long_vector;"  << std::endl <<
				"C_int_void_void = C_int_void_c_void_void;"  << std::endl <<
				""  << std::endl <<
				"lazy2::Collection<lazy2::Collection<int>, void, lazy2::Collection<int> > C_c_int_void_c_int;"  << std::endl <<
				""  << std::endl
				<< std::endl;
				
				
				lazy2::Collection<int, long> C_int_long;
				lazy2::Collection<int, void> C_int_void = C_int_long;
				lazy2::Collection<int, long, std::vector<int> > C_int_long_vector;
				
				lazy2::Collection<int, void, std::vector<int> > C_int_void_vector;
				lazy2::Collection<int, void, lazy2::Collection<int> > C_int_void_c_int;
				lazy2::Collection<int, void, lazy2::Collection<int, long, lazy2::Collection<int> > > C_int_void_c_int_long_c_int;
				lazy2::Collection<int, void, lazy2::Collection<int, long, std::vector<int> > > C_int_void_c_int_long_vector;
				lazy2::Collection<int, void, lazy2::Collection<int, void> > C_int_void_c_void_void;
				lazy2::Collection<int, void, void > C_int_void_c_void_void2 = C_int_void_c_int_long_vector;
				lazy2::Collection<int, void, lazy2::Collection<int, void> > C_int_void_c_void_void3(C_int_void_c_int_long_vector);
				lazy2::Collection<int, void, void> C_int_void_void = C_int_void_c_int_long_vector;
				C_int_void_void = C_int_void_c_void_void;
				
				lazy2::Collection<lazy2::Collection<int>, void, lazy2::Collection<int> > C_c_int_void_c_int;
			}				
			{
				std::cout<<"" <<std::endl;
				std::cout<<"*** testing now inner ...." <<std::endl;
				
				std::cout << "std::vector<int> v;" << std::endl;
				std::vector<int> v;
				std::cout << "v.push_back(5);" << std::endl;
				v.push_back(5);
				std::cout << "lazy2::Collection<int, void, std::vector<int> > C_int_long_vector(v);" << std::endl;
				lazy2::Collection<int, void, std::vector<int> > C_int_void_vector(v);
				std::cout << "std::vector<int>& v2 = C_int_long_vector.inner();" << std::endl;
				std::vector<int>& v2 = C_int_void_vector.inner();
				std::cout << "v2[0]=5 ?  " << v2[0] << std::endl;
				assert(v2[0] == 5);
				std::cout<<"lazy2::Accessor<int> acc3(lazy2::incCollection<int,int>);" <<std::endl;
				lazy2::Accessor<lazy2::Collection<int>, int> acc3(incCollection<int,int>);
				std::cout<<"lazy2::Collection<lazy2::Collection<int>, int, lazy2::Collection<int, void, std::vector<int> > > C_int_int_c_int_void_vector = C_int_void_vector.associate(acc3);" <<std::endl;
				lazy2::Collection<lazy2::Collection<int>, int, lazy2::Collection<int, void, std::vector<int> > > C_int_int_c_int_void_vector = C_int_void_vector.associate(acc3);
				std::cout << "C_int_int_c_int_void_vector[0][0]=6 ?  " << C_int_int_c_int_void_vector[0][0] << std::endl;
				assert(C_int_int_c_int_void_vector[0][0] == 6);
				std::cout << "std::vector<int>& v3 = C_int_int_c_int_void_vector.inner().inner();" << std::endl;
				std::vector<int>& v3 = C_int_int_c_int_void_vector.inner().inner();
				std::cout << "v3[0]=5 ?  " << v3[0] << std::endl;
				assert(v3[0] == 5);
				std::cout << "lazy2::Collection<int, void, std::vector<int> >& c_int_void_vector3 = C_int_int_c_int_void_vector.inner();" << std::endl;
				lazy2::Collection<int, void, std::vector<int> >& c_int_void_vector3 = C_int_int_c_int_void_vector.inner();
				std::cout << "c_int_void_vector3[0]=5 ?  " << c_int_void_vector3[0] << std::endl;
				assert(c_int_void_vector3[0] == 5);
			}		
			{
				std::cout<<"" <<std::endl;
				std::cout<<"*** testing now concatenation ...." <<std::endl;
				
				
				lazy2::Collection<int, long> c1;
				lazy2::Collection<int> c2;
				lazy2::Collection<int> c3 = c1 + c2;
				
			}
		}		
		
		std::cout << "end test of lazy 2"<<std::endl;
	}
#endif
	
#if 0	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "test of lazy 3"<<std::endl;
	{
		std::cout << "single test"<<std::endl;
		
		std::cout << "lazy3::Generic gen;"<<std::endl;
		lazy3::Generic gen;
		std::cout << "gen.empty() ? " << gen.empty() <<std::endl;
		
		std::cout << "lazy3::Flow<int, void, int> flow;"<<std::endl;
		lazy3::Flow<int, void, int> flow;
		std::cout << "flow.empty() ? " << flow.empty() <<std::endl;
		std::cout << "flow.forward() ? " << flow.forward() <<std::endl;
		std::cout << "flow.forward() ? " << flow.forward() <<std::endl;
		//std::cout << "flow.container() ? " << flow.container() <<std::endl;
		
		std::cout << "lazy3::Flow<int, void, int> flow2 = lazy3::Flow<int, void, int>();" <<std::endl;
		lazy3::Flow<int, void, int> flow2 = lazy3::Flow<int, void, int>();
		std::cout << "flow2.empty() ? " << flow2.empty() <<std::endl;
		std::cout << "flow2.forward() ? " << flow2.forward() <<std::endl;
		std::cout << "flow2.forward() ? " << flow2.forward() <<std::endl;
		
		std::cout << "lazy3::Flow<int, int, void> flow2 = lazy3::Flow<int, int, void>();" <<std::endl;
		lazy3::Flow<int, int, void> flow3 = lazy3::Flow<int, int, void>();
		std::cout << "flow3.empty() ? " << flow3.empty() <<std::endl;
		std::cout << "flow3.forward() ? " << flow3.forward() <<std::endl;
		std::cout << "flow3.forward() ? " << flow3.forward() <<std::endl;
		
		std::cout << "lazy3::Flow<void, int, void> flow4 = lazy3::Flow<int, int, void>();" <<std::endl;
		lazy3::Flow<void, int, void> flow4 = lazy3::Flow<int, int, void>();
		std::cout << "flow4.empty() ? " << flow4.empty() <<std::endl;
		std::cout << "flow4.forward() ? " << flow4.forward() <<std::endl;
		std::cout << "flow4.forward() ? " << flow4.forward() <<std::endl;
		
		std::cout << "lazy3::Collection<void, int, void> collection = lazy3::Collection<int, int, void>();" <<std::endl;
		lazy3::Collection<int, int, void> collection = lazy3::Collection<int, int, void>();
		std::cout << "collection.empty() ? " << collection.empty() <<std::endl;
		
		{
			std::cout << "accessor test"<<std::endl;
			
			std::cout << "lazy3::Flow<int> flow3;" <<std::endl;
			lazy3::Flow<int> flow3;
			
			std::cout << "lazy3::Accessor<int, double> accessor;" <<std::endl;
			lazy3::Accessor<int, double> accessor(intTodouble);
			
			std::cout << "lazy3::Flow<double> flow4 = flow3.modifyFirst(accessor);" <<std::endl;
			lazy3::Flow<double> flow4 = flow3.modifyFirst(accessor);
			
			std::cout << "lazy3::Flow<int> flow5 = flow3.filterFirst(accessor);" <<std::endl;
			lazy3::Flow<int> flow5 = flow3.filterFirst(accessor);
			
			std::cout << "lazy3::Accessor<double, lazy3::Flow<double>, int> accessor2;" <<std::endl;
			lazy3::Accessor<double, lazy3::Flow<double>, int> accessor2(doubleToFlow);
			
			std::cout << "lazy3::Flow<lazy3::Flow<double> > flow6 = flow4.modifyFirst(accessor2);" <<std::endl;
			lazy3::Flow<lazy3::Flow<double> > flow6 = flow4.modifyFirst(accessor2);
		}
		
		{
			std::cout << "modifier from flow test"<<std::endl;
			
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow3;" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow3;
			
			std::cout << "std::vector<int> vec1;" <<std::endl;
			std::vector<int> vec1;
			
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow4 = flow3.build(vec1);" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow4 = flow3.build(vec1);
			
			std::cout << "flow4.empty() ?" <<std::flush;
			std::cout << flow4.empty()  << std::endl;
		}
		
		
		{
			std::cout << "link modifier"<<std::endl;
			
			std::cout << "lazy3::Modifier<int, double> accessor;" <<std::endl;
			lazy3::Modifier<int, double> accessor;
			
			std::cout << "lazy3::Modifier<double, lazy3::Flow<double>, int> accessor2;" <<std::endl;
			lazy3::Modifier<double, lazy3::Flow<double> > accessor2;
			
			std::cout << "lazy3::Modifier<int, lazy3::Flow<double> > accessor3 = accessor.link(accessor2);" <<std::endl;
			lazy3::Modifier<int, lazy3::Flow<double> > accessor3 = accessor.link(accessor2);
			
			std::cout << "lazy3::Flow<double, void, int> flow3 = accessor3;" <<std::endl;
			//int ff = 2;
			//lazy3::Flow<double> flow3 = accessor3.build(ff);
			//std::cout << flow3.first() << std::endl;
			lazy3::Modifier<int, lazy3::Flow<double, void, int> > accessor4;
			//lazy3::Flow<double, void, int> flow4 = accessor4.build(ff);
			//std::cout << flow4.container() << std::endl;
		}
		
		{
			std::cout << "increment flow test"<<std::endl;
			
			std::cout << "std::vector<int> vec1 = {1,2};" <<std::endl;
			std::vector<int> vec1;
			vec1.push_back(1);
			vec1.push_back(2);
			int i;
			
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow(vec1);" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow(vec1);
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow_bis = flow;" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow_bis = flow;
			i = 0;
			while (!flow_bis.empty()) {
				std::cout << "flow_bis[" << i++ << "]:" <<std::flush;
				std::cout << flow_bis.first() <<std::endl;
				flow_bis.forward();
			}
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow_empty = flow_bis;" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow_empty = flow_bis;
			std::cout << "flow_empty.empty? " << flow_empty.empty() << "" <<std::endl;
			
			i = 0;
			while (!flow_bis.empty()) {
				std::cout << flow_bis.first() <<std::endl;
				flow_bis.forward();
			}
			i = 0;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				flow.forward();
			}
			std::cout << "std::vector<int> vec2 = {3,4};" <<std::endl;
			std::vector<int> vec2;
			vec2.push_back(3);
			vec2.push_back(4);
			std::cout << "lazy3::Flow<int, void, std::vector<int> > flow2 = flow.change(vec2);" <<std::endl;
			lazy3::Flow<int, void, std::vector<int> > flow2 = flow.build(vec2);
			i = 0;
			while (!flow2.empty()) {
				std::cout << "flow2[" << i++ << "]:" <<std::flush;
				std::cout << flow2.first() <<std::endl;
				flow2.forward();
			}
			std::cout << "flow = flow2;" <<std::endl;
			flow = flow2;
			i = 0;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				flow.forward();
			}
			i = 0;
			while (!flow_bis.empty()) {
				std::cout << "flow_bis[" << i++ << "]:" <<std::flush;
				std::cout << flow_bis.first() <<std::endl;
				flow_bis.forward();
			}
			
			
		}
		
		{
			std::cout << "static cast"<<std::endl;
			lazy3::Flow<int, double> flow_long;
			lazy3::Flow<long, double> flow_int = flow_long;
			
			
		}
		{
			std::cout << "copy collection and write"<<std::endl;
			
			std::vector<int> vec_int;
			vec_int.push_back(1);
			vec_int.push_back(2);
			vec_int.push_back(3);
			std::vector<int> vec_int2;
			vec_int2.push_back(-1);
			vec_int2.push_back(-2);
			vec_int2.push_back(-3);
			
			lazy3::Flow<int, void, std::vector<int> > flow_int = vec_int;
			flow_int.forward();
			lazy3::Flow<int, void, std::vector<int> > flow_int2 = flow_int;
			std::cout << &(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int).container()) << "  "<<&(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int2).container())<<std::endl;
			std::cout << flow_int.first() << " copy " << flow_int2.first() << " ref " <<vec_int[0]<<" "<<vec_int2[0]<<std::endl;
			std::cout << &(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int).container()) << "  "<<&(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int2).container())<<std::endl;
			flow_int2.forward();
			std::cout << &(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int).container()) << "  "<<&(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int2).container())<<std::endl;
			std::cout << flow_int.first() << " copy " << flow_int2.first() << " ref " <<vec_int[0]<<" "<<vec_int2[0]<<std::endl;
			std::cout << &(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int).container()) << "  "<<&(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int2).container())<<std::endl;
			flow_int2.container(vec_int2);
			//flow_int.container() = vec_int2;
			std::cout << &(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int).container()) << "  "<<&(((const lazy3::Flow<int, void, std::vector<int> >&)flow_int2).container())<<std::endl;
			std::cout << &(flow_int.container()) << "  "<<&(flow_int2.container())<<std::endl;
			std::cout << flow_int.first() << " copy " <<flow_int2.first() << " ref " <<vec_int[0]<<" "<<vec_int2[0]<<std::endl;
			flow_int.forward();
			std::cout << flow_int.first() << " copy " <<flow_int2.first() << " ref " <<vec_int[0]<<" "<<vec_int2[0]<<std::endl;
			
		}
		
		
		{
			std::cout << "increment and decrement iterator test"<<std::endl;
			
			std::cout << "std::vector<int> vec1 = {1,2};" <<std::endl;
			std::vector<int> vec1;
			vec1.push_back(1);
			vec1.push_back(2);
			
			std::cout << "lazy3::Iterator<int, void, std::vector<int> > flow(vec1);" <<std::endl;
			lazy3::Iterator<int, void, std::vector<int> > flow(vec1);
			int i = 0;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				flow.forward();
			}
			std::cout << "std::vector<int> vec2 = {3,4};" <<std::endl;
			std::vector<int> vec2;
			vec2.push_back(3);
			vec2.push_back(4);
			std::cout << "lazy3::Iterator<int, void, std::vector<int> > flow2 = flow.change(vec2);" <<std::endl;
			lazy3::Iterator<int, void, std::vector<int> > flow2 = flow.build(vec2);
			i = 0;
			while (!flow2.empty()) {
				std::cout << "flow2[" << i++ << "]:" <<std::flush;
				std::cout << flow2.first() <<std::endl;
				flow2.forward();
			}
			flow2.backward();
			std::cout << "flow2[" << --i << "]:" <<std::flush;
			std::cout << flow2.first() <<std::endl;
			flow2.backward();
			std::cout << "flow2[" << --i << "]:" <<std::flush;
			std::cout << flow2.first() <<std::endl;
			
			
		}
		
		{
			std::cout << "iterator on collection test"<<std::endl;
			
			std::cout << "std::vector<int> vec1 = {1,2};" <<std::endl;
			std::vector<int> vec1;
			vec1.push_back(1);
			vec1.push_back(2);
			
			std::cout << "lazy3::Collection<int, void, std::vector<int> > collection(vec1);" <<std::endl;
			lazy3::Collection<int&, void, std::vector<int> > collection(vec1);
			lazy3::Collection<int&, void, std::vector<int> > collection2 = collection;
			int i = 0;
			std::cout << "lazy3::Iterator<int, void, std::vector<int> > flow = collection.begin();" <<std::endl;
			lazy3::Iterator<int&, void, std::vector<int> > flow = collection.begin();
			lazy3::Iterator<int&, void, std::vector<int> > flow2 = flow;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				std::cout << "flow2[" << 0 << "]:" <<std::flush;
				std::cout << flow2.first() <<std::endl;
				flow.forward();
			}
			flow2.first() = 5;
			
			i = 0;
			flow = flow2;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				std::cout << "flow2[" << 0 << "]:" <<std::flush;
				std::cout << flow2.first() <<std::endl;
				std::cout << "collection2[" << 0 << "]:" <<std::flush;
				std::cout << collection2.begin().first() <<std::endl;
				flow.forward();
			}
			vec1[0] = 6;
			i = 0;
			flow = flow2;
			while (!flow.empty()) {
				std::cout << "flow[" << i++ << "]:" <<std::flush;
				std::cout << flow.first() <<std::endl;
				std::cout << "flow2[" << 0 << "]:" <<std::flush;
				std::cout << flow2.first() <<std::endl;
				std::cout << "collection2[" << 0 << "]:" <<std::flush;
				std::cout << collection2.begin().first() <<std::endl;
				flow.forward();
			}
			
		}
	}
	std::cout << "end of test of lazy 3"<<std::endl;
	
	std::cout << "end of test"<<std::endl;
#endif

	
	
}
