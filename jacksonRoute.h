#ifndef JACKSON_ROUTE_H
#define JACKSON_ROUTE_H

#include <stdio.h>
#include "progressStruct.h"

#include "asciiSpeak.h"

void saveGame(int slot, Progress *p);

// ================= DIALOGUE 1 =================
int jacksonD1(int ch1, Progress *p, int slot) {
    const char *txt = "jacksonDialogue.txt";

    int exitCh1 = 0;

    // Only print intro/options if starting fresh
    if (p->inDialogueChoice == 0) {
        speak(txt, "intro1S", "intro1E");
        speak(txt, "1.os", "1.oe");
    }

    while (exitCh1 == 0) {

        // resume previous input if exists
        if (p->inDialogueChoice != 0) {
            ch1 = p->inDialogueChoice;
        } else {
            printf(">>> ");
            scanf("%d", &ch1);
        }

        // SAVE MID-DIALOGUE STATE
        p->currentDialogue = 1;
        p->inDialogueChoice = ch1;
        saveGame(slot, p);

        switch (ch1) {
            case 1:
                speak(txt, "1.1s", "1.1e");
                p->j1 = 1;
                exitCh1 = 1;
                break;

            case 2:
                speak(txt, "1.2s", "1.2e");
                p->j1 = 2;
                exitCh1 = 1;
                break;

            case 3:
                speak(txt, "1.3s", "1.3e");
                p->j1 = 3;
                exitCh1 = 1;
                break;

            case 4:
                speak(txt, "1.4s", "1.4e");
                p->inDialogueChoice = 0;
                saveGame(slot, p);
                return 1;

            default:
                speak(txt, "errorS", "errorEnd");
                p->inDialogueChoice = 0; // reset invalid input
                break;
        }
    }

    // CLEAR MID STATE AFTER COMPLETION
    p->inDialogueChoice = 0;
    saveGame(slot, p);

    return 0;
}

// ================= DIALOGUE 2 =================
int jacksonD2(int ch2, Progress *p, int slot) {
    const char *txt = "jacksonDialogue.txt";

    int exitCh2 = 0;

    if (p->inDialogueChoice == 0) {
        speak(txt, "intro2S", "intro2E");
        speak(txt, "2.os", "2.oe");
    }

    while (exitCh2 == 0) {

        if (p->inDialogueChoice != 0) {
            ch2 = p->inDialogueChoice;
        } else {
            printf(">>> ");
            scanf("%d", &ch2);
        }

        p->currentDialogue = 2;
        p->inDialogueChoice = ch2;
        saveGame(slot, p);

        switch (ch2) {
            case 1:
                speak(txt, "2.1s", "2.1e");
                p->j2 = 1;
                exitCh2 = 1;
                break;

            case 2:
                speak(txt, "2.2s", "2.2e");
                p->j2 = 2;
                exitCh2 = 1;
                break;

            case 3:
                speak(txt, "2.3s", "2.3e");
                p->j2 = 3;
                exitCh2 = 1;
                break;

            case 4:
                speak(txt, "2.4s", "2.4e");
                p->inDialogueChoice = 0;
                saveGame(slot, p);
                return 1;

            default:
                speak(txt, "errorS", "errorEnd");
                p->inDialogueChoice = 0;
                break;
        }
    }

    p->inDialogueChoice = 0;
    saveGame(slot, p);

    return 0;
}

// ================= DIALOGUE 3 =================
int jacksonD3(int ch3, Progress *p, int slot) {
    const char *txt = "jacksonDialogue.txt";

    int exitCh3 = 0;

    if (p->inDialogueChoice == 0) {
        speak(txt, "intro3S", "intro3E");
        speak(txt, "3.os", "3.oe");
    }

    while (exitCh3 == 0) {

        if (p->inDialogueChoice != 0) {
            ch3 = p->inDialogueChoice;
        } else {
            printf(">>> ");
            scanf("%d", &ch3);
        }

        p->currentDialogue = 3;
        p->inDialogueChoice = ch3;
        saveGame(slot, p);

        switch (ch3) {
            case 1:
                speak(txt, "3.1s", "3.1e");
                p->j3 = 1;
                exitCh3 = 1;
                break;

            case 2:
                speak(txt, "3.2s", "3.2e");
                p->j3 = 2;
                exitCh3 = 1;
                break;

            case 3:
                speak(txt, "3.3s", "3.3e");
                p->j3 = 3;
                exitCh3 = 1;
                break;

            case 4:
                speak(txt, "3.4s", "3.4e");
                p->inDialogueChoice = 0;
                saveGame(slot, p);;
                return 1;

            default:
                speak(txt, "errorS", "errorEnd");
                p->inDialogueChoice = 0;
                break;
        }
    }

    p->inDialogueChoice = 0;
    saveGame(slot, p);

    return 0;
}

// ================= DIALOGUE 4 =================
int jacksonD4(int ch4, Progress *p, int slot) {
    const char *txt = "jacksonDialogue.txt";

    if (p->j4 != 0) {
    if (p->j4 == 1) speak(txt, "endObliv.s", "endObliv.e");
    if (p->j4 == 2) speak(txt, "endGood.s", "endGood.e");
    if (p->j4 == 3) speak(txt, "endEvil.s", "endEvil.e");
    if (p->j4 == 4) speak(txt, "endNeutral.s", "endNeutral.e");
    return 0;
    }

    int exitCh4 = 0;

    if (p->inDialogueChoice == 0) {
        speak(txt, "intro4S", "intro4E");
        speak(txt, "4.os", "4.oe");
    }

    while (exitCh4 == 0) {

        if (p->inDialogueChoice != 0) {
            ch4 = p->inDialogueChoice;
        } else {
            printf(">>> ");
            scanf("%d", &ch4);
        }

        p->currentDialogue = 4;
        p->inDialogueChoice = ch4;
        saveGame(slot, p);

        switch (ch4) {
            case 1:
                speak(txt, "4.1s", "4.1e");
                speak(txt, "endObliv.s", "endObliv.e");
                p->j4 = 1;
                exitCh4 = 1;
                break;

            case 2:
                speak(txt, "4.2s", "4.2e");
                speak(txt, "endGood.s", "endGood.e");
                p->j4 = 2;
                exitCh4 = 1;
                break;

            case 3:
                speak(txt, "4.3s", "4.3e");
                speak(txt, "endEvil.s", "endEvil.e");
                p->j4 = 3;
                exitCh4 = 1;
                break;

            case 4:
                speak(txt, "4.4s", "4.4e");
                p->inDialogueChoice = 0;
                saveGame(slot, p);
                return 1;

            default:
                speak(txt, "errorS", "errorEnd");
                p->inDialogueChoice = 0;
                break;
        }
    }

    p->inDialogueChoice = 0;
    saveGame(slot, p);

    return 0;
}

#endif
