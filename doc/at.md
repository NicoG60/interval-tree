# interval_tree<Key, Value, Comp>::at

```cpp
void at( const Key& point, std::vector<iterator>& results );             // (1)
//-----------------------------------------------------------------------------
void at( const Key& point, std::vector<const_iterator>& results ); const // (2)
```

Fill the given results vector with all intervals that overlaps the given point.
The results vector is not cleared before the function start and is filled using `push_back`. Better performance can be optained if the vector's capacity is large enough and allocation is not needed.

#### Parameters

- **point** : the point where to search for overlapping intervals
- **results** : a writable vector of interator or const_iterator which will be filled.

#### Complexity

Linear