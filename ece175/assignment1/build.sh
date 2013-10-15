#!/bin/bash
clang++ -framework OpenGL sierpinski.cpp -framework GLUT
if [ $? -ne 0 ]
then
  echo "Compile error"
  exit 1
fi

./a.out