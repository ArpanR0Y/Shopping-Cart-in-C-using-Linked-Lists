#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#define ISEMPTY printf("\nEMPTY LIST:");

struct node
{
    int id;
    char name[20];
    int price;
    int qty;
    struct node *next;
};

struct node2
{
    int id;
    int qty;
    struct node2 *next2;
};

typedef struct node snode;
typedef struct node2 snode2;
snode *newnode, *ptr, *prev,*temp;
snode *first = NULL, *last = NULL;
snode2 *newnode2, *ptr2, *prev2,*temp2;
snode2 *first2 = NULL, *last2 = NULL;


snode* create_node(int id, char *name, int price, int qty);
snode2* create_node2(int id, int qty);
void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void addToCart();
void viewCart();
void modifyCart();
void checkout();
void checkStock(int id, int qty);
void updateStock();
void updateCart(int id, int qty);
void removeProduct();
void deleteCart(int id);
void clearCart();
int posProduct(int id);
int posCart(int id);
void displayAllProduct();

void main()
{
    int ch;

    while (1)
    {
        system("cls");
        printf("=========================================================\n\n");
        printf("\t\t WELCOME TO SHOPPING CART!!\n\n");
        printf("=========================================================\n\n");
        printf("1. Manage Product\n\n");
        printf("2. Purchase Product\n\n");
        printf("3. Generate Bill\n\n");
        printf("0. Exit\n\n");
        printf("=========================================================\n\n");
        printf("\nPlease enter your Choice: ");
        scanf("%d",&ch);

        switch (ch)
        {
            case 1: {
                manageProduct();
                break;
            }
            case 2:{
                purchaseProduct();
                break;
            }
            case 3: {
                generateBill();
                break;
            }
            case 0: exit(0);
            default: printf("Valid choice not entered!");
        }

    }

}

void manageProduct()
{
    int ch;
    char ch2;

    while (1)
    {
        system("cls");
        printf("=========================================================\n\n");
        printf("\t\t WELCOME MANAGER!!\n\n");
        printf("=========================================================\n\n");
        printf("1. Add New Product\n\n");
        printf("2. Display All Products\n\n");
        printf("0. Back\n\n");
        printf("=========================================================\n\n");
        printf("\nPlease enter your Choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1: {
                addProduct();
                break;
            }
            case 2:{
                displayAllProduct();
                printf("\n Do you wish to remove an Item from Stock[Y/N]? ");
                scanf("%s",&ch2);
                if (ch2 == 'Y'||ch2 == 'y')
                {
                    removeProduct();
                    getch();
                }
                if (ch2 == 'N'||ch2 == 'n')
                {
                    return main();
                }
                break;
            }
            case 0:{
                return;
            }
            default: printf("Valid choice not entered!");

        }

    }
}

