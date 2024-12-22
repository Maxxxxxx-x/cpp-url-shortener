.DEFAULT_GOAL: all

all:
	g++ ./main.cpp ./utils/utils.cpp ./db/db.cpp -o main
