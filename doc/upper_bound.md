# interval_tree<Key, Value, Comp>::upper_bound

```cpp
iterator       upper_bound( const key_type& key );
const_iterator upper_bound( const key_type& key ) const;
```

Returns an iterator pointing to the first element that is greater than key.

#### Parameters

- **key** : key value to compare the elements to

#### Returns

Iterator pointing to the first element that is *greater* than key. If no such element is found, past-the-end (see [end()](end.md) iterator is returned.

#### Complexity

Logarithmic in the size of the container.