snode* create_node(int id, char *name, int price, int qty)
{
    newnode=(snode*)malloc(sizeof(snode));
    if(newnode==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
    else
    {
        newnode->id=id;
        strcpy(newnode->name,name);
        newnode->price=price;
        newnode->qty=qty;
        newnode->next=NULL;
        return newnode;
    }
}

snode2* create_node2(int id, int qty)
{
    newnode2=(snode2*)malloc(sizeof(snode2));
    if(newnode2==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
    else
    {
        newnode2->id=id;
        newnode2->qty=qty;
        newnode2->next2=NULL;
        return newnode2;
    }
}

void addProduct()
{
    system("cls");
    int id, price, qty,pos,cnt=0,i;
    printf("=========================================================\n\n");
    printf("\t\t ADD PRODUCTS!!\n\n");
    printf("=========================================================\n\n");
    char name[20],ch;
    printf("\nEnter the ID of the product: ");
    scanf("%d", &id);
    for (ptr = first;ptr != NULL;ptr = ptr->next)
    {
        if (ptr->id==id)
        {
            printf("Product ID already in use.");
            getch();
            return manageProduct();
        }

    }
    printf("\nEnter the name of the product: ");
    scanf("%s", name);
    printf("\nEnter the price of the product: ");
    scanf("%d", &price);
    printf("\nEnter the quantity of the product: ");
    scanf("%d", &qty);

    newnode = create_node(id, name, price, qty);
    pos = posProduct(id);
    if (pos == 0) {
        if (first == last && first == NULL) {
            first = last = newnode;
            first->next = NULL;
            last->next = NULL;
        } else {
            temp = first;
            first = newnode;
            first->next = temp;
        }
    } else {
        ptr = first;
        while (ptr != NULL) {
            ptr = ptr->next;
            cnt++;
        }
        if (pos == 1) {
            if (first == last && first == NULL) {
                first = last = newnode;
                first->next = NULL;
                last->next = NULL;
            } else {
                temp = first;
                first = newnode;
                first->next = temp;
            }
        } else if (pos > 1 && pos <= cnt) {
            ptr = first;
            for (i = 1; i < pos; i++) {
                prev = ptr;
                ptr = ptr->next;
            }
            prev->next = newnode;
            newnode->next = ptr;
        } else {
            printf("Product Not Found!!");
        }
    }

    printf("\nProduct Added Successfully!!");
    printf("\nDo you want to add another product[Y/N]? ");
    scanf("%s", &ch);
    if (ch == 'Y' || ch == 'y') {
        system("cls");
        return addProduct();
    }
    if (ch == 'N' || ch == 'n') {
        return;
    }

    getch();
}

void displayAllProduct()
{
    system("cls");
    if (first == NULL)
    {
        ISEMPTY;
        printf("No Products Available. \n");
        getch();
        return main();
    }
    else
    {
        printf("=========================================================\n\n");
        printf("\t\t Product Details\n\n");
        printf("=========================================================\n\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            printf("%d\t", ptr->id);
            printf("%s\t", ptr->name);
            printf("%d\t", ptr->qty);
            printf("%d\t", ptr->price);
            printf("\n");
        }
        printf("=========================================================\n\n");
    }
    getch();
}

void removeProduct()
{
    int id, cnt = 0, i,pos;

    if (first == NULL)
    {
        ISEMPTY;
        printf("\nNo Products to delete\n");
    }
    else
    {
        printf("\nEnter the id of value to be deleted:");
        scanf(" %d", &id);
        pos=posProduct(id);
        ptr = first;
        if (pos == 1)
        {
            first = ptr->next;
            printf("\nElement deleted");
        }
        else
        {
            while (ptr != NULL)
            {
                ptr = ptr->next;
                cnt = cnt + 1;
            }
            if (pos > 0 && pos <= cnt)
            {
                ptr = first;
                for (i = 1;i < pos;i++)
                {
                    prev = ptr;
                    ptr = ptr->next;
                }
                prev->next = ptr->next;
            }
            else
            {
                printf("\nProduct Not Found!!");
                getch();
                return manageProduct();
            }
            free(ptr);
            printf("\nElement deleted");
        }
    }
}

int posProduct(int id)
{
    int pos = 0;

    if (first == NULL)
    {
        return pos;
    }
    else
    {
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            pos = pos + 1;
            if (ptr->id == id)
            {
                return pos;
            }
        }

    }

}

int posCart(int id)
{
    int pos = 0;

    if (first2 == NULL)
    {
        return pos;
    }
    else
    {
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        {
            pos = pos + 1;
            if (ptr2->id == id)
            {
                return pos;
            }
        }

    }
}

void purchaseProduct()
{
    int ch;

    while (1)
    {
        system("cls");
        displayAllProduct();
        printf("\t\t\n WELCOME CUSTOMER!!\n\n");
        printf("\n1. Buy a product\n");
        printf("\n0. Back\n");
        printf("\nPlease enter your Choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1: {
                addToCart();
                break;
            }
            case 0:{
                return main();
            }
            default: printf("Valid choice not entered!");

        }

    }

}

void addToCart()
{
    int id, qty,pos,cnt=0,i;
    char ch;
    printf("\n Enter the ID of the product you wish to add to cart: ");
    scanf("%d",&id);
    for (ptr = first;ptr != NULL;ptr = ptr->next)
    {
        if (ptr->id == id)
        {
            printf("\n Enter the quantity[1-10]: ");
            scanf("%d",&qty);
            if (qty<=10) {
                checkStock(id, qty);
                newnode2 = create_node2(id, qty);
                pos=posCart(id);
                if(pos==0)
                {
                    if (first2 == last2 && first2 == NULL)
                    {
                        first2 = last2 = newnode2;
                        first2->next2 = NULL;
                        last2->next2 = NULL;
                    }
                    else
                    {
                        temp2 = first2;
                        first2 = newnode2;
                        first2->next2 = temp2;
                    }
                }
                else
                {
                    ptr2 = first2;
                    while (ptr2 != NULL)
                    {
                        ptr2 = ptr2->next2;
                        cnt++;
                    }
                    if (pos == 1)
                    {
                        if (first2 == last2 && first2 == NULL)
                        {
                            first2 = last2 = newnode2;
                            first2->next2 = NULL;
                            last2->next2 = NULL;
                        }
                        else
                        {
                            temp2 = first2;
                            first2 = newnode2;
                            first2->next2 = temp2;
                        }
                    }
                    else if (pos>1 && pos<=cnt)
                    {
                        ptr2 = first2;
                        for (i = 1;i < pos;i++)
                        {
                            prev2 = ptr2;
                            ptr2 = ptr2->next2;
                        }
                        prev2->next2 = newnode2;
                        newnode2->next2 = ptr2;
                    }
                    else
                    {
                        printf("Product Not Found!!");
                    }
                }
                printf("\nProduct Added Successfully!!");
            }
            else
            {
                printf("\n Quantity can't exceed 10.");
                getch();
                return purchaseProduct();
            }
            printf("\nDo you want to add another product[Y/N]? ");
            scanf("%s",&ch);
            if (ch == 'Y'||ch == 'y')
            {
                system("cls");
                return purchaseProduct();
            }
            if (ch == 'N'||ch == 'n')
            {
                return main();
            }
        }

    }

    printf("\nProduct Not Found!!");
    getch();
    return purchaseProduct();

}

