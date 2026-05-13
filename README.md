# Budget Planner

## 1. Projekto aprašymas

Budget Planner – tai C++ programa, skirta asmeninių finansų valdymui. 
Vartotojas gali registruoti pajamas ir išlaidas, priskirti jas kategorijoms, 
peržiūrėti visus įrašus, apskaičiuoti balansą bei eksportuoti duomenis į CSV failą.

Šis projektas yra ankstyvos stadijos (P1) prototipas, skirtas pagrindinės 
sistemos logikos demonstravimui.

---

## 2. Funkcionalumas

Šiuo metu įgyvendintos funkcijos:

- Pajamų pridėjimas
- Išlaidų pridėjimas
- Visų transakcijų peržiūra
- Balanso skaičiavimas
- Pajamų sumos skaičiavimas
- Išlaidų sumos skaičiavimas
- Finansinės suvestinės rodymas
- Duomenų išsaugojimas į CSV failą
- Duomenų užkrovimas iš CSV failo
- Ataskaitos eksportas į CSV failą
- Visų transakcijų išvalymas

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

Failų valdymo logika realizuota `FileManager` klasėje.

Ši klasė atsakinga už:

- transakcijų nuskaitymą iš CSV failo;
- transakcijų išsaugojimą į CSV failą;
- ataskaitos eksportavimą į CSV failą.


### 3.4. Finansų valdymo logika

Finansų valdymo logika realizuota `BudgetManager` klasėje.

Ši klasė atsakinga už:

- transakcijų saugojimą;
- naujų transakcijų pridėjimą;
- balanso skaičiavimą;
- pajamų skaičiavimą;
- išlaidų skaičiavimą;
- transakcijų išvalymą;
- duomenų pateikimą kitoms programos dalims.

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

- pridėti pajamas;
- pridėti išlaidas;
- peržiūrėti visas transakcijas;
- peržiūrėti balansą;
- peržiūrėti finansinę suvestinę;
- eksportuoti ataskaitą;
- išvalyti visas transakcijas;
- išeiti iš programos išsaugant duomenis.

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
  - sstream
  - ctime
  - iomanip
  - limits
  - string
- Duomenų saugojimas: CSV failai
- Aplinka: Visual Studio Code
- Versijavimas: Git
- Diagramų kūrimas: PlantUML
- 
---

## 8. Projekto struktūra (failai)

```txt
finance-planner/
├── main.cpp
├── Transaction.h
├── BudgetManager.h
├── BudgetManager.cpp
├── FileManager.h
├── FileManager.cpp
├── README.md
├── transactions.csv
└── report_YYYY-MM-DD.csv

## Diagramos

### Architektūros schema
<img width="495" height="527" alt="image" src="https://github.com/user-attachments/assets/83ee3143-6eb8-4cd6-924b-7254b957d18c" />

---

### Use-case diagrama
<img width="348" height="394" alt="image" src="https://github.com/user-attachments/assets/9053f2db-9d4a-4e94-a564-76914dd3a7c9" />

---

### Activity diagrama
<img width="1443" height="667" alt="image" src="https://github.com/user-attachments/assets/bebf34f8-4d05-4f68-8e7a-cd61dd1c28d9" />

---

### Klasių diagrama
<img width="322" height="356" alt="image" src="https://github.com/user-attachments/assets/3d88060e-b5ba-4910-8152-543f9dd28e7f" />

---

## 9. Kompiliavimas ir paleidimas:

```bash
g++ planner.cpp -o planner
.\planner.exe
```

## 10. Proof of Concept

Kol kas įgyvendintas tik minimalus prototipas, leidžiantis:

- įvesti finansinius duomenis
- juos saugoti faile
- peržiūrėti įrašus
- apskaičiuoti balansą

Tolimesniuose etapuose planuojama plėsti funkcionalumą, struktūrą ir testavimą.
