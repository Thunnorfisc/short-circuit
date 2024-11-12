#pragma once

void Credits_Init(void);
void Credits_Update(void);
void Credits_Exit(void);

// Define maximum number of names per category
#define MAX_NAMES_PER_CATEGORY  10

// Structure to hold a credit category
typedef struct {
    const char* category;
    const char* names[MAX_NAMES_PER_CATEGORY];
    int nameCount;
} CreditCategory;

void PrintCredit(const CreditCategory* category, float windowWidth, float* currentY);