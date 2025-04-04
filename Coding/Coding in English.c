#include <stdio.h>
#include <stdlib.h>

typedef struct Article {
    char name[50];
    float unit_price;
    int quantity;
} Article;

typedef struct Order {
    int id;
    char date[11]; 
    Article articles[10];
    int article_count;
    struct Order* prev;
    struct Order* next;
} Order;

// 1. Create an order by user input
Order* create_order() {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (!new_order) return NULL;

    printf("Order ID: ");
    scanf("%d", &new_order->id);

    printf("Date (DD/MM/YYYY): ");
    scanf("%s", new_order->date);

    printf("Number of articles: ");
    scanf("%d", &new_order->article_count);

    for (int i = 0; i < new_order->article_count; i++) {
        printf("Article %d name: ", i + 1);
        scanf("%s", new_order->articles[i].name);

        printf("Unit price: ");
        scanf("%f", &new_order->articles[i].unit_price);

        printf("Quantity: ");
        scanf("%d", &new_order->articles[i].quantity);
    }

    new_order->prev = NULL;
    new_order->next = NULL;
    return new_order;
}

// 2. Create an order with predefined data
Order* create_order_data(int id, char date[], Article articles[], int article_count) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (!new_order) return NULL;

    new_order->id = id;
    strcpy(new_order->date, date);
    new_order->article_count = article_count;

    for (int i = 0; i < article_count; i++) {
        new_order->articles[i] = articles[i];
    }

    new_order->prev = NULL;
    new_order->next = NULL;
    return new_order;
}

// 3. Calculate the length of the list
int list_length(Order* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// 4. Insert an order at a given position
Order* insert_at_position(Order* head, Order* new_order, int position) {
    if (position == 0 || !head) {
        new_order->next = head;
        if (head) head->prev = new_order;
        return new_order;
    }

    Order* current = head;
    for (int i = 0; i < position - 1 && current->next; i++) {
        current = current->next;
    }

    new_order->next = current->next;
    if (current->next) current->next->prev = new_order;

    current->next = new_order;
    new_order->prev = current;

    return head;
}

// 5. Delete an order at a given position
Order* delete_at_position(Order* head, int position) {
    if (!head) return NULL;

    if (position == 0) {
        Order* temp = head;
        head = head->next;
        if (head) head->prev = NULL;
        free(temp);
        return head;
    }

    Order* current = head;
    for (int i = 0; i < position && current; i++) {
        current = current->next;
    }

    if (!current) return head;

    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    free(current);
    return head;
}

// 6. Delete all orders on a specific date
Order* delete_all_orders_by_date(Order* head, char date[]) {
    Order* current = head;
    while (current) {
        Order* next = current->next;
        if (strcmp(current->date, date) == 0) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next;

            if (current->next) current->next->prev = current->prev;
            free(current);
        }
        current = next;
    }
    return head;
}

// 7. Display orders in forward order
void display_orders_forward(Order* head) {
    while (head) {
        printf("Order ID: %d | Date: %s | Articles: %d\n", head->id, head->date, head->article_count);
        head = head->next;
    }
}

// 8. Display orders in reverse order
void display_orders_reverse(Order* head) {
    while (head && head->next) head = head->next;
    while (head) {
        printf("Order ID: %d | Date: %s | Articles: %d\n", head->id, head->date, head->article_count);
        head = head->prev;
    }
}

// 9. Search for an order by ID
Order* search_order_by_id(Order* head, int id) {
    while (head) {
        if (head->id == id) return head;
        head = head->next;
    }
    return NULL;
}

// 10. Reverse the list
Order* reverse_list(Order* head) {
    Order* current = head;
    Order* temp = NULL;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    return temp ? temp->prev : NULL;
}

// 11. Merge two lists
Order* merge_lists(Order* l1, Order* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    Order* current = l1;
    while (current->next) current = current->next;

    current->next = l2;
    l2->prev = current;

    return l1;
}

// 12. Insert into a sorted list by date
Order* insert_sorted(Order* head, Order* new_order) {
    if (!head || strcmp(new_order->date, head->date) < 0) {
        new_order->next = head;
        if (head) head->prev = new_order;
        return new_order;
    }

    Order* current = head;
    while (current->next && strcmp(current->next->date, new_order->date) < 0) {
        current = current->next;
    }

    new_order->next = current->next;
    if (current->next) current->next->prev = new_order;
    current->next = new_order;
    new_order->prev = current;

    return head;
}

// 13. Remove duplicate orders (same ID and date)
void remove_duplicates(Order* head) {
    for (Order* i = head; i && i->next; i = i->next) {
        Order* j = i->next;
        while (j) {
            Order* next = j->next;
            if (i->id == j->id && strcmp(i->date, j->date) == 0) {
                if (j->prev) j->prev->next = j->next;
                if (j->next) j->next->prev = j->prev;
                free(j);
            }
            j = next;
        }
    }
}

// 14. Main function to test
int main() {
    Order* list = NULL;

    Order* o1 = create_order();

    Article articles[] = { {"Mouse", 50.0, 1}, {"Keyboard", 120.0, 1} };
    Order* o2 = create_order_data(2, "05/04/2025", articles, 2);

    list = insert_at_position(list, o1, 0);
    list = insert_at_position(list, o2, 1);

    printf("\nOrders in forward order:\n");
    display_orders_forward(list);

    Order* found = search_order_by_id(list, 2);
    if (found) printf("\nOrder found: ID = %d\n", found->id);

    list = reverse_list(list);
    printf("\nOrders after reversing:\n");
    display_orders_forward(list);

    list = delete_at_position(list, 0);

    printf("\nOrders after deletion:\n");
    display_orders_forward(list);

    return 0;
}
