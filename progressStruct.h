#ifndef PROGRESS_STRUCT_H
#define PROGRESS_STRUCT_H

typedef struct {
    int d1, d2, d3, d4;
    int c1, c2, c3, c4;
    int j1, j2, j3, j4;

    int epsteinDone;
    int clintonDone;
    int jacksonDone;

    int e_currentDialogue, e_inChoice;
    int c_currentDialogue, c_inChoice;
    int j_currentDialogue, j_inChoice;

    char saveName[50];
} Progress;

#endif
