#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

//#define FILENAME "array.dat"
#define COLS 1001 // Number of columns in data

class record
{
public:
    //record();
    //~record();
    int row;
    int col;
};

int main() {

	vector < vector <int> > array; // 2d array as a vector of vectors
	vector <int> rowVector(COLS); // vector to add into 'array' (represents a row)
	int row = 0; // Row counter
    int row_bound, col_bound;
    int row_tmp, col_tmp, ans_num = 0;
    queue<record> result;
    record ans;

    ifstream file;
    ofstream output;

	file.open("matrix.data", ios::in); // Open file

	if (file.is_open()) { // If file has correctly opened...
		// Output debug message
		cout << "File correctly opened" << endl;

		file >> row_bound;
        file >> col_bound;

		// Dynamically store data into array
		while (file.good()) { // ... and while there are no errors,
			array.push_back(rowVector); // add a new row,

			for (int col=0; col<col_bound; col++) {
                file >> array[row][col]; // fill the row with col elements
//cout << "(" << row <<" "<< col << ") " << array[row][col] << "\n";
			}
			row++; // Keep track of actual row
		}
	}
	else cout << "Unable to open file" << endl;

    for(int i=0; i<row_bound; i++){ //Is it possible that a value on the boundary becomes a peak value?
        for(int j=0; j<col_bound; j++){
            row_tmp = -1, col_tmp = -1;

            if(i == 0){
                if(j == 0){
                    if(array[i][j]>=array[i][j+1] && array[i][j]>=array[i+1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else if(j == col_bound-1){
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i+1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else{
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i+1][j] && array[i][j]>=array[i][j+1]){
                        row_tmp = i, col_tmp = j;
                    }
                }
            }else if(i == row_bound-1){
                if(j == 0){
                    if(array[i][j]>=array[i][j+1] && array[i][j]>=array[i-1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else if(j == col_bound-1){
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i-1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else{
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i-1][j] && array[i][j]>=array[i][j+1]){
                        row_tmp = i, col_tmp = j;
                    }
                }
            }else{
                if(j == 0){
                    if(array[i][j]>=array[i][j+1] && array[i][j]>=array[i+1][j] && array[i][j]>=array[i-1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else if(j == col_bound-1){
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i+1][j] && array[i][j]>=array[i-1][j]){
                        row_tmp = i, col_tmp = j;
                    }
                }else{
                    if(array[i][j]>=array[i][j-1] && array[i][j]>=array[i][j+1]
                       && array[i][j]>=array[i-1][j] && array[i][j]>=array[i+1][j]){
                           row_tmp = i, col_tmp = j;
                       }
                }
            }
//cout << row_tmp <<" "<< col_tmp << "  " << array[i][j] << "\n";
            if(row_tmp != -1 && col_tmp != -1){

                ans.row = row_tmp + 1;
                ans.col = col_tmp + 1;
                result.push(ans);
                ans_num ++;
            }

        }
    }

    output.open("final.peak",ios::out);

    output << ans_num << "\n";
    if (output.is_open()) {

        while(!result.empty()){
            output << result.front().row << " " << result.front().col << "\n";
            result.pop();
        }

	}
	else cout << "Unable to open file" << endl;

	file.close();
	output.close();
    return 0;
}