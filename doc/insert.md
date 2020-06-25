# interval_tree<Key, Value, Comp>::insert

```cpp
iterator insert( const value_type& value );
iterator insert( value_type&& value );                           // (1)
//---------------------------------------------------------------------
template<class P>
iterator insert( P&& value );                                    // (2)
//---------------------------------------------------------------------
iterator insert( const_iterator hint, const value_type& value );
iterator insert( const_iterator hint, value_type&& value );      // (3)
//---------------------------------------------------------------------
template<class P>
iterator insert( const_iterator hint, P&& value );               // (4)
//---------------------------------------------------------------------
template<class InputIt>
void insert( InputIt first, InputIt last );                      // (5)
//---------------------------------------------------------------------
void insert( std::initializer_list<value_type> ilist );          // (6)
```

Inserts element(s) into the container.

1. 
2. inserts value. If the container has elements with equivalent key, inserts at the upper bound of that range. The overload (2) is equivalent to `emplace(std::forward<P>(value))` and only participates in overload resolution if `std::is_constructible<value_type, P&&>::value == true`.
3. 
4. inserts value in the position as close as possible to hint. The overload (4) is equivalent to `emplace_hint(hint, std::forward<P>(value))` and only participates in overload resolution if `std::is_constructible<value_type, P&&>::value == true`.
5. Inserts elements from range `[first, last)`
6. Inserts elements from initializer list `ilist`.

No iterators or references are invalidated.

#### Parameters

- **hint** : iterator, used as a suggestion as to where to start the search
- **value** : element to insert
- **first, last** : range of elements to insert
- **ilist** : initializer list to insert the values from

##### Type requirements
InputIt must meet the requirements of LegacyInputIterator.

#### Returns

1. 
2. 
3. 
5. an iterator to the inserted element
5.  
6. (none)

#### Complexity

1. 
2. Logarithmic in the size of the container
3. 
4. Amortized constant if the insertion happens in the position just before the hint, logarithmic in the size of the container otherwise.
5. 
6.  O(N*log(size() + N)), where N is the number of elements to insert.