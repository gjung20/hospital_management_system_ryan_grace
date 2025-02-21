#include <stdio.h>
#include<string.h>

#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50
#define MAX_DIAGNOSIS_LENGTH 400
#define DAYS_IN_A_WEEK 7
// Represents each day 3 shift times: morning, afternoon, and night.
#define SHIFTS_IN_A_DAY 3

// Patient Information stored using 2D arrays.
int patientIDs[MAX_PATIENTS] = {0};
char patientFullNamesList[MAX_PATIENTS][MAX_NAME_LENGTH];
int patientAges[MAX_PATIENTS];
char patientDiagnosisList[MAX_PATIENTS][MAX_DIAGNOSIS_LENGTH];
int assignedRoomList[MAX_PATIENTS];

int doctorSchedule[DAYS_IN_A_WEEK][SHIFTS_IN_A_DAY][MAX_NAME_LENGTH];

int totalPatients = 0;

int idExists(int arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == id){
            return i;
        }
    }
    return -1;
}

// Adds the patient to the patients list.
void addPatients() {
    if (totalPatients >= MAX_PATIENTS) {
        printf("Patient list is full! Cannot take anymore patients.");
        return;
    }
    // Temporary variables
    int patientID;
    char patientFullName[MAX_NAME_LENGTH];
    int patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH];
    int assignedRoom;

    // Validates the patients ID
    printf("Enter a patient ID (positive number): ");
    scanf("%d", &patientID);
    getchar(); //consume newline

    if (patientID <= 0 || idExists(patientIDs, totalPatients, patientID) != -1) {
        printf("Invalid or duplicate patient ID. Please input a valid patient ID.\n");
        return;
    }

    // Assigns the patients full name to the temporary variable
    printf("Enter the patient's full name: ");
    fgets(patientFullName, MAX_NAME_LENGTH, stdin);
    patientFullName[strcspn(patientFullName, "\n")] = 0;

    // Assigns the patient's age to the temporary variable
    do {
        printf("Enter the patient's age (positive number): ");
        scanf("%d", &patientAge);
        getchar(); //consume newline
        if (patientAge < 0) {
            printf("Patient must be over at least 0 years old!\n");
        }
    } while (patientAge < 0);

    // Assigns the patients diagnosis to the temporary variable
    printf("Enter the patient's diagnosis: ");
    fgets(patientFullName, MAX_DIAGNOSIS_LENGTH, stdin);
    patientDiagnosis[strcspn(patientDiagnosis, "\n")] = 0;

    // Assigns the patients room number to the temporary variable
    printf("Enter the patients room number (positive number): ");
    scanf("%d", &assignedRoom);
    getchar(); //consume newline

    // Applies the values in the temporary variables to the corresponding place in the 2D array
    // (our "database")
    patientIDs[totalPatients] = patientID;
    strcpy(patientFullNamesList[totalPatients], patientFullName);
    patientAges[totalPatients] = patientAge;
    strcpy(patientDiagnosisList[totalPatients], patientDiagnosis);
    assignedRoomList[totalPatients] = assignedRoom;

    totalPatients++;
}

void manageDoctorSchedule() {
    int day, shift;
    char doctorName[MAX_NAME_LENGTH];
    printf("Enter day (0-6, where 0 = Sunday): ");
    scanf("%d", &day);
    printf("Enter shift (0=Morning, 1=Afternoon, 2=Evening): ");
    scanf("%d", &shift);
    if (day < 0 || day >= DAYS_IN_A_WEEK || shift < 0 || shift >= SHIFTS_IN_A_DAY) {
        printf("Invalid day or shift.\n");
        return;
    }
    printf("Enter Doctor's Name: ");
    scanf(" %s", doctorName);
    strcpy(doctorSchedule[day][shift], doctorName);
    printf("Doctor assigned successfully.\n");
}

void viewDoctorSchedule() {
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char *shifts[] = {"Morning", "Afternoon", "Evening"};
    printf("\nDoctor Schedule:\n");
    for (int i = 0; i < DAYS_IN_A_WEEK; i++) {
        printf("%s:\n", days[i]);
        for (int j = 0; j < SHIFTS_IN_A_DAY; j++) {
            printf("  %s: %s\n", shifts[j], doctorSchedule[i][j][0] ? doctorSchedule[i][j] : "Unassigned");
        }
    }
}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}