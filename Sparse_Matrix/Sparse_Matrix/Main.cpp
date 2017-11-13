#include <iostream>
using namespace std;


class SparseNode {
public:
	int data; //variables for input(Non-zeros element)
	int size; //the size for both row & colomn
	SparseNode * rowHead; //Pointing to subsequent row
	SparseNode * colomnHead; //Pointing to subsequent colomn
};


class SM {
private:
	int n; //variable for row
	int m; //variable for colomn
	SparseNode * head;

public:
	//overloaded constructor
	SM(int rows, int columns) {
		this->n = rows; //to assign n to the input rows from user when creating index
		this->m = columns; //assign m for colomns from input
		this->head = NULL; //assign head to null
	}

	//the following function is for asking the user of which row and colom to be assigned with the value
	void readElements() {
		system("cls");
		int data, rows, colomns;
		cout << "-------------------------------------------------" << endl;
		cout << "                 Add New Elements" << endl;
		cout << "-------------------------------------------------" << endl;

		cout << "Enter selected Row : ";
		cin >> rows;

		cout << "Enter selected Colomn :";
		cin >> colomns;

		cout << "Enter Element of non-Zero Value : ";
		cin >> data;

		insertElements(rows, colomns, data, true); //assigning variables from the input to be proccessed insert element function

	}

	//below function is where the adding matrix proccess 
	void insertElements(int row, int colomn, int data, bool check) {
		if (row < 0 || row >= n) { //to check wether the row is within the boundary
			cout << "Row out of bound !" << endl;
			abort();
		}
		else if (colomn < 0 || colomn >= m) { //to check wether the colomn is within the boundary
			cout << "Colomn out of bound !" << endl;
			abort();
		}
		else {
			SparseNode * current = head;
			if (current == NULL || current->size > row) {	//this condition is to add node for the first time																	
				SparseNode * newRow = new SparseNode;
				newRow->size = row;
				newRow->data = NULL;
				newRow->colomnHead = NULL;
				head = newRow;
				newRow->rowHead = current;
				SparseNode * newColomn = new SparseNode;
				newColomn->size = colomn;
				newColomn->data = data;
				newColomn->rowHead = NULL;
				newColomn->colomnHead = NULL;
				newRow->colomnHead = newColomn;
			}

			else {
				while (current->rowHead != NULL && current->rowHead->size <= row) {
					current = current->rowHead;
				}
				if (current->size == row) {
					while (current->colomnHead != NULL && current->colomnHead->size <= colomn) {
						current = current->colomnHead;
					}
					if (current->size == colomn && check == false) { //the condition false is used for addSM function
						current->data = current->data + data;        //to add up the two matrices
					}
					else if (current->size == colomn && check == true) {
						current->data = data;
					}

					else {
						SparseNode * newColomn = new SparseNode;
						newColomn->size = colomn;
						newColomn->data = data;
						newColomn->rowHead = NULL;
						newColomn->colomnHead = current->colomnHead;
						current->colomnHead = newColomn;
					}
				}
				else { //this condition is to add node in between end or middle
					SparseNode * newRow = new SparseNode;
					newRow->size = row;
					newRow->data = NULL;
					newRow->colomnHead = NULL;
					newRow->rowHead = current->rowHead;
					current->rowHead = newRow;

					SparseNode * newColomn = new SparseNode;
					newColomn->size = colomn;
					newColomn->data = data;
					newColomn->rowHead = NULL;
					newColomn->colomnHead = NULL;
					newRow->colomnHead = newColomn;
				}
			}
		}
	}

	//to print the matrix with the data and non-zero value
	void printMatrix() {
		SparseNode * curRow = head;
		for (int x = 0; x < n; x++)
		{
			if (curRow == NULL || curRow->size != x) { //if matrix has no element,to print an empty index of zero values
				for (int y = 0; y < m; y++)
				{
					cout << "0";
					cout << " ";
				}
			}
			else {
				SparseNode * curCol = curRow->colomnHead; //if matrix has element,print with the element and zero values
				for (int z = 0; z < m; z++)
				{
					if (curCol == NULL || curCol->size != z)
						cout << "0 ";
					else {
						cout << curCol->data << " ";
						curCol = curCol->colomnHead;
					}
				}
				curRow = curRow->rowHead;
			}
			cout << endl;
		}
	}

