# Budget Planner

## 1. Projekto aprašymas

Budget Planner – tai konsolinė C++ programa, skirta asmeninių finansų valdymui. 
Vartotojas gali registruoti pajamas ir išlaidas, priskirti jas kategorijoms, 
peržiūrėti visus įrašus, apskaičiuoti balansą bei eksportuoti duomenis į CSV failą.

Šis projektas yra ankstyvos stadijos (P1) prototipas, skirtas pagrindinės 
sistemos logikos demonstravimui.

---

## 2. Funkcionalumas

Šiuo metu įgyvendintos funkcijos:

- Naujos transakcijos pridėjimas
- Visų transakcijų peržiūra
- Balanso skaičiavimas
- Duomenų išsaugojimas į CSV failą
- Duomenų užkrovimas iš CSV failo
- Ataskaitos eksportas į CSV failą

---

## 3. Projekto struktūra

### 3.1. Vartotojo sąsaja (UI)
- Konsolinis meniu
- Vartotojo įvedimų apdorojimas
- Rezultatų atvaizdavimas

### 3.2. Duomenų modelis
- `Transaction` struktūra:
  - data (date)
  - kategorija (category)
  - aprašymas (description)
  - suma (amount)

- Visos transakcijos saugomos `std::vector<Transaction>` konteineryje

### 3.3. Failų valdymas
- Duomenys saugomi CSV faile (`transactions.csv`)
- Pagrindinės funkcijos:
  - `loadTransactions()` – duomenų nuskaitymas
  - `saveTransactions()` – duomenų išsaugojimas

### 3.4. Programos logika
- `addTransaction()` – naujos transakcijos pridėjimas
- `listTransactions()` – visų transakcijų rodymas
- `showBalance()` – balanso skaičiavimas
- `exportReport()` – ataskaitos eksportas

---

## 4. Duomenų tėkmė

1. Vartotojas įveda duomenis per meniu
2. Sukuriamas `Transaction` objektas
3. Objektas pridedamas į `vector`
4. Duomenys:
   - rodomi ekrane
   - saugomi faile
5. Paleidus programą iš naujo – duomenys užkraunami iš failo

---

## 5. Use-case

Vartotojas gali:

- pridėti transakciją
- peržiūrėti visas transakcijas
- peržiūrėti balansą
- eksportuoti ataskaitą
- išeiti iš programos išsaugant duomenis

---

## 6. Activity (veikimo eiga)

1. Programa paleidžiama
2. Užkraunami duomenys iš failo
3. Rodomas pagrindinis meniu
4. Vartotojas pasirenka veiksmą
5. Atliekamas pasirinktas veiksmas
6. Grįžtama į meniu
7. Išeinant – duomenys išsaugomi

---

## 7. Naudojamos technologijos

- Programavimo kalba: C++
- Standartinės bibliotekos:
  - iostream
  - vector
  - fstream
  - ctime
  - iomanip
  - limits
- Duomenų saugojimas: CSV failai
- Aplinka: Visual Studio Code
- Versijavimas: Git

---

## 8. Kompiliavimas ir paleidimas:

```bash
g++ planner.cpp -o planner
.\planner.exe
```

## 9. Proof of Concept

Kol kas įgyvendintas tik minimalus prototipas, leidžiantis:

- įvesti finansinius duomenis
- juos saugoti faile
- peržiūrėti įrašus
- apskaičiuoti balansą

Tolimesniuose etapuose planuojama plėsti funkcionalumą, struktūrą ir testavimą.
