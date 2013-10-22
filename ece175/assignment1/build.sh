#!/bin/bash
clang++ -framework OpenGL nicomedes.cpp -framework GLUT
if [ $? -ne 0 ]
then
  echo "Compile error"
  exit 1
fi

./a.out
