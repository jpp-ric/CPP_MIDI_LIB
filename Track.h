#ifndef Track_h
#define Track_h

#include <IDisplayer.h>

class Track
{
public:
    //--- Déclaration des Méthodes public ---

    Track(); //Constructeur
    ~Track(); //Destructeur

    int telleMethodeDeLaClasseTrack();
    void setDisplayer(IDisplayer* displayer);

    
    //--- Déclaration des membres public --- (à éviter)
    int telleMembreDeLaClasseTrack;
 
private:

    //--- Déclaration des Méthodes private ---
    IDisplayer* getDisplayer();

    //--- Déclaration des membres private ---
    IDisplayer* displayer = 0;

};

#endif