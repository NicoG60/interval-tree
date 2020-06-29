# interval_tree<Key, Value, Comp>::in

```cpp
void in( const Key& start, const Key& end, std::vector<iterator>& results ) const;       // (1)
//---------------------------------------------------------------------------------------------
void in( const Key& start, const Key& end, std::vector<const_iterator>& results ) const; // (2)
//---------------------------------------------------------------------------------------------
void in( const key_type& interval, std::vector<iterator>& results ) const;               // (3)
//---------------------------------------------------------------------------------------------
void in( const key_type& interval, std::vector<const_iterator>& results ) const;         // (4)
```

Fill the given vector with all intervals that overlaps.
This function will no clear the result vector and uses `push_back` to fill it. Better performances can be obtained using an already allocated vector (use of `reserve` or capacity large enough)

#### Parameters

- **start, end** : the lower and upper bounds of the interval to search
- **interval** : the interval to search
- **results** : a writable vector which will be filled.

#### Complexity

log N  if only one interval overlaps.
Linear if all intervals overlaps.