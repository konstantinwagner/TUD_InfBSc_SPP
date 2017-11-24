#include <stdlib.h>

typedef struct {
    char *street;
    int number;
    int post_code;
    char *city;
} address;

address *
create_address(char *street,
               int number,
               int post_code,
               char *city) {
    address *new_address = malloc(sizeof(address));
    new_address->street = street;
    new_address->number = number;
    new_address->post_code = post_code;
    new_address->city = city;
    return new_address;
}

address *
duplicate_address(address orig) {
    address *duplicated_referenced_address = malloc(sizeof(address));
    return duplicated_referenced_address;
}

int main() {
    address *a1 = create_address("Mornewegstr.", 30, 64293, "Darmstadt");
    address *a2 = duplicate_address(*a1);
    free(a1);
    free(a2);
}
