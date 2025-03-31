#include "Pump.h"

// Constructeur de la classe PumpClass
PumpClass::PumpClass(int pin) {
  pump.pin = pin;               // Initialisation du pin pour contrôler la pompe
  pump.currentState = false;     // La pompe commence éteinte
  pump.targetDose = 0;           // Pas de dose initiale
  pump.startMillis = 0;          // Pas de départ
  pump.activeDuration = 0;       // Pas de durée initiale
  lastDoseTime = 0;              // Initialisation de la dernière activation
}

// Fonction d'initialisation de la pompe
void PumpClass::begin() {
  pinMode(pump.pin, OUTPUT);     // Définit le pin comme sortie
  digitalWrite(pump.pin, LOW);   // Assure que la pompe est éteinte au démarrage
}

// Fonction pour configurer et démarrer la pompe avec une dose spécifique
void PumpClass::dosePump(int dose) {
  pump.targetDose = dose;                      // Définir la dose cible
  pump.activeDuration = (dose / 100.0) * 5000; // Calcul de la durée en ms (5 sec pour 100mL)
  pump.startMillis = millis();                 // Enregistrer l'heure de début
  pump.currentState = true;                    // Activer la pompe
  digitalWrite(pump.pin, HIGH);                // Allumer la pompe
  lastDoseTime = millis();                     // Mémoriser l'heure de la dernière activation
}

// Fonction pour gérer la mise à jour de la pompe (fonction non-bloquante)
void PumpClass::managePump(uint16_t* pumpValue) {
  if (pump.currentState) {
    // Si la durée d'activation est écoulée, on éteint la pompe
    if (millis() - pump.startMillis >= pump.activeDuration) {
      pump.currentState = false;   // Arrêter la pompe
      digitalWrite(pump.pin, LOW); // Éteindre la pompe
      *pumpValue = 0; // Mettre à jour le registre
    }
  }
}

// Fonction pour obtenir le flowrate en mL/s
float PumpClass::getFlowRate() {
  // Le flowrate en mL/s est calculé en divisant la dose par la durée d'activation en secondes
  if (pump.activeDuration > 0) {
    return (float)pump.targetDose / (float)pump.activeDuration * 1000;  // convertit en mL/s
  }
  return 0.0;  // Si aucune dose n'est définie, le flowrate est 0
}

// Fonction pour obtenir la quantité restante à servir
int PumpClass::getRemainingDose() {
  // La quantité restante est la dose cible moins la quantité déjà servie
  if (pump.currentState) {
    unsigned long elapsed = millis() - pump.startMillis;
    float quantityServed = (elapsed / (float)pump.activeDuration) * pump.targetDose;
    return pump.targetDose - quantityServed;
  } else {
    return pump.targetDose; // Si la pompe n'est pas activée, toute la dose reste à servir
  }
}

// Fonction pour arrêter immédiatement la pompe
void PumpClass::stop() {
  pump.currentState = false;                          // Désactiver la pompe
  digitalWrite(pump.pin, LOW);                         // Éteindre la pompe immédiatement
  pump.targetDose = 0;                                 // Réinitialiser la dose cible
  pump.activeDuration = 0;                             // Réinitialiser la durée d'activation
  pump.startMillis = 0;                                // Réinitialiser le moment de démarrage
}

// Fonction pour vérifier si la pompe est active (en fonctionnement)
bool PumpClass::isActive() {
  return pump.currentState;  // Retourner true si la pompe est activée, sinon false
}