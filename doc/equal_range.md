# interval_tree<Key, Value, Comp>::equal_range

```cpp
std::pair<iterator,iterator>             equal_range( const Key& key );       // (1)
//----------------------------------------------------------------------------------
std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const; // (2)
```

Returns a range containing all elements with the given key in the container. The range is defined by two iterators, one pointing to the first element that is *not less* than key and another pointing to the first element *greater* than key. Alternatively, the first iterator may be obtained with [lower_bound()](lower_bound.md), and the second with [upper_bound()](upper_bound.md).

#### Parameters

- **key** : key value to compare the elements to

#### Returns

`std::pair` containing a pair of iterators defining the wanted range: the first pointing to the first element that is *not less* than key and the second pointing to the first element *greater* than key.

If there are no elements *not less* than key, past-the-end (see [end()](end.md)) iterator is returned as the first element. Similarly if there are no elements *greater* than key, past-the-end iterator is returned as the second element.

#### Complexity

Logarithmic in the size of the container.