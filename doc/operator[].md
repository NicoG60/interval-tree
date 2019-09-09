# interval_tree<Key, Value, Comp>::operator[]

```cpp
Value& operator[]( const key_type& key ); // (1)
Value& operator[]( key_type&& key );      // (2)
```

Returns a reference to the value that is mapped to a key equivalent to `key`, performing an insertion if such key does not already exist.

#### Parameters

- **key** : the key of the element to find / insert

#### Returns

Reference to the mapped value of the new element if no element with key `key` existed. Otherwise a reference to the mapped value of the existing element whose key is equivalent to `key`.

#### Complexity

Logarithmic in the size of the container