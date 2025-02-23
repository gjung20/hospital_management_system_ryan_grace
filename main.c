#include <stdio.h>
#include<string.h>
// #include<conio.h>
#include<stdlib.h>

#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50 //Including null character
#define MAX_DIAGNOSIS_LENGTH 200 //Including null character
#define DAYS_IN_A_WEEK 7
#define SHIFTS_IN_A_DAY 3 // Represents each day 3 shift times: morning, afternoon, and night.

// Patient Information stored using 2D arrays.
int patientIDs[MAX_PATIENTS] = {0};
char patientFullNamesList[MAX_PATIENTS][MAX_NAME_LENGTH] = {0};
int patientAges[MAX_PATIENTS] = {0};
char patientDiagnosisList[MAX_PATIENTS][MAX_DIAGNOSIS_LENGTH] = {0};
int assignedRoomList[MAX_PATIENTS] = {0};

// Shift information stored using 2D arrays.
int doctorSchedule[DAYS_IN_A_WEEK][SHIFTS_IN_A_DAY][MAX_NAME_LENGTH] = {0};

int totalPatients = 0;
int currentID = 0;

void addPatients();
void viewPatients();
void searchPatients();
void dischargePatients();
void shiftArray(void *arr, int itemSize, int arrayLength, int index);
void getSafeStringInput(char *target, int limit);
void getSafeInt(int *target);
void clearStdin();
void manageDoctorSchedule();
void viewDoctorSchedule();

// Menu Interface
void menu()
{
    int choice;
    do
    {
        printf("\nHospital Management System\n");
        printf("1. Add Patient Record\n");
        printf("2. View All Patients\n");
        printf("3. Search for Patient\n");
        printf("4. Discharge Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. View Doctor Schedule\n");
        printf("7. Exit\n");
        getSafeInt(&choice);

        switch (choice)
        {
            case 1: addPatients();
                break;
            case 2: viewPatients();
                break;
            case 3: searchPatients();
                break;
            case 4: dischargePatients();
                break;
            case 5: manageDoctorSchedule();
                break;
            case 6: viewDoctorSchedule();
                break;
            case 7: printf("Exiting... \n");
                break;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    while (choice != 7);
}

//Checks if the given ID is in the patientID's array, if so return the index, if not return -1.
int idExists(int arr[], int size, int id)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == id)
        {
            return i;
        }
    }
    return -1;
}

// Adds the patient to the patients list.
void addPatients()
{
    if (totalPatients >= MAX_PATIENTS)
    {
        printf("Patient list is full! Cannot take more patients.");
        return;
    }

    // Temporary variables
    char patientFullName[MAX_NAME_LENGTH] = {0};
    int patientAge;
    char patientDiagnosis[MAX_DIAGNOSIS_LENGTH] = {0};
    int assignedRoom;


    // Assigns the patients full name to the temporary variable
    printf("Enter the patient's full name: ");
    getSafeStringInput(patientFullName, MAX_NAME_LENGTH);

    // Assigns the patient's age to the temporary variable
    do
    {
        printf("Enter the patient's age (positive number): ");
        getSafeInt(&patientAge);
        if (patientAge < 0)
        {
            printf("Patient must be over at least 0 years old!");
        }
    }
    while (patientAge < 0);

    // Assigns the patients diagnosis to the temporary variable
    printf("Enter the patient's diagnosis: ");
    getSafeStringInput(patientDiagnosis, MAX_DIAGNOSIS_LENGTH);

    // Assigns the patients room number to the temporary variable
    do
    {
        printf("Enter the patient's room number (positive number): ");
        getSafeInt(&assignedRoom);
        if (assignedRoom < 0)
        {
            printf("Room number must be positive!");
        }
    }
    while (assignedRoom < 0);

    // Applies the values in the temporary variables to the corresponding place in the 2D array
    patientIDs[totalPatients] = currentID;
    strcpy(patientFullNamesList[totalPatients], patientFullName);
    patientAges[totalPatients] = patientAge;
    strcpy(patientDiagnosisList[totalPatients], patientDiagnosis);
    assignedRoomList[totalPatients] = assignedRoom;

    totalPatients++;
    currentID++;
    printf("Patient created successfully.\n");
}

// Displays all patients in a tabular format
void viewPatients()
{
    if (totalPatients == 0)
    {
        printf("No patients found.\n");
        return;
    }

    printf("\nPatients:\n");
    printf("ID\tName\t\t\t\t\t\t\tAge\tRoom\tDiagnosis\n");
    for (int i = 0; i < totalPatients; i++)
    {
        printf("%d\t%-50s\t%d\t%d\t%s\n", patientIDs[i], patientFullNamesList[i], patientAges[i],
               assignedRoomList[i], patientDiagnosisList[i]);
    }
}

// Allows the user to search for patients by ID or by name
void searchPatients()
{
    int choice, id, index = -1;
    char input[50] = {0};

    printf("Search by (1) ID or (2) Name:");
    getSafeInt(&choice);

    if (choice == 1)
    {
        printf("Enter Patient ID:");
        getSafeInt(&id);
        index = idExists(patientIDs, totalPatients, id);
    }
    else if (choice == 2)
    {
        getSafeStringInput(input, MAX_NAME_LENGTH);
        for (int i = 0; i < totalPatients; i++)
        {
            if (strcmp(patientFullNamesList[i], input) == 0)
            {
                index = i;
                break;
            }
        }
    }

    if (index != -1)
    {
        printf("Patient Found - ID: %d, Name: %s, Age: %d, Diagnosis: %s, Room: %d\n", patientIDs[index],
               patientFullNamesList[index],
               patientAges[index], patientDiagnosisList[index], assignedRoomList[index]);
    }
    else
    {
        printf("Patient not found.\n");
    }
}

