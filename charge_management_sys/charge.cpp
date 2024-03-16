#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    int id;
    char name[50];
    float timeSpent; // ʹ��ʱ����Сʱ��
    float rate; // ÿСʱ���ʣ��̶�Ϊ0.5Ԫ
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

    printf("������ѧ��: ");
    scanf_s("%d", &id);
    printf("����������: ");
    scanf_s("%s", name, (unsigned)_countof(name));
    printf("������ʹ��ʱ����Сʱ��: ");
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
    printf("ID\t����\tʹ��ʱ��\t����\t����\n");
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
            printf("�û� %s (ѧ��: %d) �ķ���Ϊ %.2f\n", temp->name, temp->id, charge);
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ�ѧ��Ϊ%d�ļ�¼��\n", id);
}

void sortRecords(User** head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("��¼���㣬�޷���������\n");
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
                swapped = 1;  // �����˽���
                if (prev) {
                    prev->next = next;
                }
                else {
                    *head = next;
                }

                current->next = next->next;
                next->next = current;

                // ����ָ��
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

    printf("����ʹ��ʱ�������ļ�¼:\n");
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
            printf("��¼��ɾ����\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("δ�ҵ�ѧ��Ϊ%d�ļ�¼��\n", id);
}

void updateRecord(User* head, int id, float newTimeSpent) {
    User* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            temp->timeSpent = newTimeSpent;
            printf("�û� %s (ѧ��: %d) ��ʹ��ʱ���Ѹ���Ϊ %.2f Сʱ��\n", temp->name, temp->id, newTimeSpent);
            return;
        }
        temp = temp->next;
    }
    printf("δ�ҵ�ѧ��Ϊ%d�ļ�¼��\n", id);
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
        printf("����Ҫ������õ��û�ѧ��: ");
        scanf_s("%d", &id);
        calculateCharges(*head, id);
        break;
    case 4:
        sortRecords(head);
        //listRecords(*head);
        break;
    case 6:
        printf("����Ҫɾ�����û�ѧ��: ");
        scanf_s("%d", &id);
        deleteRecord(head, id);
        break;
    case 7:
        printf("����Ҫ����ʱ�����û�ѧ��: ");
        scanf_s("%d", &id);
        printf("�����µ�ʹ��ʱ����Сʱ��: ");
        scanf_s("%f", &timeSpent);
        updateRecord(*head, id, timeSpent);
        break;
    case 5:
        freeMemory(head);
        break;
    default:
        printf("��Чѡ��\n");
    }
}

int main() {
    User* head = NULL;
    int choice;

    while (1) {
        printf("\n1. ��Ӽ�¼\n2. �����¼\n3. �������\n4. �����¼\n5. �˳�\n6. ɾ����¼\n7. ����ʹ��ʱ��\n");
        printf("��ѡ�����: ");
        scanf_s("%d", &choice);

        if (choice == 5) {
            freeMemory(&head); // �˳�ǰ�ͷ��ڴ�
            break; // �˳�ѭ������������
        }

        processChoice(&head, choice);
    }

    return 0;
}