void checkStock(int id, int qty)
{
    if (first == NULL)
    {
        ISEMPTY;
    }
    else
    {
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            if (ptr->id == id)
            {
                if (ptr->qty<qty)
                {
                    printf("Not enough products available.");
                    getch();
                    return purchaseProduct();
                }
            }
        }

    }
}

void viewCart()
{
    system("cls");
    if (first == NULL)
    {
        ISEMPTY;
        printf("No Products Available in Cart. \n");
        getch();
        return main();
    }
    else
    {
        printf("=========================================================\n\n");
        printf("\t\t PRODUCTS IN CART\n\n");
        printf("=========================================================\n\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        {
            printf("%d\t", ptr2->id);
            for (ptr = first;ptr != NULL;ptr = ptr->next)
            {
                if (ptr->id==ptr2->id)
                {
                    printf("%s\t", ptr->name);
                    printf("%d\t", ptr2->qty);
                    printf("%d\t", ptr->price);
                }

            }
            printf("\n");
        }
        printf("=========================================================\n\n");
    }
    getch();
}

void generateBill()
{
    int ch;
    system("cls");
    viewCart();
    printf("\n1. Modify your cart.");
    printf("\n2. Proceed to Checkout.");
    printf("\n0. Back");
    printf("\nPlease enter your Choice: ");
    scanf("%d", &ch);
    switch (ch)
    {
        case 1: {
            modifyCart();
            break;
        }
        case 2: {
            checkout();
            break;
        }
        case 0:
        {
            return main();
        }
        default: {
            printf("Valid choice not entered!");
            getch();
            return generateBill();
        }
    }
}

void modifyCart()
{
    int id,qty,ch;
    system("cls");
    viewCart();
    printf("\nEnter the ID of the Product you wish to Modify: ");
    scanf("%d",&id);
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2) {
        if (ptr2->id == id)
        {
            printf("\n1. Delete Product.");
            printf("\n2. Modify the quantity.");
            printf("\n0. Back.");
            printf("\nPlease enter your Choice: ");
            scanf("%d", &ch);
            switch (ch) {
                case 1: {
                    deleteCart(id);
                    getch();
                    return generateBill();
                }
                case 2: {
                    printf("\nEnter the new quantity[1-10]: ");
                    scanf("%d", &qty);
                    if (qty <= 10) {
                        updateCart(id, qty);
                        getch();
                        return generateBill();
                    } else {
                        printf("Quantity can't exceed 10.");
                        getch();
                        return modifyCart();
                    }
                }
                case 0: {
                    return generateBill();
                }
                default: {
                    printf("Valid choice not entered!");
                    getch();
                    return generateBill();
                }
            }

        }

    }
    printf("\n Product Not Found!!");
    getch();
    return generateBill();

}

void deleteCart(int id)
{
    int pos,cnt=0,i;
    if (first2 == NULL)
    {
        ISEMPTY;
        printf("\nNo Products to delete\n");
    }
    else
    {
        pos = posCart(id);
        ptr2 = first2;
        if (pos == 1)
        {
            first2 = ptr2->next2;
            printf("\nProduct deleted from Cart.");
        }
        else
        {
            while (ptr2 != NULL)
            {
                ptr2 = ptr2->next2;
                cnt = cnt + 1;
            }
            if (pos > 0 && pos <= cnt)
            {
                ptr2 = first2;
                for (i = 1; i < pos; i++)
                {
                    prev2 = ptr2;
                    ptr2 = ptr2->next2;
                }
                prev2->next2 = ptr2->next2;
            }
            else
            {
                printf("\nProduct Not Found!!");
                getch();
                return generateBill();
            }
            free(ptr);
            printf("\nProduct deleted");
        }
    }
}

void updateCart(int id, int qty)
{
    if (first2 == NULL)
    {
        ISEMPTY;
    }
    else
    {
        for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2)
        {
            if (ptr2->id == id)
            {
                ptr2->qty = qty;
                return generateBill();

            }
        }
    }
}




void checkout()
{
    int total=0;
    char ch;
    viewCart();
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
    {
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            if (ptr->id==ptr2->id)
            {
                total+=(ptr2->qty)*(ptr->price);
            }
        }
        printf("\n");
    }
    printf("\n===================>> Total Bill Amount [Rs:  %d   ]\n\n",total);
    printf("\n Are you sure you want to checkout[Y/N]?");
    scanf("%s",&ch);
    if (ch == 'Y'||ch == 'y')
    {
        updateStock();
        clearCart();
        printf("\nPurchase Successful!!");
    }
    if (ch == 'N'||ch == 'n')
    {
        return generateBill();
    }
    getch();

}

void updateStock()
{
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
    {
        for (ptr = first; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->id == ptr2->id)
            {
                ptr->qty=(ptr->qty)-ptr2->qty;
            }
        }
    }
}

void clearCart()
{
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
    {
        deleteCart(ptr2->id);
    }
}