// Removes a patient from each of the arrays
void dischargePatients()
{
    if (totalPatients == 0)
    {
        printf("No patients found.\n");
    }

    int id;
    int index;

    printf("Enter Patient ID:");
    getSafeInt(&id);
    index = idExists(patientIDs, totalPatients, id);

    if (index != -1)
    {
        shiftArray(patientIDs, sizeof(patientIDs[0]), MAX_PATIENTS, index);
        shiftArray(patientFullNamesList, sizeof(patientFullNamesList[0]), MAX_PATIENTS, index);
        shiftArray(patientAges, sizeof(patientAges[0]), MAX_PATIENTS, index);
        shiftArray(patientDiagnosisList, sizeof(patientDiagnosisList[0]), MAX_PATIENTS, index);
        shiftArray(assignedRoomList, sizeof(assignedRoomList[0]), MAX_PATIENTS, index);
        totalPatients--;
        printf("Patient discharged successfully.\n");
    }
    else
    {
        printf("Patient not found.\n");
    }
}

// Edit the doctor schedule by asking for day of the week and shift time.
// If a shift is added on a day a shift is already assigned, the new shift will replace the old one.
void manageDoctorSchedule() {
    int day, shift;

    // get the day
    do
    {
        printf("Enter day (0-6, where 0 = Sunday): ");
        getSafeInt(&day);

        if (day < 0 || day > 7)
        {
            printf("Invalid day.\n");
        }
    } while (day < 0  || day > 6);

    // get the shift
    do
    {
        printf("Enter shift (0=Morning, 1=Afternoon, 2=Evening): ");
        getSafeInt(&shift);

        if (shift < 0 || shift > 2)
        {
            printf("Invalid shift.\n");
        }
    } while (shift < 0  || shift > 2);

    // get the name
    printf("Enter Doctor's Name: ");
    getSafeStringInput(doctorSchedule[day][shift], MAX_NAME_LENGTH);
    printf("Doctor assigned successfully.\n");
}

// Displays the schedule
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

/*
 * Removes the value at the given index from the given array, shifting proceeding value back an index.
 *
 * @param arr the  array to remove value from
 * @param itemSize the number of bytes 1 array item takes in memory
 * @param arrayLength the length of the array given
 * @param the index to remove
 */
void shiftArray(void *arr, int itemSize, int arrayLength, int index)
{
    if (index < 0 || index >= arrayLength) // Prevent out-of-bounds access
    {
        return;
    }

    char *charArr = arr; // Cast void * to char *

    if (index != arrayLength - 1) // Avoid shifting if removing last item
    {
        char *target = charArr + itemSize * index;
        char *source = charArr + itemSize * (index + 1);
        size_t numBytes = (arrayLength - index - 1) * itemSize;

        memmove(target, source, numBytes);
    }

    // Replace last item of array with zero bytes
    memset(charArr + (arrayLength - 1) * itemSize, 0, itemSize);
}

/*
 * Grabs a string of the given length from stdin. If there is more in stdin than the given length,
 * a warning will be posted to the console and allow the user to  re-input their response.
 *
 * To check if there is extra chars in stdin, it first grabs 1 extra character than requested and replaces the first \n with a \0.
 * If the first \0 is the last character of the string, then last character will be cut off when making the correct length string
 * thus it warns the user.
 *
 * @param the string to store the data
 * @param how long the string will be including null terminator
 */
void getSafeStringInput(char *target, int limit)
{

    int invalidString = 1;
    while (invalidString) // loop until a valid input
    {
        char tooLongString[limit + 1]; // Stores a string 1 longer than necessary

        fgets(tooLongString, limit + 1, stdin);
        tooLongString[strcspn(tooLongString, "\n")] = 0;

        strncpy(target, tooLongString, limit);
        target[limit - 1] = '\0';

        if (strcspn(tooLongString, "\0") < limit) // if the string is too long, warn the user
        {
            break;
        }

        clearStdin();
        printf("Warning! Inputted value is too long, the following value will be saved: \n%s\nEnter 1 to confirm, 2 to Cancel:", target);

            while (1)
            {
                int choice = 0;
                getSafeInt(&choice);
                if (choice == 1)
                {
                    printf("Confirmed.");
                    invalidString = 0;
                    break;
                }
                if (choice == 2)
                {
                    printf("Canceled, Input new String:");
                    break;
                }
                printf("Invalid input, try again:");
            }
    }

}

/*
 * Grabs an int from stdin, validates that it is an int, and assigns it to the given target
 * @param where to store the int
 */
void getSafeInt(int* target)
{
    char input[10];
    char *end = NULL;
    while (1)
    {
        scanf("%s", input);
        clearStdin();

        long int num = strtol(input, &end, 10);
        if (end == input || *end != '\0') {
            printf("Invalid input, try again:");
        } else {
            *target = num;
            break;
        }
    }
}

// Consumes characters in stdin until a \n is reached
void clearStdin()
{
    while (getchar() != '\n');
}

//runs the program
int main(void) {
    menu();
}