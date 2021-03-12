#include <iostream>
#include "path.h"
int main()
{
	//const char* d = "M143.983 39.31C137.583 40.11 110.529 17.223 127.183 48.11L100.05 19.80 L110.05 89.80S 150 150 157 50L137.6 10.65 Z M20 20L20 100L50 100 100";
	//geometry::Path path(d);
	//path.Approximate(0.5);
	//path.ComputeBounds();
	geometry::Path path;
	path.MakeRect(5,5,20,10,2,2);
	path.ComputeBounds();
	path.Approximate(0.5);

}