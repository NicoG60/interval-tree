# interval-tree

Implementation of an AVL Augmented Tree in the STL fashion



# Usage

## Include

make the `include` dir reachable for your project and simply include `<interval_tree.h>`

## Details

```cpp
template<
    class Key,
    class Value,
    class Comp = std::less<Key>
> class interval_tree;
```

interval_tree is a container associating pairs of keys with a value. the keys represent the lower and upper bounds of an interval. the container is ordered using the comparison function Comp. Search, insertion, removal have logarithmic complexity.

Elements with the exact same interval keys are allowed and are ordered by insertion.

### Member types

| Member type        | Definition                          |
| ------------------ | ----------------------------------- |
| `bound_type`       | Key                                 |
| `key_type`         | `std::pair<bound_type, bound_type>` |
| `mapped_type`      | Value                               |
| `key_compare`      | Comp                                |
| `value_type`       | `std::pair<key_type, mapped_type>`  |
| `reference`        | `value_type&`                       |
| `iterator`         | Legacy Bidirectionnal Iterator      |
| `reverse_iterator` | `std::reverse_iterator<iterator>`   |

### Member function

| Constructors |      |
| ---- | ---- |
| [(constructor)](doc/constructor.md) | constructs the interval tree |
| [(destructor)](doc/destructor.md) | destructs the interval tree  |
| [`operator=`](doc/operator=.md) | Assigns values to the container |



| Element access                    |                                                              |
| --------------------------------- | ------------------------------------------------------------ |
| [`at`](doc/at.md)                 | access specified element or get all intervals overlapping a single value |
| [`in`](doc/in.md)                 | get all intervals overlapping an interval.                   |
| [`operator[]`](doc/operator[].md) | access or insert specified element                           |



| Iterators                           |                                             |
| ----------------------------------- | ------------------------------------------- |
| [`begin` `cbegin`](doc/begin.md)    | returns an iterator to the beginning        |
| [`end` `cend`](doc/end.md)          | returns an iterator to the end              |
| [`rbegin` `crbegin`](doc/rbegin.md) | returns a reverse iterator to the beginning |
| [`rend` `crend`](doc/rend.md)       | returns a reverse iterator to the end       |

| Capacity                |                                     |
| ----------------------- | ----------------------------------- |
| [`empty`](doc/empty.md) | check wether the container is empty |
| [`size`](doc/size.md)   | return the number of elements       |

| Modifiers                   |                              |
| --------------------------- | ---------------------------- |
| [`clear`](doc/clear.md)     | clears the content           |
| [`insert`](doc/insert.md)   | inserts elements             |
| [`emplace`](doc/emplace.md) | constructs elements in place |
| [`erase`](doc/erase.md)     | erases elements              |
| [`swap`](doc/swap.md)       | swap contents                |

| Lookup                          |                                           |
| ------------------------------- | ----------------------------------------- |
| [`find`](doc/find.md)           | finds the first element with specific key |
| [`find_last`](doc/find_last.md) | finds the last element with specific key  |

