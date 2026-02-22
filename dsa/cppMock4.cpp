/*
Given an m x n 2D binary grid grid which represents a map of '1's (land)
and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent 
lands horizontally or vertically. You may assume all four edges of the 
grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

*/

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include <utility>


class Solution{
public:
	int numOfIslands(vector<vector<string>> grid){
	
		int delr[] = {-1, 0, 1, 0};
		int delc[] = {0, 1, 0, -1};
		int rows = grid.size();
		int cols = grid[0].size();
		int numIslands = 0;
		
		//everytime a new BFS starts, that means it is a new island
		
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				if(grid[i][j] == "1"){
					// start BFS
					numIslands++;
					queue<pair<int, int>> bfsq;
					bfsq.push({i, j});
					grid[i][j] = "0";
					while(!bfsq.empty()){
						auto currentCell = bfsq.front();
						bfsq.pop();
						int row = currentCell.first;
						int col = currentCell.second;
						
						// look in all 4 directions
						for(int k = 0; k<4; k++){
							int newRow = row + delr[k];
							int newCol = col + delc[k];
							
							if(newRow >=0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == "1"){
								bfsq.push({newRow, newCol});
								grid[newRow][newCol] = "0";
							}
						}
					}
					
				}
			}
		}

        return numIslands;
	}

};