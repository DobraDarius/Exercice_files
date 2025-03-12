/*create a multi list that contains a list of departaments, each departaments identify with a ID, and each departament have employees.
Each eployee has a ID, salary and bonus. provide a example for 3 departaments with 4 employees each(different employees).
 - in first departament we need to sort the employees by salary in ascending manner
 - in second departament we need to sort the employees by bonus in descending manner
 - in third departament we need to erase the employees with no bonus

 all the data is of tipe unsigned int, and the ID's are unsigned int pointers(max 5 digits). 
 the first leter in the Employee ID is the first leter of the departament ID, that's how we know to which departament the employee belongs
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 typedef struct {
     unsigned int* id;
     unsigned int salary;
     unsigned int bonus;
 } Employee;
 
 typedef struct {
     unsigned int* id;
     Employee* employees;
     int emp_count;
 } Department;
 
 // Function to compare employees by salary (ascending)
 int compareSalary(const void* a, const void* b) {
     return ((Employee*)a)->salary - ((Employee*)b)->salary;
 }
 
 // Function to compare employees by bonus (descending)
 int compareBonus(const void* a, const void* b) {
     return ((Employee*)b)->bonus - ((Employee*)a)->bonus;
 }
 
 // Function to remove employees with no bonus in-place
 void filterEmployees(Department* dept) {
     int newCount = 0;
     for (int i = 0; i < dept->emp_count; i++) {
         if (dept->employees[i].bonus > 0) {
             dept->employees[newCount++] = dept->employees[i];
         }
     }
     dept->emp_count = newCount;
 }
 
 // Function to print a department
 void printDepartment(Department* dept) {
     printf("Department ID: %u\n", *(dept->id));
     for (int i = 0; i < dept->emp_count; i++) {
         printf("  Employee ID: %u, Salary: %u, Bonus: %u\n", 
                *(dept->employees[i].id), dept->employees[i].salary, dept->employees[i].bonus);
     }
 }
 
 int main() {
     Department departments[3];
 
     // Define departments
     unsigned int dep_ids[3] = {10001, 20002, 30003};
     for (int i = 0; i < 3; i++) {
         departments[i].id = &dep_ids[i];
         departments[i].emp_count = 4;
         departments[i].employees = (Employee*)malloc(4 * sizeof(Employee));
     }
 
     // Define employees (IDs follow department first letter rule)
     unsigned int emp_ids[12] = {1001, 1002, 1003, 1004, 2001, 2002, 2003, 2004, 3001, 3002, 3003, 3004};
 
     // Populate departments with employees
     unsigned int salaries[12] = {3000, 2500, 4000, 3500, 5000, 4200, 3800, 6000, 3200, 4500, 3100, 4800};
     unsigned int bonuses[12] = {500, 1000, 750, 800, 1200, 0, 500, 1800, 0, 500, 0, 700};
 
     for (int i = 0; i < 12; i++) {
         int dep_index = i / 4;
         departments[dep_index].employees[i % 4].id = &emp_ids[i];
         departments[dep_index].employees[i % 4].salary = salaries[i];
         departments[dep_index].employees[i % 4].bonus = bonuses[i];
     }
 
     // Apply sorting/filtering
     qsort(departments[0].employees, departments[0].emp_count, sizeof(Employee), compareSalary);
     qsort(departments[1].employees, departments[1].emp_count, sizeof(Employee), compareBonus);
     filterEmployees(&departments[2]);
 
     // Print results
     for (int i = 0; i < 3; i++) {
         printDepartment(&departments[i]);
         printf("\n");
     }
 
     // Free memory
     for (int i = 0; i < 3; i++) {
         free(departments[i].employees);
     }
 
     return 0;
 }
 

