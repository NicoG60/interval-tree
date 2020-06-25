# interval_tree<Key, Value, Comp>::erase

```cpp
iterator  erase( iterator pos );
iterator  erase( const_iterator pos );                        // (1)
//------------------------------------------------------------------
iterator  erase( const_iterator first, const_iterator last ); // (2)
//------------------------------------------------------------------
size_type erase( const key_type& key );                       // (3)
```

Removes specified elements from the container.

1. Removes the element at pos.
2. Removes the elements in the range `[first; last)`, which must be a valid range in *this.
3. Removes all elements with the key equivalent to key.

References and iterators to the erased elements are invalidated. Other references and iterators are not affected.

The iterator `pos` must be valid and dereferenceable. Thus the [end()](end.md) iterator (which is valid, but is not dereferenceable) cannot be used as a value for `pos`.

#### Parameters

- **pos** : iterator to the element to remove
- **first, last** : range of elements to remove
- **key** : key value of the elements to remove

#### Returns

1. 
2. Iterator following the removed element.
3. Number of elements removed.

#### Complexity

1. Amortized constant
2. `log(c.size()) + std::distance(first, last)`
3. `log(c.size()) + c.count(key)`