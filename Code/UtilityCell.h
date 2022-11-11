#ifndef UTILITYCELL_H_
#define UTILITYCELL_H_

struct UtilityCell {
	int x;
	int y;
	double utility;

	UtilityCell(int xx, int yy, double v):x(xx), y(yy), utility(v) {}

	bool operator<(const UtilityCell& c) const {
		return abs(utility) < abs(c.utility);
	}
};



#endif /* UTILITYCELL_H_ */
