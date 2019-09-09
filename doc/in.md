# interval_tree<Key, Value, Comp>::in

```cpp
void in( const bound_type& start, const bound_type& end,
         std::vector<value_type>& results ) const;       // (1)
void in( const key_type& interval,
         std::vector<value_type>& results ) const;       // (2)
```

Fill the given vector with all intervals that overlaps.

#### Parameters

- **start, end** : the lower and upper bounds of the interval to search
- **interval** : the interval to search
- **& results** : a writable vector the function will fill.

#### Returns

The filled vector.

#### Complexity

Logarithmic in the size of the container