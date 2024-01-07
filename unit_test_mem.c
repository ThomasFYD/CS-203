//
// Created by Thomas Fang on 11/13/23.
//

#include <assert.h>
#include "mem.h"

struct MemoryLocation test_memory[ADDRESS_SIZE];

// Test initialization of memory
void test_initialize_memory() {
    initialize_memory();
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        assert(test_memory[i].data == 0);
        assert(test_memory[i].operation == data); // Assuming 'data' is the default operation
    }
}

struct Test_Label {
    char name[256];
    int address;
};

struct Test_Label test_label_table[256];
int test_label_count = 0;

// Test adding a label
void test_add_label() {
    // Clearing existing labels
    test_label_count = 0;
    add_label("test_label", 100);
    assert(test_label_count == 1);
    assert(strcmp(test_label_table[0].name, "test_label") == 0);
    assert(test_label_table[0].address == 100);
}

// Test resolving a label
void test_resolve_label_cpu() {
    // Assuming label "test_label" is already added
    int address = resolve_label("test_label");
    assert(address == 100);
}

// Main function to run all tests
int main() {
    test_initialize_memory();
    test_add_label();
    test_resolve_label_cpu();
    return 0;
}
