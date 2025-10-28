#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        int left = 0;
        int right = m - 1;
        int mid = 0;
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            if (matrix[mid][0] == target)
                return 1;
            if (matrix[mid][0] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        if (right < 0)
            return 0;
        int target_row = right;
        //   cout << "target_row: " << target_row << endl;

        left = 0;
        right = n - 1;

        while (left <= right)
        {
            mid = (left + right) / 2;
            if (matrix[target_row][mid] == target)
                return 1;
            if (matrix[target_row][mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return 0;
    }
};

int main()
{
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    // vector<vector<int>> matrix = {{0},{1}};
    int target = 1;
    Solution sol;
    bool res = sol.searchMatrix(matrix, target);
    cout << res << endl;
    return 0;
}