# interval_tree<Key, Value, Comp>::insert

```cpp
iterator insert( const value_type& value );                 // (1)
iterator insert( value_type&& value );                      // (2)
template<class InputIt>
void insert( InputIt first, InputIt last );             // (3)
void insert( std::initializer_list<value_type> ilist ); // (4)
```

Inserts element(s) into the container.

1. 
2. Insert value
3. Inserts elements from range `[first, last)`
4. Inserts elements from initializer list `ilist`.

#### Parameters

- **value** : element to insert
- **first, last** : range of elements to insert
- **ilist** : initializer list to insert the values from

#### Returns

1. 
2. an iterator to the inserted element
3.  
4. (none)

#### Complexity

Logarithmic in the size of the container