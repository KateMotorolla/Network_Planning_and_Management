#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Print the original matrix
void print_matrix_original(vector<vector<bool>> matrix_original)
{
	for (int i = 0; i < matrix_original.size(); i++)
	{
		for (int j = 0; j < matrix_original.size(); j++)
			cout << matrix_original[i][j] << "  ";
		cout << endl;
	}
}
// Printing matrix
void print_matrix(vector<vector <bool>>& matrix, int& size)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	}
}
// Correction of the given
void start(vector <vector<bool>>& matrix_original, vector<int>& long_work_original, int& size, vector <vector<bool>>& matrix, vector<int>& long_work)
{
	// Creating a matrix to record the result of transformations
	for (int i = 0; i < size + 2; i++)
	{
		matrix[size + 1][i] = 0;
		matrix[0][i] = 0;
		matrix[i][0] = 0;
		matrix[i][size + 1] = 0;
	}
	for (int i = 0; i < size; i++)
	{

		bool drain_1 = false;
		bool source_2 = false;
		// Search for drains and sources
		for (int j = 0; j < size; j++)
		{
			matrix[i + 1][j + 1] = matrix_original[i][j];

			if (matrix_original[i][j])
				drain_1 = true;

			if (matrix_original[j][i])
				source_2 = true;
		}
		// Creating a shared drain
		if (!drain_1)
			matrix[i + 1][size + 1] = 1;

		// Creating a common source
		if (!source_2)
			matrix[0][i + 1] = 1;
	}
	size += 2;
	for (int i = 1; i < size - 1; i++)
	{
		long_work[i] = long_work_original[i - 1];
	}

	long_work[0] = 0;
	long_work[size - 1] = 0;

	long_work_original = long_work;
}
// Deep search for cycles
bool dfs(vector<vector <bool>> matrix, int size, vector <int> color, int i)
{
	for (int j = 0;j < size;j++)
	{
		if (matrix[i][j] && color[j] != 2)
		{
			if (color[j] == 1)
				return true;

			color[i] = 1;
			if (dfs(matrix, size, color, j))
				return true;
			color[i] = 2;
		}
	}
	return false;
}
// Checking for cycles
bool finding_cycles(vector<vector <bool>> matrix, int size, vector <int> color)
{
	for (int i = 0;i < size;i++)
		color[i] = 0;
	return dfs(matrix, size, color, 0);
}
// Topological sorting depth-first search
void topological_sorting(int index, vector<vector<bool>>& matrix, vector<bool>& visit, stack<int>& sort)
{
	visit[index] = true;
	int n = visit.size();
	for (int i = index + 1; i < n; ++i)
	{
		if (matrix[index][i] && !visit[i])
			topological_sorting(i, matrix, visit, sort);
	}
	sort.push(index);
}
// Rearranging vertices
void trans_pos(int size, vector<vector <bool>>& matrix, vector <int>& long_work, stack <int>& sort, vector<vector <bool>>& new_matrix, vector<int>& new_long_work)
{
	auto num = sort._Get_container();
	reverse(num.begin(), num.end());
	for (int i = 0;i < size;i++)
	{
		new_long_work[i] = long_work[num[i]];
		for (int j = 0;j < size;j++)
		{
			new_matrix[i][j] = matrix[num[i]][num[j]];
		}
	}
}
// Early and late start
void early_dates(vector<vector <bool>>& new_matrix, vector<int>& new_long_work, int size, vector<int>& time_1, vector<int>& time_2)
{
	for (int i = 0;i < size;i++)
	{
		time_1[i] = 0;
		for (int j = 0;j < size;j++)
		{
			if (new_matrix[j][i])
				time_1[i] = max(time_1[i], time_1[j] + new_long_work[j]);
		}
	}

	for (int i = 0;i < size;i++)
	{
		for (int j = i + 1;j < size;j++)
			swap(new_matrix[i][j], new_matrix[j][i]);
	}
	for (int i = size - 1;i >= 0;i--)
	{
		time_2[i] = 0;
		for (int j = 0;j < size;j++)
		{
			if (new_matrix[j][i])
				time_2[i] = max(time_2[i], time_2[j] + new_long_work[j]);
		}
	}

}
// Maximum path length and time margin
void calc_time(vector<int>& time_1, vector<int>& time_2, vector<int>& new_long_work, int size, vector<vector<int>>& time)
{
	for (int i = 0; i < size; i++)
	{
		time[0][i] = time_1[i] + time_2[i] + new_long_work[i];
	}

	for (int i = 0; i < size; i++)
	{
		time[1][i] = time[0][0] - time[0][i];
	}

}