	//To find the sum between two matrices
	SM * addSM(SM &secondElement) {
		bool check;
		if (n != secondElement.n && m != secondElement.m) { //to check if the temp matrix have different rows/colomns
			cout << "The rows/colomns are not matched !" << endl;
			abort();
		}

		else {
			SparseNode * curRow = secondElement.head;
			SM * Temp = new SM(n, m);
			int rowSize, data, columnSize;
			while (curRow != NULL) {
				int rowSize = curRow->size;
				SparseNode * curColomn = curRow->colomnHead;
				while (curColomn != NULL) {
					columnSize = curColomn->size;
					data = curColomn->data;
					Temp->insertElements(rowSize, columnSize, data, check = true); //if the value did not have the same row/colomn set to
					curColomn = curColomn->colomnHead;							   //true to be stored without adding the two matrices
				}
				curRow = curRow->rowHead;
			}

			SparseNode * curRow2 = head;

			while (curRow2 != NULL) {
				rowSize = curRow2->size;
				SparseNode * curCol2 = curRow2->colomnHead;
				while (curCol2 != NULL) {
					columnSize = curCol2->size;
					data = curCol2->data;
					Temp->insertElements(rowSize, columnSize, data, check = false);//if the value have the same row/colomn set to
					curCol2 = curCol2->colomnHead;								   //false to add up between the two matrices
				}
				curRow2 = curRow2->rowHead;
			}
			return Temp;
		}
	}

	//destructor
	~SM() {
		SparseNode * curRow = head;
		while (curRow != NULL) {
			SparseNode * currentCol = curRow->colomnHead;
			SparseNode * delNodes = curRow->colomnHead;
			while (currentCol != NULL) {
				currentCol = currentCol->colomnHead;
				delete delNodes;
				delNodes = currentCol;
			}
			curRow = curRow->rowHead;
			delete head;
			head = curRow;
		}
	}

};


void main() {
	int choice;
	SM * sm2 = new SM(5, 5);
	SM * sm1 = new SM(5, 5);
	SM * tempSM = new SM(5, 5);
start:
	system("cls");
	cout << "-------------------------------------------------" << endl;
	cout << "                Sparse Matrix" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << " 1.Add element for first Matrix " << endl;
	cout << " 2.Add element for second Matrix" << endl;
	cout << " 3.Print the first Matrix" << endl;
	cout << " 4.Print the second Matrix" << endl;
	cout << " 5.Summation between 2 Matrix" << endl;
	cout << " 6.To Quit " << endl;
	cout << "Enter your choice : ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		sm1->readElements();
		goto start;
		break;
	case 2:
		sm2->readElements();
		goto start;
		break;
	case 3:
		system("cls");
		cout << "-------------------------------------------------" << endl;
		cout << "                  First Matrix" << endl;
		cout << "-------------------------------------------------" << endl;
		sm1->printMatrix();
		system("pause");
		goto start;
		break;
	case 4:
		system("cls");
		cout << "-------------------------------------------------" << endl;
		cout << "                  Second Matrix" << endl;
		cout << "-------------------------------------------------" << endl;
		sm2->printMatrix();
		system("pause");
		goto start;
		break;
	case 5:
		system("cls");
		cout << "-------------------------------------------------" << endl;
		cout << "                Sum of two Matrix" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl << "First Matrix :\n" << endl;
		sm1->printMatrix();
		cout << endl << "Second Matrix :\n" << endl;
		sm2->printMatrix();
		cout << endl << "Sum for both Matrix :\n" << endl;
		tempSM = sm1->addSM(*sm2);
		tempSM->printMatrix();
		system("pause");
		goto start;
		break;
	case 6:
		exit(0);
		break;
	default:
		cout << "Wrong Input !" << endl;
		main();
		break;
	}

	system("pause");

}
