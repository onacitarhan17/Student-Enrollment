//THIS CODE IS MY OWN WORK. I DID NOT CONSULT TO ANY PROGRAM WRITTEN BY OTHER STUDENTS. I READ AND FOLLOWED THE GUIDELINE GIVEN IN THE PROGRAMMING ASSIGNMENT 3. NAME: Özgün Ozan Nacitarhan

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int FLAG = 20; // Global variable declaration
int option = 0; // Global variable declaration for options

typedef struct Grade {
	char examName[20];
	int points;
}Grade;

typedef struct Student {
	int id;
	char name[20];
	char surname[20];
	char letterGrade;
	Grade grades[5];
	int numberOfExamsGraded;
	struct Student* next;
}Student;

//Provided by PA3.
Student* findStudentById(Student* head, int id);
void addStudentSorted(Student** headPtr, int id, char name[], char surname[]);
Student* removeStudent(Student** headPtr, int id);
void addGrade(Student* head, int id, char exam[], int takenPoint);
void printCourseReportForAllStudents(Student* head);
double calculateClassAvarageForOneExam(Student* head, char examName[]);
bool isStudentInList(Student* head, int id);
void calculateLetterGradesOfAllStudents(Student* head);
struct Student* head = NULL;
bool isListEmpty(Student* *headPtr);
void printStudent(Student* student);
char find_letter_grade(Student* student);

int main() {

	//Printing the options 
	printf("Option 1 - Enter 1 in order to add a new student into the course then press Enter \n");
	printf("Option 2 - Enter 2 in order to check if the student is in the course list \n");
	printf("Option 3 - Enter 3 in order to delete a student in the course then press Enter \n");
	printf("Option 4 - Enter 4 in order to add or change the grade the student then press Enter \n");
	printf("Option 5 - Enter 5 in order to calculate the class gradeAvg point then press Enter \n");
	printf("Option 6 - Enter 6 in order to print the course report for one student \n");
	printf("Option 7 - Enter 7 in order to print the course report for all students then press Enter \n");
	printf("Option 8 - Enter 8 in order to exit then press Enter \n");

	while (option != 8)
	{
		char futureID[20], name[20], surname[20], quizNumber[20], strToId[20], strToGrade[20];
		printf("Choose one option: ");
		scanf_s("%d", &option);
		int id;
		int grade;
		
		if (option == 8) // Option 8 
		{
			printf("Bye bye");
			exit(0);
		}
		// Option 7 
		else if (option == 7)
		{
			printf("You have chosen the option 7. Course report for all students: \n");
			if (!isListEmpty(head))
			{
				calculateLetterGradesOfAllStudents(head);
				printCourseReportForAllStudents(head);
			}
			else
			{
				printf("There are no students currently \n");
			}
		} // Option 6 
		else if (option == 6)
		{
			printf("You have chosen the option 6. Enter the student ID then press Enter. \n");
			scanf_s("%s", &futureID, FLAG); //Using FLAG to use scanf_s with +3 inputs
			id = atoi(futureID);
			Student *st = findStudentById(head, id);
			if (st != NULL)
			{
				st->letterGrade = find_letter_grade(st);
				printStudent(st);
			}
			else
			{
				printf("There is not a student with id %d \n", id);
			}
		}// Option 5
		else if (option == 5)
		{
			printf("You have chosen the option 5. Enter the quiz name (quiz1, quiz2...) then press Enter.\n");
			scanf_s("%s", &futureID, FLAG); //Using FLAG to use scanf_s with +3 inputs
			double avg = calculateClassAvarageForOneExam(head, futureID);
			printf("Class gradeAvg for %s is: %0.1f \n", quizNumber, avg);
		}// Option 4 
		else if (option == 4)
		{
			printf("You have chosen the option 4. Enter the student ID, quiz name (quiz1, quiz2...), and grade separated by one space then press Enter.\n");
			scanf_s("%s  %s %s", &strToId, FLAG, &quizNumber, FLAG, &strToGrade, FLAG); //Using FLAG to use scanf_s with +3 inputs
			id = atoi(strToId);
			grade = atoi(strToGrade);
			addGrade(head, id, quizNumber, grade);
		}// Option 3 
		else if (option == 3)
		{
			printf("You have chosen the option 3. Enter the student ID then press Enter. \n");
			scanf_s("%s", &futureID, FLAG); //Using FLAG to use scanf_s with 3 inputs
			id = atoi(futureID);
			Student* removed = removeStudent(&head, id);
			if (removed != NULL)
			{
				printf("Student with id %d is succesfully removed \n", id);
			}
			else
			{
				printf("Student with id %d cannot be found \n", id);
			}
		}// Option 2 
		else if (option == 2)
		{
			printf("You have chosen the option 2. Enter the student ID then press Enter. \n");
			scanf_s("%s", &futureID, FLAG); //Using FLAG to use scanf_s with +3 inputs
			id = atoi(futureID);
			if (isStudentInList(head, id))
			{
				printf("Student with id %d is in the course \n", id);
			}
			else
			{
				printf("Student with id %d is not in the course \n", id);
			}
		}// Option 1
		else if (option == 1) 
		{
			printf("You have chosen the option 1. Enter the student name, surname and ID seperated by one space then press Enter. \n");
			scanf_s("%s %s %s", &name, FLAG, &surname, FLAG, &strToId, FLAG); //Using FLAG to use scanf_s with +3 inputs
			id = atoi(strToId);
			addStudentSorted(&head, id, name, surname);
		}
	}
}

