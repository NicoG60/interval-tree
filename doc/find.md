# interval_tree<Key, Value, Comp>::find

```cpp
iterator find( const key_type& key );
const_iterator find( const key_type& key ) const;
```

Finds the first element with key equivalent to `key`.

#### Parameters

- **key** : key value of the element to search for

#### Returns

Iterator to an element with key equivalent to `key`. If no such element is found, past-the-end (see [end()](end.md) iterator is returned.

#### Complexity

Logarithmic in the size of the container.