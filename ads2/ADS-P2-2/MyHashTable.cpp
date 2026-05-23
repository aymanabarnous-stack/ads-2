#include "MyHashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

// ─────────────────────────────────────────────────────────────────────────────
// DJB2 Hashfunktion (unveränderter Original-Code)
// ─────────────────────────────────────────────────────────────────────────────
unsigned int MyHashTable::hash(const std::string& key) const {
    unsigned int h = 5381;
    for (char c : key) {
        h = ((h << 5) + h) + c; // h * 33 + c
    }
    return h % table.size();
}

// ─────────────────────────────────────────────────────────────────────────────
// rehash
//  - Neue Größe: nächste Primzahl > 2 * aktuelle Größe
//  - Kollisionszähler wird zurückgesetzt
//  - Alle alten Einträge in TABELLENREIHENFOLGE (Index 0..n-1) neu einfügen
// ─────────────────────────────────────────────────────────────────────────────
void MyHashTable::rehash() {
    // 1. Alte Tabelle sichern
    std::vector<Entry> oldTable = table;

    // 2. Neue Tabellengröße: nächste Primzahl > 2 * alte Größe
    int newSize = getNextPrime(2 * (int)oldTable.size());

    // 3. Neue leere Tabelle anlegen, Zähler zurücksetzen
    table.assign(newSize, Entry{});
    mNumElements = 0;
    collisionCount = 0;   // ← Kollisionszähler nach Rehash zurücksetzen!

    // 4. Alle alten Einträge in Tabellenreihenfolge (0..n-1) neu einfügen
    //    insert() nutzt jetzt die neue (größere) Tabelle
    for (const Entry& e : oldTable) {
        if (e.occupied) {
            insert(e.acc);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// insert
//  1. Element einfügen (Sondieren)
//  2. DANACH Belegungsfaktor prüfen: falls mNumElements / size > 0.6 → rehash
//
// Kollisionsstrategien (mHashMethod):
//   1 = Lineares Sondieren:       hi = (x + i)         % M
//   2 = Quadratisches Sondieren:  hi = (x + i²)         % M
//   3 = Doppeltes Hashing:        hi = (x + i*(R-x%R))  % M
//       R = nächstkleinere Primzahl < M
// ─────────────────────────────────────────────────────────────────────────────
void MyHashTable::insert(const Account& acc) {

    // ── VOR dem Einfügen: Belegungsfaktor prüfen ─────────────────────────────
    // Rehash wenn mNumElements / tableSize STRIKT GRÖSSER als 0.6
    if ((double)mNumElements / (double)table.size() > mMaxLoadFactor) {
        rehash();
    }

    // ── Element einfügen ─────────────────────────────────────────────────────
    int M = (int)table.size();
    int x = (int)hash(acc.website);
    int R = getLastPrime(M);   // für Doppeltes Hashing

    for (int i = 0; i < M; i++) {
        int idx = 0;

        if (mHashMethod == 1) {
            // Lineares Sondieren: h_i(x) = (x + i) % M
            idx = (x + i) % M;
        }
        else if (mHashMethod == 2) {
            // Quadratisches Sondieren: h_i(x) = (x + i²) % M
            idx = (int)((x + (long long)i * i) % M);
        }
        else {
            // Doppeltes Hashing: h_i(x) = (x + i * (R - x%R)) % M
            idx = (int)((x + (long long)i * (R - x % R)) % M);
        }

        if (!table[idx].occupied) {
            // Freier Slot gefunden → einfügen
            table[idx].acc      = acc;
            table[idx].occupied = true;
            mNumElements++;
            return;
        }

        // Slot belegt → Kollision zählen
        collisionCount++;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// login  –  Website suchen, Username + PasswordHash prüfen
// ─────────────────────────────────────────────────────────────────────────────
bool MyHashTable::login(const std::string& website,
                        const std::string& username,
                        const std::string& passwordHash) const {

    int M = (int)table.size();
    int x = (int)hash(website);
    int R = getLastPrime(M);

    for (int i = 0; i < M; i++) {
        int idx = 0;

        if (mHashMethod == 1) {
            idx = (x + i) % M;
        } else if (mHashMethod == 2) {
            idx = (int)((x + (long long)i * i) % M);
        } else {
            idx = (int)((x + (long long)i * (R - x % R)) % M);
        }

        if (!table[idx].occupied) {
            return false;   // Leerer Slot → Eintrag nicht vorhanden
        }

        if (table[idx].acc.website      == website  &&
            table[idx].acc.username     == username &&
            table[idx].acc.passwordHash == passwordHash) {
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// listEntries  –  Alle belegten Slots ausgeben
// ─────────────────────────────────────────────────────────────────────────────
void MyHashTable::listEntries() const {
    std::cout << "\n--- Hash-Tabelle (Groesse: " << table.size()
              << ", Eintraege: " << mNumElements << ") ---\n";

    for (int i = 0; i < (int)table.size(); i++) {
        if (table[i].occupied) {
            std::cout << "[" << i << "] "
                      << table[i].acc.website << " | "
                      << table[i].acc.username << "\n";
        }
    }
    std::cout << "Kollisionen: " << collisionCount << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// getNextPrime / getLastPrime  –  Original-Code unveraendert
// ─────────────────────────────────────────────────────────────────────────────
int MyHashTable::getNextPrime(int x) const {
    x = x + 1;
    bool found = true;
    while (true) {
        found = true;
        for (int i = 2; i <= sqrt(x); i++) {
            if (x % i == 0) { found = false; break; }
        }
        if (found) return x;
        x += 1;
    }
}

int MyHashTable::getLastPrime(int x) const {
    x = x - 1;
    bool found = true;
    while (true) {
        found = true;
        for (int i = 2; i <= sqrt(x); i++) {
            if (x % i == 0) { found = false; break; }
        }
        if (found) return x;
        x -= 1;
    }
}