# interval_tree<Key, Value, Comp>::upper_bound

```cpp
iterator       lower_bound( const key_type& key );
const_iterator lower_bound( const key_type& key ) const;
```

Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.

#### Parameters

- **key** : key value to compare the elements to

#### Returns

Iterator pointing to the first element that is *not less* than key. If no such element is found, past-the-end (see [end()](end.md) iterator is returned.

#### Complexity

Logarithmic in the size of the container.