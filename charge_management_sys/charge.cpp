#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    int id;
    char name[50];
    float timeSpent; // 使用时长（小时）
    float rate; // 每小时费率，固定为0.5元
    struct User* next;
} User;

User* createUser(int id, char name[], float timeSpent, float rate) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->id = id;
    strcpy_s(newUser->name, sizeof(newUser->name), name);
    newUser->timeSpent = timeSpent;
    newUser->rate = rate;
    newUser->next = NULL;
    return newUser;
}

void addRecord(User** head) {
    int id;
    char name[50];
    float timeSpent;
    const float rate = 0.5f;

    printf("请输入学号: ");
    scanf_s("%d", &id);
    printf("请输入姓名: ");
    scanf_s("%s", name, (unsigned)_countof(name));
    printf("请输入使用时长（小时）: ");
    scanf_s("%f", &timeSpent);

    User* newUser = createUser(id, name, timeSpent, rate);

    if (*head == NULL) {
        *head = newUser;
    }
    else {
        User* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newUser;
    }
}

void listRecords(User* head) {
    User* temp = head;
    printf("ID\t姓名\t使用时长\t费率\t费用\n");
    while (temp != NULL) {
        printf("%d\t%s\t%.2f\t\t%.2f\t%.2f\n", temp->id, temp->name, temp->timeSpent, temp->rate, temp->timeSpent * temp->rate);
        temp = temp->next;
    }
}

void calculateCharges(User* head, int id) {
    User* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            float charge = temp->timeSpent * temp->rate;
            printf("用户 %s (学号: %d) 的费用为 %.2f\n", temp->name, temp->id, charge);
            return;
        }
        temp = temp->next;
    }
    printf("未找到学号为%d的记录。\n", id);
}

void sortRecords(User** head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("记录不足，无法进行排序。\n");
        return;
    }

    int swapped;
    do {
        User* current = *head;
        User* prev = NULL;
        User* next = current->next;

        swapped = 0;

        while (next != NULL) {
            if (current->timeSpent > next->timeSpent) {
                swapped = 1;  // 发生了交换
                if (prev) {
                    prev->next = next;
                }
                else {
                    *head = next;
                }

                current->next = next->next;
                next->next = current;

                // 更新指针
                prev = next;
                next = current->next;
            }
            else {
                prev = current;
                current = next;
                next = next->next;
            }
        }
    } while (swapped);

    printf("根据使用时长排序后的记录:\n");
    listRecords(*head);
}



void deleteRecord(User** head, int id) {
    User* temp = *head;
    User* prev = NULL;

    while (temp != NULL) {
        if (temp->id == id) {
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            printf("记录已删除。\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("未找到学号为%d的记录。\n", id);
}

void updateRecord(User* head, int id, float newTimeSpent) {
    User* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->timeSpent = newTimeSpent;
            printf("用户 %s (学号: %d) 的使用时长已更新为 %.2f 小时。\n", temp->name, temp->id, newTimeSpent);
            return;
        }
        temp = temp->next;
    }
    printf("未找到学号为%d的记录。\n", id);
}

void freeMemory(User** head) {
    User* temp = *head;
    User* next = NULL;

    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
}

void processChoice(User** head, int choice) {
    int id;
    float timeSpent;

    switch (choice) {
    case 1:
        addRecord(head);
        break;
    case 2:
        listRecords(*head);
        break;
    case 3:
        printf("输入要计算费用的用户学号: ");
        scanf_s("%d", &id);
        calculateCharges(*head, id);
        break;
    case 4:
        sortRecords(head);
        //listRecords(*head);
        break;
    case 6:
        printf("输入要删除的用户学号: ");
        scanf_s("%d", &id);
        deleteRecord(head, id);
        break;
    case 7:
        printf("输入要更新时长的用户学号: ");
        scanf_s("%d", &id);
        printf("输入新的使用时长（小时）: ");
        scanf_s("%f", &timeSpent);
        updateRecord(*head, id, timeSpent);
        break;
    case 5:
        freeMemory(head);
        break;
    default:
        printf("无效选择！\n");
    }
}

int main() {
    User* head = NULL;
    int choice;

    while (1) {
        printf("\n1. 添加记录\n2. 浏览记录\n3. 计算费用\n4. 排序记录\n5. 退出\n6. 删除记录\n7. 更新使用时长\n");
        printf("请选择操作: ");
        scanf_s("%d", &choice);

        if (choice == 5) {
            freeMemory(&head); // 退出前释放内存
            break; // 退出循环，结束程序
        }

        processChoice(&head, choice);
    }

    return 0;
}

