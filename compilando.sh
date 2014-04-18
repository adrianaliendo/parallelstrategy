#!/bin/bash
export PROGS=main
export CC=mpic++ 
export NVCC=nvcc 
export OMPFLAG=-fopenmp
#export CUDAFLAG="-lgomp -lmpi --compiler-bindir mpic++"
export CUDAFLAG="-Xcompiler -fopenmp -lcuda -lcudart -lgomp -lmpi --compiler-bindir mpic++"
export CUDAMPIFLAG="/usr/local/cuda-5.0/lib64/ -lcudart"
#export CUDAFLAG="-Xcompiler -lcuda -lcudart -lgomp -lmpi"
ISNVCC=`which nvcc`


if [ "$ISNVCC" = "" ]; then
echo "Compilando Todo junto - sin CUDA"
ln -s -f gpu.cu gpu.cpp
$CC -DCUDA=0 $OMPFLAG CUDAejecutor.cpp MPIejecutor.cpp OpenMPejecutor.cpp ejecucion.cpp ejecutor.cpp main.cpp -o parallelstrategy
else
echo "Compilando Todo junto - con CUDA"
$NVCC -DCUDA=1  $CUDAFLAG CUDAejecutor.cpp MPIejecutor.cpp OpenMPejecutor.cpp ejecucion.cpp ejecutor.cpp main.cpp -o parallelstrategy
fi
