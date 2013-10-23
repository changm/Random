#!/bin/bash
clang++ -O0 -g -framework OpenGL chaikin.cpp -framework GLUT
if [ $? -ne 0 ]
then
  echo "Compile error"
  exit 1
fi

./a.out
