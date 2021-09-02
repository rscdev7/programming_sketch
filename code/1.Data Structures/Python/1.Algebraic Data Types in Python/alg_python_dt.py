from dataclasses import dataclass
from typing import Union


@dataclass
class Point:
    x: float
    y: float


@dataclass
class Circle:
    x: float
    y: float
    r: float


@dataclass
class Rectangle:
    x: float
    y: float
    w: float
    h: float


Shape = Union[Point, Circle, Rectangle]


def print_shape(shape: Shape):
    if isinstance(shape, Point):
        print(f"Point {shape.x} {shape.y}")
    elif isinstance(shape, Circle):
        print(f"Circle {shape.x} {shape.y} {shape.r}")
    elif isinstance(shape, Rectangle):
        print(f"Rectangle {shape.x} {shape.y} {shape.w} {shape.h}")
    else:
        raise TypeError("Unknown Data Type")


print_shape(Point(1, 2))
print_shape(Circle(3, 5, 7))
print_shape(Rectangle(11, 13, 17, 19))
print_shape(4)