int main()
{

	// The original adjacency matrix
	vector<vector <bool>> matrix_origial{
		{0,1,0,1},
		{0,0,1,0},
		{0,0,0,0},
		{0,0,1,0},
	};
	int size = matrix_origial.size();

	cout << "Original matrix " << endl;
	print_matrix_original(matrix_origial);


	// Duration of work
	vector<int> long_work_original(size);
	for (int i = 0; i < size; i++)
	{
		long_work_original[i] = 1 + rand() % 50;
	}
	// Adjusted adjacency matrix
	vector <vector<bool>> matrix(size + 2);
	for (int i = 0;i < size + 2;i++)
		matrix[i].resize(size + 2);
	// Adjusted duration of work
	vector<int> long_work(size + 2);

	cout << endl << "Original work duration array " << endl;
	for (int i = 0; i < long_work_original.size(); i++)
	{
		cout << long_work_original[i] << "  ";
	} cout << endl << endl;
	start(matrix_origial, long_work_original, size, matrix, long_work);

	cout << "Adjacency matrix " << endl;
	print_matrix(matrix, size);
	cout << endl << "Work duration array " << endl;
	for (int i = 0; i < long_work.size(); i++)
	{
		cout << long_work[i] << "  ";
	} cout << endl << endl;

	vector <int> color(size); // Array of vertex colorings
	// Calling a loop check
	if (!finding_cycles(matrix, size, color))
	{
		cout << "No cycle detected " << endl;;
	}
	else
	{
		cout << "Cycles detected ";
		return 0;
	}
	int source = 0; // Source
	stack <int> sort;
	vector <bool> visit(size);
	topological_sorting(source, matrix, visit, sort);
	cout << "Old numbering: ";
	for (int i = 0; i < size; ++i)
		cout << i << "  ";
	cout << endl << "New numbering: ";
	for (auto i = sort._Get_container().rbegin(); i != sort._Get_container().rend(); ++i)
		cout << *i << "  ";
	cout << endl;
	vector<vector<bool>> new_matrix(size);
	for (int i = 0;i < size;i++)
		new_matrix[i].resize(size);
	vector<int> new_long_work(size);
	cout << endl << "New matrix " << endl;
	trans_pos(size, matrix, long_work, sort, new_matrix, new_long_work);
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
			cout << new_matrix[i][j] << "  ";
		cout << endl;
	}cout << endl;
	cout << "New work duration array " << endl;
	for (int i = 0;i < size;i++)
	{
		cout << new_long_work[i] << "  ";
	}cout << endl;
	vector<int> time_1(size);
	vector<int> time_2(size);
	early_dates(new_matrix, new_long_work, size, time_1, time_2);
	cout << endl << "Early dates" << endl;
	for (int i = 0;i < size;i++)
	{
		cout << time_1[i] << "  ";
	}cout << endl;
	cout << "Late dates" << endl;
	for (int i = 0;i < size;i++)
	{
		cout << time_2[i] << "  ";
	}cout << endl << endl;
	vector<vector<int>> table(2);
	for (int i = 0;i < 2;i++)
		table[i].resize(size);

	calc_time(time_1, time_2, new_long_work, size, table);
	cout << "Maximum path length " << endl;
	for (int j = 0;j < size;j++)
		cout << table[0][j] << "  ";
	cout << endl;
	cout << "Leeway " << endl;
	for (int j = 0;j < size;j++)
		cout << table[1][j] << "  ";
	cout << endl;
	cout << "Vertices included in the critical path" << endl;
	for (int j = 0;j < size;j++)
	{
		if (table[1][j] == 0)
			cout << j << "  ";
	}

}