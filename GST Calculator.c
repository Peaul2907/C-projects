#include <stdio.h>

int main() {
    int choice;
    float price, gstRate, gstAmount, finalPrice, basePrice;

    do {
        printf("\nGST Calculator\n");
        printf("\n_________________________________\n\n");
        printf("1. GST Exclusive (Add GST)\n");
        printf("2. GST Inclusive (Extract GST)\n");
        printf("3. Exit\n");
        printf("Choose option (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter base price: ₹");
                scanf("%f", &price);
                printf("Enter GST rate (%%): ");
                scanf("%f", &gstRate);
                gstAmount = (price * gstRate) / 100;
                finalPrice = price + gstAmount;
                printf("GST: ₹%.2f\nTotal: ₹%.2f\n", gstAmount, finalPrice);
                break;

            case 2:
                printf("Enter total price (with GST): ₹");
                scanf("%f", &price);
                printf("Enter GST rate (%%): ");
                scanf("%f", &gstRate);
                basePrice = (price * 100) / (100 + gstRate);
                gstAmount = price - basePrice;
                printf("Base Price: ₹%.2f\nGST: ₹%.2f\n", basePrice, gstAmount);
                break;

            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid option. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}