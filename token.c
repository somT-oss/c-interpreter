typedef struct {
    int first_byte;
    int second_byte;
    int third_byte;
    int fourth_byte;
} IPaddressV1;

struct IPAddressV2 {
    int first_byte;
    int second_byte;
    int third_byte;
    int fourth_byte;
};

IPaddressV1 ip = {
    10,
    10,
    10,
    10,
};

struct IPAddressV2 new_ip = {
    .first_byte = 10,
    .second_byte = 10,
    .third_byte = 10,
    .fourth_byte = 10,
};