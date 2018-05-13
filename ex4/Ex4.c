
#include <stdio.h>
#define SIZE 8

int knightsTour(int x, int y, int num);

/************************************************************************
* function name:main.
* The Input: -.
* The Output: -.
* The Function operation: The function recieves from the user a number of 
* moves and prints in how many ways the knight can move from (1,1) to
* (8,8) in this number of moves.
*************************************************************************/
void main() {
	int n;
	int result;
	scanf(" %d", &n);
	//While the input is legit.
	while (n > 0) {
		result = knightsTour(1, 1, n);
		printf("%d\n", result);
		scanf(" %d", &n);
	}
}
/************************************************************************
* function name:main.
* The Input: the knight's position and number of moves left.
* The Output: the amount of ways the knight can move from (1,1) to
* (8,8) in this number of moves..
* The Function operation: The function calculates in how many ways the 
* knight can move from (1,1) to (8,8) in this number of moves.
*************************************************************************/
int knightsTour(int x, int y, int num)
{
	//If the knight is out of the board return 0.
	if (x < 1 || x > SIZE) return 0;
	if (y < 1 || y > SIZE) return 0;
	//If there aren't any moves left return 0 if the knight reached it's position.
	if (num == 0) return (x == SIZE && y == SIZE);
	//else calculate the amount of option the knight has with n-1 moves left.
	//There are 8 options for the knight to move.
	return knightsTour(x + 2, y + 1, num - 1)
		+ knightsTour(x + 1, y + 2, num - 1)
		+ knightsTour(x - 1, y + 2, num - 1)
		+ knightsTour(x - 2, y + 1, num - 1)
		+ knightsTour(x - 2, y - 1, num - 1)
		+ knightsTour(x - 1, y - 2, num - 1)
		+ knightsTour(x + 1, y - 2, num - 1)
		+ knightsTour(x + 2, y - 1, num - 1);
}