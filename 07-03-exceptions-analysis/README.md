# Analysis of exceptions from a function

```c++
void test(const Person &person) {
    std::cout << "test : " << person.name() << '\n';

    if (person.grade() == 10 || person.salary() > 1'000'000) {
        save(Status::success, person.id());
    } else {
        save(Status::failure, person.id());
    }
}
```

Considering that all member functions of `Person` may throw an exception, the following
expressions potentially generate an exception:

1) `person.name()` (in which case "test : " will be printed);
2) `person.grade()`;
3) `person.salary()`;
4) `person.id()`;
5) `save(Status::success, person.id())`;
6) `save(Status::failure, person.id())`;
7) All `operator<<` may throw an exception if `std::cout.exceptions()` was previously called or
   for any implementation-defined reason.

In case non of this happens, the flow of control is normal.
