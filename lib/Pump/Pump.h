#ifndef Pump_h
#define Pump_h

#include <Arduino.h>

// Définition de la structure pour la pompe
typedef struct {
  bool currentState;             // État actuel de la pompe (true = activée, false = désactivée)
  int targetDose;                // Dose cible à délivrer en millilitres (mL)
  unsigned long startMillis;     // Moment où la pompe est activée
  unsigned long activeDuration;  // Durée d'activation de la pompe en millisecondes
  int pin;                       // Pin de la pompe pour contrôler son état
} Pump;

class PumpClass {
  public:
    // Constructeur
    PumpClass(int pin);           // Le constructeur accepte un pin pour la pompe

    // Fonction d'initialisation
    void begin();

    // Fonction pour démarrer la pompe avec une dose spécifique
    void dosePump(int dose);

    // Fonction pour gérer la mise à jour de la pompe (non-bloquante)
    void managePump(uint16_t* pumpValue);

    // Fonction pour obtenir le flowrate en mL/s
    float getFlowRate();

    // Fonction pour obtenir la quantité restante à servir
    int getRemainingDose();

    // Fonction pour arrêter immédiatement la pompe
    void stop();

    // Fonction pour vérifier si la pompe est active (en fonctionnement)
    bool isActive();

  private:
    Pump pump;  // Structure interne pour la pompe
    unsigned long lastDoseTime; // Moment de la dernière dose activée
};

#endif