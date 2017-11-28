//
// Created by vincent on 25.11.17.
//

#ifndef AUFGABE5_KOMPLEX_H
#define AUFGABE5_KOMPLEX_H


class komplex {
    public:
        // Konstruktor
        komplex(double re, double im);

        // Destruktor
        ~komplex();

        // Methoden
        double getRe(); // Holt Realteil
        double getIm(); // Holt Imaginärteil
        void setRe(double); // Setzt den Realteil
        void setIm(double); // Setzt den Imaginärteil

        void add(komplex * zahl); // Addiert eine andere komplexe Zahl zu dieser Zahl
        void mult(komplex * zahl); // Multipliziert eine andere komplexe Zahl zu dieser Zahl
        int norm(); // Berechnet den Abstand des Punktes vom Ursprung

        // Zusatz-Methoden
        void print(); // Druckt die komplexe Zahl
        void printNorm(); // Druckt die Norm der komplexen Zahl

    private:
        double re;
        double im;
};


#endif //AUFGABE5_KOMPLEX_H
