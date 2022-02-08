  template <typename E>					// constructor
  SearchTree<E>::SearchTree() : T(), n(0)
    { T.addRoot(); T.expandExternal(T.root()); }	// create the super root
  
  template <typename E>					// get virtual root
  typename SearchTree<E>::TPos SearchTree<E>::root() const
    { return T.root().left(); }				// left child of super root
  
   template <typename E>					// iterator to first entry
  typename SearchTree<E>::Iterator SearchTree<E>::begin() {
    TPos v = root();					// start at virtual root
    while (v.isInternal()) v = v.left();		// find leftmost node
    return Iterator(v.parent());
  }
  
  template <typename E>					// iterator to end entry
  typename SearchTree<E>::Iterator SearchTree<E>::end()
    { return Iterator(T.root()); }			// return the super root
    
  template <typename E>					// remove key k entry
  void SearchTree<E>::erase(const K& k) { //throw(NonexistentElement) {
    TPos v = finder(k, root());				// search from virtual root
    eraser(v);						// remove it
  }
  
  template <typename E>					// erase entry at p
  void SearchTree<E>::erase(const Iterator& p)
    { eraser(p.v); }
    
  template <typename E>					// find entry with key k
  typename SearchTree<E>::Iterator SearchTree<E>::find(const K& k) {
    TPos v = finder(k, root());				// search from virtual root
    if (v.isInternal()) return Iterator(v);		// found it
    else return end();					// didn't find it
  }  
  
  template <typename E>					// insert (k,x)
  typename SearchTree<E>::Iterator SearchTree<E>::insert(const K& k, const V& x)
    { TPos v = inserter(k, x); return Iterator(v); }  
 
  template <typename E>
  int SearchTree<E>::size() const { return n; }  
    
    
//
// ToDo
//    
 
  template <typename E>					// inorder successor
  typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
    TPos w = v.right();
    
    if (w.isInternal()) {
        do {
            v = w;
            w = w.left();
        } while (w.isInternal());
    } else {
        w = v.parent();
        while (v == w.right()) {
            v = w;
            w = w.parent();
        }
        
        v = w;
    }
        
    return *this;
  }
     
    
    
  template <typename E>					// remove utility
  typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
    TPos w;
    if (v.left().isExternal()) {
        w = v.left();
    }
    else if (v.right().isExternal()) {
        w = v.right();
    }
    else {
        w = v.right();
        do { w = w.left(); } while (w.isInternal());
        TPos u = w.parent();
        (v.v)->elt.setKey((u.v)->elt.key()); (v.v)->elt.setValue((u.v)->elt.value());
    }
    
    n--;
    
    return T.removeAboveExternal(w);
  }
      
  template <typename E>					// find utility
  typename SearchTree<E>::TPos SearchTree<E>::finder(const K& k, const TPos& v) {
    TPos tmp;
    tmp.v = v.v;
    while(true) {
      if (tmp.isExternal())
        return tmp;
    if(k < (tmp.v)->elt.key())
            tmp = tmp.left();
    else if ((tmp.v)->elt.key() < k)
            tmp = tmp.right();
    else
        return tmp;
    }
  }
  
  template <typename E>					// insert utility
  typename SearchTree<E>::TPos SearchTree<E>::inserter(const K& k, const V& x) {
    
    TPos v = finder(k, root());
    
    if(v.isInternal()) {
        (v.v)->elt.setKey(k);
        (v.v)->elt.setValue(x);
        return v;
    }
    
    T.expandExternal(v);
    (v.v)->elt.setKey(k);
    (v.v)->elt.setValue(x);
    n++;
    
    return v;
  }