void printStudent(Student* student) {

	printf("%s %s\t id:%d\t", student->name, student->surname, student->id);

	printf("Graded exams: ");

	for (int i = 0; i < student->numberOfExamsGraded; i++) {
		printf("%s :%d\t", student->grades[i].examName, student->grades[i].points);
	}

	printf("\nLetter : %c \n", student->letterGrade);
}

double calculateClassAvarageForOneExam(Student* head, char examName[])
{
	Student* current = head;

	double gradesAverage = 0;
	int numberOfGrades = 0;

	while (current != NULL)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (strcmp(current->grades[i].examName, examName) == 0)
			{
				gradesAverage += current->grades[i].points;
				numberOfGrades++;
			}
		}
		current = current->next;
	}

	return gradesAverage / numberOfGrades;
}

void printCourseReportForAllStudents(Student* head)
{
	Student* current = head;
	while (current != NULL)
	{
		current->letterGrade = find_letter_grade(current);
		printStudent(current);
		current = current->next;
	}

}

void addStudentSorted(Student** headPtr, int id, char name[], char surname[])
{
	Student* new;
	Student* current = *headPtr;
	Student* previous = NULL;

	new = (Student*)malloc(sizeof(struct Student));
	new->next = NULL;
	new->numberOfExamsGraded = 0;
	new->id = id;

	for (int i = 0; i < 5; ++i)
	{
		strcpy_s(new->grades[i].examName, sizeof(new->grades[i].examName), "NOT_ENTERED");
		new->grades[i].points = 0;
	}
	strcpy_s(new->name, sizeof(new->name), name);
	strcpy_s(new->surname, sizeof(new->surname), surname);
	new->numberOfExamsGraded = 0;

	if (*headPtr == NULL)
	{
		*headPtr = new;
		return;
	}

	while (current != NULL)
	{
		if (current->id > id)
		{
			if (current == *headPtr)
			{
				new->next = current;
				*headPtr = new;
				return;
			}
			else
			{
				previous->next = new;
				new->next = current;
				return;
			}
		}
		previous = current;
		current = current->next;
	}

	previous->next = new;
	new->next = NULL;
}


void addGrade(Student* head, int id, char exam[], int takenPoint)
{
	Student* stu = findStudentById(head, id);
	int lastGrade = -1;
	if (stu != NULL)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (strcmp(stu->grades[i].examName, exam) == 0)
			{
				stu->grades[i].points = takenPoint;
				return;
			}
			if (strcmp(stu->grades[i].examName, "NOT_ENTERED") == 0 && lastGrade == -1)
			{
				lastGrade = i;
			}
		}
		if (stu->numberOfExamsGraded < 5)
		{
			Grade* grade;
			grade = (Grade*)malloc(sizeof(struct Grade));
			strcpy_s(grade->examName, sizeof(grade->examName), exam);
			grade->points = takenPoint;
			stu->grades[lastGrade] = *grade;
			stu->numberOfExamsGraded = stu->numberOfExamsGraded + 1;
		}
		else
		{
			printf("You are not able to assign more than 5 exams to the student with id %d \n", stu->id);
		}
	}
}

//This method is given by PA3
Student* removeStudent(Student** headPtr, int id)
{
	Student* current = *headPtr;
	Student* previous = NULL;

	if (current != NULL && current->id == id)
	{
		*headPtr = current->next;
		return current;
	}

	while (current != NULL && current->id != id)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
	{
		return NULL;
	}

	previous->next = current->next;
	return current;

}

void calculateLetterGradesOfAllStudents(Student* head)
{
	Student* current = head;

	while (current != NULL)
	{
		current->letterGrade = find_letter_grade(current);
		current = current->next;
	}
}

Student* findStudentById(Student *headPtr, int id)
{
	Student* current = headPtr;

	while (current != NULL)
	{
		if (current->id == id)
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
}

bool isListEmpty(Student **headPtr)
{
	if (headPtr == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char find_letter_grade(Student* student)
{
	int gradeAvg = 0;
	for (int i = 0; i < 5; ++i)
	{
		gradeAvg += student->grades[i].points;
	}
	gradeAvg = gradeAvg / 5;
	if (gradeAvg < 60)
	{
		return 'F';
	}
	else if (gradeAvg < 70 && gradeAvg >= 60)
	{
		return 'D';
	}
	else if (gradeAvg < 80 && gradeAvg >= 70)
	{
		return 'C';

	}
	else if (gradeAvg < 90 && gradeAvg >= 80)
	{
		return 'B';
	}
	else if (gradeAvg <= 100 && gradeAvg >= 90)
	{
		return 'A';
	}
}

bool isStudentInList(Student* head, int id)
{
	return findStudentById(head, id) != NULL;
}

