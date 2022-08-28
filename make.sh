#!/bin/bash

filename="TicTacToe MCTS"
gcc -o "$filename" ticTacToe.c ticTacToe.h mctsAI.c mctsAI.h player.c player.h list.c list.h tree.c tree.h utils.c utils.h
echo "Made $filename.exe"