# Boost.MultiIndex complexity test

This experiment verifies that Boost.MultiIndex can be used to provide faster-than O(N) reverse-lookup in random-access container.

Qt's grid model requires element's row index to be known. Whenever data record corresponding to a row is changed, the model must notify controls of the row index.
In case of huge datasets, the process of finding a row index of an element may be too long, if it's O(N).

MultiIndex may help here, if the random access index can be backed-up by hash index.

# Conclusions

Multi-index container allows for O(1) index_of operation.

Below is the result. container_T is multi-index based, while naive_t is baased on std::vector, using std::find to implement index_of

Run on (4 X 3392.43 MHz CPU s)
2016-05-01 12:40:14
Benchmark                                            Time(ns)    CPU(ns) Iterations
-----------------------------------------------------------------------------------
indexof_becnhmark<container_t<std::uint64_t>>/16           30         30   25000000
indexof_becnhmark<container_t<std::uint64_t>>/64           29         29   22727273
indexof_becnhmark<container_t<std::uint64_t>>/512          27         27   25000000
indexof_becnhmark<container_t<std::uint64_t>>/4k           27         27   23972603
indexof_becnhmark<container_t<std::uint64_t>>/32k          33         33   21267362
indexof_becnhmark<container_t<std::uint64_t>>/256k        118        118    6481481
indexof_becnhmark<container_t<std::uint64_t>>/2M          179        178    3804348
indexof_becnhmark<container_t<std::uint64_t>>/16M         380        382    1842105
indexof_becnhmark<naive_t<std::uint64_t>>/16               43         43   16055046
indexof_becnhmark<naive_t<std::uint64_t>>/64               56         56   13461538
indexof_becnhmark<naive_t<std::uint64_t>>/512             161        160    4268293
indexof_becnhmark<naive_t<std::uint64_t>>/4k              972        973     760870
indexof_becnhmark<naive_t<std::uint64_t>>/32k            7779       7817      97222
indexof_becnhmark<naive_t<std::uint64_t>>/256k          61449      61370      11667
indexof_becnhmark<naive_t<std::uint64_t>>/2M           730667     735874        761
indexof_becnhmark<naive_t<std::uint64_t>>/16M         6508257    6529915        117
