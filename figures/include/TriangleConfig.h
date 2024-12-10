#pragma once

struct TriangleConfig
{
	/*
	 * Comments are always failures. We must have them because we cannot always figure out how to express ourselves without them, but their use is not a cause for celebration. :-) 
	 */

	//Some clarification on the strange naming of these two constants:
	//The idea is that we generate two of the sides of the triangle in this range!
	//The third side is generated in a way that it satisfies the triangle inequality, and it may turn out to be
	//larger than the max length. 
	static constexpr int twoOfTheSidesMinLengthRandom = 1;
	static constexpr int twoOfTheSidesMaxLengthRandom = 1000;
};