# interval_tree<Key, Value, Comp>::at

```cpp
reference at( const key_type& key );               // (1)
const_reference at( const key_type& key ) const;   // (2)
//-----------------------------------------------------
void at( const bount_type& point,
         std::vector<value_type>& results ) const; // (3)
```

1. 
2. Returns a reference to the mapped value of the element with key equivalent to `key`. If no such element exists, an exception of type [std::out_of_range](https://en.cppreference.com/w/cpp/error/out_of_range) is thrown.
3. Fill the given vector with all intervals that overlaps the given point.

#### Parameters

- **key** : the key of the element to find
- **point** : the point where to search for overlapping intervals
- **& results** : a writable vector the function will fill.

#### Returns

1. 
2. A reference to the mapped value.
3. The filled vector.

#### Complexity

Logarithmic in the size of the container