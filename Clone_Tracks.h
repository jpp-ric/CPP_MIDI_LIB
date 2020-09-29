//====================== Reconnaissance d'accord =======================================

  #define NOTE_C  0
  #define NOTE_Cd 1
  #define NOTE_D  2
  #define NOTE_Dd 3
  #define NOTE_E  4
  #define NOTE_F  5
  #define NOTE_Fd 6
  #define NOTE_G  7 
  // ...
  #define NOTE_B  11

  #define NB_NOTES 12

  #define PAS_DE_NOTE NB_NOTES


  // En entrée : char tabNotesAccord = Array(NOTE_C, NOTE_E, NOTE_G, PAS_DE_NOTE, PAS_DE_NOTE)

  //=======================

  char tabAccords[NB_NOTES][NB_NOTES][PAS_DE_NOTE+1][PAS_DE_NOTE+1][PAS_DE_NOTE+1];

  tabAccords[NOTE_C][NOTE_E][NOTE_G][PAS_DE_NOTE][PAS_DE_NOTE] = "C";
  tabAccords[NOTE_C][NOTE_E][NOTE_G][NOTE_B][PAS_DE_NOTE] = "CM7";
  tabAccords[NOTE_C][NOTE_E][NOTE_G][NOTE_Bb][PAS_DE_NOTE] = "C7";
  tabAccords[NOTE_C][NOTE_D][NOTE_E][NOTE_G][NOTE_Bb] = "C9";
 //...


// Recherche de l'accord dans tabAccords

char* nomAccord = tabAccords[ tabNotesAccord[0] ] 
                            [ tabNotesAccord[1] ] 
                            [ tabNotesAccord[2] ]
                            [ tabNotesAccord[3] ]
                            [ tabNotesAccord[4] ];


*/ 



   