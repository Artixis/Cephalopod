
#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int x;
	int y;
	int value;
	int utility;

	Cell(int xx, int yy, int v):x(xx), y(yy), value(v) {}

	bool operator<(const Cell& c) const {
		return abs(value) < abs(c.value);
	}
};



#endif /* CELL_H_ */
