#include <iostream>
#include <vector>

using namespace std;


class Matrix {
    double** matrix;
    int row;
    int col;
public:
    Matrix() {}

    Matrix(int r, int c) {
        row = r, col = c;
        matrix = new double*[10];
        for (int i = 0; i < 10; i++) {
            matrix[i] = new double[10];
        }
        initialize();
    }

    double** get_matrix() {
        return matrix;
    }

    void reshape(int r, int c) {
        if (r*c != row*col) {
            cout << "Can not reshape as the new dimensions product do not match the current dimensions product." << endl;
            return;
        }

        double* flatten = new double[r*c];
        int idx = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                flatten[idx++] = matrix[i][j];
            }
        }


        double** temp = new double*[r];
        for (int i = 0; i < r; i++) {
            temp[i] = new double[c];
        }

        idx = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                temp[i][j] = flatten[idx++];
            }
        }

        delete_matrix();
        delete[] flatten;
        matrix = temp;
        row = r, col = c;
    }

    void initialize() {
         for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = 0;
            }
        }
    }


    void initialize(double** values) {
         for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = values[i][j];
            }
        }
    }

    void input_values() {

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    cout << "Enter Matrix value " << i << "," << j << ": ";
                    cin >> matrix[i][j];
                }
            }
    }

    void display() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%.3f\t", matrix[i][j]);
            }
            cout << endl;
        }
        cout << endl;
    }

    void Transpose() {

        double** T;
        T = new double*[col];
        for (int i = 0; i < col; i++) {
            T[i] = new double[row];
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                T[j][i] = matrix[i][j];
            }
        }

        delete_matrix();
        matrix = T;

        int temp = row;
        row = col;
        col = temp;
    }

    void Inverse() {
        if (row != col) {
            cout << "Non square matrix can not have inverse." << endl;
            return;
        }

        double temp;
        int order = 3;

        for (int i = 0; i < order; i++) {
          for (int j = 0; j < 2 * order; j++) {
             if (j == (i + order))
                matrix[i][j] = 1;
          }
        }
        for (int i = order - 1; i > 0; i--) {
          if (matrix[i - 1][0] < matrix[i][0]) {
             double* temp = matrix[i];
             matrix[i] = matrix[i - 1];
             matrix[i - 1] = temp;
          }
        }
        for (int i = 0; i < order; i++) {
          for (int j = 0; j < order; j++) {
             if (j != i) {
                temp = matrix[j][i] / matrix[i][i];
                for (int k = 0; k < 2 * order; k++) {
                   matrix[j][k] -= matrix[i][k] * temp;
                }
             }
          }
        }
        for (int i = 0; i < order; i++) {
          temp = matrix[i][i];
          for (int j = 0; j < 2 * order; j++) {
             matrix[i][j] = matrix[i][j] / temp;
          }
        }

        for (int i = 0; i < order; i++) {
          for (int j = order; j < 2 * order; j++) {
             printf("%.3f\t", matrix[i][j]);
          }
          cout << endl;
        }

    }

    double** Product(Matrix other, int other_row, int other_col) {

        if (col != other_row) {
            cerr << "Error: Cannot multiply matrices. Columns of A must match rows of B." << endl;
            return nullptr;
        }

        Matrix result_matrix(row, other_col);

        double** result = new double*[row];
        for (int i = 0; i < row; i++) {
            result[i] = new double[other_col];
        }


        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < other_col; ++j) {
                for (int k = 0; k < col; ++k) {
                    result[i][j] += matrix[i][k] * other.get_matrix()[k][j];
                }
            }
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < other_col; ++j) {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }


        return result;
    }

    void delete_matrix() {
        for (int i = 0; i < row; i++) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
        delete[] matrix;
        matrix = nullptr;
    }

    ~Matrix() {
        delete_matrix();
    }
};

int rows, cols;

void get_matrix_dimensions() {
    cout << "Enter matrix rows: ";
    cin >> rows;
    cout << "Enter Matrix columns: ";
    cin >> cols;
}

Matrix get_matrix(int r, int c) {
    Matrix m(r,c);
    m.input_values();

    return m;
}

int main()
{

    get_matrix_dimensions();
    Matrix matrix(rows, cols);

    while (true) {

        int choice;
        int r, c;
        cout << "\n1. Enter/Change matrix dimensions" << endl;
        cout << "2. Enter Matrix values" << endl;
        cout << "3. Display Matrix" << endl;
        cout << "4. Transpose" << endl;
        cout << "5. Inverse" << endl;
        cout << "6. Matrix Product" << endl;
        cout << "7. Display Dimensions" << endl;
        cout << "0: Exit" << endl << endl;
        do {
            cout << "Enter your choice: ";
            cin >> choice;
        } while (choice < 0 || choice > 7);
        switch (choice) {
        case 0:
            cout << "Program Terminated..." << endl;
            return 0;

        case 1:
            cout << "Enter rows: ";
            cin >> r;
            cout << "Enter cols: ";
            cin >> c;
            matrix.reshape(r, c);
            break;

        case 2:
            matrix.input_values();
            break;

        case 3:
            matrix.display();
            break;
        case 4:
            matrix.Transpose();
            cout << "Transpose: " << endl;
            matrix.display();
            break;
        case 5:
            matrix.Inverse();
            break;
        case 6:
            cout << "Enter second matrix rows: ";
            cin >> r;
            cout << "Enter second matrix cols: ";
            cin >> c;
            if (cols != r) {
                cout << "Product not possible. Rows of first are not equal to Cols of second." << endl;
                break;
            }
            matrix.Product(get_matrix(r, c), r, c);
            break;
        case 7:
            cout << rows << " X " << cols << endl;
            break;
        }

    }


    double** values = new double*[3];
    for (int i = 0; i < 3; i++) {
        values[i] = new double[3];
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            values[i][j] = (i+1)*(j+1);
        }
    }



    return 0;
}
