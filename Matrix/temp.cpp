//
//#include <iostream>
//#include <vector>
//using namespace std;
//void printMatrixValues(double** arr, int n, int m){
//   for (int i = 0; i < n; i++) {
//      for (int j = 0; j < m; j++) {
//         cout<<arr[i][j]<<"\t";
//      }
//      cout<<endl;
//   }
//   return;
//}
//void printInverseMatrix(double** arr, int n, int m){
//   for (int i = 0; i < n; i++) {
//      for (int j = 0; j < n; j++) {
//         printf("%.3f\t", arr[i][j]);
//      }
//      cout<<endl;
//   }
//   return;
//}
//void findInvMatGaussJordan(double** mat, int order){
//   double temp;
//   printf("The inverse of matrix : A = \n");
//   printMatrixValues(mat, order, order);
//   for (int i = 0; i < order; i++) {
//      for (int j = 0; j < 2 * order; j++) {
//         if (j == (i + order))
//            mat[i][j] = 1;
//      }
//   }
//   for (int i = order - 1; i > 0; i--) {
//      if (mat[i - 1][0] < mat[i][0]) {
//         double* temp = mat[i];
//         mat[i] = mat[i - 1];
//         mat[i - 1] = temp;
//      }
//   }
//   for (int i = 0; i < order; i++) {
//      for (int j = 0; j < order; j++) {
//         if (j != i) {
//            temp = mat[j][i] / mat[i][i];
//            for (int k = 0; k < 2 * order; k++) {
//               mat[j][k] -= mat[i][k] * temp;
//            }
//         }
//      }
//   }
//   for (int i = 0; i < order; i++) {
//      temp = mat[i][i];
//      for (int j = 0; j < 2 * order; j++) {
//         mat[i][j] = mat[i][j] / temp;
//      }
//   }
//   cout<<"A' =\n";
//   printInverseMatrix(mat, order, 2 * order);
//   return;
//}
//int main(){
//   int order = 3;
//   double** mat = new double*[20];
//   for (int i = 0; i < 20; i++)
//   mat[i] = new double[20];
//   mat[0][0] = 6; mat[0][1] = 9; mat[0][2] = 5;
//   mat[1][0] = 8; mat[1][1] = 3; mat[1][2] = 2;
//   mat[2][0] = 1; mat[2][1] = 4; mat[2][2] = 7;
//   findInvMatGaussJordan(mat, order);
//   return 0;
//}
