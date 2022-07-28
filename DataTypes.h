#ifndef DATATYPES_H
#define DATATYPES_H

enum Direction {
    East,
    North,
    South,
    West,
    Last = West
};

enum class ObjectType {
    None = 0,
    Town,
    Road,
    Field,
    Monastery
};

Direction opposite(Direction direction);

#endif // DATATYPES_H
