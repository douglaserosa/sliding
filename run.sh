#!/bin/bash

g++ slidingPuzzle.cpp -o slidingPuzzleMatrix
g++ slidingPuzzleInt.cpp -o slidingPuzzleInt


for class in {facil,medio,dificil}
do
	for algorithm in {slidingPuzzleMatrix,slidingPuzzleInt}
	do
		for i in {1..100}
		do
			echo "running" $algorithm $class "- exec" $i  
			./$algorithm < $class".txt" > "./results/"$algorithm"-"$class"-"$i".txt"
		done
	done
done

echo "DONE"