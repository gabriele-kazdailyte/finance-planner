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
```

## Diagramos

### Architektūros schema
<img width="341" height="263" alt="image" src="https://github.com/user-attachments/assets/6ca92634-fedd-439c-8b06-14ae2b1119b0" />


---

### Use-case diagrama
<img width="419" height="235" alt="image" src="https://github.com/user-attachments/assets/cf93b973-0caf-4cf8-a175-5a3ff7ce9f86" />


---

### Activity diagrama
<img width="839" height="319" alt="image" src="https://github.com/user-attachments/assets/d903b1df-9a9e-4105-9294-e1348cf5d1f8" />


---

### Klasių diagrama
<img width="688" height="447" alt="image" src="https://github.com/user-attachments/assets/2c0f545f-8e48-4dad-a49f-0ec8ff19a2d9" />


---

## 9. Kompiliavimas ir paleidimas:

```bash
g++ main.cpp BudgetManager.cpp FileManager.cpp -o planner
.\planner.exe
```

## 10. Proof of Concept

Įgyvendintas biudžeto planavimo programėlės prototipas:

- įvesti pajamas ir išlaidas;
- saugoti duomenis faile;
- užkrauti duomenis iš failo;
- peržiūrėti finansinius įrašus;
- apskaičiuoti balansą;
- apskaičiuoti bendras pajamas ir išlaidas;
- eksportuoti ataskaitą;
- išvalyti visus įrašus.

## UI

Programą nusprendėme palikti terminalo lygyje.

Pakeitėme dizainą, kad vartotojas matytų estetiškesnį terminalo vaizdą ir būtų patogiau naudotis programos funkcijomis.

## Darbų pasiskirstymas ir atlikimo trukmė

Darbus dalinomės po lygiai:

Gabrielė Každailytė: 50%
Rugilė Kazakevičiūtė: 50%

Trukmė etapuose:
P1: ~5h
P2: ~6h
P3: ~1h

Bendra darbo atlikimo trukmė: ~12h
