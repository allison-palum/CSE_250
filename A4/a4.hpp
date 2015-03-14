#ifndef A4_HPP
#define A4_HPP

#include <iostream>
#include "Maze.hpp"
#include <queue>
using namespace std;

struct Point {
	Point(int x = 0, int y = 0) : x_(x), y_(y) {}
	int x_;
	int y_;
};

int bfs(Maze& maze, std::queue<Point>& Q, Point target, int depth) {
	queue<Point> Qn;
	Point up, down, left, right;

	while (!Q.empty()) {
		Point pt(Q.front().x_, Q.front().y_);
		if (pt.x_ == target.x_ && pt.y_ == target.y_) return depth;
		else {
			up.x_ = pt.x_ - 1;
			up.y_ = pt.y_;
			down.x_ = pt.x_ + 1;
			down.y_ = pt.y_;
			left.x_ = pt.x_;
			left.y_ = pt.y_ - 1;
			right.x_ = pt.x_;
			right.y_ = pt.y_ + 1;

			//check up position
			if (!maze.is_visited(up.x_, up.y_) && maze.is_open(up.x_, up.y_)) {
				Qn.push(up);
				maze.mark(up.x_, up.y_);
			}
			//check down position
			if (!maze.is_visited(down.x_, down.y_) && maze.is_open(down.x_, down.y_)) {
				Qn.push(down);
				maze.mark(down.x_, down.y_);
			}
			//check left position
			if (!maze.is_visited(left.x_, left.y_) && maze.is_open(left.x_, left.y_)) {
				Qn.push(left);
				maze.mark(left.x_, left.y_);
			}
			//check right position
			if (!maze.is_visited(right.x_, right.y_) && maze.is_open(right.x_, right, y_)) {
				Qn.push(right);
				maze.mark(right.x_, right.y_);
			}
		}
	}
	depth++;
	return bfs(maze, Qn, target, depth);
}

// implement your function distance
int distance(Maze& maze, int sx, int sy, int fx, int fy) {
	queue<Point> Q; //holds starting point
	Point start(sx, sy);
	Point target(fx, fy);
	Point loc(Q.front().x_, Q.front().y_); //point from front of Q;
	Q.push(start); //push starting position on Q
	int depth = 0;
	int rtval = bfs(maze, Q, target, depth);
	return rtval;
}
#endif
